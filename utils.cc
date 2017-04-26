#include "utils.h"

template <class T>
void print_matrix(const cv::Mat &mat0) {
    for(int y = 0; y < mat0.rows; y++) {
        for(int x = 0; x < mat0.cols; x++) {
            std::cout << unsigned(mat0.at<T>(y,x)) << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;

    return;
}

bool diff_matrices(const cv::Mat& mat0, const cv::Mat& mat1, const std::string description, bool print_stats) {
    bool rv = true;
    double mav = 255.0;
    double err = 255.0;
    //double nonzeros = 255.0;
    cv::Mat diff;

    cv::absdiff(mat0, mat1, diff);
    cv::minMaxLoc(diff, NULL, &mav);
    err = (cv::sum(diff).val[0] / (diff.rows*diff.cols));
    //nonzeros = 1. * cv::countNonZero( diff ) / (diff.rows*diff.cols);

    if(err != 0.0 || mav != 0.0) {
        rv = false;
    }

    /*for(int y = 0; y < mat1.rows; y++) {
        for(int x = 1; x < mat1.cols; x++) {
            if(mat1.at<uchar>(y,x) != mat2.at<uchar>(y,x)) {
                std::cout << unsigned(mat1.at<uchar>(y,x)) << " vs. " << unsigned(mat2.at<uchar>(y,x)) << std::endl;
            }
        }
    }*/

    if(print_stats) {
        std::cout << "compare " << description << ":" << std::endl;
        std::cout << "error: " << err << std::endl;
        //std::cout << "nonzeros: " << nonzeros << std::endl;
        std::cout << "mav: " << mav << std::endl;
    }

    return rv;
}
