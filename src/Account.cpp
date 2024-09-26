#include <iostream>
#include <random>
using namespace std;

#include "account.hpp"
#include "security.hpp"

int generateUUID()
{
    random_device rd;                                   // Non-deterministic random number generator
    mt19937 gen(rd());                                  // Seed the generator with a random device
    uniform_int_distribution<> distr(1000000, 9999999); // Range for random ID (7-digit number)
    return distr(gen); 
}

Account::Account(string name, double initBalance, string hash)
    : accountID(generateUUID()),
      accountHolderName(name),
      balance(initBalance),
      passwordHash(hash){
    cout << "Account successfully created, ID: " << accountID << endl;
}

bool Account::authenticatePassword(const string& password) const{
    string hashedPassword = Security::hashPassword(password);
    return hashedPassword == passwordHash;
}

double Account::getBalance() const{
    return balance; 
}

void Account::deposit(double amount){
    balance += amount;
}

void Account::withdraw(double amount){
    balance -=amount;
}