/* GLOBAL VARS */
#define SECRET_SSID "NETGEAR63" // WiFi SSID
#define SECRET_PASS "joyoustable416" // WiFi password
// #define PLAYER_ADDR "/player1/" // Update the player number according to your need and number of players.
#define LOCALPORT 8000 // Some local port (make sure it's the same on Max in the host machine)
#define DESTINATION_IP "192.168.1.2" // Target Computer Destination. See documentation for setting static IP address reservation for host computer
#define MPU6050_TCA_ADDR 4
#define APDS_TCA_ADDR 5
#define TOF1_TCA_ADDR 6
#define TOF2_TCA_ADDR 7

/* MPU6050 Accelerometer Offset & Scaling Adjustments */
#define X_MAX 1.047;
#define X_MIN -.944;
#define Y_MAX .997;
#define Y_MIN -1.012;
#define Z_MAX .876;
#define Z_MIN -1.186;