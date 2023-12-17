/*
Taxi problem c++ implementation.
*/

#include <iostream>
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
                case 1:
                    int coordsDifferent = currentCoords[0]+1;
                    if (coordsDifferent>3){
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
                case 2:
                    int coordsDifferent = currentCoords[1]-1;
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
                case 3:
                    int coordsDifferent = currentCoords[1]+1;
                    if (coordsDifferent>3){
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
                case 4:
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
                case 5:
                    int passaengerLoc = statespace[i][2];
                    int destionationLoc = statespace[i][3]
                    if (passaengerLoc== 4 && statespace[i][0]==posDestination[destionationLoc][0] && statespace[i][1]==posDestination[destionationLoc][1] ){
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

int main() {
    


    environemnt env;
    intialize_state_space(env.stateSpace);

    for(int i = 0; i<500; i++){
        std::cout << env.stateSpace[i][0] << " " << env.stateSpace[i][1] << " " << env.stateSpace[i][2] << " "  << env.stateSpace[i][3] << std::endl;
    }

    return 0;
}