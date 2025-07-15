#include <Servo.h>

// Define servos
Servo servo5; // Left hip
Servo servo2; // Left ankle
Servo servo7; // Right hip
Servo servo3; // Right ankle
Servo servo6; // Right knee
Servo servo4; // Left knee

void setup() {
  // Attach all servos
  servo5.attach(5);
  servo2.attach(2);
  servo7.attach(7);
  servo3.attach(3);
  servo6.attach(6);
  servo4.attach(4);

  // === STEP 0: NEUTRAL ===
  servo5.write(82);   // Left hip
  servo2.write(90);   // Left ankle
  servo7.write(102);  // Right hip
  servo3.write(85);   // Right ankle
  servo6.write(30);   // Right knee
  servo4.write(65);   // Left knee

  delay(1100); // Let robot settle


// === Overview of the code ===
// The movement of the robot has been divided 
// into three main sections. The first is in regards
// to placing the right leg forward. This motion has been
// divided into two sequential and explicit movements.



  // === STEP 1: SWING RIGHT LEG EXTRA FORWARD ===
  servo7.write(130);  // Move right hip extra forward
  servo3.write(100);  // tilt right foot toe down to ensure heel doesnt strike surface
  servo2.write(95);   // Tilt left foot toe slightly up to ensure balance and stability across both legs
  delay(180);         // this delay was found to be most optimal through testing

  // === STEP 2: LOWER RIGHT FOOT ===
  servo7.write(117);  // move right hip back to stable angle for foot placement
  servo3.write(105);  // Flatten right ankle
}

void loop() {
  // Do nothing (one-time move)
}