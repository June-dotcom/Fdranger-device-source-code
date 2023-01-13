// JSON databases filename
// wifi_credentials
// floodcalibValues
// list_modes

// for main / page
void handler_root_page() {
  server.sendHeader("Location", "/index.html.gz", true);
  server.send(302, "text/plane", "");
}

// end of main page
void handler_restart_device() {
  server.send(200, "text/plane" "Your device will restart for a while...Please wait...");
  Serial.println("Device initialize to restart");
  delay(300);
  ESP.restart();
}


void set_recal() {
  if (server.method() == HTTP_POST) {
    String setBaseWaterlvlTmp = server.arg("base_water_level").c_str();
    String setflevelATmp = server.arg("flevel_a").c_str();
    String setflevelBTmp = server.arg("flevel_b").c_str();
    String setflevelCTmp = server.arg("flevel_c").c_str();


    if (setBaseWaterlvlTmp != "") {
      updateJsonDocSingleVar("profiles", "floodCalib", "baseAssocDistToWater", String(sensor_dist_out_cm));
      updateJsonDocSingleVar("profiles", "floodCalib", "baseWaterLvl", setBaseWaterlvlTmp);
    }

    if (setflevelATmp != "") {
      updateJsonDocSingleVar("profiles", "floodCalib", "flevelA", setflevelATmp);
    }

    if (setflevelBTmp != "") {
      updateJsonDocSingleVar("profiles", "floodCalib", "flevelB", setflevelBTmp);
    }

    if (setflevelCTmp != "") {
      updateJsonDocSingleVar("profiles", "floodCalib", "flevelC", setflevelCTmp);
    }

    server.sendHeader("Location", "/changes_complt.html", true);
    server.send(302, "text/plane", "");

  }
}
// handler foor settings wifi.html
void set_wifi_creds() {
  // set wifi credentials
  if (server.method() == HTTP_POST) {
    String wifissid_tmp = server.arg("wifissid").c_str();
    String wifipass_tmp = server.arg("wifipass").c_str();
    updateJsonDocSingleVar("profiles", "wifi", "wifissid", wifissid_tmp);
    updateJsonDocSingleVar("profiles", "wifi", "wifiPassword", wifipass_tmp);
    server.sendHeader("Location", "/changes_complt.html", true);
    server.send(302, "text/plane", "");
  }
}

// for device_info.html
void handler_get_vars_device() {
  String json_out_log;
  // require these stmt to other pages
  DynamicJsonDocument var_index_docs(1024);
  var_index_docs["conn_wifi_status"] = isWiFiConnected;
  var_index_docs["conn_cloud"] = isCloudConnected;
  var_index_docs["conn_sensor_sync"] = isSnsrSyncEnabled;
  var_index_docs["wifi_signal_remarks"] = signal_strength_wifi_remarks;
  var_index_docs["wifi_signal_strength"] = signal_strength_wifi_rssi;
  var_index_docs["wifi_name"] = ssid_client;

  var_index_docs["device_api_key"] = device_api_key;
  var_index_docs["device_name"] = device_name;
  var_index_docs["sensor_id"] = ultr_sensor_id;

  // require these stmt to other pages
  serializeJson(var_index_docs, json_out_log);
  server.send(200, "text/plane", json_out_log);
}


void handler_set_mode_sensor_sync() {
  if (server.arg("mode") == "start") {
    updateJsonDocSingleVar("profiles", "modes", "is_sensor_sync", "true");
    isSnsrSyncEnabled = true;
    //server.send(200, "text/plane", "sensor synced started");
    server.send(200, "text/html", "Changes completed sensor started!!<br><a href='/'>Go to home</a>");
    Serial.println("Sensor started");
  } else if (server.arg("mode") == "stop") {
    updateJsonDocSingleVar("profiles", "modes", "is_sensor_sync", "false");
    isSnsrSyncEnabled = false;
    server.send(200, "text/html", "Changes completed sensor stopped!!<br><a href='/'>Go to home</a>");
    Serial.println("Sensor stopped");

  }
}



// for sensor settings start .html
void handler_get_set_strt_snsr() {
  String json_out_log;
  // require these stmt to other pages
  DynamicJsonDocument var_index_docs(1024);
  var_index_docs["conn_wifi_status"] = isWiFiConnected;
  var_index_docs["conn_cloud"] = isCloudConnected;
  var_index_docs["conn_sensor_sync"] = isSnsrSyncEnabled;
  var_index_docs["wifi_signal_remarks"] = signal_strength_wifi_remarks;
  var_index_docs["wifi_signal_strength"] = signal_strength_wifi_rssi;
  var_index_docs["wifi_name"] = ssid_client;

  // require these stmt to other pages
  serializeJson(var_index_docs, json_out_log);
  server.send(200, "text/plane", json_out_log);

}


