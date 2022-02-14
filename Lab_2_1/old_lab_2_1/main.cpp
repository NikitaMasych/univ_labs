#include <iostream>
#include <ctime>
#include <iomanip>
#include "arr_proc.h"

int enter_command(){
    int cmd;
    std::cout << "Enter 1 for random array generating, \n"
              << "Enter 2 for keyboard array input, \n"
              << "Enter 9 for program ending: ";
    std::cin >> cmd;
    return cmd;
}

int main(){
    const int N = 20;
    int a[N + 1];
    int wk_len = 0;

    switch (enter_command()){
    case 9:
    {
        return 0;
        break;
    }
    case 1:
    {
        random_gen(a, N, wk_len);
        break;
    }
    case 2:
    {
        keyboard_input(a, N, wk_len);
        break;
    }
    }
    arr_output(a, wk_len);
    arr_processing(a, wk_len);
    return 0;
}
