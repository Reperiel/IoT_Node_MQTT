//Board: LOLIN Wemos D1 pro
#include <WiFiManager.h>  // 2.0.3 alphaWiFiManager
#include <PubSubClient.h> // 2.8.0

#include <WiFiUdp.h>
#include <ArduinoOTA.h>

//----------------------------------------------------------


#if __has_include("secrets.h")
# include "secrets.h"
#else
# include "secrets_template.h"
#endif

#include "io_def.h"
