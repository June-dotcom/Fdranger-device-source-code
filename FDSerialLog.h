void showDebugLogs_for_prevars() {
  // refractor display all variables in a JSON format in serial
DynamicJsonDocument logs_tmp_vars_doc(1024);

logs_tmp_vars_doc["device_api_key"] = device_api_key;
logs_tmp_vars_doc["ultr_sensor_id"] = ultr_sensor_id;
logs_tmp_vars_doc["device_name"] = device_name;
logs_tmp_vars_doc["device_desc"] = device_desc;
logs_tmp_vars_doc["fldlvl_a_rmk_id"] = fldlvl_a_rmk_id;
logs_tmp_vars_doc["fldlvl_b_rmk_id"] = fldlvl_b_rmk_id;
logs_tmp_vars_doc["fldlvl_c_rmk_id"] = fldlvl_c_rmk_id;
logs_tmp_vars_doc["fldlvl_nrml_rmk"] = fldlvl_nrml_rmk;
logs_tmp_vars_doc["fldlvl_curr"] = fldlvl_curr;
logs_tmp_vars_doc["ssid_client"] = ssid_client;
logs_tmp_vars_doc["password_client"] = password_client;

logs_tmp_vars_doc["base_water_level_cm"] = base_water_level_cm;
logs_tmp_vars_doc["base_water_dist_assoc_cm"] = base_water_dist_assoc_cm;
logs_tmp_vars_doc["fld_alert_cm_flevel_A"] = fld_alert_cm_flevel_A;
logs_tmp_vars_doc["fld_warning_cm_flevel_B"] = fld_warning_cm_flevel_B;
logs_tmp_vars_doc["fld_severe_fld_cm_flevel_C"] = fld_severe_fld_cm_flevel_C;
logs_tmp_vars_doc["isCloudConnected"] = isCloudConnected;
logs_tmp_vars_doc["isWiFiConnected"] = isWiFiConnected;
logs_tmp_vars_doc["isSnsrSyncEnabled"] = isSnsrSyncEnabled;
logs_tmp_vars_doc["isWaterOverflow"] = isWaterOverflow;
logs_tmp_vars_doc["water_level_out_cm"] = water_level_out_cm;
logs_tmp_vars_doc["sensor_dist_out_cm"] = sensor_dist_out_cm;

serializeJson(logs_tmp_vars_doc, Serial);

}
