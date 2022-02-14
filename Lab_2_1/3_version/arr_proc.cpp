#include <cmath>
#include <fstream>
#include <string>


bool arr_double(int *& st, int *& fin, int *& tot_end){
    int tot_len = tot_end - st;
    int* tmp = new(std::nothrow) int[tot_len*2];
    std::cout << "                       MEMORY ALLOC: "
              << fin - st << " " << tot_len*2 << " ";
    if (tmp == nullptr) {
        std::cout << "FAILED";
        return false;
    }
    int i = 0;
    for( ;i != fin-st; ++i){
        tmp[i] = st[i];
    }
    delete[] st;
    st = tmp;
    fin = st + i;
    tot_end = st + tot_len*2;
    std::cout << "\n";
    return true;
}

bool arr_input(int *& st, int *& fin, int *& tot_end, std::ifstream &in){
    int elem;
    while(!in.eof()){
        in >> elem;
        if (fin != tot_end){
            *fin = elem;
            fin++;
        }
        else{
            if (!arr_double(st, fin, tot_end)) return false;
            *fin = elem;
            fin++;
        }
    }
    if (fin - st == 1) return false;
    if(tot_end-st > 100) // was additional memory allocation
        std::cout << "\n*-------------------------------------***-------------------------------------*\n\n";
    return true;
}

void arr_output(int *st, int * fin, int * tot_end, std::string out_p){
    std::ofstream out;
    out.open(out_p, std::ios::app);
    out << "*-------------------------------------***-------------------------------------*\n\n"
        << "                               Resulting array:\n\n";
    for (int* i=st; i!=fin; ++i){
        out << std::right << std::setw(10+((i - st + 1) % 5 == 1)*12) << *i;
        if (!((i - st + 1) % 5)) out << '\n';
    }
    if ((fin - st) % 5 != 0) out << '\n';
    out << "\n*-------------------------------------***-------------------------------------*\n\n";
    out.close();
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

bool proc9(int *& st, int *& fin, int *& tot_end, int val){
    if (tot_end - fin < 2 && !arr_double(st, fin, tot_end)) return false;
    int* min_i = st;
    for (int* i=st; i!=fin; ++i){
        if (*i <= *min_i) min_i = i;
    }
    fin += 2;
    for (int* i=fin; i!= min_i+2; --i){
        *(i) = *(i-2);
    }
    *(min_i + 1) = * min_i;
    * min_i = val;
    *(min_i + 2) = val;
    return true;
}

bool proc95(int *& st, int *& fin, int *& tot_end, int val){
    int last_prime = -1;
    for(int i=0; i!=fin-st; ++i){
        if (!ferma(*(st+i))){
            if (tot_end == fin && !arr_double(st, fin, tot_end)) return false;
            pre_insertion(st, fin, st+i, val);
            ++ i;
        }
        else last_prime = i;
    }
    if (last_prime != -1){
        if (tot_end == fin) arr_double(st, fin, tot_end);
        pre_insertion(st, fin, st + last_prime + 1, val);
    }
    return true;
}

bool arr_processing(int *& st, int *& fin, int *& tot_end){
    int val = 0;
    std::cout << "                       Enter the value for inserting: ";
    std::cin >> val;
    std::cout << "\n*-------------------------------------***-------------------------------------*\n\n";
    if(!proc9(st, fin, tot_end, val) || !proc95(st, fin, tot_end, val))return false;
    return true;
}

