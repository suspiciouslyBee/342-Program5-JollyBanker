////
//  File: Jolly Banker Data Tree
//
//  Author: June
//
//  Description: Main database for Bank Data tree with support for 
//  semi-automated client creation and limited client fund management
//  
//  See design document for more information
//  
////

#ifndef BANKTREE_H_
#define BANKTREE_H_

#include <iostream>
#include <ostream>
#include <fstream>
#include <string>
#include <sstream>
#include <queue>

#include "fund_type.h"
#include "transaction.h"
#include "client.h"


class BankTree {
  public:
    BankTree();
    BankTree(std::string &fileName); //Autoruns Build & execute

    //queue manip
    void ClearQueue();
    bool BuildQueue(std::string &fileName);
    bool ExecuteQueue();

    //Wrappers 
    bool ExecuteTransaction(Transaction &rhs);
    bool CreateClient(Transaction &item);
    //Abstracted transaction manip//Wrapper
    bool MoveFunds(Transaction &rhs);

    //special bst manip
    bool AuditClient(const int &clientID, std::ostream &out = std::cout) const;
    bool AuditClient(const int &clientID, const int &fundID, 
                      std::ostream &out = std::cout) const;

    //bst manip
    //deliberately makes a copy of the ptr arg for recursion
    bool Insert(std::vector<std::string> name, const int &ID, Client *node);
    Client* Find(const int &ID, Client *node) const;
    void PrintTree(Client* t, std::ostream& out) const;

    friend std::ostream& operator<<(std::ostream& out, BankTree &rhs);

    int Size() const;
  private:

    

    int count_;
    Client *root_;
    std::queue<Transaction> transactionQueue_;  
};


std::ostream& operator<<(std::ostream& out, BankTree &rhs);
#endif //BANKTREE_H_