struct Button {
  int pin;
  char address;
};

struct Switch {
  int pin;
  char address;
  bool invert = false;
};
