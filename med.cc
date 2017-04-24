#include <iostream>
#include <cstdint>
#include <ctime>
#include <chrono>
#include <string>

#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

#include "sort.h"
#include "merge.h"
#include "utils.h"

//typedef uint8_t TType;
bool print = false;
typedef std::chrono::steady_clock::time_point TTimePoint;

/**
* Median filter 3x3, basic implementation
*/
template <class T>
void filter3(cv::Mat& src, cv::Mat& dst) {
    // resize src image and copy borders
    int center = 1;
    cv::Mat srcBorder;
    copyMakeBorder(src, srcBorder, center, center, center, center, cv::BORDER_REPLICATE);
    dst = cv::Mat(src.size(), src.type());
    T win[9];
    TTimePoint begin = std::chrono::steady_clock::now();

    // median filter
    for(int y = 0; y < src.rows; y++) {
        for(int x = 0; x < src.cols; x++) {
            win[0] = srcBorder.at<T>(y,   x);
            win[1] = srcBorder.at<T>(y+1, x);
            win[2] = srcBorder.at<T>(y+2, x);
            win[3] = srcBorder.at<T>(y,   x+1);
            win[4] = srcBorder.at<T>(y+1, x+1);
            win[5] = srcBorder.at<T>(y+2, x+1);
            win[6] = srcBorder.at<T>(y,   x+2);
            win[7] = srcBorder.at<T>(y+1, x+2);
            win[8] = srcBorder.at<T>(y+2, x+2);

            insertion_sort<T>(win, 9);
            dst.at<uchar>(y,x) = win[4];
        }
    }

    TTimePoint end = std::chrono::steady_clock::now();
    std::cout << "filter3::TimeElapsed (us): " << \
    std::chrono::duration_cast<std::chrono::microseconds>(end-begin).count()/1000 << \
    std::endl;

    return;
}

/**
* Median filter 3x3, optimized implementation
*/
template <class T>
void filter3_opt(cv::Mat& src, cv::Mat& dst) {
    // resize src image and copy borders
    int center = 1;
    cv::Mat srcBorder;
    copyMakeBorder(src, srcBorder, center, center, center, center, cv::BORDER_REPLICATE);
    dst = cv::Mat(src.size(), src.type());
    T win[9];
    T col0[3];
    T col1[3];
    T col2[3];
    int prev_x = 1;
    TTimePoint begin = std::chrono::steady_clock::now();

    // median filter
    for(int y = 0; y < src.rows; y++) {
        for(int x = 0; x < src.cols; x++) {
            if(x == (prev_x+1)) {
                std::memcpy(col0, col1, 3*sizeof(T));
                std::memcpy(col1, col2, 3*sizeof(T));
                /*col2[0] = srcBorder.at<T>(y,   x+2);
                col2[1] = srcBorder.at<T>(y+1, x+2);
                col2[2] = srcBorder.at<T>(y+2, x+2);
                */
                for(int j = 0; j < 3; j++) {
                    col2[j] = srcBorder.at<T>(y+j, x+2);
                }
                
                //insertion_sort<T>(col2, 3);
                sort3(col2);
            }
            else {
                /*col0[0] = srcBorder.at<T>(y,   x);
                col0[1] = srcBorder.at<T>(y+1, x);
                col0[2] = srcBorder.at<T>(y+2, x);

                col1[0] = srcBorder.at<T>(y,   x+1);
                col1[1] = srcBorder.at<T>(y+1, x+1);
                col1[2] = srcBorder.at<T>(y+2, x+1);

                col2[0] = srcBorder.at<T>(y,   x+2);
                col2[1] = srcBorder.at<T>(y+1, x+2);
                col2[2] = srcBorder.at<T>(y+2, x+2);
                */
                for(int j = 0; j < 3; j++) {
                    col0[j] = srcBorder.at<T>(y+j, x);
                    col1[j] = srcBorder.at<T>(y+j, x+1);
                    col2[j] = srcBorder.at<T>(y+j, x+2);
                }
                
                sort3(col0);
                sort3(col1);
                sort3(col2);
                
                //insertion_sort<T>(col0, 3);
                //insertion_sort<T>(col1, 3);
                //insertion_sort<T>(col2, 3);
            }

            merge3_arrays(col0, col1, col2, win, 3);
            prev_x = x;
            dst.at<uchar>(y,x) = win[4];
        }
    }

    TTimePoint end = std::chrono::steady_clock::now();
    std::cout << "filter3_opt::TimeElapsed (us): " << \
    std::chrono::duration_cast<std::chrono::microseconds>(end-begin).count()/1000 << \
    std::endl;

    return;
}

