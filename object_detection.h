#ifndef OBJECT_DETECTION_H
#define OBJECT_DETECTION_H

#include <opencv2/opencv.hpp>
#include <opencv2/dnn.hpp>
#include <fstream>
#include <iostream>

using namespace cv;
using namespace dnn;
using namespace std;

vector<string> loadClassList(const string& filePath) {
    vector<string> classList;
    ifstream ifs(filePath.c_str());
    string line;
    while (getline(ifs, line)) classList.push_back(line);
    return classList;
}

void drawPred(int classId, float conf, int left, int top, int right, int bottom, Mat& frame, const vector<string>& classNames) {
    rectangle(frame, Point(left, top), Point(right, bottom), Scalar(0, 255, 0), 2);
    string label = format("%.2f", conf);
    if (!classNames.empty()) label = classNames[classId] + ": " + label;
    putText(frame, label, Point(left, top - 10), FONT_HERSHEY_SIMPLEX, 0.5, Scalar(0, 255, 255), 2);
}

#endif