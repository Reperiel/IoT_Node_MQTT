const char MessageAddress = 'B';
const char TopicSend[] = "IoT-FromWemos";
const char TopicReceive[] = "IoT-ToWemos";

const Button buttons[] = {
 { TX, '1' },
 { RX, '2' },
 { D1, '3' },
 { D2, '4' },
 { D3, '5' },
};
const int button_nr = sizeof(buttons)/sizeof(buttons[0]);

const Switch switches[] = {
 { D0, '1', true },
 { D5, '2' },
 { D6, '3' },
 { D7, '4' },
 { D4, '5' },
};
const int switch_nr = sizeof(switches)/sizeof(switches[0]);
