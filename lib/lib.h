#ifndef OPENCV_SERVER_SOURCE_LIB_H
#define OPENCV_SERVER_SOURCE_LIB_H

#include <opencv2/core/core.hpp>
#include <iostream>
#include <string>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgcodecs/imgcodecs_c.h>


struct img_read_struct {
    cv::Mat img;
    int return_code;
};

img_read_struct img_read(cv::String img_pth) {
    img_read_struct img_rs;
    img_rs.img = imread(img_pth, CV_LOAD_IMAGE_GRAYSCALE);

    if(img_rs.img.data == NULL)
    {
        img_rs.return_code = -1;
    }
    else {
        img_rs.return_code = 0;
    }

    return img_rs;
    /*
     * Return Code Spec:
     *    0 => Img Read Successful
     *    -1 => Img Read Failed
     */
}

namespace roy_opencv {

    int roy_memset(int reserve_len, int all_len, char * p)
    {
        for(int i=reserve_len;i<all_len;i++)
        {
            *(p+i) = 0;
        }
        return 0;
    }

    std::string generate_msg(float score, int error)
    {
        std::string json_msg = "{\"score\":" + std::to_string(score) + "," +
                "\"error\":" + std::to_string(error) +
                "}";
        return json_msg;
    }
}


#endif //OPENCV_SERVER_SOURCE_LIB_HANDLER_H