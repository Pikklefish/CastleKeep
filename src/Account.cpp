#include <iostream>
#include <random>
using namespace std;

#include "account.hpp"
#include "security.hpp"

int GenerateUUID()
{
    random_device rd;                                   // Non-deterministic random number generator
    mt19937 gen(rd());                                  // Seed the generator with a random device
    uniform_int_distribution<> distr(1000000, 9999999); // Range for random ID (7-digit number)
    return distr(gen); 
}

Account::Account(string name, double init_balance, string hash)
    : account_id(GenerateUUID()),
      account_holder_name(name),
      balance(init_balance),
      password_hash(hash){
    cout << "Account successfully created, ID: " << account_id << endl;
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