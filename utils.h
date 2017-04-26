/**
* Interface for utils functions
*
* @author Dominik Simek
* @author Filip Listiak
*
* FIT VUT, ZPO 2016/2017
*/

#ifndef __UTILS_H__
#define __UTILS_H__

#include <iostream>
#include <ctime>
#include <chrono>

#include <getopt.h>

#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

// type for time measurement
typedef std::chrono::steady_clock::time_point TTimePoint;

// structure for command line arguments
struct TArgs {
    std::string input;
    std::string output;
    int win;
    bool help;
    bool benchmark;
    bool test;
    TArgs () : input(""), output(""), win(0), help(false), benchmark(false), test(false) {}; 
};

template <class T>
void print_matrix(const cv::Mat &mat0);
bool diff_matrices(const cv::Mat& mat0, const cv::Mat& mat1, const std::string description="", bool print_stats=false);
bool parse_cmd(int argc, char *argv[], TArgs& args);
void print_help(void);


#endif