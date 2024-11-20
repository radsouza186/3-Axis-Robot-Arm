int EN_PIN = 4;     // Define the enable signal port
int STP_PIN = 3;    // Define the step signal port
int DIR_PIN = 2;    // Define the direction signal port
int currentDelay = 450;  // Default delay

void setup() {
  pinMode(EN_PIN, OUTPUT);    // Set the enable signal port to output mode
  pinMode(STP_PIN, OUTPUT);   // Set the step signal port to output mode
  pinMode(DIR_PIN, OUTPUT);   // Set the direction signal port to output mode
  digitalWrite(EN_PIN, HIGH); // Disable motor initially
  
  Serial.begin(19200);  // Start serial communication
}

void loop() {
  if (Serial.available() > 0) {
    String input = Serial.readStringUntil('\n');  // Read incoming command

    if (input.startsWith("F")) {  // Forward command
      int delayVal = input.substring(1).toInt();
      currentDelay = delayVal;
      digitalWrite(DIR_PIN, LOW);  // Set direction forward
      digitalWrite(EN_PIN, LOW);   // Enable motor
    } 
    else if (input.startsWith("R")) {  // Reverse command
      int delayVal = input.substring(1).toInt();
      currentDelay = delayVal;
      digitalWrite(DIR_PIN, HIGH);  // Set direction reverse
      digitalWrite(EN_PIN, LOW);    // Enable motor
    } 
    else if (input == "S") {  // Stop command
      digitalWrite(EN_PIN, HIGH);  // Disable motor
    }
  }

  // Move motor if enabled
  if (digitalRead(EN_PIN) == LOW) {
    digitalWrite(STP_PIN, HIGH);    // Step pulse high
    delayMicroseconds(currentDelay);  // Use dynamic delay for speed
    digitalWrite(STP_PIN, LOW);     // Step pulse low
    delayMicroseconds(currentDelay);
  }
}


