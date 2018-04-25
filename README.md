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

Now, you have `train`, `test` , `acc` three files. These are all you need to execute the two shell script files `autotrain.sh` and `itertrain.sh`. Also, you can simply run `train` and `test` to see the result respectively.

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
  - ./acc result.txt testing_answer.txt

