/*
  Прогнозування вартості нерухомості на базі навчальних даних.
  Реалізовано sanity check з відстежуванням коректності типу даних.
  Логіка полягає у виявленні в початковій виборці 4 наборів з мінімальним розходженням по окремих
  критеріях і надання кожному з них вагової потужності вартості.
  total_price = α.price()*Ρ(α) + β.price()*Ρ(β) + γ.price()*Ρ(γ) + δ.price()*Ρ(δ) + average * τ * Ρ(τ), де
  τ = 0, якщо тип нерухомості житловий, 1 - якщо коммеційний; α, β, γ, δ - (відповідно) виборки
  з найменшою різницею у площі, кількості спальних кімнат, кількості сан-вузлів, та відстанню до метро;
  P()- потужність кожної компоненти у загальній вартості:
  P(α) = 50 %, P(β) = 20 %, Ρ(τ) = 15 %, P(γ) = 10 %, P(δ) = 5 %.
  average = (α.price() + β.price() + γ.price() + δ.price()) / 4.
  Використано кодировку UTF-16.
  Підготував студент групи К-15 Масич Нікіта Дмитрович (асистент Коваль Юрій Віталійович).
*/

#include <iostream>
#include <vector>
#include <io.h>
#include <fcntl.h>

struct features_target{
    double area;
    int bedroom_number;
    int bathroom_number;
    int metro_distance;
    bool accommodation_type;
    double price;

};

struct ponderosity{
    const double ALPHA = 0.5;
    const double BETA = 0.2;
    const double GAMMA = 0.1;
    const double DELTA = 0.05;
    const double TAU = 0.15;
};

std::wstring enter_answer(){
    std::wstring answer;
    std::wcin >> answer;
    std::wstring& a = answer;
    if (answer.size() == 2 && (a[0] == L'н' || a[0] == L'Н')\
        &&(a[1] == L'І' || a[1] == L'і')) answer = L"ні";
    else if (answer.size() == 3 && (a[0] == L'т' || a[0] == L'Т')\
             &&(a[1] == L'а' || a[1] == L'А')&&(a[2] == L'к' || a[2] == L'К')) answer = L"так";
    else{
        std::wcout << L"Введіть один із запропонованих варіантів (так/ні): ";
        answer = enter_answer();
    }
    return answer;
}

double enter_area(){
    double area;
    std::wcout << L"Введіть площу нерухомості (м" << wchar_t(0x00B2) << "): ";
    try{
        std::wstring info;
        std::wcin >> info;
        area = std::stod(info);
        if (area < 0 || area > 1000) throw 1;
    }
    catch(std::exception& ex){
        std::wcout << L"Помилка! Cпробуйте ще раз:" << L'\n';
        area = enter_area();
    }
    catch(int& ex){
        std::wcout << L"Недопустиме значення площі! Cпробуйте ще раз:" << L'\n';
        area = enter_area();
    }
    return area;
}

int enter_bedroom_number(){
    int bedroom_number;
    std::wcout << L"Введіть кількість спальних кімнат: ";
    try{
        std::wstring info;
        std::wcin >> info;
        bedroom_number = std::stoi(info);
        if (bedroom_number < 0 || bedroom_number > 100) throw 1;
    }
    catch(std::exception& ex){
        std::wcout << L"Помилка! Cпробуйте ще раз:" << L'\n';
        bedroom_number = enter_bedroom_number();
    }
    catch(int& ex){
        std::wcout << L"Недопустима кількість спальних кімнат! Cпробуйте ще раз:" << L'\n';
        bedroom_number = enter_bedroom_number();
    }
    return bedroom_number;
}

int enter_bathroom_number(){
    int bathroom_number;
    std::wcout << L"Введіть кількість сан-вузлів: ";
    try{
        std::wstring info;
        std::wcin >> info;
        bathroom_number = std::stoi(info);
        if (bathroom_number < 0 || bathroom_number > 100) throw 1;
    }
    catch(std::exception& ex){
        std::wcout << L"Помилка! Cпробуйте ще раз:" << L'\n';
        bathroom_number = enter_bathroom_number();
    }
    catch(int& ex){
        std::wcout << L"Недопустима кількість сан-вузлів! Cпробуйте ще раз:" << L'\n';
        bathroom_number = enter_bathroom_number();
    }
    return bathroom_number;
}

int enter_metro_distance(){
    int metro_distance;
    std::wcout << L"Введіть відстань до метро (хв пішки): ";
    try{
        std::wstring info;
        std::wcin >> info;
        metro_distance = std::stoi(info);
        if (metro_distance < 0 || metro_distance > 1440) throw 1;
    }
    catch(std::exception& ex){
        std::wcout << L"Помилка! Cпробуйте ще раз:" << L'\n';
        metro_distance = enter_metro_distance();
    }
    catch(int& ex){
        std::wcout << L"Недопустима відстань до метро! Cпробуйте ще раз:" << L'\n';
        metro_distance = enter_metro_distance();
    }
    return metro_distance;
}

