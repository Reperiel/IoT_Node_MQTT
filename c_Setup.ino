void
publish( const char *msg )
{
  if (SerialDebug) {
    Serial.print( "Publish message: " );
    Serial.println( msg );
  }
  client.publish( TopicSend, msg );
}

void
setup() {
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

void
setup_wifi() {
  delay(10);
  // We start by connecting to a WiFi network
  if (SerialDebug) {
    Serial.println();
    Serial.print( "MAC is " );
    Serial.println( WiFi.macAddress() );
    Serial.print( "Connecting to " );
    Serial.println( ssid );
  }

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

  if (SerialDebug) {
    Serial.println( "" );
    Serial.println( "WiFi connected" );
    Serial.println( "IP address: " );
    Serial.println( WiFi.localIP() );
  }

  ArduinoOTA.onStart( []() {
      Serial.println( "Start Updating" );
    }
  );
  ArduinoOTA.onEnd( []() {
      Serial.println( "\nUpdate Finished" );
    }
  );
  ArduinoOTA.onProgress( []( unsigned int progress, unsigned int total ) {
      Serial.printf( "\nProgress: %u%%\r", (progress / (total / 100)) );
    }
  );
  ArduinoOTA.onError( [](ota_error_t error) {
      Serial.printf("Error[%u]: ", error);
      if (error == OTA_AUTH_ERROR)
        Serial.println("Auth Failed");
      else if (error == OTA_BEGIN_ERROR)
        Serial.println("Begin Failed");
      else if (error == OTA_CONNECT_ERROR)
        Serial.println("Connect Failed");
      else if (error == OTA_RECEIVE_ERROR)
        Serial.println("Receive Failed");
      else if (error == OTA_END_ERROR)
        Serial.println("End Failed");
    }
  );

  ArduinoOTA.begin();
  if (SerialDebug) {
    Serial.println( "" );
    Serial.println( "OTA started" );
  }
}
