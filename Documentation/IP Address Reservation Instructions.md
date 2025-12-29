# IP Address Reservation for toy_11 Interface

## Overview

Routers (whether WiFi or wired) in normal operation will automatically assign and recover IP addresses to connected clients using the dynamic host configuration protocol (DHCP). In normal day-to-day functioning automates and configuration settings for networks. However, for the purposes of toy_11.x it is easier for setup purposes to reserve an IP address for the main sound synthesis host, so that all the client arduinos do not need to be updated with new software every single time the host IP potentially switches due to normal DHCP operation. The clients do not need to have an IP address reserved for them. This document will walk users through how to reserve an IP address on Netgear WNR2000v5 routers.

## Walkthrough

### Step 1:

Connect to the WiFi router using any necessary SSID & password.

### Step 2:

Open your browser of choice in go to http://routerlogin.net. This URL will take you to your router’s administration interface. You may need to sign in using the required router administration username and password.

![Example image of how to log into routerlogin.net](/Documentation/Documentation%20Assets/router_login.png)

### Step 3:

Go to Advanced>Setup>LAN Setup.

![Image with steps to reach LAN Setup area of Netgear router admin panel](/Documentation/Documentation%20Assets/lan_setup_steps.png)

### Step 4:

Under the Address Reservation submenu, click the add button.

![Image displaying where address reservation sub menu is located](/Documentation/Documentation%20Assets/address_reservation_submenu.png)

### Step 5:

If the desired host machine is already connected to the router, select the radio dial the refers to the computer that you would like to serve as the host machine for toy_11.x. You can check the identity of the machine via the MAC Address in the host machine’s networking settings.

![Image displaying where to select an already connected host machine to reserve and IP address for that machine](/Documentation/Documentation%20Assets/address_reservation_selection_1.png)

To find the host machine’s MAC Address on Apple machines:
    
> https://support.apple.com/guide/mac-help/find-your-computers-name-and-network-address-mchlp1177/mac

To find the host machine’s MAC Address on Windows machines:
    
> https://learn.microsoft.com/en-us/answers/questions/3196509/where-can-i-find-what-my-mac-address-is

To find the host machines MAC Address on Linux machines:

> https://superuser.com/questions/164426/how-can-i-see-my-mac-address-on-ubuntu

Otherwise, you may manually set the IP Address to a desired available IP (suggestion for avoiding any conflicts: 192.168.1.76), set the MAC Address to the desired machine (which is likely not currently connected using the steps for different environments above, and then assigning a device name of your desire.

![Image displaying how to manually reserve an IP address for a specific MAC Address](/Documentation/Documentation%20Assets/address_reservation_selection_2.png)

### Step 6:

Click Add

### Step 7:

You should now have a new local address for the host machine reserved. You can confirm this by connecting the host machine to the router and then navigating to the host machine’s network settings to confirm that it has been assigned the correct IP Address.