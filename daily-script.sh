#!/bin/bash

accountsFile="./input-files-daily/current_accounts.txt";
sessionFilesDirectory="./input-files-daily/sessions";
transactionFileLocation="./input-files-daily/transactions";
transactionFile="";


if [ -n "$1" ]; then
	accountsFile="$1";
	sessionFilesDirectory="$2";
	transactionFileLocation="$3";
fi

if [ -f Frontend/main.o ]; then
	continue;
else
	g++ -std=c++11 Frontend/main.cpp -o main.o;
fi

if [ $(find ${transactionFileLocation} -type f | wc -l) -gt 0 ]; then
	cd $transactionFileLocation;
	rm -rf *
	cd -;
fi

LIMIT=$(find ${sessionFilesDirectory} -type f | wc -l);

counter=0;

while [ $counter -lt $LIMIT ]
do

	fileCounter=$(($counter + 1));

	transactionFile="$transactionFileLocation/trans$fileCounter.txt";
	sessionFile="$sessionFilesDirectory/session$fileCounter.txt";
	
	./Frontend/main.o $accountsFile $transactionFile $sessionFile;
	((counter++))
done

echo "Front End Successfully Executed"; 

if [ $(find ${transactionFileLocation} -type f | wc -l) -gt 0 ]; then
	cd $transactionFileLocation;
	cat * >> mergedTransactionFile.txt;
	cd -;
fi