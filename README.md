# Arduino_Robot
## Overview
This Arduino project implements an autonomous robot capable of navigating and avoiding obstacles using infrared (IR) sensors. The robot can detect obstacles in front and on its sides, making real-time navigation decisions to prevent collisions.

## Hardware Requirements
- Arduino Board (e.g., Arduino Uno)
- 2x Servo Motors
- 3x IR Transmitter/Receiver Pairs
- 3x Status LEDs
- Breadboard and Jumper Wires
- Robot Chassis

## Pin Configuration
- Mid IR Sensor:
  - IR LED Pin: 6
  - IR Receiver Pin: 7
  - Status LED Pin: A1

- Left IR Sensor:
  - IR LED Pin: 10
  - IR Receiver Pin: 11
  - Status LED Pin: A2

- Right IR Sensor:
  - IR LED Pin: 2
  - IR Receiver Pin: 3
  - Status LED Pin: A0

- Servo Motors:
  - Left Servo: Pin 13
  - Right Servo: Pin 12

## Functionality
The robot uses three IR sensor pairs to detect obstacles:
1. Mid sensor for forward obstacle detection
2. Left sensor for left-side obstacle detection
3. Right sensor for right-side obstacle detection

Navigation Logic:
- Default movement is forward
- When mid sensor detects an obstacle (distance <= 1):
  - Stop
  - Check left and right sensors
  - Turn right or left based on sensor readings
  - If both sides are blocked, perform a default right turn

## Dependencies
- Arduino Servo Library

## Setup and Installation
1. Connect hardware according to pin configuration
2. Install Arduino IDE
3. Install Servo library via Library Manager
4. Upload the sketch to your Arduino board

## Customization
- Adjust `irDistance()` thresholds to fine-tune obstacle detection
- Modify servo microsecond values in movement functions to adjust robot speed and turning radius

## Troubleshooting
- Ensure IR sensors are clean and properly aligned
- Check servo motor connections
- Verify battery/power supply

## Safety Notes
- Test in a clear, open area
- Supervise robot during initial tests
- Use on flat surfaces

## Future Improvements
- Add more sophisticated navigation algorithms
- Implement PID control for smoother movements
- Add additional sensors (ultrasonic, accelerometer)

