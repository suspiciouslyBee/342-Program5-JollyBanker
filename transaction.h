////
//  File: Transaciton node
//
//  Author: June
//
//  Description: LL node. Write only at creation.
////


//Breaks

#ifndef TRANSACTION_H_
#define TRANSACITON_H_

#include "fund_type.h"
#include <ostream>
#include <string>


//all vals need to init nul or -1 (except id)
class Transaction {
  public:

    Transaction();
    Transaction(const char &instr, const int &srcID, const int &srcFund, 
                const int &dstID, const int &dstFund, const int &amount);
    Transaction(const Transaction &rhs);
    //~Transaction();

    void SetName(const vector<string> &name);
    //TODO: make a check for this to not overwrite read-only state
    void Clear();
    void Affirm(const bool &state);

    

    const char Instruction();
    const int SrcID();
    const int DstID();
    
    const int Amount();

    vector<string> Name();

    const int DstFund();
    const int SrcFund();

    const bool Success();
   



    void Setup(const char &instr, const int &srcID, const int &srcFund, 
                const int &dstID, const int &dstFund, const int &amount);
    //strings imply this is an open.
    void Setup(const int &ID, const vector<string> &name);

    friend ostream& operator<<(ostream& out, const Transaction &rhs);

  private:
    char instruction_;

    int srcID_;
    int dstID_;

    vector<string> name_;

    //based around FundType
    int dstFund_;
    int srcFund_;

    int amount_;   

    bool success_; //write/affirm once, needs to be copied to all iteraitons
    bool successWritten_; 

};

#endif //TRANSACTION_H_
