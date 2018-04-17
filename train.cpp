#include "hmm.h"
#include <math.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#ifndef MAX_SAMPLES
#define MAX_SAMPLES 10000
#endif

/*

Step1: Load model_init.txt
Step2: Read seq_model start with first sample
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
*/

using namespace std;

double _alpha[MAX_SAMPLES][MAX_SEQ][MAX_STATE];
double _beta[MAX_SAMPLES][MAX_SEQ][MAX_STATE];
double _gamma[MAX_SAMPLES][MAX_SEQ][MAX_STATE];
double _epsilon[MAX_SAMPLES][MAX_SEQ][MAX_STATE][MAX_STATE];

void calculate_alpha(HMM *HMM_model, char *sample, int number_of_sample)
{
    int sample_length = strlen(sample);
    int number_of_state = HMM_model->state_num;

    // printf("%s\n", sample);
    for (int state = 0; state < number_of_state; state++)
    {
        int observ = sample[0] - 'A';
        _alpha[number_of_sample][0][state] = HMM_model->initial[state] * HMM_model->observation[observ][state];
        // printf("%f\n", _alpha[number_of_sample][0][state]);
    }
    for (int observT = 1; observT < sample_length; observT++)
    {
        int observ = sample[observT] - 'A';
        for (int state = 0; state < number_of_state; state++)
        {
            double tmp_sum = 0.0;
            for (int preState = 0; preState < number_of_state; preState++)
            {
                tmp_sum += _alpha[number_of_sample][observT - 1][preState] * HMM_model->transition[preState][state];
            }
            // printf("%f", tmp_sum);
            _alpha[number_of_sample][observT][state] = tmp_sum * HMM_model->observation[observ][state];
            // printf("%f ", _alpha[number_of_sample][observT][state]);
        }
        // printf("\n");
    }
    for (int j = 0; j < number_of_state; j++)
    {
        for (int i = 0; i < 10; i++)
        {
            printf("%f ", _alpha[number_of_sample][i][j]);
        }
        printf("\n");
    }
};

void train_through_one_sample(HMM *HMM_model, char *sample, int number_of_sample)
{
    calculate_alpha(HMM_model, sample, number_of_sample);
    calculate_beta(HMM_model, sample, number_of_sample);
};

void trainHMM(int iteration_time, HMM *HMM_model, FILE *training_data)
{
    int number_of_sample;
    char sample[MAX_LINE];

    // int number_of_state = HMM_model->state_num;
    // int number_of_observation = HMM_model->observ_num;

    for (int i = 0; i < iteration_time; i++)
    {
        fseek(training_data, 0, SEEK_SET);
        for (number_of_sample = 0; fscanf(training_data, "%s", sample) > 0; number_of_sample++)
        {
            train_through_one_sample(HMM_model, sample, number_of_sample);
            printf("end\n");
            break;
        }
    }
}

int main(int argc, char *argv[])
{
    // int iteration_time = strtol(argv[1], NULL, 10);
    int iteration_time = atoi(argv[1]);

    printf("%d\n", iteration_time);
    HMM HMM_model;
    loadHMM(&HMM_model, argv[2]);

    FILE *training_data = open_or_die(argv[3], "r");
    FILE *trained_model = open_or_die(argv[4], "w");

    trainHMM(iteration_time, &HMM_model, training_data);
}