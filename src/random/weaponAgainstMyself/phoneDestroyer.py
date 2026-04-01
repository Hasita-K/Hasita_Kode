import os
import random
import cv2
from ultralytics import YOLO
from playsound import playsound
import threading

print("RUNNING:", os.path.abspath(__file__))

#all the jumpscares images
jump_images = [
    cv2.imread(r"C:\Users\Hasita_Kode\Desktop\Python\random\weaponAgainstMyself\scare1.jpg"),
    cv2.imread(r"C:\Users\Hasita_Kode\Desktop\Python\random\weaponAgainstMyself\scare2.jpg"),
    cv2.imread(r"C:\Users\Hasita_Kode\Desktop\Python\random\weaponAgainstMyself\scare3.jpg")
]

sound_file = r"C:\Users\Hasita_Kode\Desktop\Python\random\weaponAgainstMyself\scary_sound.mp3"

#if any of the images don't work then display an error message
for img in jump_images:
    if img is None:
        print("Error loading jumpscare images")
        exit()


current_img = jump_images[0].copy()


# Load YOLO model
model = YOLO("yolov8n.pt")   # downloads automatically


# Webcam
cap = cv2.VideoCapture(0)

#okay if I've seen the last frame then don't repeat the audio
phone_seen_last_frame = False

#My function to play the actual sound from FNAF
def play_sound():
    playsound(sound_file)

#have an infinite loop that will capture the frame and detect the object AND play the audio
while True:

    #get the webcam frame
    ret, frame = cap.read()
    if not ret:
        break

    #mirror the image to make it look like how real life looks 
    frame = cv2.flip(frame, 1)

    #run the YOLO AI model to analyze each frame
    results = model(frame, verbose=False)

    #after detection reset the detection flag I made
    phone_detected = False

    #loop through all the results and the boxes which have the object type 
    for r in results:
        for box in r.boxes:

            #this will identify the object type and make the confidence higher than 50 and lower than 72 lowkey 
            class_id = int(box.cls[0])
            label = model.names[class_id]
            confidence = float(box.conf[0])

            #check if the object is a phone and if it is then put a box around it
            if label == "cell phone" and confidence > 0.65:

            

                phone_detected = True

                x1, y1, x2, y2 = map(int, box.xyxy[0])

                cv2.rectangle(frame, (x1,y1), (x2,y2), (0,0,255), 2)

                cv2.putText(
                    frame,
                    "PHONE DETECTED", #make the name highkey scary asf
                    (x1, y1-10),
                    cv2.FONT_HERSHEY_SIMPLEX,
                    0.6,
                    (0,0,255),
                    2
                )

    # trigger jumpscare once per detection
    if phone_detected and not phone_seen_last_frame:

        #choose one of the random scary image
        current_img = random.choice(jump_images).copy()

        threading.Thread(target=play_sound).start()

    phone_seen_last_frame = phone_detected

    #show the windows with the webcam of yourself and the jumpscare image
    cv2.imshow("Webcam", frame)
    cv2.imshow("JUMPSCARE", current_img)

    #exit lol
    if cv2.waitKey(1) & 0xFF == 27:
        break


#turn off everything
cap.release()
cv2.destroyAllWindows()