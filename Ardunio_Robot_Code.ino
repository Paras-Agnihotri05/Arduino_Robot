#include <Servo.h>  // Include library for servo motor control

// Pin Definitions for IR Sensors and LEDs
const int 
  MID_IR_PIN = 6,     // Mid IR LED pin
  MID_RECEIVER_PIN = 7,  // Mid IR receiver pin
  MID_LED_PIN = A1,   // Mid status LED pin

  LEFT_IR_PIN = 10,   // Left IR LED pin
  LEFT_RECEIVER_PIN = 11,  // Left IR receiver pin
  LEFT_LED_PIN = A2,  // Left status LED pin

  RIGHT_IR_PIN = 2,   // Right IR LED pin
  RIGHT_RECEIVER_PIN = 3,  // Right IR receiver pin
  RIGHT_LED_PIN = A0;  // Right status LED pin

// Servo motor objects for left and right wheel control
Servo servoLeft;
Servo servoRight;

// Variables to store distance measurements
int leftDistance = 0;
int rightDistance = 0;

void setup() {
  // Initialize serial communication for debugging
  Serial.begin(9600);

  // Attach servo motors to their respective control pins
  servoLeft.attach(13);
  servoRight.attach(12);

  // Configure IR sensor and LED pins
  pinMode(LEFT_RECEIVER_PIN, INPUT);
  pinMode(LEFT_IR_PIN, OUTPUT);
  pinMode(LEFT_LED_PIN, OUTPUT);

  pinMode(MID_RECEIVER_PIN, INPUT);
  pinMode(MID_IR_PIN, OUTPUT);
  pinMode(MID_LED_PIN, OUTPUT);

  pinMode(RIGHT_RECEIVER_PIN, INPUT);
  pinMode(RIGHT_IR_PIN, OUTPUT);
  pinMode(RIGHT_LED_PIN, OUTPUT);

  // Delay to allow system stabilization
  delay(5000);
}

void loop() {
  // Measure distance from mid IR sensor
  int midDistance = irDistance(MID_IR_PIN, MID_RECEIVER_PIN);
  Serial.println(midDistance);

  // Default movement is forward
  forward();

  // Check if an obstacle is detected in the middle
  if (midDistance <= 1) {
    // Stop and assess surroundings
    leftDistance = irDistance(LEFT_IR_PIN, LEFT_RECEIVER_PIN);
    rightDistance = irDistance(RIGHT_IR_PIN, RIGHT_RECEIVER_PIN);
    
    digitalWrite(MID_LED_PIN, HIGH);
    stop();
    delay(2000);

    // Decide which way to turn based on obstacle detection
    if (leftDistance <= 3) {
      digitalWrite(LEFT_LED_PIN, HIGH);
      right();  // Turn right if left side is blocked
      delay(50);
    }
    else if (rightDistance <= 3) {
      digitalWrite(RIGHT_LED_PIN, HIGH);
      left();   // Turn left if right side is blocked
      delay(50);
    }
    else {
      right();  // Default turn if both sides seem clear
      delay(550);
    }
  }

  // Reset LED states
  delay(500);
  digitalWrite(LEFT_LED_PIN, LOW);
  digitalWrite(MID_LED_PIN, LOW);
  digitalWrite(RIGHT_LED_PIN, LOW);
}

// Detect IR signal at a specific frequency
int irDetect(int irLedPin, int irReceiverPin, long frequency) {
  tone(irLedPin, frequency);     // Activate IR LED
  delay(1);                      // Short wait
  noTone(irLedPin);              // Deactivate IR LED
  
  int ir = digitalRead(irReceiverPin);  // Read receiver state
  delay(1);                      // Short wait before next check
  
  return ir;  // 0 means detected, 1 means no detection
}

// Measure distance using IR sensors across multiple frequencies
int irDistance(int irLedPin, int irReceiverPin) {
  int distance = 0;
  
  // Check multiple frequencies to improve detection reliability
  for(long f = 38000; f <= 42000; f += 1000) {
    distance += irDetect(irLedPin, irReceiverPin, f);
  }
  
  return distance; 
}

// Movement control functions
void forward() {
  Serial.println("Moving forward");
  servoLeft.writeMicroseconds(1600);
  servoRight.writeMicroseconds(1400);
}

void left() {
  Serial.println("Turning left");
  servoLeft.writeMicroseconds(1400);
  servoRight.writeMicroseconds(1400);
}

void right() {
  Serial.println("Turning right");
  servoLeft.writeMicroseconds(1600);
  servoRight.writeMicroseconds(1600);
}

void reverse() {
  Serial.println("Moving backward");
  servoLeft.writeMicroseconds(1300);
  servoRight.writeMicroseconds(1700);
}

void stop() {
  Serial.println("Stopping");
  servoLeft.writeMicroseconds(1495);
  servoRight.writeMicroseconds(1490);
}