import cv2
import websocket
import base64
import time

esp32_ws_url = "ws://192.168.18.38/ws"

cap = cv2.VideoCapture(0)
cap.set(cv2.CAP_PROP_FRAME_WIDTH, 320)
cap.set(cv2.CAP_PROP_FRAME_HEIGHT, 240)

ws = websocket.WebSocket()
ws.connect(esp32_ws_url)

try:
    while True:
        ret, frame = cap.read()
        if not ret:
            print("Failed to grab frame")
            break

        # Convert to grayscale
        frame = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)
        
        # Display the frame
        cv2.imshow('Frame', frame)
        cv2.waitKey(1)
        
        # Encode frame as JPEG with lower quality
        _, buffer = cv2.imencode('.jpg', frame, [cv2.IMWRITE_JPEG_QUALITY, 10])
        jpg_as_text = base64.b64encode(buffer).decode('utf-8')

        try:
            ws.send(jpg_as_text)
            print(f"Sent frame of size {len(jpg_as_text)} bytes")
        except websocket.WebSocketConnectionClosedException:
            print("WebSocket connection closed. Trying to reconnect...")
            ws.connect(esp32_ws_url)

        time.sleep(1)  # Send 2 frames per second

except KeyboardInterrupt:
    print("Stopped by user")
finally:
    cap.release()
    cv2.destroyAllWindows()
    ws.close()