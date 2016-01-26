#ifndef OPENCV_SERVER_SOURCE_SHAPE_HANDLER_H
#define OPENCV_SERVER_SOURCE_SHAPE_HANDLER_H

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



namespace opencv_server {

    class shape_handler {
        IMG IMG_SH = IMG::SHRESHOLD;  // resolution shreshold
        IMG IMG_AS = IMG::R_ASPECT_RATIO;  // aspect ratio shreshold
        IMG IMG_MS = IMG::R_MIN_SHORT;  // min short border length
        int long_edge;
        int short_edge;

        public:

            shape_handler(){
                // left bank intentionally
            }

            void get_long_short_edge(cv::Mat img){
                // This is a class method with side effect, no return value;
                // This method is used to caculate the long_edge and short_edge;
                    if (img.rows > img.cols) {
                    long_edge = img.rows;
                    short_edge = img.cols;
                    }
                    else {
                        long_edge = img.cols;
                        short_edge = img.rows;
                    }
            }


            int get_aspect_ratio(){
                return long_edge/short_edge;
            }

            bool test_as_ratio(cv::Mat img){
                get_long_short_edge(img);
                    return get_aspect_ratio() < IMG_AS;
                }

            bool test_img_shreshold(cv::Mat img){
                int img_resolution = img.rows * img.cols;
                return img_resolution > IMG_SH;
            }

            bool test_min_short(cv::Mat img){
                return short_edge > IMG_MS;
            }

            int test_shape(cv::Mat img){
                get_long_short_edge(img);
                int return_code = 0;

                int img_resolution = img.rows * img.cols;
                if (test_as_ratio(img)&&test_img_shreshold(img)&&test_min_short(img)) {
                    return_code = 0;
                }
                else {
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

            ~shape_handler() {
            std::cout << "Object type<shape_handler> destrcuted" << std::endl;
        }
    };
}


#endif //OPENCV_SERVER_SOURCE_SHAPE_HANDLER_H