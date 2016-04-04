package Phase4;

import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.PrintStream;
import java.io.PrintWriter;
import java.nio.file.NotDirectoryException;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.ArrayList;

/**
 * File Name: Main.java
 * 
 * Description: This file is used as the main processing program for all of the back-end. 
 * 				It implements all the functions and objects created for the purpose of the 
 * 				back-end. This program will be used to maintain the back-end. The program takes
 * 				in one argument (args[0]) which is the name of the old master accounts file
 * 				(i.e., the master accounts file before transactions are applied) All other 
 * 				files, including the merged transaction file, and the current accounts file
 * 				are predefined in the program code. The output master transaction file will
 * 				overwrite the old master transaction file. That is to say, args[0] specifies
 * 				the name of the old master transaction file, and the name of the new one as 
 * 				well.
 * 				
 * 
 * @author Dominick Mancini, Scott McLean, Janahan Nirmalan
 * @version 1.0.0
 *
 */
public class Main {
	
	public static void main(String[] args) throws FileNotFoundException, NotDirectoryException {
		
		//----------------DELETES PREVIOUS MERGED TRANSACTION FILE--------
		Path mergedPath = Paths.get("./merged_master_transactions.txt");
		Utilities.tryDelete(mergedPath);
		//----------------------------------------------------------------
		
		//----------------DECLARE ALL FILES AND WRITERS-------------------
		File[] arrayOfTransactionFiles = Utilities.getIndividualTransactionFiles("./transaction files/");
																			  // "./transaction files/" is default
		File fMasterTransactionFile = Utilities.mergeFiles(arrayOfTransactionFiles, "merged_master_transactions.txt");
		File fOldMasterAccountsFile = new File(args[0]);
		File fNewMasterAccountsFile = new File("new_master_accounts.txt");
		File fNewCurrentAccounstFile = new File("current_accounts.txt");
		
		PrintWriter mPWriter = new PrintWriter(new FileOutputStream(fNewMasterAccountsFile, false));
		PrintWriter cPWriter = new PrintWriter(new FileOutputStream(fNewCurrentAccounstFile, false));
		//----------------------------------------------------------------
		
		//-----Redirects errors to a log file-----------------------------
		File file = new File("errors.log");
		FileOutputStream fos = new FileOutputStream(file);
		PrintStream ps = new PrintStream(fos);
		System.setErr(ps);
		//----------------------------------------------------------------
		
		//----------CREATE ARRAYS OF ACCOUNTS AND TRANSACTIONS------------
		ArrayList<Transaction> arrayOfTransactions = Utilities.getArrayOfTransactions(fMasterTransactionFile);
		ArrayList<Account> arrayOfMasterAccounts = Utilities.getArrayOfAccounts(fOldMasterAccountsFile);
		//----------------------------------------------------------------
		
		//---------DECLARE VARIABLES FOR TRANSACTION SUCCESS AND EOF------
		boolean transactionSuccess;
		Transaction eofTransaction = new Transaction("00 XXXXXXXXXXXXXXXXXXXX 00000 99999.99 MM");
		//----------------------------------------------------------------	
		System.out.println("Welcome to the Bank account system Backend.");

		//-----------Process transactions---------------------------------
		System.out.println("Processing transactions...");
		for(Transaction t : arrayOfTransactions){
			transactionSuccess = Utilities.processTransaction(t, arrayOfMasterAccounts);
			if(!transactionSuccess){
				System.err.println("ERROR: Transaction \"" + t.transAsString() + "\" has failed.");
			}
		}
		Utilities.processTransaction(eofTransaction, arrayOfMasterAccounts);
		//----------------------------------------------------------------
		
		
		//-------------Write new Accounts Files---------------------------
		System.out.println("Writing new accounts file...");
		for (Account account : arrayOfMasterAccounts) {
			mPWriter.println(account.newAcctAsMasterString());
			System.out.println("Account: " + account.newAcctAsMasterString());
			cPWriter.println(account.newAcctAsCurrentString());
			System.out.println("Account: " + account.newAcctAsCurrentString());
		}
		mPWriter.close();
		cPWriter.close();
		//----------------------------------------------------------------
		
		//---------------DELETE OLD ACCOUNTS FILE-------------------------
		Path acctMasterPath = fOldMasterAccountsFile.toPath();
		Utilities.tryDelete(acctMasterPath);
		//----------------------------------------------------------------
		
		//--------------REWRITE MASTER ACCOUNTS FILE----------------------
		File newMasterName = new File(args[0]);
		if(fNewMasterAccountsFile.renameTo(newMasterName)){
			System.out.println("Master accounts file updated");
		}
		else{
			System.err.println("Could not write changes to master accounts file, changes must be manually applied."
					+ "\nChanges can be found in " + fNewMasterAccountsFile.getName());
		}
		//----------------------------------------------------------------
	}
}
