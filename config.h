//
// Created by rao on 16-1-3.
//
#ifndef OPENCV_SERVER_SOURCE_CONFIG_H
#define OPENCV_SERVER_SOURCE_CONFIG_H

#include <opencv2/core/cvstd.hpp>

namespace opencv_server {

    enum IMG {
        // enumerator inside a namespace act like a macro
        SHRESHOLD = 150 * 150,
        R_ASPECT_RATIO = 4,
        R_MIN_SHORT = 40
    };

    enum CODE_REF {
        NO_SYMBOL = 0,
        SIZE_OK = 0,
        SCORE_READFAILED = 0
    };

    enum SOCKET_SERVER {
        MY_PORT = 7719,
        BUFF_SIZE = 4096
    };

    const float SCALE_FACTOR = 1.3f;
    const int MIN_NEIGHBORS = 1;
    const cv::String FACE_MODEL = "data/lbpcascade_frontalface.xml";
    // string type is possibly overloaded by opencv, use cv::String instead
}


#endif //OPENCV_SERVER_SOURCE_CONFIG_H