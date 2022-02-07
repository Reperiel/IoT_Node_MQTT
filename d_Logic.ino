
void
mqttCallback( char *topic, byte *payload, unsigned int length )
{
  if (SerialDebug) {
    Serial.print( "Message arrived [" );
    Serial.print( topic );
    Serial.print( "] " );
    for (int i = 0; i < length; i++) {
      Serial.print( (char)payload[i] );
    }
    Serial.println();
  }

  if (length < 2)
    return;

  char adr = payload[0];
  if (adr != MessageAddress)
    return;

  char sw = payload[1];
  if (sw == 'P') { // ping
    if (SerialDebug)
      Serial.println( "got PING" );
    char msg[] = { MessageAddress, 'p', 0 };
    publish( msg );
  }

  if (length < 3)
    return;

  char cmd = payload[2];

  for (int i=0; i < switch_nr; ++i) {
    if (switches[i].address == sw) {
      if (cmd == 'A' || cmd == 'E') {
        bool on = (cmd == 'A');
        auto mark = (on != switches[i].invert) ? HIGH : LOW;
        digitalWrite( switches[i].pin, mark );
      }
    }
  }

  if (ConfirmAction) {
    char msg[] = { MessageAddress, sw, char(tolower(cmd)), 0 };
    publish( msg );
  }
}

void
mqttReconnect()
{
  // Loop until we're reconnected
  while (!client.connected()) {
    if (SerialDebug)
      Serial.print( "Attempting MQTT connection..." );
    // Create a client ID
    String clientId = "IoT-Client-";
    const char a[] = { MessageAddress, 0 };
    clientId += a;
    // Attempt to connect
    if (client.connect( clientId.c_str() ) ) {
      if (SerialDebug)
        Serial.println( "connected" );
      // Once connected, publish an announcement...
      char msg[] = { MessageAddress, (wasConnected ? 'R' : 'B') ,0 };
      publish( msg );
      // ... and resubscribe
      client.subscribe( TopicReceive );
      wasConnected = true;
    }
    else {
      if (SerialDebug) {
        Serial.print( "failed, rc=" );
        Serial.print( client.state() );
        Serial.println( " try again in 5 seconds" );
      }
      // Wait approximately 5 seconds before retrying
      delay( 4000 + random(2000) );
    }
  }
}


void
checkButton( int i )
{
  int pin = buttons[i].pin;
  if (!digitalRead( pin )) {
    if (!lastButtonValue[pin]) {
      lastButtonValue[pin] = true;
      char msg[] = { MessageAddress, buttons[i].address, '0', 0 };
      publish( msg );
      // delay(50);
    }
  }
  else {
    lastButtonValue[pin] = false;
    // delay(20);
  }
}

void
checkButtons()
{
  for (int i=0; i < button_nr; ++i) {
    checkButton( i );
  }
}

void
loop()
{
  if (!client.connected()) {
    mqttReconnect();
  }
  client.loop();
  checkButtons();
}
