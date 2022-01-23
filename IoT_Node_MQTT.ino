//Board: LOLIN Wemos D1 pro
#include <WiFiManager.h>  // 2.0.3 alphaWiFiManager
#include <PubSubClient.h> // 2.8.0

//-------------------------------------------------------------------------------------------------------------------------

#include "conf.h"

#if __has_include("secrets.h")
# include "secrets.h"
#else
# include "secrets_template.h"
#endif

//Der DNS oder die IP des Servers, auf dem der MQTT läuft
static const char mqtt_server[] = MQTT_SERVER;

static const char ssid[] = WLAN_SSID;
static const char psk[] = WLAN_PSK;
#ifndef WLAN_SSID2
#define WLAN_SSID2 ""
#define WLAN_PSK2 ""
#endif
static const char ssid2[] = WLAN_SSID2;
static const char psk2[] = WLAN_PSK2;


//--------------------------------------------------------------------------------------------------------------------------

static WiFiClient espClient;
static PubSubClient client(espClient);
static bool lastButtonValue[6];

void
mqttCallback( char *topic, byte *payload, unsigned int length )
{
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();

  if (length < 3)
    return;

  char adr = payload[0];
  if (adr != MessageAddress)
    return;

  char sw = payload[1];
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
}

void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Create a random client ID
    String clientId = "ESP8266Client-";
    const char a[] = { MessageAddress, 0 };
    clientId += a;
    // Attempt to connect
    if (client.connect( clientId.c_str()) ) {
      Serial.println("connected");
      // Once connected, publish an announcement...
      client.publish( TopicSend, "ESP-Start" );
      // ... and resubscribe
      client.subscribe( TopicReceive );
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(4000+random(2000));
    }
  }
}


void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  for (int i=0; i < button_nr; ++i) {
    checkButton( i );
  }
}

void
checkButton( int i )
{
  int pin = buttons[i].pin;
  if (!digitalRead(pin)) {
    if (!lastButtonValue[pin]) {
      lastButtonValue[pin] = true;
      char msg[] = { MessageAddress, buttons[i].address, '0', 0 };
      Serial.print("Publish message: ");
      Serial.println(msg);
      client.publish( TopicSend, msg );
      // delay(50);
    }
  }
  else {
    lastButtonValue[pin] = false;
    // delay(20);
  }
}
