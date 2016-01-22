#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <zbar.h>
#include <iostream>
#include <iomanip>


int detect_symbols(cv::Mat img) {
    // Create a zbar reader
    zbar::ImageScanner scanner;

    // Configure the reader
    scanner.set_config(zbar::ZBAR_NONE, zbar::ZBAR_CFG_ENABLE, 1);


    // Capture an OpenCV frame
    cv::Mat frame_grayscale;
    frame_grayscale = img;


    // Obtain image data
    int width = frame_grayscale.cols;
    int height = frame_grayscale.rows;
    uchar *raw = (uchar *) (frame_grayscale.data);

    // Wrap image data
    zbar::Image image(width, height, "Y800", raw, width * height);

    // Scan the image for barcodes, etc
    int result = scanner.scan(image);
    // TODO: Handle Exceptions of scanner.scan();

    std::cout << "Symbols Result is:" << result << std::endl;

    // clean up
    image.set_data(NULL, 0);

    return result;

}