// Define FREERTOS tasks
TaskHandle_t Task1;
TaskHandle_t Task2;
TaskHandle_t Task3;

// global variables

// FdRanger0xSetup ESP32urdfld0x
const char* ssid_ap = "ESP32urdfld01";
const char* password_ap = "FDrangerI0T12";

// URDFLD0x
const String device_api_key = "URDFLD01";

// CHANGE TO URDULTRSNR0x
const String ultr_sensor_id = "URDULTRSNR01";

// change river
const String device_name = "Macalong River";
const String device_desc = "Floodranger in Macalong river";
// for sensor flood level remarks snyc
// for archival proccess
const char* fldlvl_a_rmk_id = "FLDLVLA";
const char* fldlvl_b_rmk_id = "FLDLVLB";
const char* fldlvl_c_rmk_id = "FLDLVLC";
const char* fldlvl_nrml_rmk = "FLDNRML";

// flood level alert status
String fldlvl_curr = "FLDNRML";

const char* host = "http://floodranger.xyz/";

// wifi entitiy
String ssid_client;
String password_client;

// calibs entity
int base_water_level_cm = 0;
int base_water_dist_assoc_cm = 0;
int fld_alert_cm_flevel_A = 0;
int fld_warning_cm_flevel_B = 0;
int fld_severe_fld_cm_flevel_C = 0;

bool isCloudConnected = false;
bool isWiFiConnected = false;

// modes entitiy
bool isSnsrSyncEnabled = false;


// overflow
bool isWaterOverflow = false;

// for sensor ultrasonic water level
int water_level_out_cm = 0;
int sensor_dist_out_cm = 0;
int prev_sens_out = 0;

// for signal status
String signal_strength_wifi_rssi;
String signal_strength_wifi_remarks;

// for profiles json temps
String profiles_json;

// rgb led pins
// un dos tre quat
// rgb leds
// rgb led pin
// pins
// wifi
const int un_r_pin_led = 23;
const int un_g_pin_led = 22;
const int un_b_pin_led = 1;

// cloud
const int dos_r_pin_led = 3;
const int dos_g_pin_led = 21;
const int dos_b_pin_led = 19;

// sensor sync
const int tre_r_pin_led = 14;
const int tre_g_pin_led = 12;
const int tre_b_pin_led = 13;

// alert status
const int quat_r_pin_led = 25;
const int quat_g_pin_led = 26;
const int quat_b_pin_led = 27;

// hc ultrasonic pins
const int trigPin = 16;
const int echoPin = 17;
