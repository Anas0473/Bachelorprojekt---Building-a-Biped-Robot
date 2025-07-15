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
  servo.write(endAngle); // Ensure it ends exactly at target
}

void setup() {
  // Attach all servos
  servo5.attach(5);
  servo2.attach(2);
  servo7.attach(7);
  servo3.attach(3);
  servo6.attach(6);
  servo4.attach(4);

  // === STEP 0: right leg forward (initial pose) ===
  servo5.write(82);   // Left hip
  servo2.write(105);   // Left ankle
  servo7.write(117);  // Right hip
  servo3.write(85);  // Right ankle
  servo6.write(30);   // Right knee
  servo4.write(65);   // Left knee

  delay(1100); // Let robot settle

  servo3.write(75);
  servo5.write(70);
  servo2.write(100);
  delay(180);

  
}

void loop() {
  // Do nothing (one-time move)
}