////
//  File: Client Tree Node
//
//  Author: June
//
//  Description: Holds client data and the linked list history
////

#include <vector>

#include "transaction.h"

using namespace std;

class Client {
  public:
  private:
    int ID_;
    int localFunds_[8];
    
    vector<Transaction> history_;

    Client *left_;
    Client *right_;
};