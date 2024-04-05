#include <iostream>
#include <cmath>
using namespace std;
void func2(int n, double x, double& temp2) 
{
    for(int i = 0; i < n; i++) 
    {
        temp2 += x + x;
    }
}
int main ()
{
    double temp2=0;
    func2(1000000, 10, temp2);
    cout<<temp2<<endl;
    return 0;
}
