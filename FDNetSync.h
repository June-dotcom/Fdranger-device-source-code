String evaluate_alert_status(int value) {
  String ret_val = "FLDNRML";
  if ((value > fld_alert_cm_flevel_A) && (value < fld_warning_cm_flevel_B) && (value  < fld_severe_fld_cm_flevel_C)) {
    ret_val = "FLDLVLA";
  } else if ((value > fld_alert_cm_flevel_A) && (value > fld_warning_cm_flevel_B) && (value < fld_severe_fld_cm_flevel_C)) {
    ret_val = "FLDLVLB";
  } else if ((value > fld_alert_cm_flevel_A) && (value > fld_warning_cm_flevel_B) && (value  > fld_severe_fld_cm_flevel_C)) {
    ret_val = "FLDLVLC";
  } else if ((value < fld_alert_cm_flevel_A) && (value < fld_warning_cm_flevel_B) && (value  < fld_severe_fld_cm_flevel_C)) {
    ret_val = "FLDNRML";
  }
  return ret_val;
}

void sendtoserverWaterLevel(int value, String alert_status_tmp) {
  HTTPClient http;
  String php_file = "update_water_level.php";
  String getParams, address_link;
  getParams = "?device_api_key=" + device_api_key + "&sensor_id=" + ultr_sensor_id + "&water_level=" + String(value) + "&fld_level_status=" + alert_status_tmp;
  address_link = host + php_file + getParams;
  http.begin(address_link);
  String httpCode = String(http.GET());
  String payload = http.getString();
  payload.trim();
  http.end();
}


void setConnectionSyncStatus() {
  HTTPClient http;
  String php_file = "device_update_stamp.php";
  String address_link;
  String get_param;
  get_param = "?device_api_key=" + device_api_key;
  address_link = host + php_file + get_param;
  http.begin(address_link);
  int httpCode = http.GET();
  String payload = http.getString();
  payload.trim();
  http.end();
  if (httpCode == 200) {
    isCloudConnected = true;
  } else {
    isCloudConnected = false;
  }
}

void setSignalStrength() {
  signal_strength_wifi_rssi = String(WiFi.RSSI());
  int wifi_rssi_tmp = String(WiFi.RSSI()).toInt();
  if (wifi_rssi_tmp > -50) {
    signal_strength_wifi_remarks = "Excellent";
  } else if (wifi_rssi_tmp < -50 && wifi_rssi_tmp > -60) {
    signal_strength_wifi_remarks = "Good";
  } else if (wifi_rssi_tmp < -60 && wifi_rssi_tmp > -70) {
    signal_strength_wifi_remarks = "Fair";
  } else if (wifi_rssi_tmp < -70) {
    signal_strength_wifi_remarks = "Weak";
  }
}

void checkConnectionStatusWiFiTask() {
  Serial.print(millis());
  Serial.println("Reconnecting to WiFi...");
  WiFi.disconnect();
  WiFi.reconnect();
}

//short fld_alert_cm_flevel_A = 0;
//short fld_warning_cm_flevel_B = 0;
//short fld_severe_fld_cm_flevel_C = 0;
// send alert a b c to web

// send this alert once
void syncAlertMeasCm() {
  HTTPClient http;
  String php_file = "sync_alert_water_level.php";
  String getParams, address_link;
  getParams = "?";
  getParams += "alert_a_cm=" + String(fld_alert_cm_flevel_A);
  getParams += "&alert_b_cm=" + String(fld_warning_cm_flevel_B);
  getParams += "&alert_c_cm=" + String(fld_severe_fld_cm_flevel_C);
  getParams += "&sensor_id=" + ultr_sensor_id;
  address_link = host + php_file + getParams;
  http.begin(address_link);
  int httpCode = http.GET();
  //  if (httpCode == 200) {
  //  }
  String payload = http.getString();
  payload.trim();
  http.end();
}

void sendOverflowStatus(bool isOverFlowWater_tmp) {
  HTTPClient http;
  String php_file = "sync_overflow_status.php";
  String getParams, address_link;
  getParams = "?";
  getParams += "device_api_key=" + device_api_key;
  if (isOverFlowWater_tmp == true) {
    getParams += "&overflow_status_code=1";
  } else  {
    getParams += "&overflow_status_code=0";
  }
  address_link = host + php_file + getParams;
  http.begin(address_link);
  int httpCode = http.GET();
  if (httpCode == 200) {
  }
  //  String payload = http.getString();
  //  payload.trim();
  http.end();

}
