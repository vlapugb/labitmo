
#include <cstdlib>
#include <stdexcept>
namespace std {
double sum(double a, double b){return a+b;}
double dev(double a, double b){return a-b;}
double multiyply(double a,double b){return a*b;}
double powf(double a, int b) {
    if(b==0) return 1;
    if(b<0) return 1/powf(a, -b);
    b = static_cast<int>(b);
    double temp = powf(a, b/2);
    return b % 2 == 0 ? powf(a, b/2) * powf (a, b/2) : powf(a, b/2) * powf (a, b/2) * a;
}

double convertToDouble(char* str) 
{
    char* endptr = 0;
    double value = strtod(str, &endptr);
    if (*endptr != '\0' || endptr == str) {
        throw invalid_argument("Славянский зажим яйцами");
    }
    return value;
}
}