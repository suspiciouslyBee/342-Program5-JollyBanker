////
//  File: Client Tree Node
//
//  Author: June
//
//  Description: Holds client data and the linked list history
////

#include <vector>
#include <ostream>
#include

#include "transaction.h"
#include "fund_type.h"

using namespace std;

//note to self need to init to number of elements

class Client {
  public:
    //Client(); CLIENT MUST HAVE NAME AND ID
    Client(const int &ID, vector<string> Name);

   

    void AppendInstruction(Transaction &rhs);

    //if the return matches input, the instruction was valid
    //special error returns
    //-1 : insufficient funds
    //-2 : invalid format! doesnt exist!
    int Withdrawal(const int &money, const int &fundID);
    int Deposit(const int &money, const int &fundID);

    int ID();

    bool InLocalFunds(const int &fundIndex);
    
    //simple concactinated name
    string Name();

    Client *left_;
    Client *right_;
    vector<string> SeperatedName();

    ostream& ClientAudit();
    void FundAudit();

  private:
    int ID_;

    
    int localFunds_[8]; //hardcoded size for now

    //returns amt withdrawled or -1 if invalid
  
    //Vector of transaction history for a fund, by vector of funds
    vector<vector<Transaction>> history_;
    vector<string> name_;


};