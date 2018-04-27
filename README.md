# Discrete-HMM-Implementation
## Execution

For compiling the two main program: `train.cpp` and `test.cpp`, simply run

```
make
```

Then we have two executable file `train` and `test`. For counting the accuracy of the predictoin from these two programs, you also have to run

````
g++ accuracy.cpp -o acc
````

Now, you have `train`, `test` , `acc` three files. These are all you need to execute the two shell script files `HMM_processing.sh` and `Multiple_HMM_processing.sh`. Also, you can simply run `train` and `test` to see the result respectively.

## Train

```
./train ITERATION INPUT_INIT_MODEL INPUT_SEQ OUTPUT_MODEL
```

- `ITERATION` the integer indicates how many iterations the training will run
- `INPUT_INIT_MODEL` the file name of your initial model
- `INPUT_SEQ` the file name of your training data
- `OUTPUT_MODEL` the file name of your output model
- e.g.
  - `./train 30 model_init.txt seq_model_01.txt model_01.txt `

## Test

```
./test MODEL_LIST TEST_DATA RESULT
```

- `MODEL_LIST` the file name of the text file contains all the model you want to test
- `TEST_DATA` the file name of the data you want to test
- `RESULT` the file name of the output prediction by testing the data
- e.g.
  - `./test modellist.txt testing_data1.txt result.txt`

## Accuracy

```
./acc RESULT ANSWER
```

- `RESULT` the file name of the output prediction by testing the data
- `ANSWER`the file name of the answer to the prediction by testing the data
- e.g.
  - `./acc result.txt testing_answer.txt`


## Running whole process of HMM

To run the whole process of HMM you can execute the two shell script files `HMM_processing.sh` and `Multiple_HMM_processing.sh`. The former one can run the whole process with certain number of iterations, the latter one can run several numbers of iterations at the same time to let you see the correlation between iterations and accuracy.

```
./HMM_processing.sh ITERATIONS 
```

- `ITERATIONS` the integer indicates how many iterations the training will run

```
./Multiple_HMM_processing.sh ITERATIONS1 ITERATIONS2 ITERATIONS3 ...
```

- `ITERATIONS#` the series of integers the training process will run

## Result

From training and testing the data with different parameters, we can observe how the accuracy will change with different times of iteration.

The accuracy actually has a strike drop from 0.766 to 0.5364 with iteration equals to 1 and 10 respectively. Then the accuracy bounce back to 0.7852 when iteration equals to 20. After that, the accuracy grows quite steadily, and after iteration above 700, the accuracy become stable at 0.8692 with itearations equals to 1,500 and 2,000. 

In brief, the data indicates that the maximum improvement we can make by adjusting iteration may happened around iteration equals to around 700 ~ 800. And with the increase in iteration above 800, the improvement in the accuracy become subtle.