// for index.html system summary
void handler_get_vars_index() {
  String json_out_log;
  DynamicJsonDocument var_index_docs(1024);
  // require these stmt to other pages
  var_index_docs["conn_wifi_status"] = isWiFiConnected;
  var_index_docs["conn_cloud"] = isCloudConnected;
  var_index_docs["conn_sensor_sync"] = isSnsrSyncEnabled;
  var_index_docs["wifi_signal_remarks"] = signal_strength_wifi_remarks;
  var_index_docs["wifi_signal_strength"] = signal_strength_wifi_rssi;
  var_index_docs["wifi_name"] = ssid_client;
  var_index_docs["disp_device_local_ip"] = WiFi.localIP();
  // require these stmt to other pages
  var_index_docs["fld_alert_status"] = fldlvl_curr;
  var_index_docs["dist_to_object"] = sensor_dist_out_cm;
  var_index_docs["ultr_water_lvl"] = water_level_out_cm;

  var_index_docs["ultr_fld_level_alert_a"] = fld_alert_cm_flevel_A;
  var_index_docs["ultr_fld_level_alert_b"] = fld_warning_cm_flevel_B;
  var_index_docs["ultr_fld_level_alert_c"] = fld_severe_fld_cm_flevel_C;

  // additionals
  var_index_docs["is_water_overflow"] = isWaterOverflow;


  serializeJson(var_index_docs, json_out_log);
  server.send(200, "text/plane", json_out_log);
}

// globalize for mobile pwa maybe for later
void handler_show_global_logs() {
  String json_out_log;
  DynamicJsonDocument var_index_docs(1024);
  var_index_docs["device_api_key"] = device_api_key;
  var_index_docs["sensor_id"] = ultr_sensor_id;
  var_index_docs["device_name"] = device_name;
  // require these stmt to other pages
  var_index_docs["conn_wifi_status"] = isWiFiConnected;
  var_index_docs["conn_cloud"] = isCloudConnected;
  var_index_docs["conn_sensor_sync"] = isSnsrSyncEnabled;
  var_index_docs["wifi_signal_remarks"] = signal_strength_wifi_remarks;
  var_index_docs["wifi_signal_strength"] = signal_strength_wifi_rssi;
  var_index_docs["wifi_name"] = ssid_client;
  var_index_docs["wifi_pass"] = password_client;

  var_index_docs["disp_device_local_ip"] = WiFi.localIP();
  // require these stmt to other pages
  var_index_docs["fld_alert_status"] = fldlvl_curr;
  var_index_docs["dist_to_object"] = sensor_dist_out_cm;
  var_index_docs["ultr_water_lvl"] = water_level_out_cm;

  var_index_docs["baseWaterLvl"] = base_water_level_cm;
  var_index_docs["ultr_fld_level_alert_a"] = fld_alert_cm_flevel_A;
  var_index_docs["ultr_fld_level_alert_b"] = fld_warning_cm_flevel_B;
  var_index_docs["ultr_fld_level_alert_c"] = fld_severe_fld_cm_flevel_C;

  // additionals
  var_index_docs["is_water_overflow"] = isWaterOverflow;

  serializeJson(var_index_docs, json_out_log);
  server.send(200, "text/plane", json_out_log);
}


// for settings_wifi.html preset forms
void handler_settings_wifi() {
  String json_out_log;
  DynamicJsonDocument var_index_docs(1024);
  // require these stmt to other pages
  var_index_docs["conn_wifi_status"] = isWiFiConnected;
  var_index_docs["conn_cloud"] = isCloudConnected;
  var_index_docs["conn_sensor_sync"] = isSnsrSyncEnabled;
  var_index_docs["wifi_signal_remarks"] = signal_strength_wifi_remarks;
  var_index_docs["wifi_signal_strength"] = signal_strength_wifi_rssi;

  // require these stmt to other pages
  var_index_docs["wifi_name"] = ssid_client;
  var_index_docs["wifi_pass"] = password_client;

  serializeJson(var_index_docs, json_out_log);
  server.send(200, "text/plane", json_out_log);

}

// for settings_recal.html
void handler_settings_flood_calib() {
  String json_out_log;
  DynamicJsonDocument var_index_docs(1024);
  // require these stmt to other pages
  var_index_docs["conn_wifi_status"] = isWiFiConnected;
  var_index_docs["conn_cloud"] = isCloudConnected;
  var_index_docs["conn_sensor_sync"] = isSnsrSyncEnabled;
  var_index_docs["wifi_signal_remarks"] = signal_strength_wifi_remarks;
  var_index_docs["wifi_signal_strength"] = signal_strength_wifi_rssi;
  var_index_docs["wifi_name"] = ssid_client;

  // require these stmt to other pages
  var_index_docs["baseWaterLvl"] = base_water_level_cm;
  var_index_docs["floodLvlA"] = fld_alert_cm_flevel_A;
  var_index_docs["floodLvlB"] = fld_warning_cm_flevel_B;
  var_index_docs["floodLvlC"] = fld_severe_fld_cm_flevel_C;

  serializeJson(var_index_docs, json_out_log);
  server.send(200, "text/plane", json_out_log);
}
