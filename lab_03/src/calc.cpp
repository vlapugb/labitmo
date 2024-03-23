#include "calc.hpp"
#include <vector>
#include <iostream>
using namespace std;

int main(int argc, char* argv[])
{
    if(argc < 4) cerr<<"Input error"<<endl;
    char op = *argv[argc-1];
vector <double> vecnew;
     try
     {
        for (int i = 1; i < argc-1; ++i)
     {
        vecnew.push_back(convertToDouble(argv[i]));
     }
     
       if(op == '^') 
       {
        for (int i = 1; i < argc-1; ++i)
     {
        if(static_cast<int>(vecnew[i]) != vecnew[i])
        throw invalid_argument("Славянский зажим яйцами будет");
     }
        cout << powf(vecnew[0], static_cast<int>(vecnew[1])) << endl;


       }
       if(op == '+') cout << sum(vecnew[0], vecnew[1]) << endl;
       if(op == '*') cout << multiyply(vecnew[0], vecnew[1]) << endl;
       if(op == '-') cout << dev(vecnew[0], vecnew[1]) << endl;
     }
     catch (const invalid_argument& ex)
     {
        cerr << " Error: " << ex.what() << '\n';
        return 1;
     }
      catch (const exception& ex2) {
        cerr << "Error: " << ex2.what() << '\n';
        return 1;
    }
    return 0;
}
