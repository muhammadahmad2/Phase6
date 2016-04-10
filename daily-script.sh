#!/bin/bash
if [ -f Frontend/main.o ]; then
	continue;
else
	g++ -std=c++11 Frontend/main.cpp -o main.o;
fi

transactionFiles="./input-files-daily/transactions";
if [ $(find ${transactionFiles} -type f | wc -l) -gt 0 ]; then
	cd input-files-daily/transactions;
	pwd;
	rm -rf *
	cd ..;
	cd ..;
fi

accountsFile="./input-files-daily/current_accounts.txt";
transactionFile="";
sessionFilesDirectory="./input-files-daily/sessions";

LIMIT=$(find ${sessionFilesDirectory} -type f | wc -l);

counter=0;

while [ $counter -lt $LIMIT ]
do

	fileCounter=$(($counter + 1));

	transactionFile="./input-files-daily/transactions/trans$fileCounter.txt";
	sessionFile="$sessionFilesDirectory/session$fileCounter.txt";
	
	./Frontend/main.o $accountsFile $transactionFile $sessionFile;
	((counter++))
done

echo "Front End Successfully Executed"; 

cd input-files-daily/transactions;

cat * >> mergedTransactionFile.txt;


