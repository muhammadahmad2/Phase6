/**
* Copyright 2016 Jason, Stuart, Muhammad copyright
*/
/**
* The bank of hard water is compiled with the following command:
* 	g++ -std=c++11 main.cpp -o main.o
* This program can be run with the command:
*	./main.o 
* The program can read text inputs from a file:
* 	./main.o <textfile.txt>
* When run without the command line argument, it will accept input from the 
* stdin.
* After each command is processed, a transaction log in the folder TF will be
* appended to. This will indicate all the transactions that are completed
* in a session.
* After each user input, a ressponse is send to the stdout, and the user can act
* accordingly.
* This program is intended to be a robust banking interface that does not crash
* and provides useful feedback to the user.
*/
#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <algorithm>
#include <cctype>
#include <sstream>
#include <string.h>
#include <stdlib.h>
#include <fstream>
#include "User.cpp"
using namespace std;

vector<User> users;
int nextAccountN;
bool readFile;
string accountFile;
string transactionFile;
bool standardSession;  // true if the user is in a standard session
int currentAccount;  // the index of the current account
string standardName;  // the name of the standard account

/**
 * Resets all the limits for all users.
 */
bool resetLimits() {
    for (int i = 0; i < users.size(); i++) {
        users[i].resetLimits();
    }
}

/**
 * Gets the input from a text file or cin
 */
string getInput(istream& stream) {
	string input;
    if(readFile){
        if(!getline(stream,input)){
            exit(0);
        }
    } else {
        getline(cin,input);
    }
	return input;
}

/**
 * Writes a string to the TF file.
 */
bool writeTF(string s) {
    ofstream tfFile;
    tfFile.open(transactionFile, std::ofstream::out | std::ofstream::app);
    tfFile << s <<endl;
    tfFile.close();
    return true;
}

/**
 * Retirived From http://stackoverflow.com/questions/1798112/removing-leading-and-trailing-spaces-from-a-string
 * Trims the leading and trailing spaces from a string
 */
string trim(const string& str, const string& whitespace = " \t") {
    const auto strBegin = str.find_first_not_of(whitespace);
    if (strBegin == std::string::npos)
        return "";  // no content
    const auto strEnd = str.find_last_not_of(whitespace);
    const auto strRange = strEnd - strBegin + 1;
    return str.substr(strBegin, strRange);
}

/**
 * Formats the input that will be entered into the transaction file
 * Returns true if it has written to the transaction file
 * accountN - the account number that is involved in a transaction
 * name - The name of the user who is involved in a transaction
 * transactionType - The code for the transaction that is going on
 * funds - The money involved with the transaction if any
 * mm - The miscallenous infomraiton
 */
bool formatTFString(int accountN, string name, string transactionType, double funds, string mm) {
    string tfString;  // String that will be added onto and put into the transaction file
    int nameLength = 0;
    // These two varibles convert are used to convert the numbers into a string
    stringstream convert;
    stringstream convert2;
    tfString += transactionType;  // Store the type of transaction into the string
    tfString += ' ';  // Add a space after the transaction
    tfString += name;  // Add the name of the person involved in the transaction
    nameLength = name.length();  // Store the length of the name into the varible nameLength
    // Will run only if the name of the person is less then 20 and if the name is less then 20 it will run for 20 minus the persons name times
    for (int i = 0; i < (20-nameLength); i++) {
        // Fills in the remaining spots left for the name seciton with spacew
        tfString += ' ';  // This section of code left aligns the name in the transaction file
    }
    tfString += ' ';  // Adds a space after the name section
    convert << accountN;  // Converts the integer account Number to a string and stores it in convert
    // Will run only if the number is less then 5 digits and if the number is less then 5 digits it will run 5 minus number of digits of the number times
    for (int i = 0; i< (5-convert.str().length()); i++) {
        // Fills in the front of the number with zeros
        tfString += "0";  // This section of code right aligns the number in the transaction file with leading 0's
    }
    tfString += convert.str();  // Adds on the account number to the 0's added before
    tfString += ' ';  // Adds a space after the account Number
    convert2 << fixed << setprecision(2) <<funds;  // Converts the double funds to a string and stores it in convert2 as well as ensuring that the string has two decimal points
    // Will run only if the funds is less then 8 digits including a . for the seperation between the decminal and the int
    for (int i = 0; i< (8-convert2.str().length()); i++) {
        // Fills in the front of the funds with zeros
        tfString += "0";  // This section of code right aligns the funds in the transaction file with leading 0's
    }
    tfString += convert2.str();  // Adds on the funds to the 0's added before
    tfString += ' ';  // Adds a space after funds
    tfString += mm;  // Adds the misillanues information if any to the last to characters in the transaction file
    writeTF(tfString);  // Writes the string to the transaction file
    return true;
}

