#include <cmath>

template<typename T, size_t N>
void random_gen(T (&a)[N], size_t wk_len){
    srand(time(0));
    for (size_t i=0; i<wk_len; ++i){
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
    std::cout << "\n*-------------------------------------***-------------------------------------*\n";
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

long long gcd(long long a, long long b){
	return (b == 0) ? a : gcd(b, a % b);
}

long long mul(long long a, long long b, long long m){
	if(b == 1) return a;
	if(b % 2 == 0){
		long long t = mul(a, b/2, m);
		return (2 * t) % m;
	}
	return (mul(a, b-1, m) + a) % m;
}

long long pows(long long a, long long b, long long m){
	if(b == 0) return 1;
	if(b % 2 == 0){
		long long t = pows(a, b/2, m);
		return mul(t, t, m) % m;
	}
	return (mul(pows(a, b-1, m), a, m)) % m;
}

bool ferma(long long x){
	if(x == 2)
		return true;
	srand(time(0));
	for(int i=0; i<100; i++){
		long long a = (rand() % (x - 2)) + 2;
		if(gcd(a, x) != 1) return false;
		if(pows(a, x-1, x) != 1) return false;
	}
	return true;
}

void pre_insertion(int *st, int *& fin , int* pos, int val){
    fin++;
    for(int* i=fin; i!=pos; --i)
        *i = *(i-1);
    *pos = val;

}

void proc9(int *st, int *& fin, int *tot_end, int val){
    if (tot_end - fin < 2)throw std::exception();
    int* min_i = st;
    for (int* i=st; i!=fin; ++i){
        if (*i < *min_i) min_i = i;
    }
    fin += 2;
    for (int* i=fin; i!= min_i+2; --i){
        *(i) = *(i-2);
    }
    *(min_i + 1) = * min_i;
    * min_i = val;
    *(min_i + 2) = val;
}

void proc95(int *st, int *& fin, int *tot_end, int val){
    int rem_len = tot_end - fin;
    int *last_prime = nullptr;
    int counter = 0;
    int moment_counter = 0;
    for(int* i=st; i < fin; ++i){
        if (!ferma(*i)){
            if (rem_len == 0) throw std::exception();
            pre_insertion(st, fin, i, val);
            -- rem_len;
            ++ counter;
            ++ i;
        }
        else {last_prime = i; moment_counter = counter;}
    }
    if (last_prime != nullptr){
        if (rem_len == 0) throw std::exception();
        pre_insertion(st, fin, last_prime + moment_counter + 1, val);
    }
}

size_t arr_processing(int *st, int *fin, int *tot_end){
    int val;
    std::cout << "                     Enter the value for inserting: ";
    std::cin >> val;
    std::cout << "\n*-------------------------------------***-------------------------------------*\n";
    proc9(st, fin, tot_end, val);
    proc95(st, fin, tot_end, val);
    return fin - st;
}
