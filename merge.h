/**
* Implementation of merging algorithms
*
* @author Dominik Simek
* @author Filip Listiak
*
* FIT VUT, ZPO 2016/2017
*/
#ifndef __MERGE_H__
#define __MERGE_H__

/**
* Merge 2 sorted arrays (with arbitrary length) to 3nd array
*/
template <class T>
static inline void merge2_arrays(T* a, int aLen, T* b, int bLen, T* c, int cLen) {
    int i = aLen - 1;
    int j = bLen - 1;
    int k = cLen;

    while (k > 0) {
        c[--k] = (j < 0 || (i >= 0 && a[i] >= b[j])) ? a[i--] : b[j--];
    }

    return;
}

/**
* Merge 3 sorted arrays (with equal length)
*/
template <class T>
static inline void merge3_arrays(T* a, T* b, T* c, T* d, int len) {
    int i = 0;
    int j = 0;
    int k = 0;

    for (int l = 0; l < 3*len; l++) {
        d[l] = i < len && (j >= len || a[i] < b[j])
                ? (k >= len || a[i] < c[k]
                    ? a[i++]
                    : c[k++])
                : (j < len && (k >= len || b[j] < c[k])
                    ? b[j++]
                    : c[k++]);
    }

    return;
}

/**
* merge 5 arrays of 5 elements to one array of size 25
*/
template <class T>
static inline void merge5_arrays(T* a, T* b, T* c, T* d, T* e, T* f) {
    T merged_a_b[15];
    T merged_c_d_e[10];
    merge2_arrays(a, 5, b, 5, merged_a_b, 10);
    merge3_arrays(c, d, e, merged_c_d_e, 5);
    merge2_arrays(merged_a_b, 10, merged_c_d_e, 15, f, 25);

    return;
}

/**
* merge 7 arrays of 7 elements to one array of size 49
*/
template <class T>
static inline void merge7_arrays(T* a, T* b, T* c, T* d, T* e, T* f, T* g, T* h) {
    T merged_a_b_c[21];
    T merged_d_e_f[21];
    T merged_def_g[28];

    merge3_arrays(a, b, c, merged_a_b_c, 7);
    merge3_arrays(d, e, f, merged_d_e_f, 7);
    merge2_arrays(merged_d_e_f, 21, g, 7, merged_def_g, 28);
    merge2_arrays(merged_a_b_c, 21, merged_def_g, 28, h, 49);

    return;
}

/**
* merge 7 arrays of 7 elements to one array of size 49
*/
template <class T>
static inline void merge7_arrays2(T* a, T* b, T* c, T* d, T* e, T* f, T* g, T* h) {
    T merged_a_b[14];
    T merged_c_d[14];
    T merged_e_f[14];
    T merged_ef_g[21];
    T merged_ab_cd[28];

    merge2_arrays(a, 7, b, 7, merged_a_b, 14);
    merge2_arrays(c, 7, d, 7, merged_c_d, 14);
    merge2_arrays(e, 7, f, 7, merged_e_f, 14);
    merge2_arrays(merged_e_f, 14, g, 7, merged_ef_g, 21);
    merge2_arrays(merged_a_b, 14, merged_c_d, 14, merged_ab_cd, 28);
    merge2_arrays(merged_ab_cd, 28, merged_ef_g, 21, h, 49);

    return;
}

/**
* merge 7 arrays of 7 elements to one array of size 49
*/
template <class T>
static inline void merge7_arrays3(T* a, T* b, T* c, T* d, T* e, T* f, T* g, T* h) {
    T merged_a_b[14];
    T merged_ab_c[21];
    T merged_abc_d[28];
    T merged_abcd_e[35];
    T merged_abcde_f[42];

    merge2_arrays(a, 7, b, 7, merged_a_b, 14);
    merge2_arrays(merged_a_b, 14, c, 7, merged_ab_c, 21);
    merge2_arrays(merged_ab_c, 21, d, 7, merged_abc_d, 28);
    merge2_arrays(merged_abc_d, 28, e, 7, merged_abcd_e, 35);
    merge2_arrays(merged_abcd_e, 35, f, 7, merged_abcde_f, 42);
    merge2_arrays(merged_abcde_f, 42, g, 7, h, 49);


    return;
}

/**
* merge 7 arrays of 7 elements to one array of size 49
*/
template <class T>
static inline void merge7_arrays4(T* a, T* b, T* c, T* d, T* e, T* f, T* g, T* h) {
    T merged_a_b[14];
    T merged_ab_c[21];
    T merged_abc_d[28];
    T merged_abcd_e[35];
    T merged_abcde_f[42];

    merge2_arrays(a, 7, b, 7, merged_a_b, 14);
    merge2_arrays(c, 7, merged_a_b, 14, merged_ab_c, 21);
    merge2_arrays(d, 7, merged_ab_c, 21, merged_abc_d, 28);
    merge2_arrays(e, 7, merged_abc_d, 28, merged_abcd_e, 35);
    merge2_arrays(f, 7, merged_abcd_e, 35, merged_abcde_f, 42);
    merge2_arrays(g, 7, merged_abcde_f, 42, h, 49);

    return;
}

void run_merge_tests(void);
bool test_merge2_arrays(void);
bool test_merge3_arrays(void);
bool test_merge5_arrays(void);
bool test_merge7_arrays(void);

#endif