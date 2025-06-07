#include "autofocus.h"
#include "object_detection.h"
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
                  << "f: Face detection enabled\n"
                  << "b: object detection enabled\n";
                 
        camera.loadFaceCascade("haarcascade_frontalface_default.xml");
        
        string classesFile = "yolo/coco.names";
        vector<string> classNames = loadClassList(classesFile);

        // Load the network
        Net net = readNetFromDarknet("yolov4-tiny.cfg", "yolov4-tiny.weights");
        net.setPreferableBackend(DNN_BACKEND_OPENCV);
        net.setPreferableTarget(DNN_TARGET_CPU);

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

            if(camera.object_detection)
            {
                            // === Pre-process ===
                Mat blob;
                blobFromImage(view, blob, 1/255.0, Size(416, 416), Scalar(), true, false);
                net.setInput(blob);

                // === Forward pass ===
                vector<Mat> outs;
                vector<String> outNames = net.getUnconnectedOutLayersNames();
                net.forward(outs, outNames);

                // === Post-process ===
                float confThreshold = 0.4;
                float nmsThreshold = 0.4;
                vector<int> classIds;
                vector<float> confidences;
                vector<Rect> boxes;

                for (const auto& out : outs) {
                    for (int i = 0; i < out.rows; ++i) {
                        Mat scores = out.row(i).colRange(5, out.cols);
                        Point classIdPoint;
                        double confidence;
                        minMaxLoc(scores, 0, &confidence, 0, &classIdPoint);
                        if (confidence > confThreshold) {
                            int centerX = int(out.at<float>(i, 0) * view.cols);
                            int centerY = int(out.at<float>(i, 1) * view.rows);
                            int width = int(out.at<float>(i, 2) * view.cols);
                            int height = int(out.at<float>(i, 3) * view.rows);
                            int left = centerX - width / 2;
                            int top = centerY - height / 2;

                            classIds.push_back(classIdPoint.x);
                            confidences.push_back((float)confidence);
                            boxes.push_back(Rect(left, top, width, height));
                        }
                    }
                }

                // === NMS and drawing ===
                vector<int> indices;
                NMSBoxes(boxes, confidences, confThreshold, nmsThreshold, indices);

                for (int idx : indices) {
                    Rect box = boxes[idx];
                    drawPred(classIds[idx], confidences[idx], box.x, box.y,
                            box.x + box.width, box.y + box.height,
                            view, classNames);
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
            else if (key == 'f')  camera.enableFaceDetection(); // enable face detction
            else if (key == 'b')  camera.enableObjectDetection(); // enable face detction
            
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
