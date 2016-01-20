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

enum IMG { SHRESHOLD = 150*150, R_ASPECT_RATIO = 4, R_MIN_SHORT = 40};

int detect_size(Mat img) {

    int return_code = 0;
    IMG img_shreshold = SHRESHOLD;
    IMG img_aspect_ratio = R_ASPECT_RATIO;
    IMG img_min_short = R_MIN_SHORT;
    int img_resolution = img.rows * img.cols;
    int longer = 0;
    int shorter = 0;
    int as_ratio = 0;

    if(img.rows > img.cols){
        longer = img.rows;
        shorter = img.cols;
        as_ratio = longer/(shorter+1);
    }
    else{
        longer = img.cols;
        shorter = img.rows;
        as_ratio = longer/(shorter+1);
    }

    if ((img_resolution > img_shreshold)&&(as_ratio < img_aspect_ratio)&&(shorter > img_min_short)) {
        return_code = 0;
    }
    else
    {
        return_code = 1;
    }
    std::cout << "rows:" << img.rows << std::endl;
    std::cout << "cols:" << img.cols << std::endl;
    std::cout << "Size OK Code:" << return_code << std::endl;

    // TODO: Handle Exceptions Within This Function
    return return_code;
    /*
     * Return Code Spec:
     *    0 => Image Size OK
     *    1 => Image Size NOT OK
     */
}
