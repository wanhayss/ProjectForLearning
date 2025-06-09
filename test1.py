import cv2
import mediapipe as mp
import numpy as np
mp_drawing = mp.solutions.drawing_utils
mp_drawing_styles = mp.solutions.drawing_styles
mp_hands = mp.solutions.hands

def count(hand_landmarks):
    count = 0

    if hand_landmarks.landmark[4].x < hand_landmarks.landmark[2].x:
        count += 1
    if hand_landmarks.landmark[8].y < hand_landmarks.landmark[6].y:
        count += 1
    if hand_landmarks.landmark[12].y < hand_landmarks.landmark[10].y:
        count += 1
    if hand_landmarks.landmark[16].y < hand_landmarks.landmark[14].y:
        count += 1
    if hand_landmarks.landmark[20].y < hand_landmarks.landmark[18].y:
        count += 1

    return count
def draw_line(hand_landmarks):
    cond = True
    coordinates = [0, 0]
    if abs(hand_landmarks.landmark[8].y-hand_landmarks.landmark[4].y)<0.08 and abs(hand_landmarks.landmark[8].x-hand_landmarks.landmark[4].x)<0.08:
        cond = True
        print("TRUE")
        coordinates[0] = abs(640*(hand_landmarks.landmark[8].x+hand_landmarks.landmark[4].x)/2)
        coordinates[1] = abs(480*(hand_landmarks.landmark[8].y+hand_landmarks.landmark[4].y)/2)
    else:
        cond = False
        print("FALSE")

    return cond, coordinates

cap = cv2.VideoCapture(0)
with mp_hands.Hands(
    model_complexity = 0,
    min_detection_confidence = 0.5,
    min_tracking_confidence  = 0.5,
    max_num_hands = 1
) as hands:
    canvas = None
    coords = []
    while cap.isOpened():
        success, image = cap.read()
        if not success:
            print("cant open the camera")
            continue
        if canvas is None:
            canvas = np.zeros_like(image)
        # height = cap.get(cv2.CAP_PROP_FRAME_HEIGHT)
        # width = cap.get(cv2.CAP_PROP_FRAME_WIDTH)
        # print(f"h = {height}, w = {width}")
        image = cv2.flip(image, 1)

        #preprocess image
        image.flags.writeable = False
        image = cv2.cvtColor(image, cv2.COLOR_BGR2RGB)
        results = hands.process(image)

        #postprocess image
        image.flags.writeable = True
        image = cv2.cvtColor(image, cv2.COLOR_RGB2BGR)

        if results.multi_hand_landmarks:
            for hand_landmarks in results.multi_hand_landmarks:
                #draw landmarks
                mp_drawing.draw_landmarks(
                    image,
                    hand_landmarks,
                    mp_hands.HAND_CONNECTIONS,
                    mp_drawing_styles.get_default_hand_landmarks_style(),
                    mp_drawing_styles.get_default_hand_connections_style()
                )

                count_results = count(hand_landmarks)
                cond, loc = draw_line(hand_landmarks)
                if loc[0] != 0 and loc[1] != 0 or cond == True:  # Ensure the coordinates are not [0, 0]
                    coords.append(loc)
                elif cond == False:
                    coords.clear()
                
                    
                # cv2.circle(canvas, (int(loc[0]), int(loc[1])), radius=5, color=(0,255,0), thickness=-1)

                if len(coords)>1 and cond == True:
                    for i in range (1, len(coords)):
                        cv2.line(canvas, 
                         (int(coords[i - 1][0]), int(coords[i - 1][1])),  
                         (int(coords[i][0]), int(coords[i][1])),          
                         color=(255, 255, 0),
                         thickness=5)
                
                cv2.putText(image, str(count_results),(300, 50), cv2.FONT_HERSHEY_COMPLEX, 2, (0, 0, 0), 2)
        combined = cv2.addWeighted(image, 1, canvas, 1, 0)
        cv2.imshow("camera", combined)

        if cv2.waitKey(5) & 0xFF == 27:
            break
    cap.release()
    cv2.destroyAllWindows 