/**
* Tests
*/

#include <cstdint>
#include <cstring>
#include <iostream>

#include "sort.h"

void run_sort_tests(void) {
    if(!test_sort3()) {
        std::cout << "test_sort3:            failed" << std::endl;
    }
    else {
        std::cout << "test_sort3:            ok" << std::endl;
    }

    if(!test_sort5()) {
        std::cout << "test_sort5:            failed" << std::endl;
    }
    else {
        std::cout << "test_sort5:            ok" << std::endl;
    }

    if(!test_sort7()) {
        std::cout << "test_sort7:            failed" << std::endl;
    }
    else {
        std::cout << "test_sort7:            ok" << std::endl;
    }

    if(!test_sort9()) {
        std::cout << "test_sort9:            failed" << std::endl;
    }
    else {
        std::cout << "test_sort9:            ok" << std::endl;
    }

    if(!test_insertion_sort()) {
        std::cout << "test_insertion_sort:   failed" << std::endl;
    }
    else {
        std::cout << "test_insertion_sort:   ok" << std::endl;
    }


    return;
}

bool test_sort3(void) {
    uint8_t a[3]  = {0, 1, 2};
    uint8_t ar[3] = {0, 1, 2};
    uint8_t b[3]  = {9, 5, 1};
    uint8_t br[3] = {1, 5, 9};
    uint8_t c[3]  = {2, 2, 2};
    uint8_t cr[3] = {2, 2, 2};
    
    sort3(a);
    sort3(b);
    sort3(c);

    if(memcmp(a, ar, sizeof(a)) != 0) {
        return false;
    }
    if(memcmp(b, br, sizeof(b)) != 0) {
        return false;
    }
    if(memcmp(c, cr, sizeof(c)) != 0) {
        return false;
    }

    return true;
}

bool test_sort5(void) {
    uint8_t a[5]  = {0, 1, 2, 3, 4};
    uint8_t ar[5] = {0, 1, 2, 3, 4};
    uint8_t b[5]  = {9, 5, 1, 0, 15};
    uint8_t br[5] = {0, 1, 5, 9, 15};
    uint8_t c[5]  = {2, 2, 2, 2, 2};
    uint8_t cr[5] = {2, 2, 2, 2, 2};
    
    sort5(a);
    sort5(b);
    sort5(c);

    if(memcmp(a, ar, sizeof(a)) != 0) {
        return false;
    }
    if(memcmp(b, br, sizeof(b)) != 0) {
        return false;
    }
    if(memcmp(c, cr, sizeof(c)) != 0) {
        return false;
    }

    return true;
}

bool test_sort7(void) {
    uint8_t a[7]  = {0, 1, 2, 3, 4, 5, 6};
    uint8_t ar[7] = {0, 1, 2, 3, 4, 5, 6};
    uint8_t b[7]  = {9, 5, 1, 0, 15, 6, 255};
    uint8_t br[7] = {0, 1, 5, 6, 9, 15, 255};
    uint8_t c[7]  = {2, 2, 2, 2, 2, 2, 2};
    uint8_t cr[7] = {2, 2, 2, 2, 2, 2, 2};
    
    sort7(a);
    sort7(b);
    sort7(c);

    if(memcmp(a, ar, sizeof(a)) != 0) {
        return false;
    }
    if(memcmp(b, br, sizeof(b)) != 0) {
        return false;
    }
    if(memcmp(c, cr, sizeof(c)) != 0) {
        return false;
    }

    return true;
}

bool test_sort9(void) {
    uint8_t a[9]  = {0, 1, 2, 3, 4, 5, 6, 7, 8};
    uint8_t ar[9] = {0, 1, 2, 3, 4, 5, 6, 7, 8};
    uint8_t b[9]  = {9, 5, 1, 0, 15, 6, 255, 200, 10};
    uint8_t br[9] = {0, 1, 5, 6, 9, 10, 15, 200, 255};
    uint8_t c[9]  = {2, 2, 2, 2, 2, 2, 2, 2, 2};
    uint8_t cr[9] = {2, 2, 2, 2, 2, 2, 2, 2, 2};
    
    sort9(a);
    sort9(b);
    sort9(c);

    if(memcmp(a, ar, sizeof(a)) != 0) {
        return false;
    }
    if(memcmp(b, br, sizeof(b)) != 0) {
        return false;
    }
    if(memcmp(c, cr, sizeof(c)) != 0) {
        return false;
    }

    return true;
}

bool test_insertion_sort(void) {
    uint8_t a[9]  = {0, 1, 2, 3, 4, 5, 6, 7, 8};
    uint8_t ar[9] = {0, 1, 2, 3, 4, 5, 6, 7, 8};
    uint8_t b[9]  = {9, 5, 1, 0, 15, 6, 255, 200, 10};
    uint8_t br[9] = {0, 1, 5, 6, 9, 10, 15, 200, 255};
    uint8_t c[4]  = {2, 2, 2, 2};
    uint8_t cr[4] = {2, 2, 2, 2};
    
    insertion_sort(a, 9);
    insertion_sort(b, 9);
    insertion_sort(c, 4);

    if(memcmp(a, ar, sizeof(a)) != 0) {
        return false;
    }
    if(memcmp(b, br, sizeof(b)) != 0) {
        return false;
    }
    if(memcmp(c, cr, sizeof(c)) != 0) {
        return false;
    }

    return true;
}