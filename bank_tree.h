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

    bool BuildTree(string &fileName);
    bool ApplyTransaction(Transaction &rhs);
    bool Insert(Transaction &item);
    bool Contains(const int &clientID, Client *&account);

    void Display();


  private:

    int count;
    Client *root_;
};

#endif BANKTREE_H_