import os
print("RUNNING:", os.path.abspath(__file__))

import cv2 # type: ignore
import mediapipe as mp
#select Python 3.11.9 interpreter for this to work

base = cv2.imread(r"C:\Users\Hasita_Kode\Desktop\Python\random\thinkingMonkey\thinkingMonkey1.jpg")
one = cv2.imread(r"C:\Users\Hasita_Kode\Desktop\Python\random\thinkingMonkey\ahaMonkey.jpg")


if base is None or one is None:
    print("Error: one or more images not found")
    exit()

current_img = base.copy()

#SetUp4MediaPipe
mp_hands = mp.solutions.hands
mp_draw = mp.solutions.drawing_utils

hands = mp_hands.Hands(
    static_image_mode=False,
    max_num_hands=1,
    min_detection_confidence=0.6,
    min_tracking_confidence=0.6
)

#Webcam
cap = cv2.VideoCapture(0)

while True:
    ret, frame = cap.read()
    if not ret:
        break

    frame = cv2.flip(frame, 1)

    rgb = cv2.cvtColor(frame, cv2.COLOR_BGR2RGB)
    hand_result = hands.process(rgb)

    finger_count = 0

    if hand_result.multi_hand_landmarks:
        for hand_landmarks in hand_result.multi_hand_landmarks:
            lm = hand_landmarks.landmark

            tips = [8, 12, 16, 20]
            pips = [6, 10, 14, 18]

            for tip, pip in zip(tips, pips):
                if lm[tip].y < lm[pip].y:
                    finger_count += 1

            mp_draw.draw_landmarks(
                frame,
                hand_landmarks,
                mp_hands.HAND_CONNECTIONS
            )

    #Logic2SwitchImages
    if finger_count == 1:
        current_img = one.copy()
    else:
        current_img = base.copy()

    cv2.imshow("Webcam", frame)
    cv2.imshow("Monkey", current_img)

    if cv2.waitKey(1) & 0xFF == 27:
        break

cap.release()
cv2.destroyAllWindows()
