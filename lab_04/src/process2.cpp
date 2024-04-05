#include <iostream>
#include <cmath>
using namespace std;
void func1(int n, double x, double& temp1) 
{
    for(int i = 0; i < n; i++) 
    {
        temp1 += pow(x, 2) - pow(x, 2) + pow(x, 4) - pow(x, 5) + x + x;
    }
}
int main ()
{
    double temp=0;
    func1(1000000, 10, temp);  
    cout<<temp<<endl;
    return 0;
}