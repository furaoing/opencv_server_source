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
#include "config.h"

namespace opencv_config {
    // parameters required for opencv functions
    const float scale_factor(1.3f);
    const int min_neighbors(1);
}

int detect_face(cv::Mat img) {
    using opencv_config::min_neighbors;
    using opencv_config::scale_factor;
    // import configs from a header file

    cv::String data_relpth = "data/lbpcascade_frontalface.xml";
    // .xml path is relative to the location of executable (entry point)
    cv::String abs_pth = roy_c::get_abs_pth(data_relpth);

    cv::String face_cascade_name = abs_pth;
    cv::CascadeClassifier cascade;
    if( !cascade.load( face_cascade_name ) ) {
        std::cout << "Cascade_name file:"+face_cascade_name << std::endl;
    };
    // cascade.load will only load abspath file

    equalizeHist(img, img);
    std::vector<cv::Rect> objs;

    clock_t t = clock();
    cascade.detectMultiScale(img, objs, scale_factor, min_neighbors);
    t = t - clock();

    printf ("It took me %d clicks (%f seconds).\n",t,((float)t)/CLOCKS_PER_SEC);
    std::cout << "Detect Face Count: " << objs.size() << std::endl;

    return (int) objs.size();
    // return amount of face rect detected
    /*
     *  TODO: Handle Failure of Method --- cascade.detectMultiScale(img, objs, scale_factor, min_neighbors);
     */
}
