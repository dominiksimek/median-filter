# Efficient implementation of median filter
#### ZPO project 2016/2017
## Build
#### Requirements
  * gcc, make
  * OpenCV 
#### Compilation
  * make
#### Run example
  * make run
## Usage
* ./median [-i file] [-o file] [-w N] [-c] [-b] [-t] [-h]
  * -i   input file name
  * -o   output file name
  * -w   window size, default 3 (3x3)
  * -c   use OpenCV media filter
  * -b   run benchmark
  * -t   run tests
  * -h   print help

## Examples of usage:
1. Run median filter for input.png
    * ./median -i input.png
    * default window size: 3x3, default output: output_filtered.bmp
2. Run median filter for input.png, window size 5, output image output.png
    * ./median -i input.png -w 5 -o output.png
3. Run OpenCV median filter for input.png, window size 7, output image output.png
    * ./median -i input.png -w 5 -o output.png
3. Run unit tests
    * ./median -t
4. Run unit benchmark
    * ./median -b
5. Print help
    * ./median -h
