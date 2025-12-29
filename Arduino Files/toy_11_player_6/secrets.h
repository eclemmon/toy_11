/* GLOBAL VARS */
#define SECRET_SSID "NETGEAR63" // WiFi SSID
#define SECRET_PASS "joyoustable416" // WiFi password
// #define PLAYER_ADDR "/player1/" // Update the player number according to your need and number of players.
#define LOCALPORT 8000 // Some local port (make sure it's the same on Max in the host machine)
#define DESTINATION_IP "192.168.1.2" // Target Computer Destination. See documentation for setting static IP address reservation for host computer
#define MPU6050_TCA_ADDR 0
#define APDS_TCA_ADDR 1
#define TOF1_TCA_ADDR 2
#define TOF2_TCA_ADDR 3

/* MPU6050 Accelerometer Offset & Scaling Adjustments */
#define X_MAX 1.034;
#define X_MIN -0.964;
#define Y_MAX .993;
#define Y_MIN -1.011;
#define Z_MAX .928;
#define Z_MIN -1.115;