#include "hmm.h"
#include <math.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#ifndef MAX_MODELS
#define MAX_MODELS 10
#endif

/*  
./test MODEL_LIST TEST_DATA RESULT
argv[1] = MODEL_LIST
argv[2] = TEST_DATA
argv[3] = RESULT
argc = 4

Hmm struct{
   char *model_name;
   int state_num;					            //number of state
   int observ_num;					            //number of observation
   double initial[MAX_STATE];			        //initial prob.
   double transition[MAX_STATE][MAX_STATE];	    //transition prob.
   double observation[MAX_OBSERV][MAX_STATE];	//observation prob.
}

*/

double _delta[2][MAX_STATE];

void viterbi_processing(HMM *HMM_models, int number_of_models, char *data, int *best_model_index, double *max_path_prob)
{
    int inner_best_model_index = -1;
    double inner_max_path_prob = 0.0;

    for (int model_index = 0; model_index < number_of_models; model_index++)
    {
        HMM *model = HMM_models + model_index;
        int number_of_state = model->state_num;

        int observ = data[0] - 'A';
        for (int state = 0; state < number_of_state; state++)
        {
            _delta[0][state] = model->initial[state] * model->observation[observ][state];
            // printf("%f ", _delta[0][state]);
        }
        // printf("\n");

        double tmp_high_prob = 0.0;
        for (int observT = 1; observT < strlen(data); observT++)
        {
            int observ = data[observT] - 'A';
            for (int state = 0; state < number_of_state; state++)
            {
                for (int preState = 0; preState < number_of_state; preState++)
                {
                    double tmp = _delta[0][preState] * model->transition[preState][state];
                    if (tmp > tmp_high_prob)
                    {
                        tmp_high_prob = tmp;
                    }
                }
                _delta[1][state] = tmp_high_prob * model->observation[observ][state];
            }
            for (int state = 0; state < number_of_state; state++)
            {
                _delta[0][state] = _delta[1][state];
            }
        }
        for (int state = 0; state < number_of_state; state++)
        {
            if (_delta[1][state] > inner_max_path_prob)
            {
                inner_max_path_prob = _delta[1][state];
                inner_best_model_index = model_index;
            }
        }
    }
    *best_model_index = inner_best_model_index;
    // printf("%d ", inner_best_model_index + 1);

    *max_path_prob = inner_max_path_prob;
    // printf("%f\n", inner_max_path_prob);
}

int main(int argc, char *argv[])
{
    HMM HMM_models[MAX_MODELS];

    int number_of_models = load_models(argv[1], HMM_models, MAX_MODELS);

    FILE *input_data = open_or_die(argv[2], "r");
    FILE *output_result = open_or_die(argv[3], "w");

    char data[MAX_LINE];
    int limit = 0;

    while (fscanf(input_data, "%s", data))
    {
        int best_model_index;
        double max_path_prob;
        viterbi_processing(HMM_models, number_of_models, data, &best_model_index, &max_path_prob);
        // printf("%s %f\n", HMM_models[best_model_index].model_name, max_path_prob);
        limit++;
        if (limit > 2500)
        {
            break;
        }

        // fprintf(output_result, "%s %e\n", HMM_models[best_model_index].model_name, max_path_prob);
        fprintf(output_result, "%s\n", HMM_models[best_model_index].model_name);
    }
    fclose(input_data);
    fclose(output_result);
}