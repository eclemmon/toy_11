/*
------------------------
TOY 11.2.1 PLAYER 1 FILE
------------------------
*/

/* Includes ------------------------------------------------------------------*/
#include <Arduino.h>
#include <WiFiS3.h>
#include "secrets.h" 
#include <OSCMessage.h>
#include <vl53l4cd_class.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>
#include <Adafruit_APDS9960.h>

/* Globals ------------------------------------------------------------------*/

// Communication Globals
#define DEV_I2C Wire1
#define SerialPort Serial
#define TCAADDR 0x70

// WIFI Globals
char ssid[] = SECRET_SSID;          // your network SSID (name)
char pass[] = SECRET_PASS;          // your network password (use for WPA, or use as key for WEP)
// char oscAddress[10] = PLAYER_ADDR;  // Allocated some memory and add your player osc root to it.
WiFiUDP Udp;                        // WiFi UDP Object
IPAddress IP;                       // Construct IP Object
// IPAddress IP(192, 168, 0, 107);     
int status = WL_NO_MODULE;

// Adafruit MPU6050 Accelerometer
Adafruit_MPU6050 mpu;
int mpu_TCA_ADDR = MPU6050_TCA_ADDR;
sensors_event_t a, rot, temp;

// Accelerometer Storage vars
float Ax;
float Ay;
float Az;
float Gx;
float Gy;
float Gz;

float rollA = 0;
float pitchA = 0;
float rollG = 0;
float pitchG = 0;
float yawG = 0;

// Lowpass filter Variables
float AxRaw;
float AyRaw;
float AzRaw;
float rollRaw;
float pitchRaw;
float pitchComp;
float rollComp;
float yawComp;

// MPU Accelerometer Callibration
float xMax = X_MAX;
float xMin = X_MIN;
float yMax = Y_MAX;
float yMin = Y_MIN;
float zMax = Z_MAX;
float zMin = Z_MIN;

float xOffset = (xMax + xMin)/2;
float yOffset = (yMax + yMin)/2;
float zOffset = (zMax + zMin)/2;

float xScale = 2/(xMax - xMin);
float yScale = 2/(yMax - yMin);
float zScale = 2/(zMax - zMin);

float deltaRoll = 0;
float deltaPitch = 0;
float deltaYaw = 0;

// MPU Gyroscope Callibration
float gXOffset;
float gYOffset;
float gZOffset;

// MPU Gyroscope Filter Info
int tStart = millis();

// APDS9960 Light Sensor
Adafruit_APDS9960 apds;
int apds_TCA_ADDR = APDS_TCA_ADDR;
uint16_t r, g, b, c;

// VL53L4CD Proximity Sensor
VL53L4CD sensor_vl53l4cd_sat_1(&DEV_I2C, 0);
int tof1_TCA_ADDR = TOF1_TCA_ADDR;
float tof1Alpha = 0.9;
int tof1FilteredValue = 0;
VL53L4CD sensor_vl53l4cd_sat_2(&DEV_I2C, 0);
int tof2_TCA_ADDR = TOF2_TCA_ADDR;
float tof2Alpha = 0.9;
int tof2FilteredValue = 0;
VL53L4CD_Result_t results1, results2;
uint8_t status1, status2;

/* Setup ------------------------------------------------------------------*/

