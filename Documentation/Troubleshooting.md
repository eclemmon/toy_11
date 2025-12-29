# Troubleshooting

## Arduino not connecting to Wi-Fi:

>### Solution: 
Double check the `SECRET_SSID` & `SECRET_PASS` variables in the `secrets.h` file via the Arduino IDE so that they match the desired network name and password.

>### Solution: 
Your Wi-Fi router must be setup to run a 2.4 GHz channel for the Arduino to connect to the Wi-Fi router.

## Arduino not connecting to host computer

>### Solution: 
Double check that your host computer has not connected to the wrong (perhaps default) Wi-Fi router SSID.

>### Solution: 

Double check the `DESTINATION_IP` variable in the `secrets.h` file and compare it to the IP Address of the host computer. These should be the same. Users would likely benefit by setting up the WiFi router to reserve an IP address for the target host computer using it’s MAC address. See [IP Address Reservation Instructions](/Documentation/IP%20Address%20Reservation%20Instructions.md) for a walkthrough on how to achieve this on Netgear WNR2000v5 routers. Other routers with this capacity will have a similar process to reserve an IP, and their respective documentation can be consulted.

## VL53L4CD Time of Flight Sensor Not Ranging Properly

The cover glass of each unit can sometimes be detected by the VL53L4CD Time of Flight sensor. This can occur if the cover glass gets dirty or scratched.

>### Solution: 
Remove the affected VL53L4CD sensor assembly tray using a 1.3mm hex driver. Using glass cleaner, and being careful not to get the sensor itself wet, gently clean the cover glass. Test the sensor by reconnecting any cables and booting the internal Arduino, sending data to the toy_11 host computer.

>### Solution: 
Remove the affected VL53L4CD sensor assembly tray using a 1.3mm hex driver. Tear off the cover glass using needle nose pliers. WARNING: A NEW ASSEMBLY TRAY WILL NEED TO BE 3D PRINTED AND A FRESH COVER GLASS AFFIXED TO GAIN THE PROTECTIVE BENEFITS OF A COVER GLASS

## Failed to find MPU6050 chip Error Message

>### Solution: 

Check to make sure that the Qwiik connections are properly seated in both the MPU6050 unit, the PCA9548A, and the Arduino R4 WiFi.

>### Solution: 
Sometimes when unplugging and re-plugging a sensor from the PCA9548A, the I<sup>2</sup>C multiplexer can get stuck in a faulty state, and even cycling the Arduino’s power by pressing the power button does not work. In this case, plug all sensors into the PCA multiplexer, unplug and then replug the multiplexer into the Arduino, and then cycle the power the on the Arduino.

## MPU6050 Accelerometer Returning Inaccurate Minimum and Maximum Values

The MPU6050 should return minimum and maximum values of -1.0 to 1.0 for each of the x, y, and z dimensions. Users should accept a 5% error or less in the usage of toy_11. Each toy_11 should come already calibrated. 

>### Solution:

If the error exceeds 5% in any dimension, recalibrate the MPU using the instructions found in the [MPU6050 Accelerometer Offset & Scale Correction Guide](/Documentation/MPU6050%20Accelerometer%20Offset%20&%20Scale%20Correction%20Guide.md).

## Failed to initialize APDS! error message

>### Solution: 
Check to make sure that the Qwiik connections are properly seated in both the MPU6050 unit and the PCA9548A.