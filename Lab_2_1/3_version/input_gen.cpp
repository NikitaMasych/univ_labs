#include <fstream>
#include <ctime>

void inp_gen(){
    std::ofstream out;
    out.open("input.txt");
    srand(time(0));
    int N = rand() % 1000;
    for(int i=0; i<N-1; ++i)out << rand() % 100 << " ";
    out << rand() % 100;
    out.close();
}
