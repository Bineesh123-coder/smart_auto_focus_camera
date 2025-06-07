🔍 Smart AutoFocus Camera System 🎥
A powerful real-time C++ camera system using OpenCV and YOLOv4-tiny, featuring:

⚙️ Autofocus

🔎 Digital Zoom

↔️ Pan and Tilt

🧠 Face Detection

📦 Object Detection

🎮 Keyboard-Controlled UI

Designed for surveillance, smart robotics, and intelligent vision-based applications. Built on C++, tested on Debian 12.

🚀 Features
✅ Real-time video processing from webcam or camera module

🔍 Face detection using Haar cascades

🛡️ Object detection using YOLOv4-tiny

🕹️ Keyboard control for pan, tilt, zoom, and detection toggling

🔄 Reset function for default view

📦 Easy to extend for cloud integration or embedded deployment

🎮 Controls
Key	Action
i	Zoom In
o	Zoom Out
a	Pan Left
d	Pan Right
w	Tilt Up
z	Tilt Down
r	Reset View
f	Enable Face Detection
b	Enable Object Detection
ESC or q	Exit

🛠️ Requirements
OpenCV 4.x with DNN module

C++17 or later

YOLOv4-tiny model files:

yolov4-tiny.cfg

yolov4-tiny.weights

Haar cascade file:

haarcascade_frontalface_default.xml

coco.names file with class labels

Install OpenCV on Debian:
bash
Copy
Edit
sudo apt update
sudo apt install libopencv-dev python3-opencv
📁 Project Structure
css
Copy
Edit
smart_auto_focus_camera/
├── src/
│   ├── main.cpp
│   ├── autofocus.h
│   ├── object_detection.h
├── yolo/
│   ├── yolov4-tiny.cfg
│   ├── yolov4-tiny.weights
│   └── coco.names
├── haarcascades/
│   └── haarcascade_frontalface_default.xml
├── makefile
├── README.md
└── build/

⚙️ Build & Run
1. Clone the repo:
bash
Copy
Edit
git clone https://github.com/yourusername/SmartAutoFocusCamera.git
cd SmartAutoFocusCamera
2. Build using CMake:
bash
Copy
Edit
mkdir build && cd build
cmake ..
make
3. Run:
bash
Copy
Edit
./SmartAutoFocusCamera
🧠 Sample Output
Displays a live camera feed with face and object bounding boxes, real-time pan/tilt/zoom control, and keyboard UI.


📦 Object Detection
Uses YOLOv4-tiny for real-time performance

Supports 80 COCO classes (person, car, dog, etc.)

Customize confidence and NMS thresholds

🧑‍💻 Contributors
Your Name - Developer, Vision System Engineer

📜 License
This project is licensed under the MIT License.
