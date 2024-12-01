////
//  File: Transaciton node
//
//  Author: June
//
//  Description: LL node. Write only at creation.
////


//Breaks

#include "fund_type.h"
#include <string>

class Transaction {
  public:
    Transaction();
    ~Transaction();

    SetName(const string &last, const string &first);

  private:
    char instruction_;

    int srcID_;
    int dstID_;

    string name_[2];

    FundType fund_;

};