/**
 * Checks if the string is a valid string for a name. Returns false if the name is not valid, true if valid.
 * n - the name to test if it is a valid name
 */
bool isAccountName(string n) {
    char name[256];
    strcpy(name, n.c_str());
    if(n.length() <=0)
    {
        return false;
    }
    for (int i = 0; i < n.size(); i++) {
// if(/*(int)name[i] != 32 || */((int)name[i] < 65 || (int) name[i] > 90) && ((int)name[i] < 97 || (int)name[i] > 122)){
        if ((int)name[i] == 32 || ((int)name[i] >=65 && (int)name[i] <=90) || ((int)name[i] >= 97 && (int)name[i] <= 122)) {
            // acceptedName = true;
        } else {
            return false;
        }
    }
    return true;
}
/**
 * Returns the user index of the account, -1
 * if the account is not found.
 */
int findAccount(string name) {
    // search for the account in all the users.
    for (int i = 0; i < users.size(); i++) {
        if (strcmp(name.c_str(), users.at(i).getName().c_str()) == 0) {
            return i;
        }
    }
    return -1;
}

/**
 * Gets the account index in the accounts vector for the user and and account number.
 * Returns -1 if the account is not found in the users accounts.
 * u - the user to search for the account.
 * accountN - the account number to search for
 */
int getAccountIndex(User u, int accountN) {
    vector<Account>accounts =  u.getAccountNumbers();
    for (int i = 0; i < accounts.size(); i++) {
        if (accountN == accounts.at(i).getAccountN()) {
            return i;
        }
    }
    return -1;
}

/**
 * Checks if the provided string is a number, returns true if it is a number
 * s - the string to check if it is a number
 */
bool isNumber(string s) {
    // go though all characters and see if it is a digit.
    for (int i = 0; i < s.size(); i++) {
        if (!isdigit(s[i])) {
            return false;
        }
    }
    return true;
}
/**
 * Checks if the number provided would be an acceptable double value.
 * s - the string to check if it is a double
 */
bool isDouble(string s) {
    bool startNumber = false;
    bool period = false;
    bool endNumber = false;
    bool negative = false;
    // used to only allow for 2 decimal places
    int count = 0;
    //check if it is an integer
    if(isNumber(s))
        return true;
    //go through the number and see if it is a double
    for (int i = 0; i < s.size(); i++) {
        if (period && isdigit(s[i])) {
            endNumber = true;
            count++;
        } else if (startNumber && s[i] == 46 && !endNumber) {
            period = true;
        } else if (isdigit(s[i])) {
            startNumber = true;
        } else if (!negative && s[i] == 45) {
            negative = true;
        } else {
            return false;
        }
    }
    return startNumber && period && endNumber && count < 3; 
}

/**
 * Gets the account index, user index and account number for a given account string.
 * This contains the error trapping to make it consistent throught the program.
 * This method bypasses the user name validation
 * *accountIndex - pointer to the account index
 * *userIndex - pointer to the user index
 * accountString - the string account number to be validated
 * *accountNumber - the pointer to the accountNumber
 * disableCheck - true if you want to ensure the account is not disabled for a transaction
 */
