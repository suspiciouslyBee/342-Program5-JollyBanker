////
//  File: Transaciton node
//
//  Author: June
//
//  Description: LL node. Write only at creation.
////


//Breaks

#include "fund_type.h"

class Transaction {
  private:
    char instruction_;

    int srcID_;
    int dstID_;

    FundType fund_;

};