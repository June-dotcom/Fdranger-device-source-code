void init_routes_spfsWebserver() {

  // index.html or setup.html handler

  server.on("/", handler_root_page);

  // settings_wifi.html onsubmit
  server.on("/submit_wifi_settings", set_wifi_creds);

  // settings_recal.html
  server.on("/submit_recal", set_recal);

  // restart device command from changes complt
  server.on("/restartDeviceCommand", handler_restart_device);

  // fetch / ajax on start on stop
  server.on("/set_device_sensor_mode", handler_set_mode_sensor_sync);

  // fetch mode
  server.on("/show_main_info_json", handler_get_vars_index);

  // fetch device_info.html
  server.on("/show_device_info_json", handler_get_vars_device);

  // fetch mode sensor_sync settings.html
  server.on("/get_device_sensor_mode", handler_get_set_strt_snsr);

  // fetch mode for settings_wifi.html
  server.on("/get_setter_settings_wifi", handler_settings_wifi);

  // fetch mode for settings_recal.html
  server.on("/get_setter_settings_recal", handler_settings_flood_calib);

    // global fetch mode for mobile pwa
  server.on("/show_device_logs_json_global", handler_show_global_logs);

  // fetch mode settings
  server.onNotFound(handleWebRequests);
  server.begin();
}
