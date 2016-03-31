/**
* Copyright 2016 Jason, Stuart, Muhammad copyright
*/

#include <iostream>

#ifndef Account_cpp
#define Account_cpp

using namespace std;

/**
 * Used to keep track of a bank account.
 * Example:
 *      Account a (1,100,A,N);
 *      a.deposit(200.00);
 *      a.withdrawalFunds(100.0);
 */
class Account {
 private:
    // the money in the account
    double funds;
    // the account number
    int accountN;
    // the plan type of the avvount
    char plan;
    // A for active or D for disabled
    char enable;

    // the limits of the account
    double withdrawalAmount;
    double transferAmount;
    double paybillAmount;
    double heldFunds;

 public:
    /**
     * The Account Constructor
     * accountN - the number of the account
     * funds - the initial amount of the account
     * enable - A for active, D for disabled
     * plan - the type of account, N for normal plan, S for student plan
     */
    Account(int accountN, double funds, char enable, char plan) {
        this->accountN = accountN;
        this->funds = funds;
        this->enable = enable;
        this->plan = plan;
        this->withdrawalAmount = 0;
        this->transferAmount = 0;
        this->paybillAmount = 0;
        this->heldFunds = 0;
    }

    /**
     * Returns the non-restricted funds of the account.
     */
    double getFundsInfo() {
        return funds;
    }

    /**
     * Returns the paybill transaction totals.
     */
    double getPaybillAmount() {
        return paybillAmount;
    }

    /**
     * Returns the withdrawal transaction totals.
     */
    double getWithdrawalAmount() {
        return withdrawalAmount;
    }

    /**
     * Returns the transfer transaction totals
     */
    double getTransferAmount() {
        return transferAmount;
    }

    /**
     * Increases the transfer amount of the account
     */
    bool addTransferAmount(double amount) {
        transferAmount += amount;
    }

    /**
     * Withdraws money from the account and adds to the appropriate transaction variable
     * amount - the amount to withdraw
     * type - the type of withdrawal, T for transfer, W for withdrawal, P for paybill
     */
    bool withdrawalFunds(double amount, char type) {
        this->funds -= amount;
        if (type == 'T')
            this->transferAmount += amount;
        else if (type == 'W')
            this->withdrawalAmount += amount;
        else
            this->paybillAmount += amount;
        return true;
    }

    /**
     * Changes the current plan of the account from
     * either student to normal or normal to student
     */
    bool changeplan() {
        if (plan == 'N') {
            plan = 'S';
        } else {
            plan = 'N';
        }
        return false;
    }

    /**
     * Returns the current plan of the account
     * N for normal, S for student
     */
    char getPlan() {
        return plan;
    }

    /**
     * Enables the account if disabled. otherwise displays an error message.
     */
    bool enableOrDisable(bool enableBool) {

        if (enableBool && enable =='D') {
            cout << "The account has been successfully enabled" << endl;
            enable = 'A';
            return true;
        } else if (!enableBool && enable == 'A'){
            cout << "The account has been successfully disabled" << endl;
            enable = 'D';
            return true;
        } else {
            cout << "Error: The account is already ";
            if(enableBool)
                cout << "enabled" << endl;
            else
                cout << "disabled" << endl;
            return false;
        }
    }

    /**
     * Returns the account number
     */
    int getAccountN() {
        return accountN;
    }

    /**
     * Returns true if the account is enabled.
     */
    bool isEnabled() {
        if (enable == 'D')
            return false;
        else
            return true;
    }

    /**
     * Resets all transaction limits for the account.
     * This is intended for use after logout is called.
     */
    bool resetLimits() {
        this->heldFunds = 0;
        this->withdrawalAmount = 0;
        this->transferAmount = 0;
        this->paybillAmount = 0;
        return true;
    }

    /**
     * Adds funds to an account without adding to limits
     * amount - the amount to add to the account
     */
    bool addFunds(double amount) {
        this->funds += amount;
        return true;
    }

    /**
     * Returns the restricted funds on the account
     */
    double getHeldFunds() {
        return heldFunds;
    }

    /**
     * Deposits money into the account, and adds to the held funds.
     */
    bool deposit(double amount) {
        this->funds += amount;
        this->heldFunds += amount;
        return true;
    }
};
#endif
