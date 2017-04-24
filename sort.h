/**
* Sorting algorithm
*/

#ifndef __SORT_H__
#define __SORT_H__

// sorting functions
// sorting networks
template <class T>
static inline void sort3(T* a) {
    #define SWAP(x,y) if (a[y] < a[x]) { T tmp = a[x]; a[x] = a[y]; a[y] = tmp; }
    SWAP(1, 2);
    SWAP(0, 2);
    SWAP(0, 1);
    #undef SWAP

    return;
}

template <class T>
static inline void sort5(T* a) {
    #define SWAP(x,y) if (a[y] < a[x]) { T tmp = a[x]; a[x] = a[y]; a[y] = tmp; }
    SWAP(0, 1);
    SWAP(3, 4);
    SWAP(2, 4);
    SWAP(2, 3);
    SWAP(0, 3);
    SWAP(0, 2);
    SWAP(1, 4);
    SWAP(1, 3);
    SWAP(1, 2);
    #undef SWAP

    return;
}

template <class T>
static inline void sort7(T* a) {
    #define SWAP(x,y) if (a[y] < a[x]) { T tmp = a[x]; a[x] = a[y]; a[y] = tmp; }
    SWAP(1, 2);
    SWAP(0, 2);
    SWAP(0, 1);
    SWAP(3, 4);
    SWAP(5, 6);
    SWAP(3, 5);
    SWAP(4, 6);
    SWAP(4, 5);
    SWAP(0, 4);
    SWAP(0, 3);
    SWAP(1, 5);
    SWAP(2, 6);
    SWAP(2, 5);
    SWAP(1, 3);
    SWAP(2, 4);
    SWAP(2, 3);
    #undef SWAP
    
    return;
}

template <class T>
static inline void sort9(T* a) {
    #define SWAP(x,y) if (a[y] < a[x]) { T tmp = a[x]; a[x] = a[y]; a[y] = tmp; }
    SWAP(0, 1);
    SWAP(3, 4);
    SWAP(6, 7);
    SWAP(1, 2);
    SWAP(4, 5);
    SWAP(7, 8);
    SWAP(0, 1);
    SWAP(3, 4);
    SWAP(6, 7);
    SWAP(0, 3);
    SWAP(3, 6);
    SWAP(0, 3);
    SWAP(1, 4);
    SWAP(4, 7);
    SWAP(1, 4);
    SWAP(2, 5);
    SWAP(5, 8);
    SWAP(2, 5);
    SWAP(1, 3);
    SWAP(5, 7);
    SWAP(2, 6);
    SWAP(4, 6);
    SWAP(2, 4);
    SWAP(2, 3);
    SWAP(5, 6);
    #undef SWAP

    return;
}

// insertion sort
template <class T>
static inline void insertion_sort(T* array, int n) {
    T temp;
    int i, j;
    for(i = 0; i < n; i++) {
        temp = array[i];
        for(j = i-1; j >= 0 && temp < array[j]; j--) {
            array[j+1] = array[j];
        }
        array[j+1] = temp;
    }

    return;
}

// tests
void run_sort_tests(void);
bool test_sort3(void);
bool test_sort5(void);
bool test_sort7(void);
bool test_sort9(void);
bool test_insertion_sort(void);

#endif