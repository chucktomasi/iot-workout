#define NETWORK_ATTEMPTS 20

void initializeWifi() {

  if (WiFi.status() != WL_CONNECTED) {
    doAP();
  } else {
    showWifiSuccess();
    // startServer();
    registerMDNS();
    displayIPAddress();
  }
}

void initWifi() {
  // turn off AP (if it's still on)
  WiFi.softAPdisconnect(true);
  // switch to pure station
  WiFi.mode(WIFI_STA);

}

// build device/AP name
void buildDeviceName() {

  String s1 = WiFi.macAddress();
  String s2 = netnamePrefix + s1.substring(8);
  s2.replace(":","");
  netname = (char *)malloc(s2.length()+1);
  s2.toCharArray(netname,s2.length()+1);
  // strcpy(netname, s.c_str());
  //displayText(netname);
  
  Serial.print("Device network name: ");
  Serial.println(netname);

}

// Return a URL
String buildURL() {
  
  String url = "http://" + String(netname) + ".local/";
  
  return url;
}

void attemptWifi() {

  WiFi.begin(ssid, password);
  int retry = 0;
  Serial.println("Connecting Wifi");
  // displayText("Wifi....");
  while (WiFi.status() != WL_CONNECTED && retry < NETWORK_ATTEMPTS) {
    // LEDSetState(ledState);
    Serial.print(".");
    // ledState = (ledState == ON) ? OFF : ON;
    retry++;
    delay(1000);
  }
  // LEDSetState(OFF);

}

void showWifiSuccess() {
    // connected to ssid, boot normally
    
    Serial.println("");
    Serial.println("WiFi connected");
    Serial.print("IP address: ");
    
    Serial.println(WiFi.localIP());
    // displayText("OK");

    Serial.print("Rapid LED blink (3s)...");
    // blink LED rapidly for 3 sec to confirm connection
    // LEDShowReadyState();
    Serial.println("Done.");    
}

void registerMDNS() {
  
    if(MDNS.begin(netname,WiFi.localIP(),120)) {
      Serial.print("mDNS responder started: ");
      Serial.print(netname);
      Serial.println(".local");

      MDNS.addService("http", "tcp", 80);

      MDNS.update();
      // displayText("HTTP....OK");
    } else {
      Serial.println("Error starting mDNS");
      // displayText("mDNS error\n"); 
    }

}

void doAP() {
  // clearDisplay();
  // displayText("AP mode\n");
  // displayText("Network=\n");
  // displayText(netname);
  // displayText("\n");
  // displayText("IP=192.168.4.1");
  // LEDSetState(ON);

  Serial.println("");
  Serial.println("Configuring access point...");

  // turn on AP mode
  WiFi.mode(WIFI_AP);

  WiFi.softAP(netname);

  IPAddress myIP = WiFi.softAPIP();
  delay(1000);
  Serial.print("AP IP address: ");
  Serial.println(myIP);

  // fire up web server
  // startServer();
}

void displayIPAddress() {

  IPAddress ip;
  ip = WiFi.localIP();

  Serial.print("displayIPAddress():");
  Serial.println(ip.toString());

  // displayText(ip.toString());
}

