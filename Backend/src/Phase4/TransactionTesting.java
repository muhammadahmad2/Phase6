package Phase4;

import static org.junit.Assert.*;

import java.io.File;
import java.io.FileNotFoundException;
import java.nio.file.NotDirectoryException;
import java.util.ArrayList;
import org.junit.Before;
import org.junit.Test;

public class TransactionTesting {
	
	//----GLOBAL VARIABLES FOR MASTER ACCOUNTS FILE-----------------------
	private ArrayList<Account> arrayOfAccounts = new ArrayList<Account>();
	//--------------------------------------------------------------------
	 
	@Before
	public void setup() throws FileNotFoundException, NotDirectoryException{
		File masterAccountFile = new File("master_accounts.txt");
		arrayOfAccounts = Utilities.getArrayOfAccounts(masterAccountFile);	
	}
	
	@Test
	public void createAccountTestSuccess(){
		Transaction transaction = new Transaction("05 vector prime         12351 00000.00 MM");
		assertEquals(Utilities.processTransaction(transaction, arrayOfAccounts), true);
	}
	
	@Test
	public void createAccountTestFail(){
		Transaction transaction = new Transaction("05 dominick mancini     12345 00000.00 MM");
		assertEquals(Utilities.processTransaction(transaction, arrayOfAccounts), false);
	}
	
	@Test
	public void depositFundsFail(){
		Transaction transaction = new Transaction("04 chuck norris         12348 00000.09 MM");
		assertEquals(Utilities.processTransaction(transaction, arrayOfAccounts), false);
	}
	
	@Test
	public void depositFundsSuccess(){
		Transaction transaction = new Transaction("04 janahan nirmalan     12350 00300.00 MM");
		assertEquals(Utilities.processTransaction(transaction, arrayOfAccounts), true);
	}
	
	@Test
	public void depositFundsDisabled(){
		Transaction transaction = new Transaction("04 scott mclean         12346 00010.00 MM");
		assertEquals(Utilities.processTransaction(transaction, arrayOfAccounts), false);
	}
	
	@Test
	public void withdrawFundsDisabled(){
		Transaction transaction = new Transaction("01 scott mclean         12346 00010.00 MM");
		assertEquals(Utilities.processTransaction(transaction, arrayOfAccounts), false);
	}
	
	@Test
	public void withdrawFundsSuccess(){
		Transaction transaction = new Transaction("01 dominick mancini     12345 00010.00 MM");
		assertEquals(Utilities.processTransaction(transaction, arrayOfAccounts), true);
	}
	
	@Test
	public void withdrawFundsFailure(){
		Transaction transaction = new Transaction("01 dominick mancini     12345 00200.00 MM");
		assertEquals(Utilities.processTransaction(transaction, arrayOfAccounts),false);
	}
	
	@Test
	public void paybillCompanyDoesNotExist(){
		Transaction transaction = new Transaction("03 dominick mancini     12345 00050.00 TT");
		assertEquals(Utilities.processTransaction(transaction, arrayOfAccounts),false);
	}
	
	@Test
	public void paybillSuccess(){
		Transaction transaction = new Transaction("03 dominick mancini     12345 00050.00 TV");
		assertEquals(Utilities.processTransaction(transaction, arrayOfAccounts), true);
	}
	
	@Test
	public void paybillInsufficientFunds(){
		Transaction transaction = new Transaction("03 dominick mancini     12345 00200.00 TV");
		assertEquals(Utilities.processTransaction(transaction, arrayOfAccounts), false);
	}
	
	@Test
	public void paybillDisabled(){
		Transaction transaction = new Transaction("03 scott mclean         12346 00050.00 TV");
		assertEquals(Utilities.processTransaction(transaction,arrayOfAccounts), false);
	}
	
	@Test
	public void withdrawNonExistantAccount(){
		Transaction transaction = new Transaction("01 bob mclean           15736 00050.00 MM");
		assertEquals(Utilities.processTransaction(transaction,arrayOfAccounts), false);
	}
	
	@Test
	public void depositNonExistantAccount(){
		Transaction transaction = new Transaction("04 bob mclean           15736 00050.00 MM");
		assertEquals(Utilities.processTransaction(transaction,arrayOfAccounts), false);
	}
	
	@Test
	public void paybillNonExistantAccount(){
		Transaction transaction = new Transaction("01 bob mclean           15736 00050.00 TV");
		assertEquals(Utilities.processTransaction(transaction,arrayOfAccounts), false);
	}	
	
	@Test
	public void deleteAccountSuccess(){
		Transaction transaction = new Transaction("06 dominick mancini     12345 00000.00 MM");
		assertEquals(Utilities.processTransaction(transaction, arrayOfAccounts), true);
	}
	
	@Test
	public void deleteAccountFailure(){
		Transaction transaction = new Transaction("06 bob mclean           15736 00000.00 MM");
		assertEquals(Utilities.processTransaction(transaction,arrayOfAccounts), false);
	}
	
	@Test
	public void changeplanSuccess(){
		Transaction transaction = new Transaction("08 dominick mancini     12345 00000.00 MM");
		assertEquals(Utilities.processTransaction(transaction,arrayOfAccounts), true);
	}
	
	@Test
	public void changeplanFailure(){
		Transaction transaction = new Transaction("08 bob mclean           15736 00000.00 MM");
		assertEquals(Utilities.processTransaction(transaction,arrayOfAccounts), false);
	}
	
	@Test
	public void disableAccountSuccess(){
		Transaction transaction = new Transaction("07 dominick mancini     12345 00000.00 MM");
		assertEquals(Utilities.processTransaction(transaction, arrayOfAccounts), true);
	}
	
	@Test
	public void disableAccountFailure(){
		Transaction transaction = new Transaction("07 scott mclean         12346 00000.00 MM");
		assertEquals(Utilities.processTransaction(transaction, arrayOfAccounts), false);
	}
	
	@Test
	public void enableAccountSuccess(){
		Transaction transaction = new Transaction("09 scott mclean         12346 00000.00 MM");
		assertEquals(Utilities.processTransaction(transaction, arrayOfAccounts), true);
	}
	
	@Test
	public void enableAccountFailure(){
		Transaction transaction = new Transaction("09 dominick mancini     12345 00000.00 MM");
		assertEquals(Utilities.processTransaction(transaction, arrayOfAccounts), false);
	}
	
	
	
}