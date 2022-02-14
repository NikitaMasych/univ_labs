#ifndef ARR_PROC_H_INCLUDED
#define ARR_PROC_H_INCLUDED

#include "arr_proc.cpp"
#include "input_gen.cpp"

#endif // ARR_PROC_H_INCLUDED

bool arr_input(int *& st, int *& fin, int *& tot_end, std::ifstream &in);
void arr_output(int *st, int * fin, int * tot_end, std::string out_p);
bool arr_processing(int *& st, int *& fin, int *& tot_end);
