

// modify json
String readSpfsModStr(String file_name, String file_type) {
  String output = "";
  File fsreader = SPIFFS.open("/" + file_name + "." + file_type, "r");
  if (!fsreader) {
    output = "";
  }
  while (fsreader.available()) {
    output += String(char(fsreader.read()));
  }
  //  output.replace("\"", "\\\"");
  fsreader.close();
  return output;
}


void writeSpfsModStr(String raw_txt, String file_name, String file_type) {
  File fswriter = SPIFFS.open("/" + file_name + "." + file_type, "w");
  fswriter.print(raw_txt);
  fswriter.close();
}

void updateJsonDocSingleVar(String json_file_name, String entity, String key, String value) {
  String ret_json_str = "";
  String json_tmp = readSpfsModStr(json_file_name, "json");
  DynamicJsonDocument ret_doc(1024);
  deserializeJson(ret_doc, json_tmp);
  Serial.println("--init json str--");
  Serial.println(json_tmp);
  ret_doc[entity][key] = value;
  serializeJson(ret_doc, ret_json_str);
  Serial.println("-----ret json str----");
  Serial.println(ret_json_str);
  writeSpfsModStr(ret_json_str, json_file_name, "json");
}
//
//StaticJsonDocument<256> getJSONdoc(String json_file){
//	String ret_json_var = readSpfsModStr(json_file, "json");
//	StaticJsonDocument<256> ret_doc;
//	deserializeJson(ret_doc, ret_json_var);
//	return ret_doc;
//}
