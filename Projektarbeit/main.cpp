#include <iostream>
#include <fstream>
#include <math.h>

//global variables
int k;

//global constants
float hight;
float distance;
float steps;
float g;
float m_m; //mass of monkey
float m_b; //mass of ball
float gamma_x; //friction in x-direction
float gamma_y; //friction in y-direction

void getConfig(){
    int description;
    std::ifstream in ("config.txt");
    in >> hight;
    in >> distance;
    in >> steps;
    in >> g;
    in >> m_m;
    in >> m_b;
    in >> gamma_x;
    in >> gamma_y;
}

float K_1(float v,float gamma,float m){	    //help function for Runge-Kutta in y-direction
    float k_1=g-gamma/m*v;
    v=v+0.5*steps*k_1;
    float k_2=g-gamma/m*v;
    v=v+0.5*steps*k_2;
    float k_3=g-gamma/m*v;
    v=v+steps*k_3;
    float k_4=g-gamma/m*v;

    return(k_1+2*k_2+2*k_3+k_4);
}

float K_2(float v,float gamma,float m){	//help function for Runge-Kutta in x-direction
    float k_1=-gamma/m*v;
    v=v+0.5*steps*k_1;
    float k_2=-gamma/m*v;
    v=0.5*steps*k_2;
    float k_3=-gamma/m*v;
    v=v+steps*k_3;
    float k_4=-gamma/m*v;

    return(k_1+2*k_2+2*k_3+k_4);
}

void monkey(){
    float v_1=0;
    int i=1;
    float h=hight;
    std::ofstream out ("Monkey.txt");
    //mainloop
    while(h>0){
	float v_2=v_1+1/6.0*steps*K_1(v_1,gamma_y,m_m);	//using Runge-Kutta
	h=h-v_2*steps;
	out << v_2 << " " << (steps*i) << " "<< h << std::endl;
	v_1=v_2;v_2=0;
	i++;k=i;
    }

}

float potential(float h,float m){ //calculates potential energy
    return(m*g*h);
}

float kinetic(float v,float m){ //calculates kinetic energy
    return(m/2*v*v);
}

void energy_m(){ //testing conversation of energy of the monkey
    //getting data form Monkey.txt
    std::ifstream in ("Monkey.txt");
    std::ofstream out ("Energy_Monkey.txt");
    for (int j = 0; j < (k-1); ++j){
        float v=0;
	float h=0;
	in >> v;
	in >> h;
	in >> h;
        out << potential(h,m_m) << " " << kinetic(v,m_m) << " " << (potential(h,m_m)+kinetic(v,m_m)) << std::endl;
	
    }
}

void energy_b(){
    std::ifstream in ("Ball.txt");
    std::ofstream out ("Energy_Ball.txt");
    for (int j = 0; j < (k-1); ++j){
        float v;
	float w;
	float h;
	distance=0;
	in >> v;
	in >> v;
	in >> h;
	in >> w;
	in >> distance;
	out <<kinetic(v,m_b) << " " << kinetic(w,m_b) << " " << potential(h,m_b) << " " << (kinetic(v,m_b)+kinetic(w,m_b)+potential(h,m_b)) << std::endl;
    }
}

void ball(){
    std::ofstream out ("Ball.txt");
    float w_1=5; //start speed in x-direction
    float v_1=0;
    int i=1;
    float h=hight;
    //mainloop
    while(h>0){	
        float v_2=v_1+1/6.0*steps*K_1(v_1,gamma_y,m_b);	//using Runge-Kutta
	h=h-v_2*steps;
	out << (steps*i) << " " << v_2 << " "<< h << " ";
	v_1=v_2;v_2=0;
        float w_2=w_1+1/6.0*steps*K_2(w_1,gamma_x,m_b);
	distance=distance-w_2*steps;
	out << w_2 << " " << distance << std::endl;
	w_1=w_2;w_2=0;
	i++;k=i;
    }

}

int main(int argc, char** argv){
    getConfig();
    monkey();	//call the main computing function for monkey
    energy_m();
    ball();  //call the main computing funktion for ball
    energy_b();
    return 0;
}
