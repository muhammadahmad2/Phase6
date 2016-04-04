package Phase4;

import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.FileWriter;
import java.io.IOException;
import java.io.InputStreamReader;
import java.nio.file.Files;
import java.nio.file.NotDirectoryException;
import java.nio.file.Path;
import java.util.ArrayList;
import java.util.Scanner;

/**
 * File Name: Utilities.java
 * 
 * Description: The utilities class is used for the creation and maintenance of the back-end 
 * 				file system. The utilities class is primarily composed of utility functions 
 * 				to maintain the back-end of the system.
 * 
 * @author Dominick Mancini, Scott McLean, Janahan Nirmalan
 * @version 1.0.0
 */
public class Utilities {

	//Creates an array of Transaction files
	/**
	 * This function is used to return individual transaction files from transactions that 
	 * have occurred. If the directory does not exist then an exception is thrown 
	 * @return transactionFiles
	 * @throws NotDirectoryException
	 */
	public static File[] getIndividualTransactionFiles(String fileDir)throws NotDirectoryException{ 
	  File dir = new File(fileDir);
	  File[] transactionFiles = dir.listFiles();
	  if (transactionFiles == null) {
		  System.err.println("ERROR: Could not find individual transaction Files, file list is empty");
	  }
	  return transactionFiles;
		  
	}
	
	
	
	/**
	 * This method reads in a file, and returns an array of accounts to the caller
	 * @param fOldMasterAccountsFile
	 * @return an array of the master accounts
	 * @throws FileNotFoundException 
	 */
	public static ArrayList<Account> getArrayOfAccounts(File fOldMasterAccountsFile) throws FileNotFoundException{
		ArrayList<Account> arrayOfMasterAccounts = new ArrayList<Account>();
		String acctString;
		Scanner scAccounts = new Scanner(fOldMasterAccountsFile);
		System.out.println("Loading accounts...");
		while(scAccounts.hasNextLine()) {
			acctString = scAccounts.nextLine();
			if(acctString.length() != 44){
				System.err.println("ERROR: Invalid account:" + acctString);
			}
			else{
				arrayOfMasterAccounts.add(new Account(acctString));
			}
		}
		scAccounts.close();
		return arrayOfMasterAccounts;
		//----------------------------------------------------------------
	}
	/**
	 * This method generates an array list of transaction objects from the specified transaction file.
	 * @param fMasterTransactionFile
	 * @return an array of all the transaction from the file
	 * @throws FileNotFoundException
	 * @throws NotDirectoryException
	 */
	public static ArrayList<Transaction> getArrayOfTransactions(File fMasterTransactionFile) throws FileNotFoundException, NotDirectoryException{
		//-----------Read in transactions file----------------------------
		ArrayList<Transaction> arrayOfTransactions = new ArrayList<Transaction>();
		String transactionString;
		Scanner scTransaction = new Scanner(fMasterTransactionFile);
		System.out.println("Reading transactions...");
		while(scTransaction.hasNextLine()) {
			transactionString = scTransaction.nextLine();
			if(transactionString.length() != 41){
				String culpritFile = Utilities.findFile(transactionString);
				System.err.println("ERROR: Invalid transaction, located in transaction file " + culpritFile + "."
						+ " Transaction: " + transactionString);
			}
			else {
				arrayOfTransactions.add(new Transaction(transactionString));
			}	
		}	
		scTransaction.close();
		//----------------------------------------------------------------
		return arrayOfTransactions;
	}
	/**
	 * This function is used to merge files and was borrowed from
	 * <http://www.programcreek.com/2012/09/merge-files-in-java/>
	 * @param files
	 * @param name
	 * @return
	 */
	/*
	 * --START BORROWED CODE--[
	 */
	public static File mergeFiles(File[] files, String name) {
		
		File mergedFile = new File(name);
		FileWriter fstream = null;
		BufferedWriter out = null;
		try {
			fstream = new FileWriter(mergedFile, true);
			out = new BufferedWriter(fstream);
		} 
		catch (IOException e1) {
			e1.printStackTrace();
		}
 
		for (File f : files) {
			System.out.println("merging: " + f.getName());
			FileInputStream fis;
			try {
				fis = new FileInputStream(f);
				BufferedReader in = new BufferedReader(new InputStreamReader(fis));
 
				String aLine;
				while ((aLine = in.readLine()) != null) {
					out.write(aLine);
					out.newLine();
				}
 
				in.close();
			} 
			catch (IOException e) {
				e.printStackTrace();
			}
		}
 
		try {
			out.close();
		} 
		catch (IOException e) {
			e.printStackTrace();
		}
		return mergedFile;
 
	}
	/*
	 * ]--END BORROWED CODE--
	 */
	
	/**
	 * This method tries to delete a file at a specified path, if the file
	 * does not exist, then an IOException is thrown
	 * @param pathToFile
	 */
	public static void tryDelete(Path pathToFile){
		try {
			Files.deleteIfExists(pathToFile);
		} catch (IOException e) {
			e.printStackTrace();
		}
	}
	
	/**
	 * This function is used to find a file, a string consisting of the file name will be 
	 * returned
	 * @param fileText
	 * @return fileName
	 * @throws NotDirectoryException
	 * @throws FileNotFoundException
	 */
	@SuppressWarnings("resource")
	public static String findFile(String fileText) throws NotDirectoryException, FileNotFoundException{
 		  String fileName = null;
		  File dir = new File("./");
		  File[] directoryListing = dir.listFiles();
		  if (directoryListing != null) {
		    for (File child : directoryListing) {
		      Scanner cScanner = new Scanner(child);
		      while(cScanner.hasNextLine()){
		    	  if(cScanner.nextLine().equals(fileText)){
		    		  fileName = child.getName();
		    	  }
		      }
		    }
		    if(fileName.isEmpty()){
		    	fileName = "File does not exist";
		    }
		  }
		  return fileName;
	}
	
