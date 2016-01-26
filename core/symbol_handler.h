#ifndef OPENCV_SERVER_SOURCE_SYMBOL_HANDLER_H
#define OPENCV_SERVER_SOURCE_SYMBOL_HANDLER_H

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <zbar.h>
#include <iostream>
#include <iomanip>

namespace opencv_server {

    class symbol_handler {
        zbar::ImageScanner scanner;
        cv::Mat frame_grayscale;

        public:
            symbol_handler() {
                scanner.set_config(zbar::ZBAR_NONE, zbar::ZBAR_CFG_ENABLE, 1);
            }

            int detect_symbols(cv::Mat img) {
                frame_grayscale = img;
                // Capture an OpenCV frame
                int width = frame_grayscale.cols;
                int height = frame_grayscale.rows;
                uchar *raw = (uchar *) (frame_grayscale.data);
                // Wrap image data
                zbar::Image image(width, height, "Y800", raw, width * height);
                // Scan the image for barcodes, etc

                int result = scanner.scan(image);
                // TODO: Handle Exceptions of scanner.scan();
                std::cout << "Symbols Result is:" << result << std::endl;
                // print some debugging information;
                image.set_data(NULL, 0);
                // clean up

                return result;
            }

        ~symbol_handler() {
            std::cout << "Object type<symbol_handler> destrcuted" << std::endl;
        }
    };
}


#endif //OPENCV_SERVER_SOURCE_SYMBOL_HANDLER_H