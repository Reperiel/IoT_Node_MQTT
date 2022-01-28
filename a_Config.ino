static bool SerialDebug = true; // not const, auto-disable on use of RX/TX

static const char MessageAddress = 'B';
static const char TopicSend[] = "IoT-FromNode";
static const char TopicReceive[] = "IoT-ToNode";

static const Button buttons[] = {
 //{ TX, '1' },
 //{ RX, '2' },
 { D1, '3' },
 { D2, '4' },
 { D3, '5' },
};
static const int button_nr = sizeof(buttons)/sizeof(buttons[0]);

static const Switch switches[] = {
 { D0, '1', true },
 { D5, '2' },
 { D6, '3' },
 { D7, '4' },
 { D4, '5' },
};
static const int switch_nr = sizeof(switches)/sizeof(switches[0]);