bool accountValidator(int *accountIndex, int *userIndex, string accountString, int *accountNumber, bool disableCheck){
    if (isNumber(accountString)) {
        *accountNumber = atoi(accountString.c_str());
    } else {
        cout << "Error: Must enter an integer value." << endl;
        return false;
    }
    //this is for the transfer method
    if(*userIndex == -1){
        for (int i = 0; i < users.size(); i++) {
            if (getAccountIndex(users.at(i), *accountNumber) != -1) {
                *userIndex = i;
                break;
            }
        }
    } 
    //still see if it is -1
    if(*userIndex == -1){
        cout << "Error: Please enter a valid account." << endl;
        return false;
    }
    // get the index of the from account
    *accountIndex = getAccountIndex(users.at(*userIndex), *accountNumber);
  
    // see if the account exists
    if (*accountIndex == -1 && standardSession) {
        cout << "Error: Please enter a valid account." << endl;
        return false;
    } else if (*accountIndex == -1) {  // check for admin mode too
        cout << "Error: Please enter a valid account." << endl;
        return false;
    }
    if (!users[*userIndex].isEnabled(*accountIndex) && disableCheck) {  // see if the account is enabled
        cout << "INVAILD – Your account has been disabled" << endl;
        return false;
    }
    return true;
}

/**
 * Gets the account info which includes getting the user's name and acocunt information.
 * Error traps to ensure that a valid name, and other parameters are entered.
 * *userIndex - the pointer ot the userIndex
 * *accountIndex - the pointer to the accountNumber
 * stream - the input stream
 * disableCheck - true if you want to check if the account is disabled.
 */
bool getAccountInfo(int *userIndex, int *accountIndex, int *accountNumber, istream& stream, bool disableCheck) {
    string accountHolder = "";
    string accountString = "";
    if (!standardSession) {
        cout << "Please enter the account holder name:" << endl;
        accountHolder = trim(getInput(stream));
        *userIndex = findAccount(accountHolder);
        if (!isAccountName(accountHolder) || *userIndex == -1) {
            cout << "ERROR: The account does not exist" << endl;
            return false;
        }
    } else {
        // set the userIndex to the current standard acount for a standard session
        *userIndex = currentAccount;
    }
    cout << "Please enter the account number:" << endl;
    accountString = trim(getInput(stream));
    if(!accountValidator(accountIndex, userIndex, accountString, accountNumber,disableCheck))
        return false;
    return true;
}

/**
 * The login transaction. Attempts to
 * log the user into an account.
 * Retruns false if the login was not successful.
 * Also displays error messages for guidance.
 * stream - the input stream of the input
 */
bool login(istream& stream) {
    bool acceptedName = false;
    string input = "";
    cout << "Welcome to the Bank of Hard Water. Please enter login:" << endl;
    input = trim(getInput(stream));
    // continue to see if they enter login
    while (strcasecmp(input.c_str(), "login") != 0) {
        cout << "ERROR: Please enter login:" << endl;
        input = getInput(stream);
    }
    cout << "Please enter Standard or Admin:" << endl;
    input = getInput(stream);
    // keep trying to get standard or admin from the user
    while ((strcasecmp(input.c_str(), "standard") != 0) && (strcasecmp(input.c_str(), "admin") != 0)) {
        cout << "ERROR: Please enter Standard or Admin:" << endl;
      	input = trim(getInput(stream));
    }
    // set the sessision variable accordingly
    if (strcasecmp(input.c_str(), "Standard") == 0)
        standardSession = true;
    else
        standardSession = false;
    // the name of the user
    char name[256];
    if (standardSession) {
        cout << "Please enter your name:" << endl;
      	input = trim(getInput(stream));
        strcpy(name, input.c_str());
        standardName = name;
        acceptedName = isAccountName(input);
        // keep trying to get a valid name from the user
        while (!acceptedName) {
            cout << "ERROR: Please enter a valid name:" << endl;
          	input = trim(getInput(stream));
            acceptedName = isAccountName(input);
        }
        // find the index of the current standard user
        int userIndex = findAccount(input);
        if (userIndex == -1) {
            cout << "Error: Account does not exist" << endl;
            return false;
        }
        // set the currentAccount to the user index for other methods
        currentAccount = userIndex;
    }
    // write to the transaction file
    if (standardSession)
        formatTFString(0, name, "10", 00.00, "S ");
    else
        formatTFString(0, "                    ", "10", 00.00, "A ");
    return true;
}

