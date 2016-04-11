#!/bin/bash

numberOfDays=5
counter=1
previousCount=0;
#ARG1 - CURRENT ACCOUNTS FILE LOCATION
#ARG2 - SESSION FILE LOCATION
#ARG3 - TRANSACTION FILE LOCATION
#ARG4 - NEW MASTER ACCOUNT FILE
#ARG5 - OLD MASTER ACCOUNT FILE

ARG1="./input-files-weekly/current_accounts.txt";
ARG5="./input-files-weekly/master_accounts.txt";
while [ $counter -le $numberOfDays ]
do
	ARG2="./input-files-weekly/day$counter/sessions";
	ARG3="./input-files-weekly/day$counter/transactions";
	ARG4="./input-files-weekly/master_accounts_day$counter.txt";
	if [ $counter -gt 1 ]; then
		perviousCount=$counter - 1;
		ARG5="./input-files-weekly/master_accounts_day$previousCount.txt";
	fi
	./daily-script.sh "$ARG1" "$ARG2" "$ARG3" "$ARG4" "$ARG5";
	
done