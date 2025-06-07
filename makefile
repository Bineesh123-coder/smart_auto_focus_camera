# Makefile for Smart Auto Focus Camera (C++11 + OpenCV4)

CXX = g++
CXXFLAGS = -std=c++17 -Wall `pkg-config --cflags opencv4`
LDFLAGS = `pkg-config --libs opencv4`
TARGET = smart_camera
SRC = main.cpp

all: $(TARGET)

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRC) $(LDFLAGS)

clean:
	rm -f $(TARGET)
