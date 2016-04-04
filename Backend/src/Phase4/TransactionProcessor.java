package Phase4;

import java.util.ArrayList;

/**
 * File Name: TransactionProcessor.java
 * 
 * Description: This file is used to process the operations done. The processor will store
 * 				any valid 
 * 
 * @author Dominick Mancini, Scott McLean, Janahan Nirmalan
 * @version 1.0.0
 */
public class TransactionProcessor {
	
	
	/**
	 * The function withdrawal takes an account object and a transaction object as an argument
	 * this function will make sure that the withdrawal is valid so that the transaction
	 * will go through. If the balance is negative then the transaction will not be completed.
	 * @param t
	 * @param a
	 * @return completed
	 */
	public static boolean withdrawal(Transaction t, Account a){
		double wdAmount = t.getFundsInvolved();
		double surcharge = a.getSurcharge();
		boolean completed;
		
		if(a.isValid(wdAmount + surcharge)){
			a.decreaseBalance(wdAmount + surcharge);
			a.incrementTransactionCount();
			completed = true;
			
			System.err.println("SUCCESS: Withdrawal Transaction completed successfully.");
		}
		else{
			System.err.println("ERROR: Transaction will leave negative account balance. Cannot complete."
					+ "\nTransaction: " + t.transAsString());
			completed = false;
		}
		return completed;
	}
	
	/**
	 * This is function is just a placeholder for now but it will be the back-end function
	 * for making a transfer
	 * @param t
	 * @param a
	 * @return
	 */
	public static boolean transfer(Transaction t, Account a){
		//STUB
		return false;
	}
	
	/**
	 * The paybill transaction will be used to maintain the back-end for paying bills
	 * If the company does not exist or if enough funds aren't in the account then
	 * the transaction will fail.
	 * @param t
	 * @param a
	 * @return completed
	 */
	public static boolean paybill(Transaction t, Account a){
		double payAmount = t.getFundsInvolved();
		double surcharge = a.getSurcharge();
		boolean completed = false;
		String[] companies = {
				"EC",
				"CQ",
				"TV",
		};
		String company = t.getMisc();
		boolean companyMatch = false;
		for (String comp : companies) {
			if(company.equals(comp))
			{
				companyMatch = true;
			}
		}
		if(!companyMatch){
			System.err.println("ERROR: Company not found. Cannot complete."
					+ "\nTransaction: " + t.transAsString());
			return completed;
		}
		//-----Only executed if the company was valid.-----
		if(a.isValid(payAmount + surcharge)){
			a.decreaseBalance(payAmount + surcharge);
			a.incrementTransactionCount();
			completed = true;
			System.err.println("SUCCESS: Paybill Transaction completed successfully.");
		}
		else{
			System.err.println("ERROR: Paying the bill will leave negative account balance. Cannot complete."
					+ "\nTransaction: " + t.transAsString());
			completed = false;
		}
		return completed;
	}
	
	/**
	 * This function will be used to maintain deposits in the back-end
	 * The deposit will return a completed value of true so that the transaction is completed
	 * @param t
	 * @param a
	 * @return completed
	 */
	public static boolean deposit(Transaction t, Account a){
		double depAmount = t.getFundsInvolved();
		double surcharge = a.getSurcharge();
		boolean completed;
		
		if(a.isValid(surcharge - depAmount)){
			a.increaseBalance(depAmount - surcharge);
			a.incrementTransactionCount();
			completed = true;
			
			System.err.println("SUCCESS: Deposit Transaction completed successfully.");
		}
		else{
			System.err.println("ERROR: Depositing will leave negative account balance. Wow, you're really depositing something small. Cannot complete."
					+ "\nTransaction: " + t.transAsString());
			completed = false;
		}
		return completed;
	}

	/**
	 * This function is used to create a new account. Once the account is successfully created
	 * it will be stored in the back-end, and a value of true is returned to verify
	 * the account was created successfully
	 * @param t
	 * @param a
	 * @return completed
	 */
	public static boolean create(Transaction t, ArrayList<Account> a){
		boolean completed = false;
		for (int i = 0; i < a.size(); i++) {
			if(t.getAccountNumber().equals(a.get(i).getNumber())){
				System.err.println("ERROR: Account already exists, cannot use the same number twice."
						+ "\nTransaction: " + t.transAsString());
				return completed;
			}
		}	
		//Only executed if account number does not exist
		System.err.println("This prototype autogenerates a new account number, and disregards the transaction's provided number."
				+ "\nIf the frontend is changed in the future, this can be modified easily.");
		String newAcctNum = Utilities.createNewAccountNumber(a);
		a.add(new Account(newAcctNum, t.getName()));
		completed = true;
		System.err.println("SUCCESS: Account Created Successfully");
		return completed;
	}

	/**
	 * The delete function is used to delete an account from the back-end on the condition 
	 * that the account exists in the system. If the account exists the account will be 
	 * deleted from the back-end successfully
	 * @param t
	 * @param a
	 * @param allAccts
	 * @return completed
	 */
	public static boolean delete(Transaction t, Account a, ArrayList<Account> allAccts){
		String sToBeDeleted = t.getAccountNumber();
		boolean completed = false;
		for (int i = 0; i < allAccts.size(); i++) {
			if(allAccts.get(i).getNumber().equals(sToBeDeleted)){
				allAccts.remove(i);
				completed = true;
			}
		}
		if(!completed){
			System.err.println("ERROR: Account not found, cannot complete transaction."
					+ "\nTransaction: " + t.transAsString());
		}
		return completed;
	}
	
	/**
	 * This function is used to disable an account in the back-end
	 * @param t
	 * @param a
	 * @return
	 */
	public static boolean disable(Transaction t, Account a){
		a.setStatus('D');
		return true;
	}
	
	/**
	 * This function is used to change the plan on the account. The change of plan will
	 * decrease or increase the surcharge on transactions for account holders.
	 * @param t
	 * @param a
	 * @return done
	 */
	public static boolean changeplan(Transaction t, Account a){
		boolean done;		
		if(a.getPlan() == 'S'){
			a.setPlan('N');
			done = true;
		}
		else{
			a.setPlan('S');
			done = true;
		}
		return done;
	}
	
	/**
	 * This function is used to enable a disabled account in the back-end.
	 * @param t
	 * @param a
	 * @return
	 */
	public static boolean enable(Transaction t, Account a){
		boolean success;
		if(a.getStatus() == 'A'){
			System.err.println("ERROR: Account is already enables, cannot complete transaction");
			success = false;
		}
		else{
			a.setStatus('A');
			success = true;
		}
		return success;
	}
	
	

}
