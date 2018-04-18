#i!/usr/bin/env bash

iter=200

./train $iter model_init.txt seq_model_01.txt model_01.txt
./train $iter model_init.txt seq_model_02.txt model_02.txt
./train $iter model_init.txt seq_model_03.txt model_03.txt
./train $iter model_init.txt seq_model_04.txt model_04.txt
./train $iter model_init.txt seq_model_05.txt model_05.txt
