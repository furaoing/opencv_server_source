#ifndef OPENCV_SERVER_SOURCE_SCORE_H
#define OPENCV_SERVER_SOURCE_SCORE_H

#include <opencv2/core/core.hpp>

#include "lib/lib.h"
#include "lib/roy_system.h"
#include "core/face_handler.h"
#include "core/symbol_handler.h"
#include "core/shape_handler.h"


namespace opencv_server {

    float _score(int rect_count, int symbol_code, int size_code) {
        int filter;
        int score;
        int cv_score;
        if ((symbol_code != CODE_REF::NO_SYMBOL) || (size_code != CODE_REF::SIZE_OK)) {
            filter = -2;
            cv_score = 0;
        }
        else {
            filter = 0;
            cv_score = rect_count;
        }

        score = filter + cv_score;

        return (float) score;
    }

    std::string score(cv::String img_pth,
                      symbol_handler* p_symbol_detector,
                      shape_handler* p_shape_examiner,
                      face_handler* p_face_detector)
    {
        using namespace opencv_server;

        int rect_count, symbol_code, size_code;
        std::string json_msg;

        img_read_struct img_rs = img_read(img_pth);
        int read_result = img_rs.return_code;
        cv::Mat img = img_rs.img;
        // read image into a Mat object
        // read_result is a int indicting whether file read operation is succeed or not

        if (read_result == 0) {

            symbol_code = p_symbol_detector->detect_symbols(img.clone());
            size_code = p_shape_examiner->test_shape(img.clone());
            rect_count = p_face_detector->detect_face(img.clone());
            float score = _score(rect_count, symbol_code, size_code);

            json_msg = roy_opencv::generate_msg(score, read_result);
            std::cout << "Image Processing Complete" << std::endl;
            // call detect_face function to process image referenced by the file path given by buffer
        }
        else if (read_result == -1) {
            std::cout << "Image Reading Failed" << std::endl;
            json_msg = roy_opencv::generate_msg(CODE_REF::SCORE_READFAILED, read_result);
            // if read failed, use 0 as the default score
        }
        else {
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
}


#endif //OPENCV_SERVER_SOURCE_SCORE_H
