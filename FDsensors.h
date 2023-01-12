//setGreenColorRGB
//setBlueColorRGB
//setMagentaColorRGB
//setYellowColorRGB
//setWhiteColorRGB
//setOrangeColorRGB
//setRedColorRGB


long microsecondsToCms(long microseconds) {
  return (microseconds / 29) / 2;
}

bool evaluateOverflow(long dist_water_level_tmp) {
  bool result_tmp = false;
  if (dist_water_level_tmp < 5) {
    result_tmp = true;
  } else {
    result_tmp = false;
  }
  return result_tmp;
}


void sensorHCChnEd() {

  long duration, dist_cm;
  pinMode(trigPin, OUTPUT);
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  pinMode(echoPin, INPUT);
  duration = pulseIn(echoPin, HIGH);

  dist_cm = microsecondsToCms(duration);

  long distance_to_obj = dist_cm;
  if (distance_to_obj > 2 && distance_to_obj < 400) {
    // distance obj is the final here so eather display
    sensor_dist_out_cm = distance_to_obj;
    // calculate water level
    int sensor_dist_out_diff = prev_sens_out - sensor_dist_out_cm;
    water_level_out_cm =  (base_water_dist_assoc_cm - sensor_dist_out_cm) + base_water_level_cm;
    //    evaluate_alert_status(water_level_out_cm);
  
    isWaterOverflow = evaluateOverflow(sensor_dist_out_cm);
    fldlvl_curr = evaluate_alert_status(water_level_out_cm);

    if (abs(sensor_dist_out_diff) >= 1) {
      if (isSnsrSyncEnabled == true && WiFi.status() == WL_CONNECTED) {
        String fldlvl_tmp;
        fldlvl_tmp = fldlvl_curr;
        sendOverflowStatus(isWaterOverflow);

        sendtoserverWaterLevel(water_level_out_cm, fldlvl_tmp);
      }
    }
    prev_sens_out = sensor_dist_out_cm;
  }
}
