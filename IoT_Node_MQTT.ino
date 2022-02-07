//Board: LOLIN Wemos D1 pro

// required additional libraries:
// WiFiManager; https://github.com/tzapu/WiFiManager.git
// PubSubClient; https://github.com/knolleary/pubsubclient.git

#include <WiFiManager.h>
#include <PubSubClient.h>

#include <WiFiUdp.h>
#include <ArduinoOTA.h>

//----------------------------------------------------------


#if __has_include("secrets.h")
# include "secrets.h"
#else
# include "secrets_template.h"
#endif

#include "io_def.h"
