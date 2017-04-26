#ifndef __MEDIAN_H__
#define __MEDIAN_H__

// median filter functions
void filter3(cv::Mat& src, cv::Mat& dst);
void filter3_opt(cv::Mat& src, cv::Mat& dst);
void filter3_opt_sort_only(cv::Mat& src, cv::Mat& dst);

void filter5(cv::Mat& src, cv::Mat& dst);
void filter5_opt(cv::Mat& src, cv::Mat& dst);

void filter7(cv::Mat& src, cv::Mat& dst);
void filter7_opt(cv::Mat& src, cv::Mat& dst);

void filter_cv(cv::Mat& src, cv::Mat& dst, int filterSize);

void median_filter(cv::Mat& src, cv::Mat& dst, int filterSize);

// tests
void run_median_tests(void);

bool test_filter3(void);
bool test_filter3_opt(void);
bool test_filter3_opt_sort_only(void);

bool test_filter5(void);
bool test_filter5_opt(void);

bool test_filter7(void);
bool test_filter7_opt(void);

// benchmark
void run_benchmark(void);

#endif