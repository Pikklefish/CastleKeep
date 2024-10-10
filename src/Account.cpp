#include <iostream>
#include <random>
using namespace std;

#include "account.hpp"
#include "security.hpp"

int GenerateUUID()
{
    random_device rd;                                   // Non-deterministic random number generator
    mt19937 gen(rd());                                  // Seed the generator with a random device
    uniform_int_distribution<> distr(100000000, 999999999); // Range for random ID (9-digit number)
    return distr(gen); 
}

// Constructor for creating a new account
Account::Account(Database& db, std::string name, double init_balance, std::string hash)
    : db(db),
      account_id(GenerateUUID()),  // Generate new UUID
      account_holder_name(name),
      balance(init_balance),
      password_hash(Security::HashPassword(hash)){
    cout << "Account successfully created, ID: " << account_id << endl;
}

// Constructor for retrieving an existing account from the database
Account::Account(Database& db, int account_id, std::string name, double init_balance, std::string hash)
    : db(db),
      account_id(account_id),  // Use the account_id from the database
      account_holder_name(name),
      balance(init_balance),
      password_hash(Security::HashPassword(hash)) {
    cout << "Account successfully retrieved, ID: " << account_id << endl;
}

bool Account::AuthenticatePassword(const string& password) const{
    string hashed_password = Security::HashPassword(password);
    return hashed_password == password_hash;
}

double Account::GetBalance() const{
    return balance; 
}

void Account::Deposit(double amount){
    balance += amount;
}

void Account::Withdraw(double amount){
    balance -=amount;
}

int Account::GetAccountID() const{   //Getter
    return account_id;
}