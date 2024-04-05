#include <iostream>
#include <cmath>
#include <chrono>
#include <boost/thread.hpp>
#include <boost/process.hpp>
#include <boost/ref.hpp>
using namespace std;
using bt = boost::thread; //не пространсво имен, а именно класс boost обращающийся к thread.
void func1(int n, double x, double& result) 
{
    double temp1=0;
    for(int i = 0; i < n; i++) 
    {
        temp1 += pow(x, 2) - pow(x, 2) + pow(x, 4) - pow(x, 5) + x + x;
    }
    result += temp1;
}
void func2(int n, double x, double& result) 
{
     double temp2=0;
    for(int i = 0; i < n; i++) 
    {
        temp2 += x + x;
    }
    result = temp2;
}
int main() 
{
    int n;
    double x;
    double temp1 = 0, temp2 = 0;
    cin >> n >> x;
    auto start = chrono::high_resolution_clock::now();
    bt thread1(boost::bind(&func1, n, x, boost::ref(temp1)));
    bt thread2(boost::bind(&func2, n, x, boost::ref(temp2)));
    thread1.join();
    thread2.join();                         
        auto end = chrono::high_resolution_clock::now();
    cout<<"Результат 1: "<<temp1<<endl;
    cout<<"Результат 2: "<<temp2<<endl;
    auto duration = chrono::duration_cast<chrono::microseconds>(end - start).count();
     cout<<"Время выполнения программы: "<<duration<<" мкс."<<endl;
    return 0;
}