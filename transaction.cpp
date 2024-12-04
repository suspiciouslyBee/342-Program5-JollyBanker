#include "transaction.h"
#include <vector>
#include <string>

using namespace std;


Transaction::Transaction() {
  instruction_ = '\0';
  srcID_ = -1;
  dstID_ = -1;
  dstFund_ = UNDEFINED;
  srcFund_ = UNDEFINED;
  amount_ = -1;
  success_ = false;
  successWritten_ = false;
}

Transaction::Transaction(const char &instr, const int &srcID, 
                          const int &srcFund, const int &dstID, 
                          const int &dstFund, const int &amount) {


  Setup(instr, srcID, srcFund, dstID, dstFund, amount);
}

Transaction::Transaction(const Transaction &rhs) {
  instruction_ = rhs.instruction_;
  srcID_ = rhs.srcID_;
  dstID_ = rhs.dstID_;
  dstFund_ = rhs.dstFund_;
  srcFund_ = rhs.srcFund_;
  amount_ = rhs.amount_;
  success_ = rhs.success_;
  successWritten_ = rhs.successWritten_;
}

void Transaction::SetName(const vector<string> &name) {
  name_ = name;
}

void Transaction::Affirm(const bool &state)
{
  if(!successWritten_) {
    successWritten_ = true;
    success_ = state;
  }
}

const char Transaction::Instruction() {
  return instruction_;
}

const int Transaction::SrcID() {
  return srcID_;
}

const int Transaction::DstID() {
  return dstID_;
}

const int Transaction::Amount() {
  return amount_;
}

vector<string> Transaction::Name() {
  return name_;
}

const int Transaction::SrcFund() {
  return srcFund_;
}

const bool Transaction::Success(){
  return success_;
}

void Transaction::Setup(const char &instr, const int &srcID, const int &srcFund,
                        const int &dstID, const int &dstFund, 
                        const int &amount) {
  instruction_ = instr;
  srcID_ = srcID;
  dstID_ = dstID;
  dstFund_ = dstFund;
  srcFund_ = srcFund;
  amount_ = amount;   
}

void Transaction::Setup(const int &ID, const vector<string> &name) {
  instruction_ = 'O';
  name_ = name;
  srcID_ = ID;
}

const int Transaction::DstFund() {
  return dstFund_;
}


//friend op
ostream &operator<<(ostream &out, const Transaction &rhs) {

  bool dontBreak = false;
  out << rhs.instruction_ << " ";
  switch(rhs.instruction_) {
    case 'T':
      dontBreak = true;
    case 'D':
      out << rhs.srcID_ << " " << rhs.srcFund_ << " ";
      if(!dontBreak) { break; }
    case 'W':
      out << rhs.dstID_ << " " << rhs.dstFund_ << " ";
      break;
    default:
      //going to pretend that this doenst happen lol
      break;
  }

  out << rhs.amount_;

  if(!rhs.success_) {
    out << " (Failed)";
  }
  
  return out;

}
