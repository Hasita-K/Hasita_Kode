import os
import cv2
import mediapipe as mp
import math

print("RUNNING:", os.path.abspath(__file__))

# ----------------- Load Images -----------------
neutral = cv2.imread(r"C:\Users\Hasita_Kode\Desktop\Python\random\hasitaFutureInGaming\closedMouth\hasitaClosed.jpg")
frown = cv2.imread(r"C:\Users\Hasita_Kode\Desktop\Python\random\hasitaFutureInGaming\closedMouth\hasitaFrown.jpg")
smile = cv2.imread(r"C:\Users\Hasita_Kode\Desktop\Python\random\hasitaFutureInGaming\smileMouth\hasitaSmile.jpg")
anger = cv2.imread(r"C:\Users\Hasita_Kode\Desktop\Python\random\hasitaFutureInGaming\angryMouth\hasitaAngry.jpg")


talking_A = cv2.imread(r"C:\Users\Hasita_Kode\Desktop\Python\random\hasitaFutureInGaming\openMouth\hasitaOpenMouth_A.jpg")
talking_E = cv2.imread(r"C:\Users\Hasita_Kode\Desktop\Python\random\hasitaFutureInGaming\openMouth\hasitaOpenMouth_E.jpg")
talking_O = cv2.imread(r"C:\Users\Hasita_Kode\Desktop\Python\random\hasitaFutureInGaming\openMouth\hasitaOpenMouth_O.jpg")

talking_frames = [talking_A, talking_E, talking_O]

if any(img is None for img in [neutral, frown, smile, *talking_frames]):
    print("Error: One or more images not found")
    exit()

current_img = neutral.copy()

# ----------------- MediaPipe Setup -----------------
mp_face = mp.solutions.face_mesh
mp_draw = mp.solutions.drawing_utils

face_mesh = mp_face.FaceMesh(
    static_image_mode=False,
    max_num_faces=1,
    refine_landmarks=True,
    min_detection_confidence=0.6,
    min_tracking_confidence=0.6
)

# ----------------- Webcam -----------------
cap = cv2.VideoCapture(0)

def dist(p1, p2):
    return math.hypot(p1.x - p2.x, p1.y - p2.y)

frame_count = 0

while True:
    ret, frame = cap.read()
    if not ret:
        break

    frame = cv2.flip(frame, 1)
    rgb = cv2.cvtColor(frame, cv2.COLOR_BGR2RGB)
    result = face_mesh.process(rgb)

    mouth_state = "closed"

    if result.multi_face_landmarks:
        for face_landmarks in result.multi_face_landmarks:
            lm = face_landmarks.landmark

            # ---- Mouth landmarks ----
            upper_lip = lm[13]
            lower_lip = lm[14]
            left_corner = lm[61]
            right_corner = lm[291]

            mouth_open = dist(upper_lip, lower_lip)
            mouth_width = dist(left_corner, right_corner)

            # ---- Mouth State Logic ----
            if mouth_open < 0.015:
                mouth_state = "closed"

            elif mouth_open > 0.035:
                mouth_state = "open"

            elif mouth_width > 0.08:
                mouth_state = "smile"

            else:
                mouth_state = "closed"

            mp_draw.draw_landmarks(
                frame,
                face_landmarks,
                mp_face.FACEMESH_LIPS,
                mp_draw.DrawingSpec(color=(0, 255, 0), thickness=1, circle_radius=1)
            )

    # ----------------- Image Switching -----------------
    frame_count += 1

    if mouth_state == "smile":
        current_img = smile.copy()

    elif mouth_state == "open":
        index = (frame_count // 5) % len(talking_frames)
        current_img = talking_frames[index].copy()

    else:
        current_img = neutral.copy()

    # ----------------- Display -----------------
    cv2.putText(frame, f"Mouth: {mouth_state}", (30, 50),
                cv2.FONT_HERSHEY_SIMPLEX, 1, (0, 255, 0), 2)

    cv2.imshow("Webcam", frame)
    cv2.imshow("Avatar", current_img)

    if cv2.waitKey(1) & 0xFF == 27:
        break

cap.release()
cv2.destroyAllWindows()
