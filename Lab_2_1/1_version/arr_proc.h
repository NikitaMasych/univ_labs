#ifndef ARR_PROC_H_INCLUDED
#define ARR_PROC_H_INCLUDED

#include "arr_proc.cpp"

#endif // ARR_PROC_H_INCLUDED

template<typename T, size_t N>
void random_gen(T (&a), size_t wk_len);
template<typename T, size_t N>
size_t keyboard_input(T(&a)[N], size_t wk_len);
void arr_output(int *a, size_t wk_len);
