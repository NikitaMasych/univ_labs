#ifndef ARR_PROC_H_INCLUDED
#define ARR_PROC_H_INCLUDED

#include "arr_proc.cpp"
#include "input_gen.cpp"

#endif // ARR_PROC_H_INCLUDED

void arr_input(std::vector <int> &a, std::ifstream &in);
void arr_output(const std::vector <int> &a, std::string out_p);
void arr_processing(std::vector <int> &a);
