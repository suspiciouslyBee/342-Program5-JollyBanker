////
//  File: Client Tree Node
//
//  Author: June
//
//  Description: Holds client data and the linked list history
////

#include <vector>

#include "transaction.h"
#include "fund_type.h"

using namespace std;

class Client {
  public:
    vector<Transaction> history_;
  private:
    int ID_;
    int localFunds_[8]; //hardcoded size for now

    //returns amt withdrawled or -1 if invalid
    int Withdrawl(const int &money, const FundType &FUCK); 
    
    

    Client *left_;
    Client *right_;
};