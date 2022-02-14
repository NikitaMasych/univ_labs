template<typename T, size_t N>
void random_gen(T (&a)[N], size_t wk_len){
    srand(time(0));
    for (int i=0; i<wk_len; ++i){
        a[i] = rand();
    }
}

template<typename T, size_t N>
size_t keyboard_input(T (&a)[N], size_t wk_len){
    int elem;
    std::cout << '\n';
    while(wk_len < N  && std::cout << std::right << std::setw(29)
          << "Enter a[" << wk_len << "]:"
          << ((wk_len < 10) ? "  " : " ")
          && std::cin >> elem){
        a[wk_len ++] = elem;
    }
    std::cout << "\n*-------------------------------------***-------------------------------------*\n\n";
    return wk_len;
}

void arr_output(int *a, size_t wk_len){
    std::cout << "\n                               Resulting array:\n\n";
    for (int i=0; i<wk_len; ++i){
        std::cout << std::right << std::setw(10+((i+1) % 5 == 1)*12) << a[i];
        if (!((i+1) % 5)) std::cout << '\n';
    }
    if (wk_len % 5 != 0) std::cout << '\n';
    std::cout << "\n*-------------------------------------***-------------------------------------*\n\n";
}