void setup() {
  // put your setup code here, to run once:
  DEV_I2C.begin();
  Serial.begin(115200);
  DEV_I2C.setClock(100000);

  while (!Serial) {
    delay(20); // wait for serial port to connect. Needed for native USB port only
  }
  IP.fromString(DESTINATION_IP);                     // IP Address of data destination

  // Start up WiFi
  Udp = bootWiFi(status, SECRET_SSID, SECRET_PASS, Udp, LOCALPORT);
  // OSC Messages
  OSCMessage error_msg("/player1/error/");

  // Select the MPU 6050 and Boot
  tcaselect(mpu_TCA_ADDR);
  delay(10);
  if (!mpu.begin(MPU6050_I2CADDR_DEFAULT, &DEV_I2C)) {
    error_msg.add("Failed to find MPU6050 chip");
    Udp.beginPacket(IP, LOCALPORT);
    error_msg.send(Udp);
    Udp.endPacket();
    error_msg.empty();
    while (1) {
      delay(10);
    }
  } else {
    error_msg.add("MPU6050 Found!");
    Udp.beginPacket(IP, LOCALPORT);
    error_msg.send(Udp);
    Udp.endPacket();
    error_msg.empty();
  }

  // MPU 6050 Settings
  mpu.setAccelerometerRange(MPU6050_RANGE_2_G);
  mpu.setGyroRange(MPU6050_RANGE_2000_DEG);
  mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);

  error_msg.add("MPU6050 Booted!");
  Udp.beginPacket(IP, LOCALPORT);
  error_msg.send(Udp);
  Udp.endPacket();
  error_msg.empty();

  error_msg.add("Callibrating Gyro, keep the gyro stationary");
  Udp.beginPacket(IP, LOCALPORT);
  error_msg.send(Udp);
  Udp.endPacket();
  error_msg.empty();

  calibrateGyro();

  error_msg.add("Gyro callibrated, adjusted offsets are:");
  error_msg.add("x-offset:");
  error_msg.add(gXOffset);
  error_msg.add("y-offset:");
  error_msg.add(gYOffset);
  error_msg.add("z-offset:");
  error_msg.add(gZOffset);
  Udp.beginPacket(IP, LOCALPORT);
  error_msg.send(Udp);
  Udp.endPacket();
  error_msg.empty();

  // Select the APDS9960 and Boot
  tcaselect(apds_TCA_ADDR);
  delay(10);
  if(!apds.begin(5, APDS9960_AGAIN_4X, APDS9960_ADDRESS, &DEV_I2C)){
    error_msg.add("Failed to initialize APDS!");
    Udp.beginPacket(IP, LOCALPORT);
    error_msg.send(Udp);
    Udp.endPacket();
    error_msg.empty();
  } else {
    error_msg.add("APDS initialized!");
    Udp.beginPacket(IP, LOCALPORT);
    error_msg.send(Udp);
    Udp.endPacket();
    error_msg.empty();
  }

  //enable color sensing mode
  apds.enableColor(true);

  tcaselect(tof1_TCA_ADDR);
  delay(10);
  sensor_vl53l4cd_sat_1.begin();
  sensor_vl53l4cd_sat_1.VL53L4CD_Off();
  sensor_vl53l4cd_sat_1.InitSensor();
  sensor_vl53l4cd_sat_1.VL53L4CD_SetRangeTiming(10, 0);
  sensor_vl53l4cd_sat_1.VL53L4CD_StartRanging();

  error_msg.add("TOF Sensor 1 initialized!");
  Udp.beginPacket(IP, LOCALPORT);
  error_msg.send(Udp);
  Udp.endPacket();
  error_msg.empty();

  tcaselect(tof2_TCA_ADDR);
  delay(10);
  sensor_vl53l4cd_sat_2.begin();
  sensor_vl53l4cd_sat_2.VL53L4CD_Off();
  sensor_vl53l4cd_sat_2.InitSensor();
  sensor_vl53l4cd_sat_2.VL53L4CD_SetRangeTiming(10, 0);
  sensor_vl53l4cd_sat_2.VL53L4CD_StartRanging();

  error_msg.add("TOF Sensor 2 initialized!");
  Udp.beginPacket(IP, LOCALPORT);
  error_msg.send(Udp);
  Udp.endPacket();
  error_msg.empty();

  delay(100);
}

/* Main Loop ------------------------------------------------------------------*/

