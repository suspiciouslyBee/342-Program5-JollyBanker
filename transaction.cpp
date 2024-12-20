//Stub header for transaction implementation

#include "transaction.h"

#include <vector>
#include <ostream>
#include <string>

#include "fund_type.h"

Transaction::Transaction() {
  instruction_ = '\0';
  srcID_ = -1;
  dstID_ = -1;
  dstFund_ = kUndefined;
  srcFund_ = kUndefined;
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
  name_ = rhs.name_;
  srcID_ = rhs.srcID_;
  dstID_ = rhs.dstID_;
  dstFund_ = rhs.dstFund_;
  srcFund_ = rhs.srcFund_;
  amount_ = rhs.amount_;
  success_ = rhs.success_;
  successWritten_ = rhs.successWritten_;
}

void Transaction::SetName(const std::vector<std::string> &name) {
  name_ = name;
}

void Transaction::Clear()
{
  instruction_ = '\0';
  srcID_ = -1;
  dstID_ = -1;
  dstFund_ = kUndefined;
  srcFund_ = kUndefined;
  amount_ = -1;
  success_ = false;
  successWritten_ = false;
}

void Transaction::Affirm(const bool &state)
{
  if(!successWritten_) {
    successWritten_ = true;
    success_ = state;
  }
}

char Transaction::Instruction() const {
  return instruction_;
}

int Transaction::SrcID() const {
  return srcID_;
}

int Transaction::DstID() const {
  return dstID_;
}

int Transaction::Amount() const {
  return amount_;
}

std::vector<std::string> Transaction::Name() {
  return name_;
}

int Transaction::SrcFund() const {
  return srcFund_;
}

bool Transaction::Success() const {
  return success_;
}

bool Transaction::isAffirmed() const {
  return successWritten_;
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

void Transaction::Setup(const int &ID, const std::vector<std::string> &name) {
  instruction_ = 'O';
  name_ = name;
  srcID_ = ID;
}

int Transaction::DstFund() const {
  return dstFund_;
}


//friend op
std::ostream &operator<<(std::ostream &out, const Transaction &rhs) {

  bool dontBreak = false;
  out << rhs.instruction_ << " ";
  switch(rhs.instruction_) {
    case 'T':
      dontBreak = true;
    case 'W':
      out << rhs.srcID_ << " " << rhs.srcFund_ << " ";
      if(!dontBreak) { break; }
    case 'D':
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
