/*
Taxi problem c++ implementation.
*/

#include <iostream>
#include <random>
#include <ctime>
#include <chrono>


struct environemnt {

    /*
    0: taxi row
    1: taxi col
    2: passenger index
    3: destination
    */

    int stateSpace[500][4];


    /*
    0: move south
    1: move north
    2: move east
    3: move west
    4: pickup passenger
    5: drop off passenger
    */
    int actions[6] = {0,1,2,3,4,5};
    // 0 = r, 1 = g, 2 = y, 3 = b, 4 in taxi
    int passengerLocation[5] = {0,1,2,3,4};
    int destination[4] = {0,1,2,3};

    // reward table
    float reward[500][6][4];

    // coords for passenger and dropoff
    int posDestination [4][2] = {{0,0}, {0,4}, {4,0}, {4,3}};
    /*
    int r[2] = {0,0};
    int g[2] = {0,4};
    int y[2] = {4,0};
    int b[2] = {4,3};
    */
    
};
// Intialize environment
void intialize_state_space(int statespace[500][4]){
    int state = 0;
    for(int i = 0; i<5;i++){
        for(int j = 0;j<5;j++){
            for (int k = 0; k<5; k++){
                for(int l = 0; l< 4; l++){
                    statespace[state][0] = i;
                    statespace[state][1] = j;
                    statespace[state][2] = k;
                    statespace[state][3] = l;
                    state+=1;
                }
            }
            
        }
            
    }
}

// intialize reward table
void intialize_reward_table(int statespace[500][4],float reward[500][6][4], int posDestination [4][2]){
    for (int i = 0; i<500;i++){
        int currentCoords[2] = {statespace[i][0],statespace[i][1]};
        for (int j = 0; j<6;j++){
            switch (j){
                case 0:
                {
                    int coordsDifferent = currentCoords[0]+1;
                    if (coordsDifferent>4){
                        reward[i][j][0] =1.0;
                        reward[i][j][1] =i;
                        reward[i][j][2] = -1.0;
                        reward[i][j][3] = 0;
                    } else {
                        int nextState = 0;
                        int passaengerLoc = statespace[i][2];
                        int destination = statespace[i][3];

                        for (int state = 0; state<500; state++){
                            if (coordsDifferent==statespace[state][0] && statespace[i][1]==statespace[state][1] && passaengerLoc==statespace[state][2]&&destination==statespace[state][3]){
                                reward[i][j][0] =1.0;
                                reward[i][j][1] =state;
                                reward[i][j][2] = -1.0;
                                reward[i][j][3] = 0;
                                break;
                            }
                        }
                    }
                    break;
                }
                case 1:
                {
                    int coordsDifferent = currentCoords[0]-1;
                    if (coordsDifferent<0){
                        reward[i][j][0] =1.0;
                        reward[i][j][1] =i;
                        reward[i][j][2] = -1.0;
                        reward[i][j][3] = 0;
                    } else {
                        int nextState = 0;
                        int passaengerLoc = statespace[i][2];
                        int destination = statespace[i][3];

                        for (int state = 0; state<500; state++){
                            if (coordsDifferent==statespace[state][0] && statespace[i][1]==statespace[state][1] && passaengerLoc==statespace[state][2]&&destination==statespace[state][3]){
                                reward[i][j][0] =1.0;
                                reward[i][j][1] =state;
                                reward[i][j][2] = -1.0;
                                reward[i][j][3] = 0;
                                break;
                            }
                        }
                    }
                    break;
                }
                case 2:
                {
                    int coordsDifferent = currentCoords[1]+1;
                    bool isWall = false;
                    if (currentCoords[0]==4 && currentCoords[1]==0){
                        isWall = true;
                    }else if(currentCoords[0]==3 && currentCoords[1]==0){
                        isWall = true;
                    }else if(currentCoords[0]==0 && currentCoords[1]==1){
                        isWall = true;
                    }else if(currentCoords[0]==4 && currentCoords[1]==2){
                        isWall = true;
                    }else if(currentCoords[0]==3 && currentCoords[1]==2){
                        isWall = true;
                    }else{
                        isWall = false;
                    }
                    if (coordsDifferent>4||isWall){
                        reward[i][j][0] =1.0;
                        reward[i][j][1] =i;
                        reward[i][j][2] = -1.0;
                        reward[i][j][3] = 0;
                    } else {
                        int nextState = 0;
                        int passaengerLoc = statespace[i][2];
                        int destination = statespace[i][3];

                        for (int state = 0; state<500; state++){
                            if (statespace[i][0]==statespace[state][0] && coordsDifferent ==statespace[state][1] && passaengerLoc==statespace[state][2]&&destination==statespace[state][3]){
                                reward[i][j][0] =1.0;
                                reward[i][j][1] =state;
                                reward[i][j][2] = -1.0;
                                reward[i][j][3] = 0;
                                break;
                            }
                        }
                    }
                    break;
                }
                case 3:
                {
                    int coordsDifferent = currentCoords[1]-1;
                    bool isWall = false;
                    if (currentCoords[0]==4 && currentCoords[1]==1){
                        isWall = true;
                    }else if(currentCoords[0]==3 && currentCoords[1]==1){
                        isWall = true;
                    }else if(currentCoords[0]==0 && currentCoords[1]==2){
                        isWall = true;
                    }else if(currentCoords[0]==4 && currentCoords[1]==3){
                        isWall = true;
                    }else if(currentCoords[0]==3 && currentCoords[1]==3){
                        isWall = true;
                    }else{
                        isWall = false;
                    }
                    if (coordsDifferent<0 || isWall){
                        reward[i][j][0] =1.0;
                        reward[i][j][1] =i;
                        reward[i][j][2] = -1.0;
                        reward[i][j][3] = 0;
                    } else {
                        int nextState = 0;
                        int passaengerLoc = statespace[i][2];
                        int destination = statespace[i][3];

                        for (int state = 0; state<500; state++){
                            if (statespace[i][0]==statespace[state][0] && coordsDifferent ==statespace[state][1] && passaengerLoc==statespace[state][2]&&destination==statespace[state][3]){
                                reward[i][j][0] =1.0;
                                reward[i][j][1] =state;
                                reward[i][j][2] = -1.0;
                                reward[i][j][3] = 0;
                                break;
                            }
                        }
                    }
                    break;
                }
                case 4:
                {
                    int passaengerLoc = statespace[i][2];
                    if (passaengerLoc!= 4 && statespace[i][0]==posDestination[passaengerLoc][0] && statespace[i][1]==posDestination[passaengerLoc][1] ){
                        reward[i][j][0] =1.0;
                        reward[i][j][1] =i;
                        reward[i][j][2] = -1.0;
                        reward[i][j][3] = 0;
                    } else {
                        reward[i][j][0] =1.0;
                        reward[i][j][1] =i;
                        reward[i][j][2] = -10.0;
                        reward[i][j][3] = 0;
                    }
                    break;
                }
                case 5:
                {
                    int passaengerLoc = statespace[i][2];
                    int destionationLoc = statespace[i][3];
                    if (passaengerLoc== 4 && statespace[i][0]==posDestination[destionationLoc][0] && statespace[i][1]==posDestination[destionationLoc][1] ){
                        std::cout<<"State: " <<  i<< " "<< std::endl;
                        reward[i][j][0] =1.0;
                        reward[i][j][1] =i;
                        reward[i][j][2] = 20;
                        reward[i][j][3] = 1;
                    } else {
                        reward[i][j][0] =1.0;
                        reward[i][j][1] =i;
                        reward[i][j][2] = -10.0;
                        reward[i][j][3] = 0;
                        
                    }
                    break;
                }
            }
        }
    }
}

