#!/bin/bash
g++ -O2 `pkg-config --cflags opencv` main.cpp `pkg-config --libs opencv` -o main
#g++ `pkg-config --cflags opencv` test.cpp `pkg-config --libs opencv` -o test
# g++ -I/usr/include/opencv -I/usr/include main.cpp /usr/lib/libopencv_calib3d.so /usr/lib/libopencv_contrib.so /usr/lib/libopencv_core.so /usr/lib/libopencv_features2d.so /usr/lib/libopencv_flann.so /usr/lib/libopencv_gpu.so /usr/lib/libopencv_highgui.so /usr/lib/libopencv_imgproc.so /usr/lib/libopencv_legacy.so /usr/lib/libopencv_ml.so /usr/lib/libopencv_objdetect.so /usr/lib/libopencv_video.so -o main
#g++ -I/usr/local/include/opencv -I/usr/local/include main.cpp /usr/local/lib/libopencv_core.so /usr/lib/libopencv_highgui.so /usr/lib/libopencv_imgproc.so /usr/lib/libopencv_legacy.so /usr/lib/libopencv_ml.so /usr/lib/libopencv_video.so -o main
