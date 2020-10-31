///Sonar pin
#define TRIG_PIN   4
#define ECHO_PIN   3
#define BAUD_RATE  115200
#define READ_DELAY 990
#define LED 13

// CONVERSION CONSTANTS
#define MS_PER_CM  29.031
#define MS_PER_M   2903.1
#define MS_PER_IN  74.746

//print the distance when variance is more than 5 cm
#define THRESHOLD  3 * MS_PER_CM * 2

double tempMS, lastMS;

const int kMicroSec = 0, kCentiMeters = 1, kMeters = 2, kInches = 3;

void setup() {
  tempMS = 0;
  lastMS = 0;
  Serial.begin(BAUD_RATE);
  pinMode(TRIG_PIN, OUTPUT); // Switch signalpin to output
  pinMode(ECHO_PIN, INPUT); // Switch signalpin to input
  pinMode(LED, OUTPUT);   // SET LED pin to output.
  Serial.println("Entering to repeater mode, type 'z' to exit or 'r'to reset.");
}

/* Send low-high-low pulse to activate the trigger pulse of the sensor */
void triggerSignal() {
  digitalWrite(TRIG_PIN, LOW); // Send low pulse
  delayMicroseconds(2); // Wait for 2 microseconds
  digitalWrite(TRIG_PIN, HIGH); // Send high pulse
  delayMicroseconds(10); // Wait for 10 microseconds
  digitalWrite(TRIG_PIN, LOW); // Holdoff
}

double msToInches(double microseconds) {
  // According to Parallax's datasheet for the PING))), there are
  // 73.746 microseconds per inch (i.e. sound travels at 1130 feet per
  // second).  This gives the distance travelled by the ping, outbound
  // and return, so we divide by 2 to get the distance of the obstacle.
  // See: http://www.parallax.com/dl/docs/prod/acc/28015-PING-v1.3.pdf
  return microseconds /= (MS_PER_IN * 2);
}

double msToCm(double microseconds) {
  // The speed of sound is 340 m/s or 29.031 microseconds per centimeter.
  // The ping travels out and back, so to find the distance of the
  // object we take half of the distance travelled.
  return microseconds /= (MS_PER_CM * 2);
}

/* Derived convertions*/
double msToM(double microseconds) {
  return microseconds /= (MS_PER_M * 2);
}

double getSonarDistance(int type) {
  double  timecount = 0; // Echo counter
  triggerSignal();
  // waits to assigned pin to be HIGH, then counts microsecounds until pin was LOW
  timecount = pulseIn(ECHO_PIN, HIGH);
  switch (type) {
    case kMicroSec:   return timecount;
    case kCentiMeters:   return msToCm(timecount);
    case kMeters:        return msToM(timecount);
    case kInches:  return msToInches(timecount);
    default: return timecount;
  }
  return timecount;
}

void printDistances(double delayMs) {
  //  Serial.print("microseconds: ");
  //  Serial.println(delayMs);
  Serial.print("Centimeters: ");
  Serial.println(msToCm(delayMs));
  Serial.print("Inches: ");
  Serial.println(msToInches(delayMs));
  Serial.println();
}

void(* resetFunc) (void) = 0; //declare reset function at address 0

void processSerialInput() {
  if (Serial.available()) {
    String str = Serial.readString();
    boolean exit = str == "z";
    boolean reset = str == "r";
    Serial.println(str);  // Sends input back -- as ACK
    if (reset) {
      Serial.println("Reseting ...");
      resetFunc();
    }
    while (exit);
  }
}

void loop() {
  digitalWrite(LED, LOW);
  tempMS = getSonarDistance(kMicroSec); //get distance in ms
  double diff = abs(tempMS - lastMS);
  if ( diff > THRESHOLD ) {
    Serial.print("Difference: ");
    Serial.println(diff / MS_PER_CM / 2);
    printDistances(tempMS);
    lastMS = tempMS;
    digitalWrite(LED, HIGH);
  }
  processSerialInput();
  delay(READ_DELAY);
}
