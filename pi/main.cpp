#include <iostream>
#include <random>

int main(int argc, char** argv){
    std::mt19937 gen;
    gen.seed(254784);
    int i=100000000;
    int iKreis=0;
    int aKreis=0;
    std::uniform_real_distribution<float> dis(0,1);
    for (int n =0;n<i;n++){
      float x=dis(gen);
      float y=dis(gen);
      if (hypot(x,y)<1){
          iKreis++;
      }
      else{
	  aKreis++;
      }
    }
    //Pi ausrechnen
    float pi=4.0*iKreis/i;
    std::cout << "pi= " << pi << std::endl;
    return 0;
}
