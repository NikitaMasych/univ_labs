#include <iostream>
#include <ctime>
#include <iomanip>
#include "arr_proc.h"


void print_work_id(){
    std::cout << "\n*-------------------------------------***-------------------------------------*\n\n"
              << "                                    Morning!\n"
              << "        This is Lab 1.3 for the 2-nd semester of the course \"Programming\".\n"
              << "           Project done by student Masych Nikita from the group K-15.\n\n"
              << "*-------------------------------------***-------------------------------------*\n\n";
}

void enter_path(std::string &in_p, std::string &out_p, bool is_second){
    std::cout << "                       Enter the path to the input file: ";
    std::getline(std::cin, in_p);
    if (in_p.length() == 0) in_p = "in.txt";
    if (!is_second){
        std::cout << "                       Enter the path to the output file: ";
        std::getline(std::cin, out_p);
        if (out_p.length() == 0) out_p = "out.txt";
    }
    std::cout << "\n*-------------------------------------***-------------------------------------*\n\n";
}

int main(){
    print_work_id();
    inp_gen();

    std::ifstream in;
    std::string in_p, out_p;
    bool is_second = false;
    do{
        enter_path(in_p, out_p, is_second);
        in.open(in_p);
        is_second = true;
    }while(!in.is_open() && std::cout << "                       Unable to open, please try again:\n\n" );

    const int N = 100;
    int* st = new int[N];
    int* fin = st;
    int* tot_end = st + N;

    if (!arr_input(st, fin, tot_end, in)){
            std::cout << "                           Unsuccessful array input!\n"
                        << "\n*-------------------------------------***-------------------------------------*\n\n";
            return 0;
    }
    arr_output(st, fin, tot_end, out_p);
    if (!arr_processing(st, fin, tot_end)) return 0;
    arr_output(st, fin, tot_end, out_p);

    return 0;
}