/**
* Median filter 3x3, optimized implementation, fast sort only
*/
template <class T>
void filter3_opt_sort_only(cv::Mat& src, cv::Mat& dst) {
    // resize src image and copy borders
    int center = 1;
    cv::Mat srcBorder;
    copyMakeBorder(src, srcBorder, center, center, center, center, cv::BORDER_REPLICATE);
    dst = cv::Mat(src.size(), src.type());
    T win[9];
    TTimePoint begin = std::chrono::steady_clock::now();
    int widx = 0;

    // median filter
    for(int y = 0; y < src.rows; y++) {
        for(int x = 0; x < src.cols; x++) {
            for(int j = 0; j < 3; j++) {
                for(int i = 0; i < 3; i++) {
                    win[widx] = srcBorder.at<T>(y+j, x+i);
                    widx++;
                }
            }
            widx = 0;
            sort9(win);
            dst.at<uchar>(y,x) = win[4];
        }
    }

    TTimePoint end = std::chrono::steady_clock::now();
    std::cout << "filter3_opt_sort_only::TimeElapsed (us): " << \
    std::chrono::duration_cast<std::chrono::microseconds>(end-begin).count()/1000 << \
    std::endl;

    return;
}

/**
* Median filter 5x5, basic implementation
*/
template <class T>
void filter5(cv::Mat& src, cv::Mat& dst) {
    // resize src image and copy borders
    int center = 2;
    cv::Mat srcBorder;
    copyMakeBorder(src, srcBorder, center, center, center, center, cv::BORDER_REPLICATE);
    dst = cv::Mat(src.size(), src.type());
    T win[25];
    TTimePoint begin = std::chrono::steady_clock::now();
    //std::vector<T> winvec(25);
    int widx = 0;

    // median filter
    for(int y = 0; y < src.rows; y++) {
        for(int x = 0; x < src.cols; x++) {
            for(int j = 0; j < 5; j++) {
                for(int i = 0; i < 5; i++) {
                    win[widx] = srcBorder.at<T>(y+j, x+i);
                    widx++;
                }
            }
            widx = 0;
            insertion_sort<T>(win, 25);
            //std::sort(winvec.begin(), winvec.end());
            dst.at<uchar>(y,x) = win[12];
        }
    }

    TTimePoint end = std::chrono::steady_clock::now();
    std::cout << "filter5::TimeElapsed (us): " << \
    std::chrono::duration_cast<std::chrono::microseconds>(end-begin).count()/1000 << \
    std::endl;

    return;
}

