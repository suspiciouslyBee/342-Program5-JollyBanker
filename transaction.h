////
//  File: Transaciton node
//
//  Author: June
//
//  Description: This node holds the "instructions" that bank tree reads. Any
//  Money movement gets logged in a valid node's history_. 
////

#ifndef TRANSACTION_H_
#define TRANSACTION_H_

#include <vector>
#include <ostream>
#include <string>

#include "fund_type.h"

//all vals need to init nul or -1 (except id)
class Transaction {
  public:

    Transaction();
    Transaction(const char &instr, const int &srcID, const int &srcFund, 
                const int &dstID, const int &dstFund, const int &amount);
    Transaction(const Transaction &rhs);
    //~Transaction(); Not needed due to simple or defined types

    void SetName(const std::vector<std::string> &name);
    void Clear();
    void Affirm(const bool &state);

    
    //Getters
    char Instruction() const;
    int SrcID() const;
    int DstID() const;
    int Amount() const;
    std::vector<std::string> Name();
    int DstFund() const;
    int SrcFund() const;
    bool Success() const;
    bool isAffirmed() const;
   



    void Setup(const char &instr, const int &srcID, const int &srcFund, 
                const int &dstID, const int &dstFund, const int &amount);
    //strings imply this is an open transaction.
    void Setup(const int &ID, const std::vector<std::string> &name);

    friend std::ostream& operator<<(std::ostream& out, const Transaction &rhs);

  private:
    char instruction_;

    int srcID_;
    int dstID_;

    std::vector<std::string> name_;

    //based around FundType
    int dstFund_;
    int srcFund_;

    int amount_;   

    bool success_; //write/affirm once, needs to be copied to all iteraitons
    bool successWritten_; 

};

#endif //TRANSACTION_H_
