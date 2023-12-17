#include <iostream>
#include <random>
#include <ctime>

struct environment{
    float arms[10] = {0.1,0.5,0.6,0.8,0.10,0.25,0.6,0.45,0.75,0.65};
};

struct agent{
    
    float reward;
    int action[10] = {0,0,0,0,0,0,0,0,0,0};
    float q[10] = {0,0,0,0,0,0,0,0,0,0};

} ;

int step(float *arms, int action) {
    // std::default_random_engine rand_number;
    // std::uniform_real_distribution<float> distribution(0.0,1.0);
    float r = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
    
    if(r<arms[action]){
        return 1;
    }else{
        return 0;
    }

}

void update_q(int action,float *q, float *arms, int *actions){
    
    q[action] = q[action] + (((step(arms,action)-q[action]))/actions[action]);
}

int episilonGreedy(float esp,float *q){
    float r = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist6(0,9); // distribution in range [0, 9]
    if (r < esp){
        return dist6(rng);
    }else{
        float max = 0;
        int action = 0;
        for (int i = 0; i < 10; i++){
            if (q[i]>max){
                max = q[i];
                action = i;
            }
        }
        return action;
    }
}

int main() {

    float esp = 0.1;
    environment env;
    agent a;
    int action = episilonGreedy(esp,a.q);
    std::cout<< action<<"\n";
    a.action[action]+=1;
    update_q(action,a.q,env.arms,a.action);

    for (int t = 0; t < 1000; t++){
        action = episilonGreedy(esp,a.q);
        a.action[action]+=1;
        std::cout << "Action Chosen: " << action << "\n";
        update_q(action,a.q,env.arms,a.action);
    }
    for (int i = 0; i<10;i++){
        std::cout << "Arm: " << i << "\n";
        std::cout << a.action[i]<< "\n";
        std::cout << a.q[i]<< "\n";
    }
    
    return 0;
}