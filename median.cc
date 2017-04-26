#include <iostream>
#include <cstdint>
#include <ctime>
#include <chrono>
#include <string>

#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

#include "median.h"
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
    //T win[9];
    std::vector<T> winvec(9);
    TTimePoint begin = std::chrono::steady_clock::now();
    int widx = 0;

    // median filter
    for(int y = 0; y < src.rows; y++) {
        for(int x = 0; x < src.cols; x++) {
            for(int j = 0; j < 3; j++) {
                for(int i = 0; i < 3; i++) {
                    //win[widx] = srcBorder.at<T>(y+j, x+i);
                    winvec[widx] = srcBorder.at<T>(y+j, x+i);
                    widx++;
                }
            }
            widx = 0;

            //insertion_sort<T>(win, 9);
            std::sort(winvec.begin(), winvec.end());
            dst.at<uchar>(y,x) = winvec[4];
        }
    }

    if(print) {
        TTimePoint end = std::chrono::steady_clock::now();
        std::cout << "filter3::TimeElapsed (us): " << \
        std::chrono::duration_cast<std::chrono::microseconds>(end-begin).count()/1000 << \
        std::endl;
    }

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
                for(int j = 0; j < 3; j++) {
                    col2[j] = srcBorder.at<T>(y+j, x+2);
                }
                
                //insertion_sort<T>(col2, 3);
                sort3(col2);
            }
            else {
                for(int j = 0; j < 3; j++) {
                    col0[j] = srcBorder.at<T>(y+j, x);
                    col1[j] = srcBorder.at<T>(y+j, x+1);
                    col2[j] = srcBorder.at<T>(y+j, x+2);
                }
                
                sort3(col0);
                sort3(col1);
                sort3(col2);
            }

            merge3_arrays(col0, col1, col2, win, 3);
            prev_x = x;
            dst.at<uchar>(y,x) = win[4];
        }
    }

    if(print) {
        TTimePoint end = std::chrono::steady_clock::now();
        std::cout << "filter3_opt::TimeElapsed (us): " << \
        std::chrono::duration_cast<std::chrono::microseconds>(end-begin).count()/1000 << \
        std::endl;
    }

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

    if(print) {
        TTimePoint end = std::chrono::steady_clock::now();
        std::cout << "filter3_opt_sort_only::TimeElapsed (us): " << \
        std::chrono::duration_cast<std::chrono::microseconds>(end-begin).count()/1000 << \
        std::endl;
    }

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
    //T win[25];
    TTimePoint begin = std::chrono::steady_clock::now();
    std::vector<T> winvec(25);
    int widx = 0;

    // median filter
    for(int y = 0; y < src.rows; y++) {
        for(int x = 0; x < src.cols; x++) {
            for(int j = 0; j < 5; j++) {
                for(int i = 0; i < 5; i++) {
                    //win[widx] = srcBorder.at<T>(y+j, x+i);
                    winvec[widx] = srcBorder.at<T>(y+j, x+i);
                    widx++;
                }
            }
            widx = 0;
            //insertion_sort<T>(win, 25);
            std::sort(winvec.begin(), winvec.end());
            dst.at<uchar>(y,x) = winvec[12];
        }
    }

    if(print) {
        TTimePoint end = std::chrono::steady_clock::now();
        std::cout << "filter5::TimeElapsed (us): " << \
        std::chrono::duration_cast<std::chrono::microseconds>(end-begin).count()/1000 << \
        std::endl;
    }

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

    if(print) {
        TTimePoint end = std::chrono::steady_clock::now();
        std::cout << "filter5_opt::TimeElapsed (us): " << \
        std::chrono::duration_cast<std::chrono::microseconds>(end-begin).count()/1000 << \
        std::endl;
    }

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
    //T win[49];
    std::vector<T> winvec(49);
    TTimePoint begin = std::chrono::steady_clock::now();
    int widx = 0;

    // median filter
    for(int y = 0; y < src.rows; y++) {
        for(int x = 0; x < src.cols; x++) {
            for(int j = 0; j < 7; j++) {
                for(int i = 0; i < 7; i++) {
                    winvec[widx] = srcBorder.at<T>(y+j, x+i);
                    widx++;
                }
            }
            widx = 0;
            //insertion_sort<T>(win, 49);
            std::sort(winvec.begin(), winvec.end());
            dst.at<uchar>(y,x) = winvec[24];
        }
    }

    if(print) {
        TTimePoint end = std::chrono::steady_clock::now();
        std::cout << "filter7::TimeElapsed (us): " << \
        std::chrono::duration_cast<std::chrono::microseconds>(end-begin).count()/1000 << \
        std::endl;
    }

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

    if(print) {
        TTimePoint end = std::chrono::steady_clock::now();
        std::cout << "filter7_opt::TimeElapsed (us): " << \
        std::chrono::duration_cast<std::chrono::microseconds>(end-begin).count()/1000 << \
        std::endl;
    }

    return;
}

