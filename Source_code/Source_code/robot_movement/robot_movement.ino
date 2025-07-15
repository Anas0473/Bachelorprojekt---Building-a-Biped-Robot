#include <Servo.h>

// Define servos
Servo servo5; // Left hip
Servo servo2; // Left ankle
Servo servo7; // Right hip
Servo servo3; // Right ankle
Servo servo6; // Right knee
Servo servo4; // Left knee

bool isMoving = false;

// Smooth movement function
void smoothMove(Servo &servo, int startAngle, int endAngle, int delayTime) {
  int step = (endAngle > startAngle) ? 1 : -1;
  for (int angle = startAngle; angle != endAngle; angle += step) {
    servo.write(angle);
    delay(delayTime);
  }
  servo.write(endAngle); // Final position
}

void setup() {
  // Attach servos
  servo5.attach(5);
  servo2.attach(2);
  servo7.attach(7);
  servo3.attach(3);
  servo6.attach(6);
  servo4.attach(4);

  // Set initial neutral pose
  servo5.write(82);   // Left hip
  servo2.write(90);   // Left ankle
  servo7.write(102);  // Right hip
  servo3.write(85);   // Right ankle
  servo6.write(30);   // Right knee
  servo4.write(65);   // Left knee

  Serial.begin(9600); // For Raspberry Pi communication
}

void loop() {
  if (Serial.available()) {
    char command = Serial.read();
    if (command == 'M' && !isMoving) {
      moveSequence();
    }
  }
}

void moveSequence() {
  isMoving = true;

  // === Sequence 1 ===
  servo7.write(130);
  servo3.write(100);
  servo2.write(95);
  delay(180);
  servo7.write(117);
  servo3.write(105);

  delay(600);

  // === Sequence 2 ===
  smoothMove(servo2, 95, 105, 15);
  smoothMove(servo3, 105, 85, 15);

  delay(600);

  // === Sequence 3 ===
  servo3.write(75);
  servo5.write(70);
  servo2.write(100);
  delay(180);

  delay(600);

  // === Sequence 4 ===
  smoothMove(servo7, 117, 102, 15);
  smoothMove(servo3, 75, 85, 15);
  smoothMove(servo5, 70, 82, 15);
  smoothMove(servo2, 100, 90, 15);

  isMoving = false;
}
