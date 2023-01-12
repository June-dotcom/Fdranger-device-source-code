void showDebugLogs_for_prevars() {
  //String is_sensor_sync_str;
  //String is_setup_mode_str;
  //String is_alert_mode_str;
  //String is_sleep_enabled_str;

  Serial.println("------------------");
  Serial.println(WiFi.localIP());
  Serial.println("-----Profile -----");
  Serial.println(profiles_json);
  Serial.println("-----Flags -----");
  Serial.println("-----Dev mode-----");
  Serial.println("Client wifi ssid: " +  String(ssid_client_tmp) + " Client password: " + String(password_client_tmp));
  Serial.println("base_water_level_cm: " + String(base_water_level_cm));
  Serial.println("fld_alert_cm_flevel_A: " + String(fld_alert_cm_flevel_A));
  Serial.println("fld_warning_cm_flevel_B: " + String(fld_warning_cm_flevel_B));
  Serial.println("fld_severe_fld_cm_flevel_C: " + String(fld_severe_fld_cm_flevel_C));

  Serial.println("-----------------------------------------------");

}
