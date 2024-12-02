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


//all vals need to init nul or -1 (except id)
class Transaction {
  public:
    Transaction();
    ~Transaction();


    char Instruction();
    void SetName(const string &last, const string &first);
    void Clear();

    void Setup(const int array[], int len);
    void Setup(const string &last, const string &first, const int &ID);

  private:
    char instruction_;

    int srcID_;
    int dstID_;

    string name_[2];

    FundType fund_;

    bool success; //write/affirm once, needs to be copied to all iteraitons

};