/**
* Median filter 5x5, optimized implementation
*/
template <class T>
void filter5_opt(cv::Mat& src, cv::Mat& dst) {
    // resize src image and copy borders
    int center = 2;
    cv::Mat srcBorder;
    copyMakeBorder(src, srcBorder, center, center, center, center, cv::BORDER_REPLICATE);
    dst = cv::Mat(src.size(), src.type());
    T win[25];
    T col0[5];
    T col1[5];
    T col2[5];
    T col3[5];
    T col4[5];
    int prev_x = 1;
    TTimePoint begin = std::chrono::steady_clock::now();

    // median filter
    for(int y = 0; y < src.rows; y++) {
        for(int x = 0; x < src.cols; x++) {
            if(x == (prev_x+1)) {
                std::memcpy(col0, col1, 5*sizeof(T));
                std::memcpy(col1, col2, 5*sizeof(T));
                std::memcpy(col2, col3, 5*sizeof(T));
                std::memcpy(col3, col4, 5*sizeof(T));
                for(int j = 0; j < 5; j++) {
                    col4[j] = srcBorder.at<T>(y+j, x+4);
                }
                //insertion_sort<T>(col4, 5);
                sort5<T>(col4);
            }
            else {
                for(int j = 0; j < 5; j++) {
                    col0[j] = srcBorder.at<T>(y+j, x);
                    col1[j] = srcBorder.at<T>(y+j, x+1);
                    col2[j] = srcBorder.at<T>(y+j, x+2);
                    col3[j] = srcBorder.at<T>(y+j, x+3);
                    col4[j] = srcBorder.at<T>(y+j, x+4);
                }
                sort5<T>(col0);
                sort5<T>(col1);
                sort5<T>(col2);
                sort5<T>(col3);
                sort5<T>(col4);
            }

            merge5_arrays<T>(col0, col1, col2, col3, col4, win);

            //insertion_sort<T>(win, 25);
            //std::sort(winvec.begin(), winvec.end());
            dst.at<uchar>(y,x) = win[12];
        }
    }

    TTimePoint end = std::chrono::steady_clock::now();
    std::cout << "filter5_opt::TimeElapsed (us): " << \
    std::chrono::duration_cast<std::chrono::microseconds>(end-begin).count()/1000 << \
    std::endl;

    return;
}

/**
* Median filter 7x7, basic implementation
*/
template <class T>
void filter7(cv::Mat& src, cv::Mat& dst) {
    // resize src image and copy borders
    int center = 3;
    cv::Mat srcBorder;
    copyMakeBorder(src, srcBorder, center, center, center, center, cv::BORDER_REPLICATE);
    dst = cv::Mat(src.size(), src.type());
    T win[49];
    TTimePoint begin = std::chrono::steady_clock::now();
    int widx = 0;

    // median filter
    for(int y = 0; y < src.rows; y++) {
        for(int x = 0; x < src.cols; x++) {
            for(int j = 0; j < 7; j++) {
                for(int i = 0; i < 7; i++) {
                    win[widx] = srcBorder.at<T>(y+j, x+i);
                    widx++;
                }
            }
            widx = 0;
            insertion_sort<T>(win, 49);
            dst.at<uchar>(y,x) = win[24];
        }
    }

    TTimePoint end = std::chrono::steady_clock::now();
    std::cout << "filter7::TimeElapsed (us): " << \
    std::chrono::duration_cast<std::chrono::microseconds>(end-begin).count()/1000 << \
    std::endl;

    return;
}

/**
* Median filter 7x7, optimized implementation
*/
template <class T>
void filter7_opt(cv::Mat& src, cv::Mat& dst) {
    // resize src image and copy borders
    int center = 3;
    cv::Mat srcBorder;
    copyMakeBorder(src, srcBorder, center, center, center, center, cv::BORDER_REPLICATE);
    dst = cv::Mat(src.size(), src.type());
    T win[49];
    T col0[7];
    T col1[7];
    T col2[7];
    T col3[7];
    T col4[7];
    T col5[7];
    T col6[7];
    int prev_x = 1;
    TTimePoint begin = std::chrono::steady_clock::now();

    // median filter
    for(int y = 0; y < src.rows; y++) {
        for(int x = 0; x < src.cols; x++) {
            if(x == (prev_x+1)) {
                std::memcpy(col0, col1, 7*sizeof(T));
                std::memcpy(col1, col2, 7*sizeof(T));
                std::memcpy(col2, col3, 7*sizeof(T));
                std::memcpy(col3, col4, 7*sizeof(T));
                std::memcpy(col4, col5, 7*sizeof(T));
                std::memcpy(col5, col6, 7*sizeof(T));

                for(int j = 0; j < 7; j++) {
                    col6[j] = srcBorder.at<T>(y+j, x+6);
                }
                //insertion_sort<T>(col6, 7);
                sort7<T>(col6);
            }
            else {
                for(int j = 0; j < 7; j++) {
                    col0[j] = srcBorder.at<T>(y+j, x);
                    col1[j] = srcBorder.at<T>(y+j, x+1);
                    col2[j] = srcBorder.at<T>(y+j, x+2);
                    col3[j] = srcBorder.at<T>(y+j, x+3);
                    col4[j] = srcBorder.at<T>(y+j, x+4);
                    col5[j] = srcBorder.at<T>(y+j, x+5);
                    col6[j] = srcBorder.at<T>(y+j, x+6);
                }
                sort7<T>(col0);
                sort7<T>(col1);
                sort7<T>(col2);
                sort7<T>(col3);
                sort7<T>(col4);
                sort7<T>(col5);
                sort7<T>(col6);
            }

            merge7_arrays<T>(col0, col1, col2, col3, col4, col5, col6, win);
            dst.at<uchar>(y,x) = win[24];
        }
    }

    TTimePoint end = std::chrono::steady_clock::now();
    std::cout << "filter7_opt::TimeElapsed (us): " << \
    std::chrono::duration_cast<std::chrono::microseconds>(end-begin).count()/1000 << \
    std::endl;

    return;
}

