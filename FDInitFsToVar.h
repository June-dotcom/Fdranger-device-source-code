// JSON databases filename
// wifi_credentials
// floodcalibValues
// list_modes


void init_preset_fs_to_var() {
  // change single file to JSON
  // if(setupmode)

  profiles_json = readSpfsModStr("profiles", "json");
  DynamicJsonDocument profiles(1024);
  deserializeJson(profiles, profiles_json);

  const char* ssid_client_out = profiles["wifi"]["wifissid"];
  const char* password_client_out = profiles["wifi"]["wifiPassword"];
  const char* is_sensor_sync_chars = profiles["modes"]["is_sensor_sync"];

  ssid_client = ssid_client_out;
  password_client = password_client_out;
  
//  ssid_client_tmp = (char*)ssid_client_out;
//  password_client_tmp = (char*)password_client_out;
  //  ssid_client_tmp = ssid_client_out;
  //  password_client_tmp = password_client_out;
  const String is_sensor_sync_chars_tmp = is_sensor_sync_chars;
  if (is_sensor_sync_chars_tmp == "true") {
    isSnsrSyncEnabled = true;
  } else {
    isSnsrSyncEnabled = false;
  }

  // convert to int
  const char* base_water_dist_assoc_cm_chars = profiles["floodCalib"]["baseAssocDistToWater"];
  const char* base_water_level_cm_chars = profiles["floodCalib"]["baseWaterLvl"];
  const char* fld_alert_cm_flevel_A_chars = profiles["floodCalib"]["flevelA"];
  const char* fld_warning_cm_flevel_B_chars = profiles["floodCalib"]["flevelB"];
  const char* fld_severe_fld_cm_flevel_C_chars = profiles["floodCalib"]["flevelC"];

  // calibs entity tmp
  char* bs_wtr_dst_asc_chrs = (char*)base_water_dist_assoc_cm_chars;
  char* bs_wtr_lvl = (char*)base_water_level_cm_chars;
  char* fl_alrt_a = (char*)fld_alert_cm_flevel_A_chars;
  char* fl_alrt_b = (char*)fld_warning_cm_flevel_B_chars;
  char* fl_alrt_c = (char*)fld_severe_fld_cm_flevel_C_chars;

  base_water_dist_assoc_cm = (String(bs_wtr_dst_asc_chrs)).toInt();
  base_water_level_cm = (String(bs_wtr_lvl)).toInt();
  fld_alert_cm_flevel_A = (String(fl_alrt_a)).toInt();
  fld_warning_cm_flevel_B = (String(fl_alrt_b)).toInt();
  fld_severe_fld_cm_flevel_C = (String(fl_alrt_c).toInt());

}
