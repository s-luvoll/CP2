#include <iostream>
#include <fstream>

float tempf(float temp){
  float ergebnis;

  ergebnis=temp*1.8+32;
  return ergebnis;
}

float tempc(float temp){
  float ergebnis;

  ergebnis=(temp-32)*5.0/9.0;
  return ergebnis;
}

int main(int argc, char** argv){
//Einlesen der Datei
    std::ifstream in("input");
    std::ofstream out("output");
    float wert;
    char einheit;
    for (int i = 0; i < 4; ++i){
        in>>wert;
	in>>einheit;
	if (einheit=='F'){
	    wert=tempc(wert);
	    einheit='C';
	}
	else if (einheit=='C'){
	    wert=tempf(wert);
	    einheit='F';
	}
	else{
	std::cout << "Falsche Einheit in Zeile ";
	std::cout << i << std::endl;
	}
	out<<wert;
	out<<" ";
	out<<einheit<<std::endl;
    }
    std::cout << "Datei 'output' geschrieben!\n";
    return 0;
}
