#include <iostream>
#include <ctime>
#include <iomanip>
#include "arr_proc.h"

int enter_command(){
    int cmd;
    std::cout << "                     Enter 1 for random array generating, \n"
              << "                     Enter 2 for keyboard array input, \n"
              << "                     Enter another number for program ending: ";
    std::cin >> cmd;
    std::cout << "\n*-------------------------------------***-------------------------------------*\n";
    return cmd;
}

void print_work_id(){
    std::cout << "\n*-------------------------------------***-------------------------------------*\n\n"
              << "                                    Morning!\n"
              << "        This is Lab 1.1 for the 2-nd semester of the course \"Programming\".\n"
              << "           Project done by student Masych Nikita from the group K-15.\n\n"
              << "*-------------------------------------***-------------------------------------*\n\n";
}

int main(){
    print_work_id();

    const int N = 13;
    int a[N];
    size_t wk_len = 0;

    switch (enter_command()){
    case 1:
        srand(time(0));
        wk_len = (rand() % N) + 1;
        random_gen(a, wk_len);
        break;

    case 2:
        wk_len = keyboard_input(a, wk_len);
        if (!wk_len){
                std::cout << "                          Unsuccessful array input!\n"
                          << "\n*-------------------------------------***-------------------------------------*\n\n";
                return 0;
        }
        break;

    default:
        return 0;

    }
    arr_output(a, wk_len);
    return 0;
}