	/**
	 * This function is used for padding spaces on the right
	 * @param s
	 * @param n
	 * @return
	 */
	public static String padSpaceRight(String s, int n) {
	     return String.format("%1$-" + n + "s", s);  
	}

	/**
	 * This function is used for padding spaces on the left
	 * @param s
	 * @param n
	 * @return
	 */
	public static String padSpaceLeft(String s, int n) {
	    return String.format("%1$" + n + "s", s);  
	}
	
	/**
	 * This function is used to pad 0's on the left 
	 * @param num
	 * @param size
	 * @return
	 */
	public static String padZeroesLeft (String num, int size){
		return String.format("%0" + size + "d", Integer.parseInt(num));
	}
	
	/**
	 * This function is used to find the highest account number in the system.
	 * The highest account number will be returned after searching through a list of 
	 * accounts in the system
	 * @param arrayOfAccounts
	 * @return
	 */
	public static int getHighestAcctNum (ArrayList<Account> arrayOfAccounts){
		int highest = 0;
		for (int i = 0; i < arrayOfAccounts.size(); i++) {
			if(Integer.parseInt(arrayOfAccounts.get(i).getNumber()) > highest){
				highest = Integer.parseInt(arrayOfAccounts.get(i).getNumber());
			}
		}
		return highest;
	}
	
	/**
	 * This function will be used to create a new valid account number for a new account
	 * when it is created. The new number will be made sure that is usable before returning the
	 * value.
	 * @param existingAccounts
	 * @return
	 */
	public static String createNewAccountNumber(ArrayList<Account> existingAccounts){
		int highestNum = getHighestAcctNum(existingAccounts);
		return padZeroesLeft(Integer.toString(highestNum + 1), 5);
	}
	
	/**
	 * This function is used to return an account object based on the account number given as
	 * an argument. Once the account is found, a new account object will be created from the 
	 * information found by the account number.
	 * @param acctNum
	 * @param arrayOfAccounts
	 * @return acct
	 */
	public static Account getAccountByNumber(String acctNum, ArrayList<Account> arrayOfAccounts){
		Account acct = new Account("00000", "XXXXXXXXXXXXXXXXXXXX");
		acct.setStatus('D');
		for (Account account : arrayOfAccounts) {
			if(account.getNumber().equals(acctNum)){
				acct = account;
				break;
			}
		}
		return acct;
	}
	
	/**
	 * This function is used to drive the back-end of the system by grabbing the functions
	 * that are declared in the TransactionProcessor.java file.
	 * @param t
	 * @param accounts
	 * @return
	 */
	public static boolean processTransaction(Transaction t, ArrayList<Account> accounts){
		String sTransNum = t.getTransactionNumber();
		//System.out.println("Transaction number: " + sTransNum);
		boolean transactionSuccess = false;
		Account acct = Utilities.getAccountByNumber(t.getAccountNumber(), accounts);
		//----------------------------------------------------------------
		// Create is a special case, as no account will exist, 
		// so the program should still allow execution even if
		// the account is not "Active", so to speak. Furthermore
		// Enable will only work on a disabled account.
		//----------------------------------------------------------------
		if(acct.getStatus() != 'A' && !sTransNum.equals("05") && !sTransNum.equals("09")){
			transactionSuccess = false;
			System.err.println("ERROR Account with number " + t.getAccountNumber() +". Account is Disabled");
		}
		else if(sTransNum.equals("00")){
			System.out.println("End of session.");	
		}
		else if(sTransNum.equals("01")){
			System.out.println("Transaction: Withdrawal\n");
			transactionSuccess = TransactionProcessor.withdrawal(t, acct);
		}
		else if(sTransNum.equals("02")){
			System.out.println("Transaction: Transfer, you should not be seeing this");
			transactionSuccess = TransactionProcessor.transfer(t, acct);
		}
		else if(sTransNum.equals("03")){
			System.out.println("Transaction: Pay Bill\n");
			transactionSuccess = TransactionProcessor.paybill(t, acct);
		}
		else if(sTransNum.equals("04")){
			System.out.println("Transaction: Deposit\n");
			transactionSuccess = TransactionProcessor.deposit(t, acct);
		}
		/*!-----BEGIN ADMIN TRANSACTIONS-----!*/
		else if(sTransNum.equals("05")){//Special case
			System.out.println("Transaction: Create\n");
			transactionSuccess = TransactionProcessor.create(t, accounts);
		}
		else if(sTransNum.equals("06")){
			System.out.println("Transaction: Delete\n");
			transactionSuccess = TransactionProcessor.delete(t, acct, accounts);
		}
		else if(sTransNum.equals("07")){
			System.out.println("Transaction: Disable\n");
			transactionSuccess = TransactionProcessor.disable(t, acct);
		}
		else if(sTransNum.equals("08")){
			System.out.println("Transaction: Change Plan\n");
			transactionSuccess = TransactionProcessor.changeplan(t, acct);
		}
		else if(sTransNum.equals("09")){
			System.out.println("Transaction: Enable\n");
			transactionSuccess = TransactionProcessor.enable(t, acct);
		}
		/*!-----END ADMIN TRANSACTIONS-----!*/
		else{
			System.err.println("ERROR: Transaction ID " + sTransNum + " is unknown.\nTransaction: " + t.transAsString());
			transactionSuccess = false;
		}
		return transactionSuccess;
	}
}