/**
* Use OpenCV implementation of median filter to check results
*/
void filter_cv(cv::Mat& src, cv::Mat& dst, int filterSize) {
    TTimePoint begin = std::chrono::steady_clock::now();
    dst = cv::Mat(src.size(), src.type());

    cv::medianBlur(src, dst, filterSize);

    if(print) {
        TTimePoint end = std::chrono::steady_clock::now();
        std::cout << "filter_cv::TimeElapsed (us): " << \
        std::chrono::duration_cast<std::chrono::microseconds>(end-begin).count()/1000 << \
        std::endl;
    }

    return;
}

/**
* Wrapper to median functions
* 
* @param src sorce matrix
* @param dst destination matrix
* @param filterSize size of filter, supported sizes are 3 (3x3), 5 (5x5), 7 (7x7)
*/
template <class T>
void median_filter(cv::Mat& src, cv::Mat& dst, int filterSize) {
    if(filterSize == 3) {
        filter3_opt<T>(src, dst);
    }
    else if(filterSize == 5) {
        filter5_opt<T>(src, dst);
    }
    else if(filterSize == 7) {
        filter7_opt<T>(src, dst);
    }
    else {
        std::cerr << "Unsupported filter size" << std::endl;
    }

    return;
}

/*****************************************************************************/
/**
* Tests
*/
void run_median_tests(void) {
    if(!test_filter3()) {
        std::cout << "test_filter3:                failed" << std::endl;
    }
    else {
        std::cout << "test_filter3:                ok" << std::endl;
    }

    if(!test_filter3_opt()) {
        std::cout << "test_filter3_opt:            failed" << std::endl;
    }
    else {
        std::cout << "test_filter3_opt:            ok" << std::endl;
    }

    if(!test_filter3_opt_sort_only()) {
        std::cout << "test_filter3_opt_sort_only:  failed" << std::endl;
    }
    else {
        std::cout << "test_filter3_opt_sort_only:  ok" << std::endl;
    }

    if(!test_filter5()) {
        std::cout << "test_filter5:                failed" << std::endl;
    }
    else {
        std::cout << "test_filter5:                ok" << std::endl;
    }

    if(!test_filter5_opt()) {
        std::cout << "test_filter5_opt:            failed" << std::endl;
    }
    else {
        std::cout << "test_filter5_opt:            ok" << std::endl;
    }

    if(!test_filter7()) {
        std::cout << "test_filter7:                failed" << std::endl;
    }
    else {
        std::cout << "test_filter7:                ok" << std::endl;
    }

    if(!test_filter7_opt()) {
        std::cout << "test_filter7_opt:            failed" << std::endl;
    }
    else {
        std::cout << "test_filter7_opt:            ok" << std::endl;
    }

    return;
}

bool test_filter3(void) {
    cv::Mat src0(1024, 1024, cv::DataType<uint8_t>::type);
    cv::Mat dst0 = cv::Mat::zeros(src0.rows, src0.cols, cv::DataType<uint8_t>::type);
    cv::Mat dst1 = cv::Mat::zeros(src0.rows, src0.cols, cv::DataType<uint8_t>::type);
    cv::randu(src0, 0, 255);

    filter3<uint8_t>(src0, dst0);
    filter_cv(src0, dst1, 3);

    if(!diff_matrices(dst0, dst1)) {
        return false;
    }

    return true;
}

bool test_filter3_opt(void) {
    cv::Mat src0(1024, 1024, cv::DataType<uint8_t>::type);
    cv::Mat dst0 = cv::Mat::zeros(src0.rows, src0.cols, cv::DataType<uint8_t>::type);
    cv::Mat dst1 = cv::Mat::zeros(src0.rows, src0.cols, cv::DataType<uint8_t>::type);
    cv::randu(src0, 0, 255);

    filter3_opt<uint8_t>(src0, dst0);
    filter_cv(src0, dst1, 3);

    if(!diff_matrices(dst0, dst1)) {
        return false;
    }

    return true;
}

bool test_filter3_opt_sort_only(void) {
    cv::Mat src0(1024, 1024, cv::DataType<uint8_t>::type);
    cv::Mat dst0 = cv::Mat::zeros(src0.rows, src0.cols, cv::DataType<uint8_t>::type);
    cv::Mat dst1 = cv::Mat::zeros(src0.rows, src0.cols, cv::DataType<uint8_t>::type);
    cv::randu(src0, 0, 255);

    filter3_opt_sort_only<uint8_t>(src0, dst0);
    filter_cv(src0, dst1, 3);

    if(!diff_matrices(dst0, dst1)) {
        return false;
    }

    return true;
}

bool test_filter5(void) {
    cv::Mat src0(1024, 1024, cv::DataType<uint8_t>::type);
    cv::Mat dst0 = cv::Mat::zeros(src0.rows, src0.cols, cv::DataType<uint8_t>::type);
    cv::Mat dst1 = cv::Mat::zeros(src0.rows, src0.cols, cv::DataType<uint8_t>::type);
    cv::randu(src0, 0, 255);

    filter5<uint8_t>(src0, dst0);
    filter_cv(src0, dst1, 5);

    if(!diff_matrices(dst0, dst1)) {
        return false;
    }

    return true;
}

