# Setup

## *toy_11* Overview

![toy_11 unfolded](/Documentation/Documentation%20Assets/toy_11_unfolded.png)

![The top, Side 1, and Side 4 of toy_11](/Documentation/Documentation%20Assets/toy_11_top_side_1.png)

![The top, Side 2, and Side 3 of toy_11](/Documentation/Documentation%20Assets/toy_11_top_side_3.png)

## Opening the *toy_11* Interface

Unscrew the four M3 hex bolts affixing the top of the interface to the rest of the body.

> NOTE: OPEN THE TOP SLOWLY SO AS TO NOT DAMAGE THE QWIICK CONNECTOR JACKS ON EITHER THE VL53L4CD or the PCA MULTIPLEXER UNIT

![toy_11 interface with pointers towards M3 hex bolts affixing top to body of the interface](/Documentation/Documentation%20Assets/M3%20Hex.png)

## Inserting Batteries Into the *toy_11* Interface 18650 Battery Shield

**Important: Observe correct polarity. Inserting batteries backward may permanently damage the shield.**

1) Locate the + (positive) and – (negative) markings on the battery holder and batteries.

2) Insert an 18650 Li-ion battery into the slot:

    * Positive (+) end → matches the + marking
    * Negative (–) end → against the - marking

3) Press the batteries gently into the spring and seat it fully.

4) Confirm batteries are secure and properly aligned before powering the shield.

![toy_11 18650 battery shield diagram](/Documentation/Documentation%20Assets/battery_shield_diagram%20copy.webp)

## Turning on and off the *toy_11* Interface

To turn on the toy_11 interface, press the power button on the underside of the 18650 battery shield once. 

![toy_11 18650 battery shield diagram](/Documentation/Documentation%20Assets/battery_shield_diagram%20copy.webp)

The hold power switch should need no adjustment, but should be set to the right with Side 1 facing your body.

The battery shield should remain on as long as the Arduino R4 WiFi is drawing power from the shield

To turn off the toy_11 interface, press the power button on the underside of the 18650 battery shield twice.

## Connecting *toy_11* to the Host via WiFi

1) Connect the host computer to your 2.4GHz network.
2) Find the the IP address assigned to your computer and record it.

    To find the host machine’s MAC Address on Apple machines:
        
    > https://support.apple.com/guide/mac-help/find-your-computers-name-and-network-address-mchlp1177/mac

    To find the host machine’s MAC Address on Windows machines:
        
    > https://learn.microsoft.com/en-us/answers/questions/3196509/where-can-i-find-what-my-mac-address-is

    To find the host machines MAC Address on Linux machines:

    > https://superuser.com/questions/164426/how-can-i-see-my-mac-address-on-ubuntu

    NB: follow the [IP Address Reservation Instructions](/Documentation/IP%20Address%20Reservation%20Instructions.md) to skip needing to update the IP Address setup most every time the host is disconnected from the 2.4GHz network.

3. Open the secrets.h file in your player folder using the [Arduino IDE](https://www.arduino.cc/en/software/). Simply opening the toy_11_player_x.ino file will open all the relevant project files in the IDE.

4. Update the `SECRET_SSID`, `SECRET_PASS`, and `DESTINATION_IP` variables to reflect the local WiFI network's SSID and password. 

    ```secrets.h file
    secrets.h file:
    /* GLOBAL VARS */
    #define SECRET_SSID "SSID HERE" 
    #define SECRET_PASS "PASSWORD HERE" 
    ...
    #define DESTINATION_IP "HOST COMPUTER IP HERE"
    ```
5. Connect the Arduino R4 WiFi unit to your computer by unplugging the USB-C to USB-A cable from the 18650 Battery Shield and plugging it into a USB-A port on your computer.

6. Using the Arduino IDE, upload the project files to the Arduino R4 Wifi.

7. Disconnect the USB-C to USB-A cable and reconnect it to the 18650 Battery Shield. 

8. Turn the 18650 Battery Shield on. See the section on [turning on and off the toy_11 interface](#turning-on-and-off-the-toy_11-interface).

9. Open the included `toy_11_API.maxpat` file and navigate to your player to monitor incoming data. Check error statuses in the Max console as needed. 