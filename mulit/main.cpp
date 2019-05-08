#include <iostream>
double multi(double f1,double f2,double f3){
 return f1*f2*f3;
}

int main(int argc, char** argv){
    double a,b,c;
    std::cin >> a;
    std::cin >> b;
    std::cin >> c;
    double ergebnis = multi(a,b,c);
    std::cout << "Das Ergebnis ist: " << ergebnis  << std::endl;
    return 0;
}
