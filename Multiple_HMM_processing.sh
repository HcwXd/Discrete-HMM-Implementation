#i!/usr/bin/env bash
if [[ $# == 0 ]] ; then
	echo "Usage: ./Multiple_HMM_processing.sh <number of iterations> <number of iterations> <number of iterations> ..."
else
	for iter in $@
	do
	echo "Iterations = $iter"

	./train $iter model_init.txt seq_model_01.txt model_01.txt
	./train $iter model_init.txt seq_model_02.txt model_02.txt
	./train $iter model_init.txt seq_model_03.txt model_03.txt
	./train $iter model_init.txt seq_model_04.txt model_04.txt
	./train $iter model_init.txt seq_model_05.txt model_05.txt

	./test modellist.txt testing_data1.txt result.txt
	./acc result.txt testing_answer.txt

	done
fi


