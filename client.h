////
//  File: Client Tree Node
//
//  Author: June
//
//  Description: Holds client data and transaction history as an even "smarter"
//  struct than the Transaction Class. Acts as a binary node for the Bank Tree.
//  Basic Withdrawls, deposits are implemented here but more complex tasks
//  such as transfers are handled by the higher context (Bank Tree)
//
//  INTENDED TO BE COMPOSED INTO BANK_TREE.
////

#ifndef CLIENT_H_
#define CLIENT_H_

#include <vector>
#include <iostream>
#include <ostream>

#include "transaction.h"
#include "fund_type.h"


//note to self need to init to number of elements

class Client {
  public:
    //Client(); CLIENT MUST HAVE NAME AND ID
    Client(const int &ID, std::vector<std::string> Name);

   
    //Logs transaction history
    void AppendTransaction(Transaction &rhs);

    //If the return matches input, the instruction was valid
    //Accepts only positive ints.
    //Error Return
    //-2 : error, money unchanged
    int Withdrawl(const int &money, const int &fundID);
    int Deposit(const int &money, const int &fundID);

    int ID() const;

    bool InLocalFunds(const int &fundIndex) const;
    
    //simple concactinated name
    std::string Name() const;

    
    std::vector<std::string> SeperatedName() const;

    std::ostream& PrintFund(std::ostream& out, const int &fund, 
                        const bool &showHistory) const;
    friend std::ostream& operator<<(std::ostream& out, Client &rhs);

    //These are "public" but should still be inaccessable due to the node itself
    //being intended to be a private data member to BankTree
    Client *left_;
    Client *right_;
  private:
    int ID_;

    
    std::vector<int> localFunds_; //hardcoded size for now

    
  
    //Vector of transaction history for a fund, by vector of funds
    //so that each vector contains a list according to the id implicit
    std::vector<std::vector<Transaction>> history_;
    std::vector<std::string> name_;
};

#endif //CLIENT_H_