/**
 * Logs a user out of a session by resetting limits and
 * the current acount, as well as write to the transaciton
 * file.
 */
bool logout() {
    currentAccount = -1;
    // reset the limits of all accounts
    resetLimits();
    // write to the TF
    if (standardSession)
        formatTFString(0, standardName, "00", 00.00, "S ");
    else
        formatTFString(0, "                    ", "00", 00.00, "A ");
    return false;
}

/**
 * Tries to enable or disable an account based on a users input.
 * stream - the input stream
 * enable - true to enable an account, false to disable an account.
 */
bool enableOrDisable(istream& stream, bool enable) {
    // default code for disable
    string transCode = "07";
    // These two variables store the index of the User and account number from there list
    int accountIndex = -1;
    int userIndex = -1;
    int accountN;  // The account number the admin is trying to enable is stored here
    if(enable){
        transCode = "09";
    }
    if(!getAccountInfo(&userIndex, &accountIndex, &accountN, stream, false))
        return false;    
    if (users.at(userIndex).enableOrDisable(users.at(userIndex), accountIndex, enable)){  // Enables the users account
        formatTFString(accountN, users.at(userIndex).getName(), transCode, 00.00, "  ");
        return true;
    }
    return false;
}



/**
 * The delete function
 * Tries to delete an account.
 * Returns true if the deletion was successful.
 * stream - the input stream
 */
bool deleteAccount(istream& stream) {
    // These two variables store the index of the User and account number from there list
    int accountIndex = -1;
    int userIndex = -1;
    int accountN;  // The account number the admin is trying to disable is stored here
    if(!getAccountInfo(&userIndex, &accountIndex, &accountN, stream, true))
        return false;  
    users.at(userIndex).deleteAccountN(users.at(userIndex), accountIndex);  // Deletes the users account
    // write to the TF
    formatTFString(accountN, users.at(userIndex).getName(), "06", 00.00, "  ");
    return false;
}

/**
 * Tries to change the plan of a user account.
 * Returns false if the changeplan fails.
 */
bool changeplan(istream& stream) {
    // These two variables store the index of the User and account number from there list
    int accountIndex = -1;
    int userIndex = -1;
    string planString = "NP";
    int accountN;  // The account number the admin is trying to change plans for is stored here
    if(!getAccountInfo(&userIndex, &accountIndex, &accountN, stream, true))
        return false;  
    users.at(userIndex).changeplan(users.at(userIndex), accountIndex);  // Change plnas the users account
    char planType = users.at(userIndex).getAccountPlan(accountIndex);
    if(planType == 'S')
        planString = "SP";
    formatTFString(accountN, users.at(userIndex).getName(), "08", 00.00, planString);
    return false;
}

/**
 * Tries to transfer money to and from an account
 * Returns false if the transfer fails.
 * stream - the input stream
 */