void intilize_qTable(long double q[500][6]){
    for(int i =0; i< 500; i++){
        for(int j =0; j<6;j++){
            q[i][j] =0;
        }
    }
}

int rangeRandomAlg2 (int min, int max){
    int n = max - min + 1;
    int remainder = RAND_MAX % n;
    int x;
    do{
        x = rand();
    }while (x >= RAND_MAX - remainder);
    return min + x % n;
}

int randomNumberGen(int max){
    std::mt19937 e{
            static_cast<unsigned int> (
                    std::chrono::steady_clock::now().time_since_epoch().count()
            )
    };
    std::uniform_int_distribution<int> d{0, max};
    return d(e);
}

int episilonGreedy(float esp,int state, float q[500][6]){
    float r = randomNumberGen(100)/100.0f;
    if (r < esp){
        // std::cout<<"Explore"<<std::endl;
        return randomNumberGen(5);
    }else{
        // std::cout<<"Exploits"<<std::endl;
        float max = 0;
        int action = 0;
        for (int i = 0; i < 6; i++){
            if (q[state][i]>max){
                max = q[state][i];
                action = i;
            }
        }
        return action;
    }
}


/*
Reset Environment
Start state cant start with passenger in taxi and passenger cant be at the desitnation
*/
int reset_environment(int stateSpace[500][4]){
    int rndState = 0;
    do{
        rndState = rangeRandomAlg2(0,499);
    }while(stateSpace[rndState][2]==stateSpace[rndState][3] || stateSpace[rndState][2]==4);
    return rndState;
}

