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
    void SetName(const vector<string> &name);
    void Clear();
    void Affirm(const bool &state);
    int Amount();
    int DstID();
    int DstFund();
    int SrcFund();
    int SrcID();
    int FundID();

    vector<string> Name();


  
    void Setup(const char &instr, const int &srcID, const int &srcFund, 
                const int &dstID, const int &dstFund, const int &amount);
    //strings imply this is an open.
    void Setup(const int &ID, const vector<string> &name);

  private:
    char instruction_;

    int srcID_;
    int dstID_;

    vector<string> name_;

    FundType fund_;

    bool success_; //write/affirm once, needs to be copied to all iteraitons

};