bool transfer(istream& stream) {
    // used for the account numbers and names
    string accountHolder = "";
    string accountFromString;
    string accountToString;
    string input = "";
    // account numbers
    int accountFromN;
    int accountToN;
    double transferAmount = 0.0;
    double userFunds = 0.0;  // the current funds of the account
    char accountPlan;  // the account plan
    double charge = 0.0;
    // used to keep track of the indexes of the users and accounts
    int userIndex = -1;
    int accountToIndex = -1;
    int userToIndex = -1;
    int accountFromIndex = -1;
    // get the account name from the user when in admin mode
    if(!getAccountInfo(&userIndex, &accountFromIndex, &accountFromN, stream, true))
        return false;
    cout << "Please enter the number of the account to transfer to:" << endl;
    accountToString = trim(getInput(stream));
    if(!accountValidator(&accountToIndex, &userToIndex, accountToString, &accountToN, true))
        return false;
    cout << "Please enter the amount to transfer (XXXX.XX):" << endl;
  	input = trim(getInput(stream));
    if(!isDouble(input)){
        cout << "Error: Must enter a double or an integer value." << endl;
        return false;
    }
    transferAmount = stod(input);
    // get the funds and account plan from the users account
    userFunds = users.at(userIndex).getFundsInfo(accountFromIndex) - users.at(userIndex).getHeldFunds(accountFromIndex);
    accountPlan = users.at(userIndex).getAccountPlan(accountFromIndex);
    // set the charge price otherwise it is 0.0
    if (standardSession) {
        if (accountPlan == 'N') {
            charge = 0.10;
        } else
            charge = 0.05;
    }
    if (transferAmount < 0) {
        cout << "Error - Please enter a postive amount" << endl;
        return false;
    }
    // check if amount is less than 1000.00
    if (standardSession && transferAmount + users[userIndex].getTransferAmount(accountFromIndex) > 1000.00) {
        cout << "Error: Exceeds account limits" << endl;
        return false;
    }
    // see if the user has enough funds
    if (userFunds - charge - transferAmount < 0.0) {
        cout << "Error: Insufficient funds" << endl;
        return false;
    }
    // the funds of the destination user account
    double userToFunds = users.at(userToIndex).getFundsInfo(accountToIndex);
    // check if the transfer will exceed the limitations
    if (userToFunds + transferAmount > 99999.99) {
        cout << "Error - Transfer would exceed limitations" << endl;
        return false;
    }
    // perform the withdrawal and write to the TF
    users.at(userIndex).withdrawal(accountFromIndex, transferAmount + charge, 'T');
    if (standardSession) {
        formatTFString(accountFromN, users.at(userIndex).getName(), "02", transferAmount, "F ");
        formatTFString(accountToN, users.at(userToIndex).getName(), "02", transferAmount, "T ");
    } else {
        formatTFString(accountFromN, users.at(userIndex).getName(), "02", transferAmount, "F ");
        formatTFString(accountToN, users.at(userToIndex).getName(), "02", transferAmount, "T ");
    }
    users.at(userToIndex).transferTo(accountToIndex, transferAmount);
    cout << "Successful Transfer" << endl;
    return true;
}

/**
 * Tries to perform the paybill transaction.
 * Returns false if the transaction fails.
 * stream - the input stream
 */
bool paybill(istream& stream) {
    string input = "";
    string companyName = "";
    int accountN;  // the account number of the transaction
    // the index of the items in the vectors for accessing
    int userIndex = -1;
    int accountIndex = -1;
    double userFunds = 0.0;  // the current funds of the account
    char accountPlan;  // the account plan
    double charge = 0.0;
    double paybillAmount = 0.0;
    if(!getAccountInfo(&userIndex, &accountIndex, &accountN, stream, true))
        return false;
    cout << "Please enter a company:" << endl;
  	input = trim(getInput(stream));
    companyName = input;
    // see if it is a valid company
    if (input.compare("EC") != 0 && input.compare("CQ") != 0 && input.compare("TV") != 0) {
        cout << "ERROR: Invalid company" << endl;
        return false;
    }
    cout << "Please enter the amount to pay (XXXX.XX):" << endl;
  	input = trim(getInput(stream));
    // see if it is a valid double or int
    if (!isDouble(input)) {
        cout << "Error: Must enter a double or an integer value." << endl;
        return false;
    }
    paybillAmount = stod(input);
    // get the funds and account plan from the users account
    userFunds = users.at(userIndex).getFundsInfo(accountIndex) - users.at(userIndex).getHeldFunds(accountIndex);
    accountPlan = users.at(userIndex).getAccountPlan(accountIndex);
    // set the charge price otherwise it is 0.0
    if (standardSession) {
        if (accountPlan == 'N') {
            charge = 0.10;
        } else
            charge = 0.05;
    }
    if (paybillAmount < 0) {
        cout << "Error - Please enter a postive amount" << endl;
        return false;
    }
    // check if amount is less than 2000.00
    if (standardSession && paybillAmount + users.at(userIndex).getPaybillAmount(accountIndex) > 2000.00) {
        cout << "Error: Amount exceeds account limitations." << endl;
        return false;
    }
    if (userFunds - charge - paybillAmount < 0.0) {
        cout << "Error: Insufficient funds" << endl;
        return false;
    } else {  // finaly complete the transacion and write to the TF
        users.at(userIndex).withdrawal(accountIndex, paybillAmount + charge, 'P');
        if (standardSession)
            formatTFString(accountN, standardName, "03", paybillAmount, companyName);
        else
            formatTFString(accountN, users.at(userIndex).getName(), "03", paybillAmount, companyName);
        cout << "You successfully paid the bill." << endl;
        return true;
    }
    return false;
}

