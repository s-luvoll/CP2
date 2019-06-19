#include <iostream>
#include <random>
#include <fstream>
#include <array>


const int teilchen=1000000;
//Entscheidung ob links oder rechts
int lr(float v){
    if (v<0.5){
        return(-1);
    }
    else{
    return(1);
    }
}

//Erstes Moment berechnen
int m1(std::array<int,teilchen> dots){
    int m=0;
    for (int i = 0; i < teilchen; ++i){
        m=m+dots[i];
    }
    return m;
}

//Zweites Moment berechnen
int m2(std::array<int,teilchen> dots){
    int m=0;
    for (int i = 0; i < teilchen; ++i){
        m=m+(dots[i]*dots[i]);
    }
    return m;
}

int main(int argc, char** argv){
std::mt19937 gen;
gen.seed(12447987);
std::uniform_real_distribution<> dis(0,1);
    std::array<int,teilchen> dots;
    std::ofstream out ("output.txt");
    //Teilchen initialisieren
    for (int i = 0; i < teilchen; ++i){
        dots[i]=0;
    }
    //Schleife über die Zeitschritte
    int steps=1000;
    for (int i = 0; i < steps; ++i){
	for (int k = 0; k < teilchen; ++k){
	    dots[k]=dots[k]+lr(dis(gen));
//	    std::cout << dots[k] << std::endl;
	}
      out<< i << " " << m1(dots) << " " << m2(dots) << std::endl;
    }

    return 0;
}



