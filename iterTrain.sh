#i!/usr/bin/env bash
for iter in 1 2 3 4 5 6 7 8 9 10 20 40 80 100 200 300 400 500 600 700 800 900 1000 1100 1200 1300 1400 1500 1600 1700 1800 1900 2000
do
echo $iter

./train $iter model_init.txt seq_model_01.txt model_01.txt
./train $iter model_init.txt seq_model_02.txt model_02.txt
./train $iter model_init.txt seq_model_03.txt model_03.txt
./train $iter model_init.txt seq_model_04.txt model_04.txt
./train $iter model_init.txt seq_model_05.txt model_05.txt

./test modellist.txt testing_data1.txt result.txt
./acc result.txt testing_answer.txt

done
