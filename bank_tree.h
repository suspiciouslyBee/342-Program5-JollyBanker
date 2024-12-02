////
//  File: Jolly Banker Data Tree
//
//  Author: June
//
//  Description: Main database for Data tree
////

#ifndef BANKTREE_H_
#define BANKTREE_H_


#include <iostream>
#include <fstream>
#include <string>
#include <queue>

#include "fund_type.h"
#include "transaction.h"
#include "client.h"

using namespace std;

class BankTree {
  public:
    BankTree();
    BankTree(const BankTree &rhs);
    ~BankTree();

    //  queue manip
    void ClearQueue();
    bool BuildQueue(string &fileName);
    bool ExecuteQueue();



    //need to keep in mind: transfer is essentially a
    // withdrawl and then a deposit.
    bool ExecuteTransaction(Transaction &rhs);
    bool CreateClient(Transaction &item);
    
    //note to self: dp/wdis transfering from a hypothetically infinite acc
    bool MoveFunds(Transaction &rhs);
    bool Contains(const int &clientID, Client *&account);

    void Display();


  private:

    

    int count;
    Client *root_;
    queue<Transaction> transactionQueue_;  
};

#endif BANKTREE_H_