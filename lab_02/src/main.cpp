
#include <iostream>
#include "header.hpp"
#include <chrono>
using namespace std;

int main ()
{
    double x;
    int n;
    setlocale(LC_ALL, "ru_RU.UTF-8");
    cout<<"Введите x:"<<endl;
    cin>>x;
    cout<<"Введите n:"<<endl;
    cin>>n;
    auto start = chrono::high_resolution_clock::now();
    for(int i = 0; i < n; ++i)
    calc(1.0, 100);
    auto end = chrono::high_resolution_clock::now();
    
    auto duration = chrono::duration_cast<chrono::nanoseconds>(end - start);
    cout << "Программа выполнилась за " << duration.count() << " наносекунд" << std::endl;

    return 0;
}