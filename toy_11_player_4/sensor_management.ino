Adafruit_MPU6050 mpu6050_setup(Adafruit_MPU6050 sensor, WiFiUDP Udp, IPAddress ipaddress, int localPort) {
  // Starting up MPU6050 Message Dispatch
  // sendOscError(Udp, ipaddress, localPort, 1);

  // Start up the MPU6050
  if (!sensor.begin()) {
    // If the sensor does not start up, dispatch message with error.
    // sendOscError(Udp, ipaddress, localPort, 4);
    Serial.println("booted mpu6050");
  } else {
    // else, indicate that the MPU6050 was found.
    // sendOscError(Udp, ipaddress, localPort, 3);
  }

  mpu.setAccelerometerRange(MPU6050_RANGE_2_G);
  mpu.setGyroRange(MPU6050_RANGE_1000_DEG);
  mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);

  return sensor;

}

void apds_setup(Adafruit_APDS9960 apds, WiFiUDP Udp, IPAddress ipaddress, int localPort) {
  if(!apds.begin()){
    Serial.println("failed to initialize device! Please check your wiring.");
  }
  else Serial.println("Device initialized!");

  //enable color sensign mode
  apds.enableColor(true);
}

void get_color_data(Adafruit_APDS9960 apds, uint16_t r, uint16_t g, uint16_t b, uint16_t c) {
  while(!apds.colorDataReady()){
    delay(5);
  }

  //get the data and print the different channels
  apds.getColorData(&r, &g, &b, &c);
  Serial.print("red: ");
  Serial.print(r);
  
  Serial.print(" green: ");
  Serial.print(g);
  
  Serial.print(" blue: ");
  Serial.print(b);
  
  Serial.print(" clear: ");
  Serial.println(c);
  Serial.println();
}

void tcaselect(uint8_t i) {
  if (i > 7) return;
 
  DEV_I2C.beginTransmission(TCAADDR);
  DEV_I2C.write(1 << i);
  DEV_I2C.endTransmission();  
}

void calibrateGyro() {
  int i;
  float sumX = 0;
  float sumY = 0;
  float sumZ = 0;
  int numPoints=1000;
  for (i=0;i<numPoints;i=i+1) {
    mpu.getEvent(&a, &rot, &temp);
    sumX = sumX + rot.gyro.x;
    sumY = sumY + rot.gyro.y;
    sumZ = sumZ + rot.gyro.z;
    delay(10);
  }
  gXOffset = sumX/numPoints;
  gYOffset = sumY/numPoints;
  gZOffset = sumZ/numPoints;
}