bool test_filter5_opt(void) {
    cv::Mat src0(1024, 1024, cv::DataType<uint8_t>::type);
    cv::Mat dst0 = cv::Mat::zeros(src0.rows, src0.cols, cv::DataType<uint8_t>::type);
    cv::Mat dst1 = cv::Mat::zeros(src0.rows, src0.cols, cv::DataType<uint8_t>::type);
    cv::randu(src0, 0, 255);

    filter5_opt<uint8_t>(src0, dst0);
    filter_cv(src0, dst1, 5);

    if(!diff_matrices(dst0, dst1)) {
        return false;
    }

    return true;
}

bool test_filter7(void) {
    cv::Mat src0(1024, 1024, cv::DataType<uint8_t>::type);
    cv::Mat dst0 = cv::Mat::zeros(src0.rows, src0.cols, cv::DataType<uint8_t>::type);
    cv::Mat dst1 = cv::Mat::zeros(src0.rows, src0.cols, cv::DataType<uint8_t>::type);
    cv::randu(src0, 0, 255);

    filter7<uint8_t>(src0, dst0);
    filter_cv(src0, dst1, 7);

    if(!diff_matrices(dst0, dst1)) {
        return false;
    }

    return true;
}

bool test_filter7_opt(void) {
    cv::Mat src0(1024, 1024, cv::DataType<uint8_t>::type);
    cv::Mat dst0 = cv::Mat::zeros(src0.rows, src0.cols, cv::DataType<uint8_t>::type);
    cv::Mat dst1 = cv::Mat::zeros(src0.rows, src0.cols, cv::DataType<uint8_t>::type);
    cv::randu(src0, 0, 255);

    filter7_opt<uint8_t>(src0, dst0);
    filter_cv(src0, dst1, 7);

    if(!diff_matrices(dst0, dst1)) {
        return false;
    }

    return true;
}

void run_benchmark(void) {
    print = true;
    cv::Mat src0(512, 512, cv::DataType<uint8_t>::type);
    cv::Mat dst0 = cv::Mat::zeros(src0.rows, src0.cols, cv::DataType<uint8_t>::type);
    cv::randu(src0, 10, 64);
    std::cout << "Benchmark for matrix size 512x512:" << std::endl;

    filter3<uint8_t>(src0, dst0);
    filter3_opt<uint8_t>(src0, dst0);
    filter5<uint8_t>(src0, dst0);
    filter5_opt<uint8_t>(src0, dst0);
    filter7<uint8_t>(src0, dst0);
    filter7_opt<uint8_t>(src0, dst0);

    cv::Mat src1(1024, 1024, cv::DataType<uint8_t>::type);
    cv::Mat dst1 = cv::Mat::zeros(src1.rows, src1.cols, cv::DataType<uint8_t>::type);
    cv::randu(src1, 10, 64);
    std::cout << "Benchmark for matrix size 1024x1024:" << std::endl;

    filter3<uint8_t>(src1, dst1);
    filter3_opt<uint8_t>(src1, dst1);
    filter5<uint8_t>(src1, dst1);
    filter5_opt<uint8_t>(src1, dst1);
    filter7<uint8_t>(src1, dst1);
    filter7_opt<uint8_t>(src1, dst1);

    cv::Mat src2(2048, 4096, cv::DataType<uint8_t>::type);
    cv::Mat dst2 = cv::Mat::zeros(src2.rows, src2.cols, cv::DataType<uint8_t>::type);
    cv::randu(src2, 10, 64);
    std::cout << "Benchmark for matrix size 2048x4096:" << std::endl;

    filter3<uint8_t>(src2, dst2);
    filter3_opt<uint8_t>(src2, dst2);
    filter5<uint8_t>(src2, dst2);
    filter5_opt<uint8_t>(src2, dst2);
    filter7<uint8_t>(src2, dst2);
    filter7_opt<uint8_t>(src2, dst2);
    print = false;

    return;
}

/**
* Main function
*/
int main(int argc, char* argv[]) {
    run_sort_tests();
    run_merge_tests();
    run_median_tests();

    if(argc == 1)
    {
        std::cout <<  "Usage: ./median window_size [path/to/image]" << std::endl;
        return -1;
    }

    cv::Mat src;
    if(argc > 2)
    {
        src = cv::imread(argv[2], CV_LOAD_IMAGE_ANYDEPTH);
        if(! src.data )
        {
            std::cout <<  "Could not open or find the image" << std::endl ;
            return -1;
        }
    }
    else 
    {
        src = cv::Mat(4096,2048, cv::DataType<uint8_t>::type);
        cv::randu(src, 10, 64);
    }

    cv::Mat dst0 = cv::Mat::zeros(src.rows, src.cols, cv::DataType<uint8_t>::type);
    int window = atoi(argv[1]);
    
    median_filter<uint8_t>(src, dst0, window);
    imwrite( "filtered0.bmp", dst0 );

    run_benchmark();

    return 0;
}
