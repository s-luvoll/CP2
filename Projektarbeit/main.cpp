#include <iostream>
#include <fstream>
#include <math.h>

//global variables
float hight=10;
float steps=0.001;
int k;

//global constants
float g=9.81;
//float gamma=1.0;
float m=1;

float K(float v){	    //help function for Runge-Kutta
    float gamma=2;
    float k_1=g-gamma/m*v;
    v=v+0.5*steps*k_1;
    float k_2=g-gamma/m*v;
    v=v+0.5*steps*k_2;
    float k_3=g-gamma/m*v;
    v=v+steps*k_3;
    float k_4=g-gamma/m*v;

    return(k_1+2*k_2+2*k_3+k_4);
}

void monkey(){
    float v_1=0;
    int i=1;
    std::ofstream out ("Monkey.txt");

    //mainloop
    while(hight>0){
	float v_2=v_1+1/6.0*steps*K(v_1);	//using Runge-Kutta
	hight=hight-v_2*steps;
	out << v_2 << " "<< hight << std::endl;
	v_1=v_2;v_2=0;
	i++;k=i;
    }

}

float potential(float h){ //calculates potential energy
    return(m*g*h);
}

float kinetic(float v){ //calculates kinetic energy
    return(m/2*v*v);
}

void energy(){ //testing conversation of energy
    //getting data form Monkey.txt
    std::ifstream in ("Monkey.txt");
    std::ofstream out ("Energy.txt");
    for (int j = 0; j < (k-1); ++j){
        float v=0;
	hight=0;
	in >> v;
	in >> hight;
        out << potential(hight) << " " << kinetic(v) << " " << (potential(hight)+kinetic(v)) << std::endl;
	
    }
}

int main(int argc, char** argv){
    monkey();	//call the main computing function
    energy();
    return 0;
}