void loop() {
  uint8_t NewDataReady = 0;

  tcaselect(mpu_TCA_ADDR);
  mpu.getEvent(&a, &rot, &temp);

  Ax = a.acceleration.x / 9.81;
  Ay = a.acceleration.y / 9.81;
  Az = a.acceleration.z / 9.81;
 
  Gx = rot.gyro.x - gXOffset;
  Gy = (rot.gyro.y - gYOffset);
  Gz = rot.gyro.z - gZOffset;
 
  rollG = rollG + (millis() - tStart) / 1000. * Gy * 360. / 2. / 3.14159;
  pitchG = pitchG + (millis() - tStart) / 1000. * Gx * 360. / 2. / 3.14159;
  yawG = yawG + (millis() - tStart) / 1000. * Gz * 360. /2. / 3.14159;
  deltaRoll = (millis() - tStart) / 1000. * Gy * 360. /2. / 3.14159;
  deltaPitch = (millis() - tStart) / 1000. * Gx * 360. /2. / 3.14159;
  tStart = millis();
 
  Ax = xScale * (Ax - xOffset);
  Ay = yScale * (Ay - yOffset);
  Az = zScale * (Az - zOffset);
 
  pitchRaw = atan2(Ay, sqrt(Az * Az + Ax * Ax)) * 360 / (2 * 3.14159);
  rollRaw = atan2(Ax, sqrt(Az * Az + Ay * Ay)) * 360 / (2 * 3.14159);
 
  rollComp = .25 * rollRaw + .75 * (rollComp + deltaRoll);
  pitchComp = .25 * pitchRaw + .75 * (pitchComp + deltaPitch);

  tcaselect(apds_TCA_ADDR);
  apds.getColorData(&r, &g, &b, &c);

  tcaselect(tof1_TCA_ADDR);
  do {
    status1 = sensor_vl53l4cd_sat_1.VL53L4CD_CheckForDataReady(&NewDataReady);
  } while (!NewDataReady);

  if ((!status1) && (NewDataReady != 0)) {
    // (Mandatory) Clear HW interrupt to restart measurements
    sensor_vl53l4cd_sat_1.VL53L4CD_ClearInterrupt();
    // Read measured distance. RangeStatus = 0 means valid data
    sensor_vl53l4cd_sat_1.VL53L4CD_GetResult(&results1);
  }

  // Lowpass filter for TOF
  tof1FilteredValue = tof1Alpha * results1.distance_mm + (1 - tof1Alpha) * tof1FilteredValue;

  tcaselect(tof2_TCA_ADDR);
  do {
    status2 = sensor_vl53l4cd_sat_2.VL53L4CD_CheckForDataReady(&NewDataReady);
  } while (!NewDataReady);

  if ((!status2) && (NewDataReady != 0)) {
    // (Mandatory) Clear HW interrupt to restart measurements
    sensor_vl53l4cd_sat_2.VL53L4CD_ClearInterrupt();
    // Read measured distance. RangeStatus = 0 means valid data
    sensor_vl53l4cd_sat_2.VL53L4CD_GetResult(&results2);
  }

  // Lowpass filter for TOF
  tof2FilteredValue = tof2Alpha * results2.distance_mm + (1 - tof2Alpha) * tof2FilteredValue;

  // Dispatch data to Max

  OSCMessage mpu_msg("/player1/mpu/");
  mpu_msg.add(Ax);
  mpu_msg.add(Ay);
  mpu_msg.add(Az);
  mpu_msg.add(rollComp);
  mpu_msg.add(pitchComp);
  mpu_msg.add(Gx);
  mpu_msg.add(Gy);
  mpu_msg.add(Gz);
  Udp.beginPacket(IP, LOCALPORT);
  mpu_msg.send(Udp);
  Udp.endPacket();
  mpu_msg.empty();

  OSCMessage apds_msg("/player1/apds/");
  apds_msg.add(r);
  apds_msg.add(g);
  apds_msg.add(b);
  apds_msg.add(c);
  Udp.beginPacket(IP, LOCALPORT);
  apds_msg.send(Udp);
  Udp.endPacket();
  apds_msg.empty();

  OSCMessage tof1_msg("/player1/tof1/");
  tof1_msg.add(results1.range_status);
  tof1_msg.add(tof1FilteredValue);
  Udp.beginPacket(IP, LOCALPORT);
  tof1_msg.send(Udp);
  Udp.endPacket();
  tof1_msg.empty();

  OSCMessage tof2_msg("/player1/tof2/");
  tof2_msg.add(results2.range_status);
  tof2_msg.add(tof2FilteredValue);
  Udp.beginPacket(IP, LOCALPORT);
  tof2_msg.send(Udp);
  Udp.endPacket();
  tof2_msg.empty();

}
