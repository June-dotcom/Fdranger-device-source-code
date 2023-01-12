void globalRGBLoading() {
  for (int x = 1; x <= 4; x++) {
    setMagentaColorRGB(x);
  }
}

void globalRGBOnset() {
  for (int y = 1; y <= 5; y++) {
    for (int x = 1; x <= 4; x++) {
      setWhiteColorRGB(x);
    }
    delay(500);
    for (int x = 1; x <= 4; x++) {
      setMagentaColorRGB(x);
    }
    delay(500);
  }

}

void globalRGBLocked(){
   for (int x = 1; x <= 4; x++) {
      setCyanColorRGB(x);
    }
}

void setterRGBConnStatus() {
  if (isWiFiConnected == true) {
    setBlueColorRGB(1);
  } else if (isWiFiConnected == false) {
    setRedColorRGB(1);
  }
}

void setterRGBCloudStatus() {
  if (isCloudConnected == true) {
    setBlueColorRGB(2);
  } else if (isCloudConnected == false) {
    setRedColorRGB(2);
  }
}

void setterRGBSensorSync() {
  if (isSnsrSyncEnabled == true) {
    setBlueColorRGB(3);
  } else if (isSnsrSyncEnabled == false) {
    setRedColorRGB(3);
  }
}

void setterRGBAlertStat() {
  if (fldlvl_curr == "FLDNRML") {
    setBlueColorRGB(4);
  } else if (fldlvl_curr == "FLDLVLA") {
    setYellowColorRGB(4);
  } else if (fldlvl_curr == "FLDLVLB") {
    setMagentaColorRGB(4);
  } else if (fldlvl_curr = "FLDLVLC") {
    setRedColorRGB(4);
  }
}

void ledTaskRealtimeInit() {
  setterRGBSensorSync();
  setterRGBAlertStat();
  //  setOrangeColorRGB(4);

  setterRGBCloudStatus();
  setterRGBConnStatus();
}
