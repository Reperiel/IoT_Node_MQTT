
void setup() {
  for (int i = 0; i < button_nr; i++) {
    pinMode( buttons[i].pin, INPUT_PULLUP );
    if (buttons[i].pin == RX || buttons[i].pin == TX)
      SerialDebug = false;
  }
  for (int i = 0; i < switch_nr; i++) {
    pinMode( switches[i].pin, OUTPUT );
    digitalWrite( switches[i].pin, switches[i].invert ? HIGH : LOW );
  }

  if (SerialDebug)
    Serial.begin(115200); // Wegen Nutzung der Pins 1 + 3 (RX/TX) darf die Schnittstelle im Betrieb nicht geöffnet werden
  setup_wifi();
  client.setServer( mqtt_server, 1883 );
  client.setCallback( mqttCallback );
}

void setup_wifi() {

  delay(10);
  // We start by connecting to a WiFi network
  if (SerialDebug) {
    Serial.println();
    Serial.print( "Connecting to " );
    Serial.println( ssid );
  }

  // WiFi.begin(ssid, password);

  // scan Wifi
  int n = WiFi.scanNetworks();
  for (int i = 0; i < n; ++i) {
    if (WiFi.SSID(i) == ssid ) {
      WiFi.begin( ssid, psk ); //trying to connect the modem
      break;
    }
    if (WiFi.SSID(i) == ssid2) {
      WiFi.begin( ssid2, psk2 ); //trying to connect the modem
      break;
    }
  }

  randomSeed( micros() );

  while (WiFi.status() != WL_CONNECTED) {
    delay( 400 + random(200) );
    if (SerialDebug) {
      Serial.print(".");
    }
  }

  randomSeed( micros() );

  if (SerialDebug) {
    Serial.println( "" );
    Serial.println( "WiFi connected" );
    Serial.println( "IP address: " );
    Serial.println( WiFi.localIP() );
  }
}