/**
* Use OpenCV implementation of median filter to check results
*/
void filter_cv(cv::Mat& src, cv::Mat& dst, int filterSize) {
    TTimePoint begin = std::chrono::steady_clock::now();

    cv::medianBlur(src, dst, filterSize);

    TTimePoint end = std::chrono::steady_clock::now();
    std::cout << "filter_cv::TimeElapsed (us): " << \
    std::chrono::duration_cast<std::chrono::microseconds>(end-begin).count()/1000 << \
    std::endl;
}

int main(int argc, char* argv[]) {
    print = false;
    //cv::Mat src(10,10, cv::DataType<uint8_t>::type);
    //cv::Mat src(1024,1024, cv::DataType<uint8_t>::type);
    cv::Mat src(4096,2048, cv::DataType<uint8_t>::type);
    cv::Mat dst0 = cv::Mat::zeros(src.rows, src.cols, cv::DataType<uint8_t>::type);
    cv::Mat dst1 = cv::Mat::zeros(src.rows, src.cols, cv::DataType<uint8_t>::type);
    cv::Mat dst2 = cv::Mat::zeros(src.rows, src.cols, cv::DataType<uint8_t>::type);
    cv::Mat dst3 = cv::Mat::zeros(src.rows, src.cols, cv::DataType<uint8_t>::type);
    cv::randu(src, 10, 64);

    //print_matrix<uint8_t>(src);
    //print_matrix<uint8_t>(dst);
    for(unsigned i = 0; i < 2; i++)
        filter3<uint8_t>(src, dst0);
    for(unsigned i = 0; i < 2; i++)
        filter3_opt<uint8_t>(src, dst1);
    for(unsigned i = 0; i < 2; i++)
        filter3_opt_sort_only<uint8_t>(src, dst2);
    for(unsigned i = 0; i < 2; i++)
        filter_cv(src, dst3, 3);

    diff_matrices(dst0, dst1, "filter3, filter3_opt");
    diff_matrices(dst0, dst2, "filter3, filter3_opt_sort_only");
    diff_matrices(dst0, dst3, "filter3, filter3_cv");
    
    for(unsigned i = 0; i < 1; i++)
        filter5<uint8_t>(src, dst0);
    for(unsigned i = 0; i < 1; i++)
        filter5_opt<uint8_t>(src, dst1);
    for(unsigned i = 0; i < 1; i++)
        filter_cv(src, dst2, 5);
    
    diff_matrices(dst0, dst1, "filter5, filter5_opt");
    diff_matrices(dst0, dst2, "filter5, filter5_cv");
    
    for(unsigned i = 0; i < 2; i++)
        filter7<uint8_t>(src, dst0);
    for(unsigned i = 0; i < 5; i++)
        filter7_opt<uint8_t>(src, dst1);
    for(unsigned i = 0; i < 1; i++)
        filter_cv(src, dst2, 7);
    
    diff_matrices(dst0, dst1, "filter7, filter7_opt");
    diff_matrices(dst0, dst2, "filter7, filter7_cv");
    diff_matrices(dst1, dst2, "filter7_opt, filter7_cv");

    run_sort_tests();
    run_merge_tests();

    return 0;
}
