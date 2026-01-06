import os
import cv2 # type: ignore
import mediapipe as mp
import math
#select Python 3.11.9 interpreter for this to work

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

if any(img is None for img in [neutral, frown, smile, anger, *talking_frames]):
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

    mouth_state = "neutral"

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

            # Corner vertical position relative to center lip
            corner_avg_y = (left_corner.y + right_corner.y) / 2
            lip_center_y = (upper_lip.y + lower_lip.y) / 2

            # ---- Mouth Measurements ----
            mouth_open = dist(upper_lip, lower_lip)
            mouth_width = dist(left_corner, right_corner)

            # How slanted the mouth is
            corner_slope = ((left_corner.y + right_corner.y) / 2) - ((upper_lip.y + lower_lip.y) / 2)

            # ---- Mouth State Logic (FIXED) ----
            if mouth_open > 0.04:
                mouth_state = "open"

            elif mouth_width > 0.085 and corner_slope < -0.002:
                mouth_state = "smile"

            elif corner_slope > 0.003:
                if mouth_open < 0.018:
                    mouth_state = "angry"
                else:
                    mouth_state = "frown"

            else:
                mouth_state = "neutral"


    # ----------------- Image Switching -----------------
    frame_count += 1

    if mouth_state == "smile":
        current_img = smile.copy()

    elif mouth_state == "open":
        index = (frame_count // 5) % len(talking_frames)
        current_img = talking_frames[index].copy()

    elif mouth_state == "frown":
        current_img = frown.copy()

    elif mouth_state == "angry":
        current_img = anger.copy()

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
