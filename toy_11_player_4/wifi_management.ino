void printWifiStatus() {

  // print the SSID of the network you're attached to:
  Serial.print(F("SSID: "));
  Serial.println(WiFi.SSID());

  // print your board's IP address:
  IPAddress ip = WiFi.localIP();
  Serial.print(F("IP Address: "));
  Serial.println(ip);

  // print the received signal strength:
  long rssi = WiFi.RSSI();
  Serial.print(F("signal strength (RSSI):"));
  Serial.print(rssi);
  Serial.println(F(" dBm"));
}

WiFiUDP bootWiFi(int status, char ssid[], char password[], WiFiUDP Udp, unsigned int localPort) {
    // check for the WiFi module:
    if (WiFi.status() == WL_NO_MODULE) {
      Serial.println(F("Communication with WiFi module failed!"));
      // don't continue
      while (true);
    }

    // Check for the latest firmware
    String fv = WiFi.firmwareVersion();

    if (fv < WIFI_FIRMWARE_LATEST_VERSION) {
      Serial.println(F("Please upgrade the firmware"));
    }

    // attempt to connect to WiFi network:
    while (status != WL_CONNECTED) {
      Serial.print(F("Attempting to connect to SSID: "));
      Serial.println(ssid);
      // Connect to WPA/WPA2 network. Change this line if using open or WEP network:
      status = WiFi.begin(ssid, password);
      // wait 10 seconds for connection:
      delay(10000);
    }

    Serial.println(F("Connected to WiFi"));
    printWifiStatus();
    Serial.println(F("\nStarting connection to server..."));

    // if you get a connection, report back via serial:
    Udp.begin(localPort);
    return Udp;
}
