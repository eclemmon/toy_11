# toy_11: A New Interface for Musical Expression

## About

The toy_11 musical interface is an 8"x8"x8" wooden box with embedded two [VL53L4CD](https://www.st.com/en/imaging-and-photonics-solutions/vl53l4cd.html) time of flight sensors, one [APDS-9960](https://www.broadcom.com/products/optical-sensors/integrated-ambient-light-and-proximity-sensors/apds-9960) digital RGB, ambient light, proximity and gesture sensor, and one [MPU6050](https://invensense.tdk.com/products/motion-tracking/6-axis/mpu-6050/) 6-axis MEMS motion tracking sensor.

The sensors route captured data via an [Arduino R4 WiFi](https://store-usa.arduino.cc/products/uno-r4-wifi) to a local host Max patch via OSC over UDP. This data can then be digested for programming purposes.

## Documentation

### Start Here
* [Setup](/Documentation/Setup.md)

### Other Documentation
* [IP Address Reservation Instructions](/Documentation/IP%20Address%20Reservation%20Instructions.md)
* [MPU6050 Accelerometer Offset & Scale Adjustment Instructions](/Documentation/MPU6050%20Accelerometer%20Offset%20&%20Scale%20Correction%20Guide.md)
* [Troubleshooting](/Documentation/Troubleshooting.md)
