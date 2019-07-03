#include <iostream>
#include <fstream>
#include <array>
#include <math.h>

bool abbruch(std::array<std::array<double,100>,100> potentialn,std::array<std::array<double,100>,100>potentiala,double fmax){
  std::array<double,10000> fehler;  
  for (int i = 0; i < 100; ++i){
        for (int j = 0; j < 100; ++j){
            double diff=pow(pow(potentialn[i][j]-potentiala[i][j],2),0.5);
	    fehler[i*100+j]=diff/potentialn[i][j];
	   // std::cout << fault << std::endl;
	}
  }
  double a=0;
  for (int i = 0; i < 10000; ++i){
      if (fehler[i]>a){
          a=fehler[i];
      }
  }
  if (a<=fmax){
      return 0;
  }
  else return 1;
}

int main(int argc, char** argv){
    //Potential intertialisieren
    std::array<std::array<double,100>,100> pot;
    for (int i = 0; i < 100; ++i){
        for (int j = 0; j < 100; ++j){
            pot[i][j]=0;
        }
    }
    //
    //Randbedingungen einfügen
    for (int i = 0; i < 100; ++i){
        pot[0][i]=1000;
    }
    
    //Ladungsverteilung definieren
    std::array<std::array<double,100>,100> ladung;
    for (int i = 0; i < 100; ++i){
        for (int j = 0; j < 100; ++j){
            ladung[i][j]=0;
        }
    }
    
    ladung[50][50]=-1000;


    //Solver
    std::array<std::array<double,100>,100> potn;
    potn=pot;
    bool abb;
    int i=0;
    do{
      for (int i = 1; i < 99; ++i){
	  for (int j = 1; j < 99; ++j){
	      potn[i][j]=(pot[i+1][j]+pot[i-1][j]+pot[i][j+1]+pot[i][j-1]+ladung[i][j])/4;
	  }
      }
      abb = abbruch(potn,pot,0.01);
      pot=potn;
      i++;
    }while(abb);

    //Ausgabe
    std::ofstream out ("Potential.txt");
    for (int i = 0; i < 100; ++i){
        for (int j = 0; j < 100; ++j){
            out << i << " " << j << " " << pot[i][j] << std::endl;
        }
    }

    return 0;
}
