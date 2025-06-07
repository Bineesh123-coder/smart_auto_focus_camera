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
                  << "r: Reset\n";

        while (true) {
            cv::Mat frame = camera.captureFrame();
            cv::Mat view = camera.applyZoomPanTilt(frame);

            cv::imshow("Smart Camera", view);

            char key = (char)cv::waitKey(30);
            if (key == 27 ) break;        // ESC to quit
            else if (key == 'i') camera.setZoom(camera.getZoom() + 0.1); // Zoom in
            else if (key == 'o') camera.setZoom(camera.getZoom() - 0.1); // Zoom out
            else if (key == 'a') camera.panLeft();   // Pan left
            else if (key == 'd') camera.panRight();  // Pan right
            else if (key == 'w') camera.tiltUp();    // Tilt up
            else if (key == 'z') camera.tiltDown();  // Tilt down
            else if (key == 'r') camera.reset();  // reset 
        }
      
    } catch (const std::exception& ex) {
        std::cerr << "Exception: " << ex.what() << std::endl;
    }

    return 0;
}
