#include "hmm.h"
#include <math.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

/*
train $iter model_init.txt seq_model_01.txt model_01.txt
argv[1] = $iter
argv[2] = model_init.txt
argv[3] = seq_model.txt
argv[4] = output_model.txt
argc = 5

Hmm struct{
   char *model_name;
   int state_num;					            //number of state
   int observ_num;					            //number of observation
   double initial[MAX_STATE];			        //initial prob.
   double transition[MAX_STATE][MAX_STATE];	    //transition prob.
   double observation[MAX_OBSERV][MAX_STATE];	//observation prob.
}

Step1: Load model_init.txt
Step2: Read seq_model staet with first sample
Step3: Go through all 10,000 samples in seq_model
Step4: Update model_init, jump back to step1 and repeat $iteration times

Step3{
    1. calculate sample's alpha[sequence][state]
        - alpha[1][state] = hmm->initial[state] * hmm->observation[1][state]
        - alpha[t+1][state] = sum(alpha[t][i] * hmm->transition[i][state]) * hmm->observation[t+1][state]
    2. calculate sample's beta[sequence][state]
        - beta[T][state] = 1
        - beta[t][state] = sum(hmm->transition[state][j] * hmm->observation[t+1][j] * beta[t+1][j])
    3. calculate sample's gamma[sequence][state]
        - gamma[sequence][state] = 
        (alpha[sequence][state] * beta[sequence][state])/sum(alpha[sequence][i] * beta[sequence][i])
    4. calculate sample's epsilon
        - epsilon[sequence][fromState][toState] = 
        (alpha[sequence][fromState] * beta[sequence+1][toState]) * hmm->transition[fromState][toState] * hmm->observation[t+1][toState]
        /sum(alpha[sequence][i] * beta[sequence+1][j]) * hmm->transition[i][j] * hmm->observation[t+1][j])
    5. calculate new parameters for lambda
        - initial[state] = gamma[1][state]
        - transition[i][j] = sumt(epsilon[t][i][j]) / sum(gamma[t][j])
        - observation[t][i]
}
*/

int main(int argc, char *argv[]){
}