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
    //BankTree(const BankTree &rhs);
    BankTree(string &fileName); //Autoruns Build & execute
    //~BankTree();

    //  queue manip
    void ClearQueue();
    bool BuildQueue(string &fileName);
    bool ExecuteQueue();



    //need to keep in mind: transfer is essentially a
    // withdrawl and then a deposit.

    //transaction manip
    bool ExecuteTransaction(Transaction &rhs);
    bool CreateClient(Transaction &item);
    bool MoveFunds(Transaction &rhs);

    //special bst manip
    bool AuditClient(const int &clientID, ostream &out);
    bool AuditClient(const int &clientID, const int &fundID, ostream &out);

    //bst manip
    //bool Contains(const int &clientID, Client *&account);
    bool Insert(vector<string> name, const int &ID, Client *node);
    Client* Find(const int &ID, Client *node) const;
    void PrintTree(Client* t, ostream& out) const;

    friend ostream& operator<<(ostream& out, BankTree &rhs);
  private:

    

    int count;
    Client *root_;
    queue<Transaction> transactionQueue_;  
};

#endif BANKTREE_H_