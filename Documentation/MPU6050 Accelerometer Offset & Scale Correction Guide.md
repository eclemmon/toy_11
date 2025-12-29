# MPU6050 Accelerometer Offset & Scale Correction
***toy_11 Interface Calibration Guide***

## Overview

Due to normal manufacturing tolerances in the MPU6050 sensor and minor mechanical imprecision in the fabrication of the toy_11 interface, raw accelerometer readings will exhibit measurable bias and scale error. These errors manifest as:

* Offset (bias): A constant shift in reported acceleration values.
* Scale (gain) error: A proportional deviation where reported values are consistently too large or too small.

This document describes the procedure for correcting both issues so that measured acceleration more accurately reflects desired values. The target outcome of this process is a calibrated accelerometer with a total error of less than 5% across all axes.

## Expected Sensor Behavior

When the toy_11 interface is stationary and resting on a level surface:
* One accelerometer axis (X, Y, or Z) should read approximately +1 g or −1 g, depending on orientation.
* The remaining two axes should read approximately 0 g.

Any persistent deviation from these values indicates offset and/or scaling error and should be corrected using the procedure below.

## Prerequisites

* Arduino IDE installed
* Access to the toy_11 Arduino project files along with any dependencies
* Stable WiFi network shared by the toy_11 interface and host computer
* `toy_11_API.maxpat`available and configured for your player number

## Calibration Procedure

### 1. Initialize Calibration Values

Open the `secrets.h` file included with the Arduino project. This file contains global configuration values for networking, device addressing, and accelerometer calibration.

Locate the section labeled:

```Arduino
/* MPU6050 Accelerometer Offset & Scaling Adjustments */
#define X_MAX 1.047;
#define X_MIN -.944;
#define Y_MAX .997;
#define Y_MIN -1.012;
#define Z_MAX .876;
#define Z_MIN -1.186;
```

Replace all six values with the following defaults:

```Arduino 
/* MPU6050 Accelerometer Offset & Scaling Adjustments */
#define X_MAX 1.0;
#define X_MIN -1.0;
#define Y_MAX 1.0;
#define Y_MIN -1.0;
#define Z_MAX 1.0;
#define Z_MIN -1.0;
```

This establishes a neutral baseline from which calibration values can be derived.

### 2. Upload Firmware

Connect the toy_11 interface to your computer via USB and upload the Arduino sketch containing the updated `secrets.h` file.

Once the upload completes successfully, disconnect the USB cable.

### 3. Prepare the Physical Environment

Close the toy_11 enclosure and place it on a stable, level surface. The floor is often the most reliably level option, though calibration performed on the same surface used during performance will generally yield the most accurate results.

Power on the toy_11 interface and allow it to connect normally over WiFi.

### 4. Establish Network Communication

On your computer:
* Connect to the same WiFi router as the toy_11 interface.
* If the toy_11 interface does not connect and transmit data as expected, verify that the `DESTINATION_IP` value in `secrets.h` matches the IP address of the host machine.

Refer to the setup or troubleshooting documentation if network communication cannot be established.

### 5. Monitor Live Accelerometer Data

Open the `toy_11_API.maxpat` file in Max and navigate to the subpatch corresponding to your assigned player number.
You should observe a continuous stream of accelerometer data arriving from the toy_11 interface.

### 6. Measure Axis Extremes

For each of the six faces of the toy_11 enclosure:

1.	Place the device so that one face is pointing directly upward.
2.	Observe the accelerometer values in Max.
3.	Identify the axis reading that is closest to +1 g or −1 g. Only one axis should be near ±1 g in any given orientation.
4.	Note the most stable value observed for that axis.
Update the corresponding `*_MAX` or `*_MIN` value in `secrets.h` to match the observed reading.

**Example:**

If the X-axis consistently reads 1.024 when facing upward, update:

```Arduino
#define X_MAX 1.024;
```
Repeat this process until all six values (`X_MAX`, `X_MIN`, `Y_MAX`, `Y_MIN`, `Z_MAX`, `Z_MIN`) have been updated.

### 7. Apply Calibration

Reconnect the toy_11 interface to your computer via USB and upload the Arduino sketch with the updated calibration values

### 8. Verify Results

Run the toy_11 interface again and observe live accelerometer data.
Confirm that:
* The axis aligned with gravity reports approximately ±1 g
* The remaining axes report approximately 0 g
* Overall error across all orientations is less than 5%
If necessary, repeat the calibration steps to further refine accuracy.
