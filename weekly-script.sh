#!/bin/bash

numberOfDays=5
counter=1


ARG1="./input-files-weekly/current_accounts.txt";
while [ $counter -le $numberOfDays ]
do
	ARG2="./input-files-weekly/day$counter/sessions";
	ARG3="./input-files-weekly/day$counter/transactions";
	./daily-script.sh "$ARG1" "$ARG2" "$ARG3";
	((counter++))
done