#ifndef AUTO_FOCUS_H
#define AUTO_FOCUS_H

#include <opencv2/opencv.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/objdetect.hpp>
#include <chrono>

class AutoFocusCamera {
private:
    cv::VideoCapture cap;  // Camera capture object
    cv::CascadeClassifier face_cascade;  // Face detector
    int camera_id;
    double zoom_level;
    int pan_offset;
    int tilt_offset;
    

 
    

public:
    bool face_detection = false;
    bool object_detection = false;
    std::chrono::steady_clock::time_point lastFocusTime; 
    // Constructor: open camera
    AutoFocusCamera(int cam_id = 0) : camera_id(cam_id), zoom_level(1.0), pan_offset(0), tilt_offset(0){
        cap.open(camera_id);
        if (!cap.isOpened()) {
            throw std::runtime_error("Error opening camera");
        }
    }

    // Destructor: release camera
    ~AutoFocusCamera() {
        cap.release();
    }

    // Capture and return current frame
    cv::Mat captureFrame() {
        cv::Mat frame;
        cap >> frame;
        if (frame.empty()) {
            throw std::runtime_error("Empty frame captured");
        }
        return frame;
    }

    void setZoom(double zoom) {
    zoom_level = std::max(1.0, std::min(zoom, 5.0));
    if(zoom_level == 1.0)
        {
            pan_offset = 0;
            tilt_offset = 0;
        }
    std::cout << "Zoom level set to: " << zoom_level << std::endl;
    }

    void reset()
    {
        zoom_level = 1.0;
        pan_offset = 0;
        tilt_offset = 0;
    }

    void panLeft()  { pan_offset -= 20; std::cout << "Pan Left\n"; }
    void panRight() { pan_offset += 20; std::cout << "Pan Right\n"; }
    void tiltUp()   { tilt_offset -= 20; std::cout << "Tilt Up\n"; }
    void tiltDown() { tilt_offset += 20; std::cout << "Tilt Down\n"; }

    double getZoom() const { return zoom_level; }


    cv::Mat applyZoomPanTilt(const cv::Mat& frame) {
        if (zoom_level <= 1.0) return frame;  // No zoom

        int w = frame.cols / zoom_level;
        int h = frame.rows / zoom_level;

        int center_x = frame.cols / 2 + pan_offset;
        int center_y = frame.rows / 2 + tilt_offset;

        int x = center_x - w / 2;
        int y = center_y - h / 2;

        // Keep within bounds
        x = std::max(0, std::min(x, frame.cols - w));
        y = std::max(0, std::min(y, frame.rows - h));

        cv::Rect roi(x, y, w, h);
        cv::Mat cropped = frame(roi);
        cv::Mat zoomed;
        cv::resize(cropped, zoomed, frame.size());

        return zoomed;
    }

    void loadFaceCascade(const std::string& path) {
        if (!face_cascade.load(path)) {
            throw std::runtime_error("Failed to load face cascade");
        }
    }

    std::vector<cv::Rect> detectFaces(const cv::Mat& frame_gray) {
        std::vector<cv::Rect> faces;
        face_cascade.detectMultiScale(frame_gray, faces, 1.1, 4, 0, cv::Size(30, 30));
        return faces;
    }
    void enableFaceDetection()
    {
        face_detection =! face_detection;
        std::cout<<(face_detection?"face_detection enbaled\n" :"face_detection disabled\n");
    }

    void enableObjectDetection()
    {
        object_detection =! object_detection;
        std::cout<<(object_detection?"object_detection enbaled\n" :"object_detection disabled\n");
    }


    
};

#endif //AUTO_FOCUS_H