/**
 * Attempts to complete the create transaction
 * Returns false if the transaction fails.
 * stream - the input stream.
 */
bool create(istream& stream) {
    string accountName;
    string initialAmountString;
    double initialAmountDouble;
    bool userExists = false;
    cout << "Please enter the name of the account holder:" << endl;
  	accountName = trim(getInput(stream));
    if (!isAccountName(accountName)) {
        cout << "Error: Please only enter a valid name." << endl;
        return false;
    }
    // truncate and trim the account name
    accountName = accountName.substr(0, 20);
    accountName = trim(accountName);
    cout << "Please enter the initial ammount of the account (XXXX.XX):" << endl;
  	initialAmountString = getInput(stream);
    // trim and set to a double
    initialAmountString = trim(initialAmountString);
    if(!isDouble(initialAmountString)){
        cout << "Error: Must enter a double or an integer value." << endl;
        return false;
    }
    initialAmountDouble = stod(initialAmountString);
    // see if initial amount is valid
    if (initialAmountDouble > 99999.99 || initialAmountDouble < 0.0) {
        cout << "Error: Must enter a positive amount up to $99999.99" << endl;
        return false;
    }
    // search to see if a user with the same name exists.
    for (int i = 0; i < users.size(); i++) {
        if (users[i].getName().compare(accountName) == 0) {
            users[i].addAccount(nextAccountN++, initialAmountDouble, 'A', 'N');
            userExists = true;
            break;
        }
    }
    // if it does exist, dont make a new user object
    if (!userExists) {
        User newUser(accountName);
        newUser.addAccount(nextAccountN++, initialAmountDouble, 'A', 'N');
        users.push_back(newUser);
    }
    cout << "Successfully created the account." << endl;
    formatTFString(nextAccountN - 1, accountName, "05", initialAmountDouble, "  ");
    return true;
}

