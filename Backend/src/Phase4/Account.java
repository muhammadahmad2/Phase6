package Phase4;

import java.text.DecimalFormat;

/**
 * File Name: account.java
 * 
 * Description: This class is used to store account information
 * 				Information such as the old account string and new account string
 * 				
 * 				In addition to that the account number, account holder name, account status
 * 				account plan, current balance, number of transactions and surcharge.
 * 
 * @author Dominick Mancini, Scott McLean, Janahan Nirmalan
 * @version 1.0.0
 * 
 */
public class Account {
	private String newMAcctString;
	private String newCAcctString;
	private String oldAcctString;
	private String sAcctNum;
	private String sAcctHolderName;
	private char cAcctStatus;
	private char cAcctPlan;
	private double dBalance;
	private int numTransactions;
	private double surcharge;

	private DecimalFormat df = new DecimalFormat("#.##");

	/**
	 * This is the parameterized constructor to make an account object
	 * created from the account line argument
	 * @param accountLine
	 */
	public Account(String accountLine) {
		oldAcctString = accountLine;
		sAcctNum = accountLine.substring(0,5).trim();
		sAcctHolderName = accountLine.substring(6, 26).trim();
		cAcctStatus = accountLine.charAt(27);
		dBalance = Double.parseDouble(accountLine.substring(29,37));
		numTransactions = Integer.parseInt(accountLine.substring(38,42));
		cAcctPlan = accountLine.charAt(43);
		this.setSurcharge(cAcctPlan);
	}

	//Constructor for "create" transaction
	/**
	 * This constructor is used to create a brand new account in the system
	 * Since the new account is created from an admin, the only arguments given
	 * are the account number and account holder name
	 * @param acctNum
	 * @param acctName
	 */
	public Account(String acctNum, String acctName){
		sAcctNum = acctNum;
		sAcctHolderName = acctName;
		cAcctStatus = 'A';
		dBalance = 0;
		numTransactions = 0;
		cAcctPlan = 'N';
		this.setSurcharge(cAcctPlan);
	}

	/**
	 * Get method for retrieving account holder name
	 * @return sAcctHolderName
	 */
	public String getName(){
		return sAcctHolderName;
	}

	/**
	 * Get method for retrieving account number
	 * @return sAcctNum
	 */
	public String getNumber(){
		return sAcctNum;
	}

	/**
	 * Get method to retrieve the current status of the account
	 * @return cAcctStatus
	 */
	public char getStatus(){
		return cAcctStatus;
	}

	/**
	 * Get method to retrieve the current balance of the account
	 * @return dBalance
	 */
	public double getBalance(){
		return dBalance;
	}

	/**
	 * Get method to retrieve the number of transactions
	 * @return numTransactions
	 */
	public int getNumTransactions(){
		return numTransactions;
	}

	/**
	 * Get method to retrieve the current account plan
	 * @return cAcctPlan
	 */
	public char getPlan(){
		return cAcctPlan;
	}

	/**
	 * This method is used to increase the current balance of the account
	 * when a deposit is made
	 * @param addAmt
	 */
	public void increaseBalance(double addAmt){
		dBalance+=addAmt;
	}

	/**
	 * This method is used to decrease the current balance of the account
	 * when a withdrawal is made
	 * @param subAmt
	 */
	public void decreaseBalance(double subAmt){
		dBalance-=subAmt;
	}

	/**
	 * This method is used to check if the new balance after withdrawal is greater than
	 * or equal to 0. If the amount computed is not valid it will return a false value
	 * @param subAmt
	 * @return
	 */
	public boolean isValid(double subAmt){
		if(dBalance - subAmt >= 0){
			return true;
		}
		else{
			return false;
		}
	}
	/**
	 * 
	 */
	public void incrementTransactionCount(){
		numTransactions++;
	}
	/**
	 * This setter method is used to set the new balance of the account
	 * @param newBalance
	 */
	public void setBalance(double newBalance){
		dBalance = newBalance;
	}
	
	/**
	 * This function is used to create a new master string variable of the information
	 * currently within the account object
	 * @return newMAcctString
	 */
	public String newAcctAsMasterString(){
		newMAcctString = sAcctNum + " " + Utilities.padSpaceRight(sAcctHolderName,20)+ " " + cAcctStatus + " "
				+ Utilities.padSpaceLeft(df.format(dBalance), 8) + " " + Utilities.padZeroesLeft("" + numTransactions, 4)
				+ " " + cAcctPlan;
		return newMAcctString;
	}
	
	/**
	 * Returns the current new account as a string
	 * @return newCAcctString
	 */
	public String newAcctAsCurrentString(){
		newCAcctString = sAcctNum + " " + Utilities.padSpaceRight(sAcctHolderName,20)+ " " + cAcctStatus + " "
				+ Utilities.padSpaceLeft(df.format(dBalance), 8);
		return newCAcctString;
	}

	/**
	 * Returns the old account string
	 * @return oldAcctString
	 */
	public String currentAcctAsString(){
		return oldAcctString;
	}

	/**
	 * This function is used to set the surcharge by changing the plan of the account
	 * If the plan argument is S, the surcharge is $0.05
	 * If the plan is not S, then the surcharge is $0.10
	 * @param plan
	 */
	public void setSurcharge(char plan){
		if(plan == 'S'){
			surcharge = 0.05;
		}
		else{
			surcharge = 0.10;
		}
	}

	/**
	 * Returns the current surcharge rate that is charged to the account
	 * @return surcharge
	 */
	public double getSurcharge(){
		return surcharge;
	}

	/**
	 * This is used to set the current plan on the account
	 * @param plan
	 */
	public void setPlan(char plan){
		if(cAcctPlan == plan){
			System.err.println("ERROR: Account is already this type");
		}
		else if(plan != 'S' && plan != 'N'){
			System.err.println("ERROR: Account plan not recognized");
		}
		else if(cAcctPlan != plan){
			cAcctPlan = plan;
		}
	}

	/**
	 * This function is used to set the status on the account.
	 * @param newStatus
	 */
	public void setStatus(char newStatus){
		if(newStatus != 'A' && newStatus != 'D'){
			System.err.println("ERROR: status cannot be set to " + newStatus);
		}
		else{
			cAcctStatus = newStatus;
		}
	}

}
