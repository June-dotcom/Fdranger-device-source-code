// JSON databases filename
// wifi_credentials
// floodcalibValues

bool loadFromSpiffs(String path)
{
  String dataType = "text/plain";

  if (path.endsWith("/")){
      path += "index.html.gz";
  }

  if (path.endsWith(".src"))
    path = path.substring(0, path.lastIndexOf("."));

  else if (path.endsWith(".html"))
    dataType = "text/html";

  else if (path.endsWith(".htm"))
    dataType = "text/html";

  else if (path.endsWith(".css"))
    dataType = "text/css";

  else if (path.endsWith(".js"))
    dataType = "application/javascript";

  else if (path.endsWith(".png"))
    dataType = "image/png";

  else if (path.endsWith(".gif"))
    dataType = "image/gif";

  else if (path.endsWith(".jpg"))
    dataType = "image/jpeg";

  else if (path.endsWith(".ico"))
    dataType = "image/x-icon";

  else if (path.endsWith(".xml"))
    dataType = "text/xml";

  else if (path.endsWith(".svg"))
    dataType = "image/svg+xml";

  else if (path.endsWith(".pdf"))
    dataType = "application/pdf";

  else if (path.endsWith(".zip"))
    dataType = "application/zip";

  else if (path.endsWith(".json"))
    dataType = "application/json";

  else if (path.endsWith(".html.gz"))
    dataType = "text/html";

  else if (path.endsWith(".css.gz"))
    dataType = "text/css";

  else if (path.endsWith(".js.gz"))
    dataType = "application/javascript";
    
  File dataFile = SPIFFS.open(path.c_str(), "r");
  if (server.hasArg("download"))
    dataType = "application/octet-stream";
  if (server.streamFile(dataFile, dataType) != dataFile.size())
  {}

dataFile.close();
return true;
}

void handleWebRequests()
{
  if (loadFromSpiffs(server.uri())) return;

  String message = "File not detected\n\n";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += (server.method() == HTTP_GET) ? "GET" : "POST";
  message += "\nArguments: ";
  message += server.args();
  message += "\n";

  for (uint8_t i = 0; i < server.args(); i++)
  {
    message += " NAME:" + server.argName(i) + "\n VALUE:" + server.arg(i) + "\n";
  }

  server.send(404, "text/plain", message);
  //Serial.println(message);
}