/**
* The withdrawal transaction.
* Checks for user error then withdraws the amount from the user's bank account.
* Returns false if the transaction fails
* stream - the input stream
*/
bool withdrawal(istream& stream) {
    string input = "";
    int accountN;  // the account number of the transaction
    // the index of the items in the vectors for accessing
    int userIndex = -1;
    int accountIndex = -1;
    double userFunds = 0.0;  // the current funds of the account
    char accountPlan;  // the account plan
    double charge = 0.0;
    double withdrawalAmount = 0.0;
    // ask additional info if in admin mode
    if(!getAccountInfo(&userIndex, &accountIndex, &accountN, stream, true))
        return false;
    cout << "Please enter the amount to withdraw (XXXX.XX):" << endl;
  	input = trim(getInput(stream));
    if(!isDouble(input)){
        cout << "Error: Must enter a double or an integer value." << endl;
        return false;
    }
    withdrawalAmount = stod(input);  // convert to a double.. not working if like 1u8.1 or something    
    // get the funds and account plan from the users account
    userFunds = users.at(userIndex).getFundsInfo(accountIndex) - users.at(userIndex).getHeldFunds(accountIndex);
    accountPlan = users.at(userIndex).getAccountPlan(accountIndex);
    // set the charge price otherwise it is 0.0
    if (standardSession) {
        if (accountPlan == 'N') {
            charge = 0.10;
        } else
            charge = 0.05;
    }
    if (withdrawalAmount < 0) {
        cout << "Error - Please enter a postive amount" << endl;
        return false;
    }
    // the ammount must be a multiple of $5
    if (fmod(withdrawalAmount, 5) != 0) {
        cout << "Error: Invalid amount. Can only withdraw multiples of $5, $10, $20, $50" << endl;
        return false;
    }
    // check if the standard withdrawal is <= 500.00
    if (standardSession && withdrawalAmount + users.at(userIndex).getWithdrawalAmount(accountIndex) > 500.0) {
        cout << "Error: Exceeded withdrawal limit" << endl;
        return false;
    }
    if (userFunds - charge - withdrawalAmount < 0.0) {
        cout << "Error: Insufficient funds" << endl;
        return false;
    } else {  // finally complete the transaction
        users.at(userIndex).withdrawal(accountIndex, withdrawalAmount + charge, 'W');
        if (standardSession) {
            formatTFString(accountN, standardName, "01", withdrawalAmount, "  ");
        } else {
            formatTFString(accountN, users.at(userIndex).getName(), "01", withdrawalAmount, "  ");
        }
        cout << "Successful withdrawal" << endl;
        return true;
    }
    return false;
}

/**
* The deposit transaction.
* Checks for user error then deposits the amount to the user's bank.
* stream - the input stream
*/
bool deposit(istream& stream) {
    string input = "";
    int accountN;  // the account number of the transaction
    // the index of the items in the vectors for accessing
    int userIndex = -1;
    int accountIndex = -1;
    double userFunds = 0.0;  // the current funds of the account
    char accountPlan;  // the account plan
    double charge = 0.0;
    double depositAmount = 0.0;
    if(!getAccountInfo(&userIndex, &accountIndex, &accountN, stream, true))
        return false;
    cout << "Please enter the amount to deposit (XXX.XX):" << endl;
  	input = trim(getInput(stream));
   	if(!isDouble(input)){
        cout << "Error: Must enter a double or an integer value." << endl;
        return false;
    }
        // convert to a double.. not working if like 1u8.1 or something
    depositAmount = stod(input); 
    
    // get the funds and account plan from the users account
    userFunds = users.at(userIndex).getFundsInfo(accountIndex);
    accountPlan = users.at(userIndex).getAccountPlan(accountIndex);
    // set the charge if not an admin
    if (standardSession) {
        if (accountPlan == 'N') {
            charge = 0.10;
        } else
            charge = 0.05;
    }
    if (depositAmount < 0) {
        cout << "Error - Please enter a postive amount" << endl;
        return false;
    }
    if (depositAmount < charge) {
        cout << "Error - Amount is less than the transaction fee" << endl;
        return false;
    }
    if (depositAmount + userFunds - charge > 99999.99) {
        cout << "Error: Deposit rejected. Account would be over maximum balance." << endl;
        return 0;
    }
    users.at(userIndex).deposit(accountIndex, depositAmount - charge);
    // write to the TF
    if (standardSession)
        formatTFString(accountN, standardName, "04", depositAmount, "  ");
    else
        formatTFString(accountN, users.at(userIndex).getName(), "04", depositAmount, "  ");
    cout << "Successful deposit" << endl;
    return true;
}

/**
 * Reads all the accounts from the accounts file and makes users
 * and accounts for the users.
 * Returns false if the file cannot be opened
 */
