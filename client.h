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
    Client();
    Client(const int &ID, const string name[]);

    vector<Transaction> history_;

    void AppendInstruction(const Transaction &rhs);

    //if the return matches input, the instruction was valid
    //special error returns
    //-1 : insufficient funds
    //-2 : FundType doesnt exist!
    int Withdrawal(const int &money, const FundType &FUCK);
    int Deposit(const int &money, const FundType &FUCK);
  private:
    int ID_;
    int localFunds_[8]; //hardcoded size for now

    //returns amt withdrawled or -1 if invalid
  
    
    string name_[2];

    Client *left_;
    Client *right_;
};