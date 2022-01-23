
void setup() {
  for (int i = 0; i < button_nr; i++) {
    pinMode( buttons[i].pin, INPUT_PULLUP );
  }
  for (int i = 0; i < switch_nr; i++) {
    pinMode( switches[i].pin, OUTPUT);
    digitalWrite( switches[i].pin, switches[i].invert ? HIGH : LOW );
  }

  Serial.begin(115200); // Wegen Nutzung der Pins 1 + 3 (RX/TX) darf die Schnittstelle im Betrieb nicht geöffnet werden
  setup_wifi();
  client.setServer( mqtt_server, 1883 );
  client.setCallback( mqttCallback );
}

void setup_wifi() {

  delay(10);
  // We start by connecting to a WiFi network
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  // WiFi.begin(ssid, password);

  // scan Wifi
  int n = WiFi.scanNetworks();
  for (int i = 0; i < n; ++i) {
    if (WiFi.SSID(i) == ssid ) {
      WiFi.begin(ssid, psk); //trying to connect the modem
      break;
    }
    if (WiFi.SSID(i) == ssid2) {
      WiFi.begin(ssid2, psk2); //trying to connect the modem
      break;
    }
  }

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  randomSeed(micros());

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}
