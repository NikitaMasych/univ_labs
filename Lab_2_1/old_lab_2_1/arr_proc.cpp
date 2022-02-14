void random_gen(int * a , int N, int& wk_len){
    std::cout << "Enter number of array elements: ";
    std::cin >> wk_len;
    srand(time(0));
    for (int i=0; i<wk_len; ++i){
        a[i] = rand() % 100;
    }
}

void keyboard_input(int *a, int N, int& wk_len){
    char elem;
    while(wk_len < N  && std::cout << "Enter a[" << wk_len << "]: "
          && std::cin.get(elem) && std::cin.get(elem) && elem != '\n'){
        a[wk_len] = int(elem) - 48;
        wk_len ++;
    }
}

void arr_output(int *a, int wk_len){

    for (int i=0; i<wk_len; ++i){
        std::cout << a[i] << std::setw(4);
        if ((i+1) % 5 == 0) std::cout << '\n';
    }

}

void swap(int *a, int * b){
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

void arr_rev(int* st, int * fin){
    while(st < fin){
        swap(st++, fin--);
    }
}

void proc4(int * a, int wk_len, int shift = 2){
    if(shift %= wk_len){
        arr_rev(a, a + shift - 1);
        arr_rev(a+shift, a + wk_len - 1);
        arr_rev(a, a + wk_len - 1);
    }
}

void proc5(int * a, int wk_len, int shift = 2){
    if(shift %= wk_len){
        arr_rev(a, a + wk_len - 1);
        arr_rev(a, a + shift - 1);
        arr_rev(a+shift, a + wk_len - 1);
    }
}

void proc7(int * a, int wk_len){
    int shift = (wk_len + 1) / 2;
    arr_rev(a, a + wk_len - 1);
    arr_rev(a, a + shift - 1);
    arr_rev(a+shift, a + wk_len - 1);
}

void proc10(int * a, int &wk_len){
    int max_i = 0;
    int val;
    std::cout << "Enter value: ";
    std::cin >> val;
    for(int i=1; i<wk_len; ++i)
        if (a[max_i] < a[i]) max_i = i;
    a[wk_len] = val;
    wk_len ++;
    arr_rev(a + max_i + 1, a + wk_len - 1);
    arr_rev(a + max_i + 2, a + wk_len - 1);
}

void proc11(int * a, int &wk_len){
    int max_i = 0;
    int val;
    std::cout << "Enter value: ";
    std::cin >> val;
    for(int i=1; i<wk_len; ++i)
        if (a[max_i] < a[i]) max_i = i;
    a[wk_len] = val;
    wk_len ++;
    arr_rev(a + max_i, a + wk_len - 1);
    arr_rev(a + max_i + 1, a + wk_len - 1);
}

void arr_processing(int * a, int& wk_len){
    proc4(a, wk_len);
    proc5(a, wk_len);
    proc7(a, wk_len);
    proc10(a, wk_len);
    proc11(a, wk_len);
}
