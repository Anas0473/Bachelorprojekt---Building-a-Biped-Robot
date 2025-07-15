from picamera2 import Picamera2
import cv2
import mediapipe as mp
import time
import math
import serial

# Initialize Picamera2
picam2 = Picamera2()
picam2.preview_configuration.main.size = (640, 480)
picam2.preview_configuration.main.format = "RGB888"
picam2.configure("preview")
picam2.start()

# Initialize Serial Communication with Arduino
arduino = serial.Serial('/dev/ttyUSB0', 9600, timeout=1)
time.sleep(2)  # Allow Arduino time to reset

# Initialize MediaPipe Hands
mp_hands = mp.solutions.hands
hands = mp_hands.Hands()
mp_draw = mp.solutions.drawing_utils

# FPS calculation
pTime = 0

# Calibration values
KNOWN_DISTANCE = 30  # cm
KNOWN_WIDTH = 8      # average hand width in cm
FOCAL_LENGTH = 600

# Helper function to calculate distance
def calculate_distance(knownWidth, focalLength, perWidth):
    return (knownWidth * focalLength) / perWidth

while True:
    frame = picam2.capture_array()

    # Convert to RGB
    img_rgb = cv2.cvtColor(frame, cv2.COLOR_BGR2RGB)
    results = hands.process(img_rgb)

    distance_cm = None

    # Draw hand landmarks and calculate distance
    if results.multi_hand_landmarks:
        for handLms in results.multi_hand_landmarks:
            mp_draw.draw_landmarks(frame, handLms, mp_hands.HAND_CONNECTIONS)

            h, w, _ = frame.shape
            lmList = []
            for lm in handLms.landmark:
                lmList.append((int(lm.x * w), int(lm.y * h)))

            if len(lmList) >= 18:
                x1, y1 = lmList[5]   # Base of index finger
                x2, y2 = lmList[17]  # Base of pinky finger

                pixel_width = math.hypot(x2 - x1, y2 - y1)

                if pixel_width != 0:
                    distance_cm = calculate_distance(KNOWN_WIDTH, FOCAL_LENGTH, pixel_width)

    # FPS calculation
    cTime = time.time()
    fps = 1 / (cTime - pTime) if (cTime - pTime) != 0 else 0
    pTime = cTime

    # Draw text
    cv2.putText(frame, f'FPS: {int(fps)}', (10, 30),
                cv2.FONT_HERSHEY_SIMPLEX, 1, (0, 255, 0), 2)

    if distance_cm is not None:
        cv2.putText(frame, f'Distance: {int(distance_cm)} cm', (10, 70),
                    cv2.FONT_HERSHEY_SIMPLEX, 1, (255, 0, 0), 2)

        # Send command to Arduino if distance is greater than 40 cm
        if distance_cm > 40:
            arduino.write(b'M')
            print("Move command sent")

    # Show frame
    cv2.imshow("Hand Detection", frame)

    if cv2.waitKey(1) & 0xFF == ord('q'):
        break

# Cleanup
cv2.destroyAllWindows()
picam2.close()
arduino.close()