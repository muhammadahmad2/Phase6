package Phase4;

/**
 * File Name: transaction.java
 * 
 * Description: The transaction class is used to keep track day to day transactions
 * 				Transaction information stored includes the transaction number,
 * 				the account holder name, the account number involved, any Miscellaneous
 * 				information and the funds involved in the transaction
 * 	
 *
 * @author Dominick Mancini, Scott McLean, Janahan Nirmalan
 * @version 1.0.0
 *
 */
public class Transaction {
	
	private String sTransactionString;
	private String sTransactionNum;
	private String sAccountHName;
	private String sAccountNumber;
	private String sMiscInfo;
	private double dFundsInvolved;
	
	
	
	/**
	 * The Transaction constructor is used to create a new transaction object
	 * Information is set from a transaction record string.
	 * @param transactionRecord
	 */
	public Transaction(String transactionRecord) {
		sTransactionString = transactionRecord;
		sTransactionNum = transactionRecord.substring(0,2).trim();
		sAccountHName = transactionRecord.substring(3,23).trim();
		sAccountNumber = transactionRecord.substring(24,29).trim();
		
		dFundsInvolved = Double.parseDouble(transactionRecord.substring(30,38));
		sMiscInfo = transactionRecord.substring(39);
	}
	
	
	/**
	 * Get method used to return the transaction number
	 * @return sTransactionNum
	 */
	public String getTransactionNumber(){
		return sTransactionNum;
	}
	
	/**
	 * Get method used to return the account holder name involved in the transaction
	 * @return sNamAccountHName
	 */
	public String getName(){
		return sAccountHName;
	}
	
	/**
	 * Get method used to return the account number involved in the transaction
	 * @return sAccountNumber
	 */
	public String getAccountNumber(){
		return sAccountNumber;
	}
	
	/**
	 * Get method used to return Miscellaneous information in the transaction 
	 * @return sMiscInfo
	 */
	public String getMisc(){
		return sMiscInfo;
	}
	
	/**
	 * get method used to return the funds involved in the transaction
	 * @return dFundsInvolved
	 */
	public double getFundsInvolved(){
		return dFundsInvolved;
	}
	
	/**
	 * Returns the current transaction object as string
	 * @return sTransactionString
	 */
	public String transAsString(){
		return sTransactionString;
	}

}
