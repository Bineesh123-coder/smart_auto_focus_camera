#include "autofocus.h"
#include <iostream>

int main() {
    try {
        AutoFocusCamera camera(0);

        std::cout << "Controls:\n"
                  << "i: Zoom In\n"
                  << "o: Zoom Out\n"
                  << "w: Tilt Up\n"
                  << "z: Tilt Down\n"
                  << "a: Pan Left\n"
                  << "d: Pan Right\n"
                  << "ESC: Exit\n"
                  << "r: Reset\n"
                  << "f: Face detection enabled\n";
        camera.loadFaceCascade("haarcascade_frontalface_default.xml");
        while (true) {
            cv::Mat frame = camera.captureFrame();
            cv::Mat view = camera.applyZoomPanTilt(frame);

            if(camera.face_detection)
            {
               
                // Convert to grayscale for detection
                cv::Mat gray;
                cv::cvtColor(view, gray, cv::COLOR_BGR2GRAY);
                cv::equalizeHist(gray, gray); // Improve contrast

                // Detect faces
                std::vector<cv::Rect> faces = camera.detectFaces(gray);

                // Draw face rectangles
                for (const auto& face : faces) {
                    cv::rectangle(view, face, cv::Scalar(0, 255, 0), 2);
                }
            }

            

            cv::imshow("Smart Camera", view);

            char key = (char)cv::waitKey(30);
            key = std::tolower(key);
            if (key == 27  || key == 'q') break;        // ESC to quit
            else if (key == 'i') camera.setZoom(camera.getZoom() + 0.1); // Zoom in
            else if (key == 'o') camera.setZoom(camera.getZoom() - 0.1); // Zoom out
            else if (key == 'a') camera.panLeft();   // Pan left
            else if (key == 'd') camera.panRight();  // Pan right
            else if (key == 'w') camera.tiltUp();    // Tilt up
            else if (key == 'z') camera.tiltDown();  // Tilt down
            else if (key == 'r') camera.reset();  // reset 
            else if(key == 'f')  camera.enableFaceDetection(); // enable face detction
        }
      
    } catch (const std::exception& ex) {
        std::cerr << "Exception: " << ex.what() << std::endl;
    }
    catch (...)
    {
        std::cerr <<"Error in starting autofocus camerea"<<std::endl;
    }

    return 0;
}
