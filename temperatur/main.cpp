#include <iostream>
#include <fstream>
#include <array>

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
    struct Temperaturen{
      std::array<float,4> wert;
      std::array<char,4> einheit;
    };
    Temperaturen eingabe;
    std::ifstream in("input");
    std::ofstream out("output");
    for (int i = 0; i < 4; ++i){
        in>>eingabe.wert[i];
	in>>eingabe.einheit[i];
    }
//Ausgabematrix definieren
    Temperaturen ausgabe;
//Ausrechnen
	for (int i = 0; i < 4; ++i){  
	if (eingabe.einheit[i]=='F'){
	    ausgabe.wert[i]=tempc(eingabe.wert[i]);
	    ausgabe.einheit[i]='C';
	}
	else if (eingabe.einheit[i]=='C'){
	    ausgabe.wert[i]=tempf(eingabe.wert[i]);
	    ausgabe.einheit[i]='F';
	}
	else{
	std::cout << "Falsche Einheit in Zeile ";
        std::cout << i << std::endl;
	}
    }
//Ausgabe
    for (int i = 0; i < 4; ++i){
      out << ausgabe.wert[i] << " ";
      out << ausgabe.einheit[i] << std::endl;
    }
    std::cout << "Datei 'output' geschrieben!\n";
    return 0;
}
