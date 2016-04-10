/**
* Copyright 2016 Jason, Stuart, Muhammad copyright
*/

#include <iostream>
#include "Account.cpp"

#ifndef User_cpp
#define User_cpp

/**
 * Allows management of bank accounts for a user.
 * Example:
 *      User user ("User Name");
 *      user.addAccount(1,100,A,N);
 *      string name = user.getName();
 *      vector<Account> a = user.getAccounts();
 *      user.deposit(0,1000);
 */
class User {
 private:
    // all accounts of the user
    vector<Account>  accounts;
    // the name of the user
    string name;
 public:
    /**
     * The user constructor.
     * name - the name of the account
     */
    User(string name) {
        this->name = name;
    }

    /**
     * Adds an account to the users profile.
     * accountN - the account number of the account
     * funds - the initial funds of the account
     * enable - whether the account is enabled or not
     * plan - the plan type of the account
     */
    bool addAccount(int accountN, double funds, char enable, char plan) {
        Account a(accountN, funds, enable, plan);
        accounts.push_back(a);
        return false;
    }

    /**
     * Returns the name of the account.
     */
    string getName() {
        return name;
    }

    /**
     * Returns true if the account is enabled.
     */
    bool isEnabled(int accountIndex) {
        return accounts[accountIndex].isEnabled();
    }

    /**
     * Changes the plan of the user.
     * u - the user
     * accountIndex - the local index of the account
     */
    bool changeplan(User u, int accountIndex) {
        accounts = u.getAccountNumbers();
        accounts.at(accountIndex).changeplan();
        if(accounts.at(accountIndex).getPlan() == 'N')
            cout << "You have successfully changed plans from a student plan to a non-student plan" << endl;
        else
            cout << "You have successfully changed plans from a non-student plan to a student plan" << endl;
        return true;
    }

    /**
     * Enables or disables the account
     * Returns false if it could not enable or disable the account.
     * u - the user
     * accountIndex - the local index of the account
     */
    bool enableOrDisable(User u, int accountIndex, bool enable) {
        accounts = u.getAccountNumbers();
        return accounts.at(accountIndex).enableOrDisable(enable);
    }

    /**
     * Resets all the limits of all user accounts
     */
    bool resetLimits() {
        for (int i = 0; i < accounts.size(); i++) {
            accounts[i].resetLimits();
        }
    }
    /**
     * Deposits money into the account.
     * accountIndex - the local index of the account
     * amount - the amount of money to deposit
     */
    bool deposit(int accountIndex, double amount) {
        accounts.at(accountIndex).deposit(amount);
        return false;
    }

    /**
     * Returns the current transfer useage of the account
     * accountIndex - the local index of the account
     */
    double getTransferAmount(int accountIndex) {
        return accounts[accountIndex].getTransferAmount();
    }
    /**
     * Returns the current withdrawal useage of the account
     * accountIndex - the local index of the account
     */
    double getWithdrawalAmount(int accountIndex) {
        return accounts[accountIndex].getWithdrawalAmount();
    }

    /**
     * Withdraws from a user account
     * accountIndex - the local index of the account
     * amount - the amount to withdraw
     * type - the type of withdraw (paybill, transfer or withdrawal)
     */
    bool withdrawal(int accountIndex, double amount, char type) {
        accounts.at(accountIndex).withdrawalFunds(amount, type);
        return false;
    }

    /**
     * Returns the current paybill usage of the account
     * accountIndex - the local index of the account
     */
    double getPaybillAmount(int accountIndex) {
        return  accounts.at(accountIndex).getPaybillAmount();
    }

    /**
     * Transfers money to an account.
     * accountIndex - the local index of the account
     * amount - the amount to transfer
     */
    bool transferTo(int accountIndex, double amount) {
        accounts.at(accountIndex).addFunds(amount);
        return false;
    }

    /**
     * Deletes an account the user owns
     * u - the user
     * accountIndex - the local index of the account
     */
    bool deleteAccountN(User u, int accountIndex) {
        accounts = u.getAccountNumbers();
        accounts.erase(accounts.begin()+accountIndex);
        cout << "Successfully delete the account" << endl;
        return false;
    }
    /**
     * Returns the funds that are not allowed to be used in the session
     * accountIndex - the local index of the account
     */
    double getHeldFunds(int accountIndex) {
        return accounts.at(accountIndex).getHeldFunds();
    }

    /**
     * Returns the type of plan the account is.
     * Returns S for student plan, N for normal plan.
     */
    char getAccountPlan(int accountIndex) {
        return accounts.at(accountIndex).getPlan();
    }

    /**
     * Returns the ammount of non-restricted funds in the account
     * accountIndex - the local index of the account
     */
    double getFundsInfo(int accountIndex) {
        return accounts.at(accountIndex).getFundsInfo();
    }

    /**
     * Returns all accounts the user owns.
     */
    vector<Account> getAccountNumbers() {
        return accounts;
    }
};
#endif
