#include <opencv2/core/core.hpp>
#include <string>
#include <iostream>

#include "config.h"
#include "lib/lib.h"
#include "core/detect_face.h"
#include "core/detect_symbols.h"
#include "core/detect_size.h"


using namespace std;
using namespace cv;

enum CODE_REF { NO_SYMBOL = 0, SIZE_OK = 0, SCORE_READFAILED = 0};

float _score(int rect_count, int symbol_code, int size_code)
{
    int filter;
    int score;
    int cv_score;
    if ((symbol_code != CODE_REF::NO_SYMBOL) || (size_code != CODE_REF::SIZE_OK))
    {
        filter = -2;
        cv_score = 0;
    }
    else{
        filter = 0;
        cv_score = rect_count;
    }

    score = filter + cv_score;

    return (float) score;
}

string score(String img_pth) {

    int rect_count, symbol_code, size_code;
    std::string json_msg;

    img_read_struct img_rs = img_read(img_pth);

    int read_result = img_rs.return_code;
    cv::Mat img = img_rs.img;
    // read image into a Mat object
    // read_result is a int indicting whether file read operation is succeed or not

    if (read_result == 0) {
        rect_count = detect_face(img.clone());
        symbol_code = detect_symbols(img.clone());
        size_code = detect_size(img.clone());

        float score = _score(rect_count, symbol_code, size_code);

        json_msg = roy_opencv::generate_msg(score, read_result);

        std::cout << "Image Processing Complete" << std::endl;
        // call detect_face function to process image referenced by the file path given by buffer
    }
    else if (read_result == -1) {
        std::cout << "Image Reading Failed" << std::endl;

        json_msg = roy_opencv::generate_msg(CODE_REF::SCORE_READFAILED , read_result);
        // if read failed, use 0 as the default score
    }
    else{
        std::cout << "Program Bug, Return Code Out Of Range" << std::endl;
        // TODO: Handle Unspecified Return Code
    }

    return json_msg;
    /*
     * Return Code in json_msg Spec:
     *     0 => Img Scoring Process Succeed
     *     -1 => Img Reading Failed
     */
}
