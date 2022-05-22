/*
    Implements Blake method using PDNF (perfect disjunctive normal form)
    SDNF - shortened disjunctive normal form
    Details: 0 means variable with negative, 1 - positive, _ - absence of variable
    All variables output position sensitive
*/
#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

class booleanFunction{
    private:
        int var_number;
        int cardinality;
        std::vector <char> func;
    public:
        booleanFunction(){
            std::cout << "Enter the number of variables in the boolean function: ";
            std::cin >> var_number;
            cardinality = pow(2, var_number);
            char tmp;
            std::cout << "Enter values of the boolean function:\n";
            for (int i = 0; i != cardinality; ++i){
                std::cin >> tmp;
                func.push_back(tmp);
            }
        }
        void outputBooleanFunction(){
            for(int i = 0; i != cardinality; ++i){
                std::cout << func[i] << " ";
            }
        }

        class PDNF{
            private:
                std::vector<std::vector <char> > representation;
            public:
                PDNF(booleanFunction obj){
                    for (int i = 0; i != obj.cardinality; ++i){
                        if (obj.func[i] == '1'){
                            std::vector <char> SD;
                            int value = i;
                            for (int j = obj.var_number-1; j >= 0; --j){
                                int tmp = pow(2, j);
                                if (value >= tmp){
                                    SD.push_back('1');
                                    value -= tmp;
                                }else SD.push_back('0');
                            }
                            representation.push_back(SD);
                        }
                    }
                }
                void outputPDNF(){
                    std::cout << "Perfert disjunctive normal form: \n";
                    for (int i = 0; i < representation.size(); ++i){
                        for (int j = 0; j < representation[i].size(); ++j){
                            std::cout << representation[i][j] << " ";
                        }
                        std::cout << "\n";
                    }
                }

                friend class booleanFunction;
                friend class SDNF;
        };
        class SDNF{
            private:
                std::vector<std::vector <char> > representation;
            public:
                SDNF(PDNF obj){
                    representation = obj.representation;
                    for (int i = 0; i < representation.size(); ++i){
                        for (int j = 0; j < representation.size(); ++j){
                            int pos = checkMatch(representation[i], representation[j]);
                            if (pos != -1){
                                representation[i][pos] = '_';
                                representation.erase(representation.begin() + j);
                                --i;
                                break;
                            }
                        }
                    }
                }
                int checkMatch(std::vector <char> first, std::vector <char> second){
                    int index, counter = 0;
                    for (int i = 0; i < first.size(); ++i){
                        if (first[i] != second[i]){
                            counter += 1;
                            if (counter > 1) break;
                            index = i;
                        }
                    }
                    return (counter == 1) ? index : -1;
                }
                void outputSDNF(){
                    std::cout << "Shortened disjunctive normal form: \n";
                    for (int i = 0; i < representation.size(); ++i){
                        for (int j = 0; j < representation[i].size(); ++j){
                            std::cout << representation[i][j] << " ";
                        }
                        std::cout << "\n";
                    }
                }
        };
};


int main()
{
    booleanFunction example;
    booleanFunction::PDNF example2(example);
    example2.outputPDNF();
    booleanFunction::SDNF example3(example2);
    example3.outputSDNF();
    return 0;
}
