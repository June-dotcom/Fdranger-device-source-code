#include <Arduino.h>
#include <ArduinoJson.h>
#include <analogWrite.h>
#include "WiFi.h"
#include <WebServer.h>
#include <HTTPClient.h>
#include <FS.h>
#include "SPIFFS.h"
#include <NTPClient.h>
#include <WiFiUdp.h>

WebServer server(80);

// initialize variables
#include "FDRenv.h"
#include "FdRgbIeds.h"
#include "FdfsvarHandler.h"
#include "FDInitFsToVar.h"
#include "FDNetSync.h"
#include "FDsensors.h"
#include "SPfsWebserverCust.h"
#include "FDRoutesHandler.h"
#include "FDroutes.h"
#include "FDSerialLog.h"
#include "FDSetupInits.h"
#include "FDRgbLedTasks.h"

void Wifi_connected(WiFiEvent_t event, WiFiEventInfo_t info) {
  isWiFiConnected = true;

  Serial.println("ESP32 WIFI Connected to Access Point");
  setSignalStrength();

}

void Get_IPAddress(WiFiEvent_t event, WiFiEventInfo_t info) {
  Serial.println("WIFI Connected!");
  Serial.println("IP address of Connected WIFI: ");
  Serial.println(WiFi.localIP());
}

void Wifi_disconnected(WiFiEvent_t event, WiFiEventInfo_t info) {
  Serial.println("Disconnected from WIFI");
  Serial.print("Connection Lost Reason: ");
  Serial.println(info.disconnected.reason);
  isWiFiConnected = false;
  isCloudConnected = false;
  Serial.println("Reconnecting...");

  char* ssid_local_client = strdup(ssid_client.c_str());
  char* pass_local_client = strdup(password_client.c_str());

  WiFi.begin(ssid_local_client, pass_local_client);

}


void setup() {
  Serial.begin(115200);
  SPIFFS.begin();

  WiFi.disconnect(true);
  init_preset_fs_to_var();
  delay(1000);
  Serial.println("Pass 1 setup");
  WiFi.softAP(ssid_ap, password_ap);
  delay(500);

  WiFi.onEvent(Wifi_connected, SYSTEM_EVENT_STA_CONNECTED);
  WiFi.onEvent(Get_IPAddress, SYSTEM_EVENT_STA_GOT_IP);
  WiFi.onEvent(Wifi_disconnected, SYSTEM_EVENT_STA_DISCONNECTED);

  char* ssid_local_client = strdup(ssid_client.c_str());
  char* pass_local_client = strdup(password_client.c_str());

  WiFi.begin(ssid_local_client, pass_local_client);
  WiFi.persistent(true);

  Serial.println("Pass 2 setup");

  globalRGBLoading();

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  globalRGBOnset();
  Serial.println("Pass 3 setup");
  delay(500);
  init_routes_spfsWebserver();
  delay(500);
  Serial.println("Pass 4 setup");
  delay(500);

  xTaskCreatePinnedToCore(Task1code, "Task1", 10000, NULL, 1, &Task1, 0);
  delay(500);

  // check wifi status and sync status network tasks
  xTaskCreatePinnedToCore(Task2code, "Task2", 2048, NULL, 1, &Task2, 1);
  delay(500);

  // check wifi status and sync status
  xTaskCreatePinnedToCore(Task3code, "Task3", 10000, NULL, 3, &Task3, 1);
  delay(500);


}
// primary tasks the webserver running only in core 0
void Task1code( void * parameter ) {
  Serial.print("Task1 is running on core ");
  Serial.println(xPortGetCoreID());
  for (;;) {
    server.handleClient();
    vTaskDelay(15);

  }
}

// secondary tasks and tertiary tasks running in core 1
void Task2code(void * parameter ) {
  Serial.print("Task 2 running on check sync");
  for (;;) {
    ledTaskRealtimeInit();
    if (isWiFiConnected == true) {
      setConnectionSyncStatus();
      syncAlertMeasCm();
    }
    vTaskDelay(10);
    delay(2000);


  }
}

// tertiary tasks is the sensor only
void Task3code(void * parameter) {
  Serial.print("Task3 is running on core ");
  Serial.println(xPortGetCoreID());
  for (;;) {
    sensorHCChnEd();
    delay(1000);
    vTaskDelay(10);

  }
}


void loop() {
}
