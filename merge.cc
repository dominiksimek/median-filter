/**
* Tests
*/

#include <cstdint>
#include <cstring>
#include <iostream>

#include "merge.h"

void run_merge_tests(void) {
    if(!test_merge2_arrays()) {
        std::cout << "test_merge2_arrays:          failed" << std::endl;
    }
    else {
        std::cout << "test_merge2_arrays:          ok" << std::endl;
    }

    if(!test_merge3_arrays()) {
        std::cout << "test_merge3_arrays:          failed" << std::endl;
    }
    else {
        std::cout << "test_merge3_arrays:          ok" << std::endl;
    }

    if(!test_merge5_arrays()) {
        std::cout << "test_merge5_arrays:          failed" << std::endl;
    }
    else {
        std::cout << "test_merge5_arrays:          ok" << std::endl;
    }

    if(!test_merge7_arrays()) {
        std::cout << "test_merge5_arrays:          failed" << std::endl;
    }
    else {
        std::cout << "test_merge5_arrays:          ok" << std::endl;
    }

    return;
}

bool test_merge2_arrays(void) {
    uint8_t a[3]   = {0, 2, 4};
    uint8_t b[3]   = {1, 9, 255};
    uint8_t abr[6] = {0, 1, 2, 4, 9, 255};
    uint8_t ab[6];

    uint8_t c[5]   = {0, 2, 4, 9, 100};
    uint8_t d[7]   = {1, 9, 9, 69, 127, 201, 255};
    uint8_t cdr[12] = {0, 1, 2, 4, 9, 9, 9, 69, 100, 127, 201, 255};
    uint8_t cd[12];

    merge2_arrays(a, 3, b, 3, ab, 6);
    merge2_arrays(c, 5, d, 7, cd, 12);

    if(memcmp(ab, abr, sizeof(ab)) != 0) {
        return false;
    }
    if(memcmp(cd, cdr, sizeof(cd)) != 0) {
        return false;
    }

    return true;
}

bool test_merge3_arrays(void) {
    uint8_t a[3]    = {0, 2, 4};
    uint8_t b[3]    = {1, 9, 255};
    uint8_t c[3]    = {2, 10, 12};
    uint8_t abcr[9] = {0, 1, 2, 2, 4, 9, 10, 12, 255};
    uint8_t abc[9];

    merge3_arrays(a, b, c, abc, 3);

    if(memcmp(abc, abcr, sizeof(abc)) != 0) {
        return false;
    }

    return true;
}

bool test_merge5_arrays(void) {
    uint8_t a[5] = {0, 2, 4, 6, 8};
    uint8_t b[5] = {0, 2, 4, 6, 8};
    uint8_t c[5] = {9, 10, 11, 12, 13};
    uint8_t d[5] = {1, 9, 20, 30, 40};
    uint8_t e[5] = {1, 2, 3, 4, 5};
    uint8_t abcder[25] = {0, 0, 1, 1, 2, 2, 2, 3, 4, 4, 4, 5, 6, 6, 8, 8, 9, 9, 10, 11, 12, 13, 20, 30, 40};
    uint8_t abcde[25];

    merge5_arrays(a, b, c, d, e, abcde);

    if(memcmp(abcde, abcder, sizeof(abcde)) != 0) {
        return false;
    }

    return true;
}

bool test_merge7_arrays(void) {
    uint8_t a[7] = {0, 2, 4, 6, 8, 10, 12};
    uint8_t b[7] = {0, 2, 4, 6, 8, 10, 12};
    uint8_t c[7] = {1, 3, 5, 7, 9, 11, 13};
    uint8_t d[7] = {1, 3, 5, 7, 9, 11, 13};
    uint8_t e[7] = {14, 16, 18, 20, 22, 24, 26};
    uint8_t f[7] = {14, 16, 18, 20, 22, 24, 26};
    uint8_t g[7] = {15, 17, 19, 21, 23, 25, 27};
    uint8_t abcdefgr[49] = {0, 0, 1, 1, 2, 2, 3, 3, 4, 4, 5, 5, 6, 6, 7, 7, 8, 8, 9, 9, 10, 10, \
                            11, 11, 12, 12, 13, 13, 14, 14, 15, 16, 16, 17, 18, 18, 19, 20, 20, \
                            21, 22, 22, 23, 24, 24, 25, 26, 26, 27};
    uint8_t abcdefg[49];

    merge7_arrays(a, b, c, d, e, f, g, abcdefg);

    if(memcmp(abcdefg, abcdefgr, sizeof(abcdefg)) != 0) {
        return false;
    }

    return true;
}
