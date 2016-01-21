#include <opencv2/imgproc/imgproc.hpp>  // Gaussian Blur
#include <opencv2/core/core.hpp>        // Basic OpenCV structures (cv::Mat, Scalar)
#include <opencv2/objdetect/objdetect.hpp>
#include <stdio.h>
#include <string>
#include <vector>
#include <iostream>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgcodecs/imgcodecs_c.h>
#include <time.h>

#include "lib/roy_system.h"

using namespace std;
using namespace cv;

int detect_face(Mat img) {

    String data_relpth = "data/lbpcascade_frontalface.xml";
    String abs_pth = roy_c::get_abs_pth(data_relpth);

    // String face_cascade_name = "/home/furaoing/roy_tensorflow_cv/opencv_test_ws/opencv_test/cpp/data/lbpcascades/lbpcascade_frontalface.xml";
    String face_cascade_name = abs_pth;
    CascadeClassifier cascade;
    if( !cascade.load( face_cascade_name ) ){ std::cout << "Cascade_name file:"+face_cascade_name << std::endl;};
    // cascade.load will only load abspath file
    const float scale_factor(1.3f);
    const int min_neighbors(1);

    equalizeHist(img, img);
    vector<Rect> objs;
    clock_t t = clock();
    cascade.detectMultiScale(img, objs, scale_factor, min_neighbors);
    t = t - clock();
    printf ("It took me %d clicks (%f seconds).\n",t,((float)t)/CLOCKS_PER_SEC);
    cout << "Detect Face Count: " << objs.size() << endl;
    return (int) objs.size();
    // return amount of face rect detected
    /*
     *  TODO: Handle Failure of Method --- cascade.detectMultiScale(img, objs, scale_factor, min_neighbors);
     */
}