bool enter_accommodation_type(){
    int accommodation_type;
    std::wcout << L"Введіть 0, якщо бажаєте коммерційну нерухомість, 1 - якщо житлову: ";
    try{
        std::wstring info;
        std::wcin >> info;
        accommodation_type = std::stoi(info);
        if (accommodation_type != 0 && accommodation_type != 1) throw 1;
    }
    catch(std::exception& ex){
        std::wcout << L"Помилка! Cпробуйте ще раз:" << L'\n';
        accommodation_type = enter_accommodation_type();
    }
    catch(int& ex){
        std::wcout << L"Помилка! Введіть одне з запропонованих позначень:" << L'\n';
        accommodation_type = enter_accommodation_type();
    }
    return bool(accommodation_type);
}

double enter_price(){
    double price;
    std::wcout << L"Введіть вартість нерухомості ($): ";
    try{
        std::wstring info;
        std::wcin >> info;
        price = std::stod(info);
    }
    catch(std::exception& ex){
        std::wcout << L"Помилка! Cпробуйте ще раз:" << L'\n';
        price = enter_price();
    }
    return price;
}

features_target neuron(bool forecast){
    features_target example;
    example.area = enter_area();
    if (example.area != 0){
        example.bedroom_number = enter_bedroom_number();
        example.bathroom_number = enter_bathroom_number();
        example.metro_distance = enter_metro_distance();
        example.accommodation_type = enter_accommodation_type();
        if(!forecast)example.price = enter_price();
    }
    return example;
}

double prediction(features_target &forecast, std::vector <features_target> &dataset){
    double price;
    ponderosity weight;

    double area_difference;
    int bedroom_difference, bathroom_difference, metro_distance_difference;

    int min_area_difference_neuron = 0, min_bedroom_difference_neuron = 0, \
        min_bathroom_difference_neuron = 0, min_metro_distance_difference_neuron = 0;

    int &ad = min_area_difference_neuron, &bad = min_bathroom_difference_neuron,\
        &bed = min_bedroom_difference_neuron, &md = min_metro_distance_difference_neuron;

    for (long long unsigned int i=1; i<dataset.size(); i++){

        area_difference = abs(dataset[i].area - forecast.area);
        bedroom_difference = abs(dataset[i].bedroom_number - forecast.bedroom_number);
        bathroom_difference = abs(dataset[i].bathroom_number - forecast.bathroom_number);
        metro_distance_difference = abs(dataset[i].metro_distance - forecast.metro_distance);

        if (area_difference < dataset[ad].area)ad = i;
        if (bedroom_difference < dataset[bed].bedroom_number)bed = i;
        if (bathroom_difference < dataset[bad].bathroom_number)bad = i;
        if (metro_distance_difference < dataset[md].metro_distance)md = i;

    }

    price = dataset[ad].price * weight.ALPHA;
    price += dataset[bed].price * weight.BETA;
    price += dataset[bad].price * weight.GAMMA;
    price += dataset[md].price * weight.DELTA;
    double average = (dataset[ad].price + dataset[bed].price \
           + dataset[bad].price + dataset[md].price) / 4;
    price += average * forecast.accommodation_type * weight.TAU;

    return price;
}

int main()
{
    _setmode(_fileno(stdout), _O_U16TEXT);
    _setmode(_fileno(stdin), _O_U16TEXT);
    std::wcout << L"Для отримання прогнозу необхідно спочатку ввести базу даних." << \
    L'\n' << L"*Введіть площу 0, щоб завершити введення.*" << L'\n' << L'\n';
    std::vector <features_target> dataset;
    do{
        dataset.push_back(neuron(false));
        if (dataset[dataset.size()-1].area == 0 && dataset.size() == 1){
            std::wcout << L'\n' << L"Порожня база даних! Прогнозування не можливе." << \
            L'\n' << L'\n' << L"Бажаєте ввести знов? (так/ні): ";
            if(enter_answer() == L"так"){
                dataset.pop_back();
                std::wcout << L'\n';
                continue;
            }
            else{
                std::wcout << L'\n' << L"Гарного дня!" <<  L'\n';
                return 0;
            };
        }
        if(dataset[dataset.size()-1].area != 0) {
           std::wcout << L'\n' << L"Завершено введення " << \
           dataset.size() << L" экземпляру." << L'\n' << L'\n';
        }
    }while(dataset[dataset.size()-1].area != 0);
    dataset.pop_back();
    std::wcout << L'\n' << L"Введення бази даних завершено. " << \
                                          L"Введіть дані для прогнозування:" << L'\n' << L'\n';
    do{
        features_target forecast = neuron(true);
        if(forecast.area == 0){
            std::wcout << \
            L"Прогнозування не можливе. Бажаєте ввести нові дані для прогнозування? (так/ні): ";
            continue;
        }
        std::wcout << L'\n' << L"Спрогнозована вартість: " << prediction(forecast, dataset) << L'\n' << L'\n';
        std::wcout << L"Бажаєте ще раз ввести дані для прогнозування? (так/ні): ";
    }while(enter_answer() == L"так");
    std::wcout << L'\n' << L"Гарного дня!" << L'\n';

    return 0;
}
