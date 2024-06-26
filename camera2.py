import serial
import cv2
import numpy as np

# Configuration de la communication série avec l'Arduino
# Remplacez 'COMX' par le port COM de votre Arduino
ser = serial.Serial('COM3', 500000)

# Fonction pour initialiser la caméra


def initialize_camera():
    ser.write(b'I')  # 'I' est la commande pour initialiser la caméra

# Fonction pour démarrer la capture vidéo


def start_capture():
    ser.write(b'S')  # 'S' est la commande pour démarrer la capture

# Fonction pour arrêter la capture vidéo


def end_capture():
    ser.write(b'E')  # 'E' est la commande pour arrêter la capture

# Fonction pour capturer une image


def capture_frame():
    ser.write(b'R')  # 'R' est la commande pour capturer une image
    # La taille de l'image dépend de la configuration de la caméra
    frame_data = ser.read(38400)
    frame = np.frombuffer(frame_data, dtype=np.uint8).reshape(120, 160, 2)
    return frame


# Exemple d'utilisation
if __name__ == "__main__":
    initialize_camera()
    start_capture()

    fourcc = cv2.VideoWriter_fourcc(*'XVID')
    out = cv2.VideoWriter('output.avi', fourcc, 20.0, (160, 120))

    try:
        while True:
            frame = capture_frame()
            out.write(frame)
            cv2.imshow('Frame', frame)

            if cv2.waitKey(1) & 0xFF == ord('q'):
                break

    except KeyboardInterrupt:
        pass

    end_capture()
    out.release()
    cv2.destroyAllWindows()
