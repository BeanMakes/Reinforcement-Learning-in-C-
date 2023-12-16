#include <iostream>
#include <random>



struct  {
    float arms[100];
}environment;

int step(float *arms, int action) {
    float r = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
    if(r<arms[action]){
        return 1;
    }else{
        return 0;
    }

}

int main() {
    for (int i = 0; i<100; i++){
        float r = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
        environment.arms[i] = r;
        std::cout << environment.arms[i] << "\n";
    }
    std::cout << step(environment.arms, 6);
    return 0;
}