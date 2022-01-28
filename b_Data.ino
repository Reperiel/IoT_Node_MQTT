
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


//------------------------------------------------------------

static WiFiClient espClient;
static PubSubClient client( espClient );
static bool wasConnected;
static bool lastButtonValue[button_nr];
