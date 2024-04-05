#include <iostream>
#include <cmath>
#include <chrono>
using namespace std;
void func1(int n, double x, double& temp1) 
{
    for(int i = 0; i < n; i++) 
    {
        temp1 += pow(x, 2) - pow(x, 2) + pow(x, 4) - pow(x, 5) + x + x;
    }
}
void func2(int n, double x, double& temp2) 
{
    for(int i = 0; i < n; i++) 
    {
        temp2 += x + x;
    }
}
int main() 
{
    int n;
    double x;
    cin >> n >> x;
    auto start = chrono::high_resolution_clock::now();
    double temp1 = 0, temp2 = 0;
    func1(n,x,temp1);
    func2(n,x,temp2);
        auto end = chrono::high_resolution_clock::now();
    cout << temp1 + temp2 << endl;
    auto duration = chrono::duration_cast<chrono::microseconds>(end - start).count();
     cout<<"Время выполнения программы: "<<duration<<" мкс."<<endl;
    return 0;
}