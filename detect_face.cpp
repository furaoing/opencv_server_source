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
#include "roy_system.h"

using namespace std;
using namespace cv;

unsigned long detect_face(String img_pth) {
    String self_pth = get_selfpath();
    // String face_cascade_name = "/home/furaoing/roy_tensorflow_cv/opencv_test_ws/opencv_test/cpp/data/lbpcascades/lbpcascade_frontalface.xml";
    std::cout << "Self path:"+ self_pth << std::endl;
    String face_cascade_name = self_pth + "/" + lbpcascade_frontalface.xml;
    CascadeClassifier cascade;
    if( !cascade.load( face_cascade_name ) ){ printf("--(!)Error loading face cascade\n");};
    // cascade.load will only load abspath file
    const float scale_factor(1.3f);
    const int min_neighbors(1);
    //Size min_size = Size[30, 30];


    Mat img = imread(img_pth, CV_LOAD_IMAGE_GRAYSCALE);
    if(img == NULL)
    {
        cout << "Img Read ERROR" << endl;
        return -1;
    }
    else
    {
        equalizeHist(img, img);
        vector<Rect> objs;
        clock_t t = clock();
        cascade.detectMultiScale(img, objs, scale_factor, min_neighbors);
        t = t - clock();
        printf("It took me %d clicks (%f seconds).\n", t, ((float) t) / CLOCKS_PER_SEC);
        cout << "Detect Face Count: " << objs.size() << endl;
        return objs.size();
        // return amount of face rect detected
    }
}

int main(){
    String img_pth = "/home/furaoing/roy_tensorflow_cv/face++test_ws/test_samples/test.jpg";
    detect_face(img_pth);
}