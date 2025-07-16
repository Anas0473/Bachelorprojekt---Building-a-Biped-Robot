#include <Servo.h>

// Define servos
Servo servo5; // Left hip
Servo servo2; // Left ankle
Servo servo7; // Right hip
Servo servo3; // Right ankle
Servo servo6; // Right knee
Servo servo4; // Left knee

// Smooth movement function
void smoothMove(Servo &servo, int startAngle, int endAngle, int delayTime) {
  int step = (endAngle > startAngle) ? 1 : -1;
  for (int angle = startAngle; angle != endAngle; angle += step) {
    servo.write(angle);
    delay(delayTime);
  }
  servo.write(endAngle); // Final write
}

void setup() {
  // Attach all servos
  servo5.attach(5);  // Left hip
  servo2.attach(2);  // Left ankle
  servo7.attach(7);  // Right hip
  servo3.attach(3);  // Right ankle
  servo6.attach(6);  // Right knee
  servo4.attach(4);  // Left knee

  // === STEP 0: Right leg forward (initial pose) ===
  servo5.write(70);   // Left hip
  servo2.write(100);  // Left ankle
  servo7.write(117);  // Right hip
  servo3.write(75);   // Right ankle
  servo6.write(30);   // Right knee
  servo4.write(65);   // Left knee

  delay(1100); // Let robot settle

  // === STEP 1: Smooth transition to new pose ===
  smoothMove(servo7, 117, 102, 15);  // Right hip
  smoothMove(servo3, 75, 85, 15);    // Right ankle
  smoothMove(servo5, 70, 82, 15);    // Left hip
  smoothMove(servo2, 100, 90, 15);   // Left ankle
  // Knees stay the same: servo6 (30), servo4 (65)
}

void loop() {
  // Do nothing
}