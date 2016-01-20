#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <zbar.h>
#include <iostream>
#include <iomanip>


using namespace std;
using namespace cv;
using namespace zbar;

int detect_symbols(Mat img) {
    // Create a zbar reader
    ImageScanner scanner;

    // Configure the reader
    scanner.set_config(ZBAR_NONE, ZBAR_CFG_ENABLE, 1);


    // Capture an OpenCV frame
    cv::Mat frame_grayscale;
    frame_grayscale = img;


    // Obtain image data
    int width = frame_grayscale.cols;
    int height = frame_grayscale.rows;
    uchar *raw = (uchar *) (frame_grayscale.data);

    // Wrap image data
    Image image(width, height, "Y800", raw, width * height);

    // Scan the image for barcodes, etc
    int result = scanner.scan(image);
    // TODO: Handle Exceptions of scanner.scan();

    std::cout << "Symbols Result is:" << result << std::endl;

    /*
    // Extract results
    int counter = 0;
    for (Image::SymbolIterator symbol = image.symbol_begin(); symbol != image.symbol_end(); ++symbol) {
        time_t now;
        tm *current;
        now = time(0);
        current = localtime(&now);

        // do something useful with results
        cout    << "[" << current->tm_hour << ":" << current->tm_min << ":" << setw(2) << setfill('0') << current->tm_sec << "] " << counter << " "
                << "decoded " << symbol->get_type_name()
                << " symbol \"" << symbol->get_data() << '"' << endl;

        //cout << "Location: (" << symbol->get_location_x(0) << "," << symbol->get_location_y(0) << ")" << endl;
        //cout << "Size: " << symbol->get_location_size() << endl;


        // Get points
        /*for (Symbol::PointIterator point = symbol.point_begin(); point != symbol.point_end(); ++point) {
            cout << point << endl;
        } */

/*
    counter++;
}
*/

    // clean up
    image.set_data(NULL, 0);

    return result;

}