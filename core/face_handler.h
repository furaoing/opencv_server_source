#ifndef OPENCV_SERVER_SOURCE_FACE_HANDLER_H
#define OPENCV_SERVER_SOURCE_FACE_HANDLER_H

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

    class face_handler {
        cv::CascadeClassifier cascade;

        public:
            face_handler(){
                cv::String data_relpth = FACE_MODEL;
                // .xxx path is relative to the location of executable (entry point)
                cv::String abs_pth = roy_c::get_abs_pth(data_relpth);
                cv::String face_cascade_name = abs_pth;
                if (!cascade.load(face_cascade_name)) {
                    std::cout << "Cascade_name file:" + face_cascade_name << std::endl;
                };
            // cascade.load will only load abspath file
            }

            int detect_face(cv::Mat img){

                equalizeHist(img, img);
                std::vector<cv::Rect> objs;

                clock_t t = clock();
                cascade.detectMultiScale(img, objs, SCALE_FACTOR, MIN_NEIGHBORS);
                t = t - clock();

                printf("It took me %d clicks (%f seconds).\n", t, ((float) t) / CLOCKS_PER_SEC);
                std::cout << "Detect Face Count: " << objs.size() << std::endl;

                return (int) objs.size();
                // return amount of face rect detected
                /*
                 *  TODO: Handle Failure of Method --- cascade.detectMultiScale(img, objs, scale_factor, min_neighbors);
                 */
            }

            ~face_handler(){
                std::cout << "Object type<face_handler> destrcuted" << std::endl;
                // This function is intentionally left blank;
            }
        };

}


#endif //OPENCV_SERVER_SOURCE_FACE_HANDLER_H