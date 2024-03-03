#define red_pin 8
#define green_pin 7

void setup() {
  Serial.begin(9600);
  pinMode(red_pin, OUTPUT);
  delay(2000);
}

void loop() {
  // Check if data is available to read from serial port
  if (Serial.available() > 0) {
    // Read the command sent from the Qt application
    char command = Serial.read();

    // If the received command is '1', turn on the LED
    if (command == '1') {
      digitalWrite(red_pin, HIGH);
    }
    // If the received command is '0', turn off the LED
    else if (command == '0') {
      digitalWrite(red_pin, LOW);
    }
    if (command == '3') {
      digitalWrite(green_pin, HIGH);
    }
    // If the received command is '0', turn off the LED
    else if (command == '2') {
      digitalWrite(green_pin, LOW);
    }
  }
}
