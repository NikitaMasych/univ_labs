#include <cmath>
#include <fstream>
#include <string>
#include <vector>

void arr_input(std::vector <int> &a, std::ifstream &in){
    int elem;
    while(!in.eof()){
        in >> elem;
        a.push_back(elem);
    }
}

void arr_output(const std::vector <int> &a, std::string out_p){
    std::ofstream out;
    out.open(out_p, std::ios::app);
    out << "*-------------------------------------***-------------------------------------*\n\n"
        << "                               Resulting array:\n\n";
    for (int i=0; i<a.size(); ++i){
        out << std::right << std::setw(10 + ((i + 1) % 5 == 1) * 12) << a.at(i);
        if (!((i + 1) % 5)) out << '\n';
    }
    if (a.size() % 5 != 0) out << '\n';
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

void proc9(std::vector <int> &a, int val){
    std::vector<int>::iterator min_i = a.begin();
    for (std::vector<int>::iterator i=min_i+1; i!=a.end(); ++i){
        if (*i <= *min_i) min_i = i;
    }
    a.insert(min_i, val);
    a.insert(min_i+2, val);
}

void proc95(std::vector <int> &a, int val){
    std::vector<int>::iterator last_prime = a.end();
    for(std::vector<int>::iterator i=a.begin(); i<a.end(); ++i){
        if (!ferma(*i)) i = a.insert(i, val) + 1;
        else last_prime = i;
    }
    if (last_prime != a.end()) a.insert(last_prime + 1, val);
}

void arr_processing(std::vector <int> &a){
    int val = 0;
    std::cout << "                       Enter the value for inserting: ";
    std::cin >> val;
    std::cout << "\n*-------------------------------------***-------------------------------------*\n\n";
    proc9(a, val);
    proc95(a, val);
}