int main() {
    


    environemnt env;
    intialize_state_space(env.stateSpace);

    intialize_reward_table(env.stateSpace, env.reward, env.posDestination);

    //Training Agent
    int totalEpochs=0;
    int totalPenalties=0;
    long double qtable[500][6];
    intilize_qTable(qtable);

    //Hyperparameter
    double alpha = 1;
    double gamma = 0.6;
    double epsilon = 0.2;
    std::cout << "State: " << 486 << " " << env.stateSpace[486][0] <<" "<< env.stateSpace[486][1]<<" "<< env.stateSpace[486][2]<<" "<< env.stateSpace[486][3]<<std::endl;
    for(int i = 0; i<6; i++){
        std::cout << env.reward[16][i][0] <<" "<< env.reward[16][i][1]<<" "<< env.reward[16][i][2]<<" "<< env.reward[16][i][3]<<std::endl;
    }

    std::mt19937 e{
            static_cast<unsigned int> (
                    std::chrono::steady_clock::now().time_since_epoch().count()
            )
        };
        std::uniform_int_distribution<int> d{0, 499};
    
    std::mt19937 f{
            static_cast<unsigned int> (
                    std::chrono::steady_clock::now().time_since_epoch().count()
            )
            };
        std::uniform_int_distribution<int> prob{0, 100};

    for(int i =0; i<100;i++){
        int rndState = 0;
        
        int state = 0;

        do {
            state = d(e);
        }while(env.stateSpace[state][2]==env.stateSpace[state][3] || env.stateSpace[state][2]==4);


        // int state = 36;
        int epochs = 0;
        int penalties = 0;
        int reward = 0;
        bool done = false;
        long double newValue = 0;
        long double oldValue =0;
        long double nextMax = -1000000000;
        int nextState= 0;
        int action = 0;

        
        
        std::cout<<"Start State: " << state <<std::endl;
        
        std::cout<<"here"<<std::endl;

        while(!done){
            
            float r = prob(f)/100.0f;
            if (r < epsilon){
                // std::cout<<"Explore"<<std::endl;
                std::mt19937 g{
                static_cast<unsigned int> (
                        std::chrono::steady_clock::now().time_since_epoch().count()
                )
                };
                std::uniform_int_distribution<int> d{0, 5};
                action = d(g);
            }else{
                // std::cout<<"Exploits"<<std::endl;
                float max = -1000000000.0f;
                action = 0;
                for (int i = 0; i < 6; i++){
                    if (qtable[state][i]>max){
                        max = qtable[state][i];
                        action = i;
                    }
                }
            }
            nextState = env.reward[state][action][1];
            reward = env.reward[state][action][2];
            done = env.reward[state][action][3];
            oldValue = qtable[state][action];

            nextMax = -1000000000.0f;
            for (int ac = 0; ac< 6; ac++)
                if(qtable[nextState][ac]>nextMax){
                    nextMax=qtable[nextState][ac];
                }
            
            
            newValue = oldValue + alpha * (reward+gamma*nextMax-oldValue);
            qtable[state][action] = newValue;

            if(reward == -10){
                penalties+=1;
            }
            
            std::cout<<"State: " << state << " " << qtable[state][0] << " " << qtable[state][1] << " " << qtable[state][2] << " " << qtable[state][3] << " " << qtable[state][4] << " " << qtable[state][5] << " "<< std::endl;
            state = nextState;
            // std::cout<<"Next State: " << state << std::endl;
            // std::cout<<"Done: " << done << std::endl;
            // std::cout<<"newValue: " << newValue << std::endl;
            epochs +=1;
            // break;
            // if( epochs == 10){
            //     break;
            // }
            
            
        }
        std::cout<<"Episode: " << i << std::endl;
        if(i%100 == 0){
            std::cout<<"Episode: " << i << std::endl;
        }
    std::cout << "Training Complete!"<< std::endl;

    
    }
    for (int i =0;i<500;i++){
        std::cout<<"State: " << i << " " << qtable[i][0] << " " << qtable[i][1] << " " << qtable[i][2] << " " << qtable[i][3] << " " << qtable[i][4] << " " << qtable[i][5] << " "<< std::endl;
    }

    // int episodes = 100;

    

    // bool done = false;

    // int startState = 328;
    // int nextState = startState;
    // while(!done){
    //     int action = rangeRandomAlg2(0,5);
    //     int tmp = nextState;
    //     nextState = env.reward[tmp][action][1];
    //     int reward = env.reward[tmp][action][2];
    //     done = env.reward[tmp][action][3];

    //     if (reward == -10){
    //         penalties += 1;
    //     }

    //     epochs+=1;
    // }

    // std::cout << "Time Taklen: " <<  epochs << std::endl;
    // std::cout << "Penalties incurred: " << epochs << std::endl;

    return 0;
}