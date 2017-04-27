/**
* Simple utils implementation
*
* @author Dominik Simek
* @author Filip Listiak
*
* FIT VUT, ZPO 2016/2017
*/

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

/**
* Parse command line arguments
*/
bool parse_cmd(int argc, char *argv[], TArgs& args) {
    extern int opterr;
    opterr = 0;

    if(argc < 2) {
        return false;
    }

    char command;
    while((command = getopt(argc, argv, "i:o:w:hbtc")) != -1) {
        switch(command) {
            case 'i':
                args.input = optarg;
                break;
            case 'o':
                args.output = optarg;
                break;
            case 'w':
                args.win = std::atoi(optarg);
                break;
            case 'h':
                args.help = true;
                break;
            case 'b':
                args.benchmark = true;
                break;
            case 't':
                args.test = true;
                break;
            case 'c':
                args.cv = true;
                break;   
            case ':':
            case '?':
                args.help = true;
                break;
        }
    }   

    if(args.help || (args.input.empty() && !args.benchmark && !args.test)) {
        return false;
    }
    if(args.output.empty()) {
        args.output = "output_filtered.bmp";
    }
    if(args.win == 0) {
        args.win = 3;
    }

    return true;
}

/**
* Print help
*/
void print_help(void) {
    using namespace std;
    cout << "Usage: ./median [-i file] [-o file] [-w N] [-b] [-t] [-h]" << endl;
    cout << "  -i   input file name" << endl;
    cout << "  -o   output file name" << endl;
    cout << "  -w   window size, default 3 (3x3)" << endl;
    cout << "  -c   use OpenCV media filter" << endl;
    cout << "  -b   run benchmark" << endl;
    cout << "  -t   run tests" << endl;
    cout << "  -h   print help" << endl;

    return;
}