bool readAccounts() {
    char  linec[37];
    char *tokens;
    int accountN;
    string name;
    char active;
    double funds;
    char plan;
    bool userExists = false;
    string line;
    ifstream accountsFile(accountFile);
    if (accountsFile.is_open()) {
        while	(getline(accountsFile, line)) {
            accountN = atoi(line.substr(0, 6).c_str());
            name = line.substr(6, 20);
            name = trim(name);
            active = line[27];
            funds = stod(line.substr(28, 36));
            plan = line[38];

            userExists = false;
            // don't add END_OF_FILE ACCOUNT"
            if (accountN != 0) {
                nextAccountN = accountN + 1;
                // check if the account exists and add it if it does.
                for (int i = 0; i < users.size(); i++) {
                    if (users[i].getName().compare(name) == 0) {
                        users[i].addAccount(accountN, funds, active, plan);
                        userExists = true;
                        break;
                    }
                }
                // make a new user if they dont exist
                if (!userExists) {
                    User newUser(name);
                    newUser.addAccount(accountN, funds, active, plan);
                    users.push_back(newUser);
                }
            }
        }
        accountsFile.close();
    } else {
        cout << "error opening accounts file" << endl;
        return false;
    }
    return true;
}

/**
 * Calls the appropriate transaction method.
 * Returns true if the user logs out
 * input - the command string
 * stream - the input stream
 */
bool doCommand(string input, istream& stream) {
    if (strcasecmp(input.c_str(), "withdrawal") == 0) {
        withdrawal(stream);
    } else if (strcasecmp(input.c_str(), "transfer") == 0) {
        transfer(stream);
    } else if (strcasecmp(input.c_str(), "paybill") == 0) {
        paybill(stream);
    } else if (strcasecmp(input.c_str(), "deposit") == 0) {
        deposit(stream);
    } else if (strcasecmp(input.c_str(), "logout") == 0) {
        logout();
        return true;
    } else {
        // Checks to see if the session is Standard if not allow Admin to use these functions
        if (!standardSession) {
            if (strcasecmp(input.c_str(), "create") == 0) {
                create(stream);
            } else if (strcasecmp(input.c_str(), "delete") ==0) {
                deleteAccount(stream);
            } else if (strcasecmp(input.c_str(), "enable") ==0) {
                enableOrDisable(stream, true);
            } else if (strcasecmp(input.c_str(), "disable") ==0) {
                enableOrDisable(stream, false);
            } else if (strcasecmp(input.c_str(),"changeplan") == 0) {
                changeplan(stream);
            } else {
                cout << "ERROR: Please enter a valid command:" << endl;
            }
        } else {
            cout << "ERROR: Please enter a valid command:" << endl;
        }
    }
    return false;
}

/**
 * Initalizes the system. Allows for text input from a file.
 * Then recieves input from the command line.
 * argc - the number of arguments from the command line
 * argv - the arguments
 */
int main(int argc, char* argv[]) {
    bool validCommand = false;
    nextAccountN = 1;
    bool logout = false;
    string input;
    string file = "";
    transactionFile = "./TF/transactionFile.txt"; 
    accountFile = "./Accounts/valid-accounts";
    // if there is a text file, try to read the input
    if(argc > 2){
        accountFile = argv[1];
        transactionFile = argv[2];
    }
    if (argc > 3){
        file = argv[3];
        readFile = true;
    } else {
        readFile = false;
    }
    readAccounts();
    ifstream commandsFile(file);
    while (true) {
        // try to login and complete do the transaction
        while (!login(commandsFile)) {}
        while (!logout) {
            if (standardSession)
                cout << "Options: withdrawal, transfer, paybill, deposit, logout" << endl;
            else
                cout << "Options: withdrawal, transfer, paybill, deposit, create, delete, disable, changeplan, logout, enable" << endl;
            cout << "Please enter a command:" << endl;
            input = getInput(commandsFile);
            input = trim(input);
            logout = doCommand(input, commandsFile);
        }
        logout = false;
    }
    commandsFile.close();
    return 0;
}
