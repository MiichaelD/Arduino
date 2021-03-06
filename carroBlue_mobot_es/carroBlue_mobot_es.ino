/*
  MOBOT BTCar
  Author: Daniel Garrote
  Project: MOBOT
  Project URL: www.mobot.es
*/


int forward = 12; 	// Pin 12 - Forward
int reverse = 11;	// Pin 11 - Reverse
int left = 10;		// Pin 10 - Left
int right = 9;		// Pin 9  - Right
int turbo = 8;		// Pin 8  - Turbo
int short_lights = 7;	// Pin 7  - Short Lights
int long_lights = 6;	// Pin 6  - Long Lights
int back_lights = 5;	// Pin 5  - Back Lights
int reverse_lights = 4;	// Pin 4  - Reverse Lights

char val;  // Variable to receive data from the Serial3 port

void setup() {

  // initialize the digital pins as output
  pinMode(forward, OUTPUT);
  pinMode(reverse, OUTPUT);
  pinMode(left, OUTPUT);
  pinMode(right, OUTPUT);
  pinMode(turbo, OUTPUT);
  pinMode(short_lights, OUTPUT);
  pinMode(long_lights, OUTPUT);
  pinMode(back_lights, OUTPUT);
  pinMode(reverse_lights, OUTPUT);

  Serial3.begin(9600); 	// Start Serial3 communication at 9600bps
}


// Fordward action
void go_forward() {
  digitalWrite(forward, HIGH);
  digitalWrite(turbo, LOW);
  digitalWrite(reverse, LOW);
}

// Stop Forward action
void stop_go_forward() {
  digitalWrite(forward, LOW);
}

// Reverse action
void go_reverse() {
  digitalWrite(reverse, HIGH);
  digitalWrite(forward, LOW);
  digitalWrite(turbo, LOW);
  digitalWrite(reverse_lights, HIGH);
}

// Stop Reverse action
void stop_go_reverse() {
  digitalWrite(reverse, LOW);
  digitalWrite(reverse_lights, LOW);
}

// Turbo action
void go_turbo() {
  digitalWrite(turbo, HIGH);
  digitalWrite(forward, LOW);
  digitalWrite(reverse, LOW);
}

// Stop Turbo action
void stop_go_turbo() {
  digitalWrite(turbo, LOW);
}

// Left action
void go_left() {
  digitalWrite(left, HIGH);
  digitalWrite(right, LOW);
}

// Right action
void go_right() {
  digitalWrite(right, HIGH);
  digitalWrite(left, LOW);
}

// Stop turn action
void stop_turn() {
  digitalWrite(right, LOW);
  digitalWrite(left, LOW);
}

// Stop car
void stop_car() {
  digitalWrite(forward, LOW);
  digitalWrite(reverse, LOW);
  digitalWrite(turbo, LOW);
  digitalWrite(right, LOW);
  digitalWrite(left, LOW);
  digitalWrite(reverse_lights, LOW);
}

// Short Lights ON
void lights_on() {
  digitalWrite(short_lights, HIGH);
  digitalWrite(back_lights, HIGH);
}

// Short Lights OFF
void lights_off() {
  digitalWrite(short_lights, LOW);
  digitalWrite(back_lights, LOW);
}

// Long Lights ON
void long_lights_on() {
  digitalWrite(long_lights, HIGH);
}

// Long Lights OFF
void long_lights_off() {
  digitalWrite(long_lights, LOW);
}

// Reverse Lights ON
void back_lights_on() {
  digitalWrite(reverse_lights, HIGH);
}

// Reverse Lights OFF
void back_lights_off() {
  digitalWrite(reverse_lights, LOW);
}
  
// Read Serial3 port and perform command
void performCommand() {
  if (Serial3.available()) {
    val = Serial3.read();
  }
    if (val == 'f') { // Forward
      go_forward();
    } else if (val == 'z') { // Stop Forward
      stop_go_forward();
    } else if (val == 'b') { // Backward
      go_reverse();
    } else if (val == 'y') { // Stop Backward
      stop_go_reverse();
    } else if (val == 't') { // Turbo
      go_turbo();
    } else if (val == 'x') { // Stop Turbo
      stop_go_turbo();
    } else if (val == 'l') { // Right
      go_right();
    } else if (val == 'r') { // Left
      go_left();
    } else if (val == 'v') { // Stop Turn
      stop_turn();
    } else if (val == 's') { // Stop
      stop_car();
    } else if (val == 'a') { // Short Lights
      lights_on();
    } else if (val == 'c') { // Stop Short Lights
      lights_off();
    } else if (val == 'd') { // Long Lights
      long_lights_on();
    } else if (val == 'e') { // Stop Long Lights
      long_lights_off();
    }
  
}


void loop() {
  performCommand();
}
