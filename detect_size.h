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

using namespace cv;

enum IMG { SHRESHOLD = 300*300};

int detect_size(Mat img) {

    int return_code = 0;
    IMG img_shreshold = SHRESHOLD;
    int img_resolution = img.rows * img.cols;
    if (img_resolution > img_shreshold) {
        return_code = 0;
        // return amount of face rect detected
    }
    else
    {
        return_code = 1;
    }
    std::cout << "rows:" << img.rows << std::endl;
    std::cout << "cols:" << img.cols << std::endl;
    std::cout << "Size OK Code:" << return_code << std::endl;

    return return_code;
}
