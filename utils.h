#ifndef __UTILS_H__
#define __UTILS_H__

#include <iostream>

#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

template <class T>
void print_matrix(const cv::Mat &mat0);
bool diff_matrices(const cv::Mat& mat0, const cv::Mat& mat1, const std::string description="", bool print_stats=false);

#endif