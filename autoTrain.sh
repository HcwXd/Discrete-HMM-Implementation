#i!/usr/bin/env bash
# for iter in 50 60 70 80 90 100 110 120 130 140 150 160 170 180 190 200
# do
iter=2000
echo $iter

./train $iter model_init.txt seq_model_01.txt model_01.txt
echo 1
./train $iter model_init.txt seq_model_02.txt model_02.txt
echo 2
./train $iter model_init.txt seq_model_03.txt model_03.txt
echo 3
./train $iter model_init.txt seq_model_04.txt model_04.txt
echo 4
./train $iter model_init.txt seq_model_05.txt model_05.txt
echo 5

./test modellist.txt testing_data1.txt result.txt handin.txt
./acc result.txt testing_answer.txt

# done
