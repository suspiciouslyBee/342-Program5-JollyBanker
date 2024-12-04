#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <queue>

#include "fund_type.h"
#include "transaction.h"
#include "client.h"
#include "bank_tree.h"

using namespace std;

//Open File
bool BankTree::BuildQueue(string &fileName) {

  //open file, if cant then bail
  ifstream file(fileName);


  //parse each line, create new object. push to queue
  char instr = 0;
  int otherData[5] = {-1};
  string hopper;
  string nameHopper[2];
  stringstream parser;
  Transaction transactionHopper;  //should be fresh and not need clearing first

  //load lines sucessively
  //usage: instr id (first last) |  ()
  while(getline(file, hopper)){


    //loop within each line
    //Assumes the format is correct. grabs the first char
    
    parser << hopper;
    parser >> instr;

    //Parses int because all args have second int (an id)
    parser >> otherData[0];
    vector<string> fullName;

    //Special split here if the data is an O
    //load the data otherwise.
    if(instr == 'O'){ 
      parser >> nameHopper[0];
      parser >> nameHopper[1];
      
      fullName.push_back(nameHopper[0]);
      fullName.push_back(nameHopper[1]);

    } else {
      //Keeps parsing until it fails or reaches the max amount of vals
      //Jank as hell. might have UB if parser still puts stuff in in a fail
      for(int i = 1; !parser.eof() && i < 5; i++) {
        parser >> otherData[i];
      }
      //build the transactionHopper with our data. passing array and length 
      //TODO: go back to the old manual setup, or code the parsing in this setup
    }

    
    //interpret parser with switch statement
    switch(instr) {
      case 'O':
        transactionHopper.Setup(otherData[0], fullName);
        break;
      case 'D':
        transactionHopper.Setup(instr, -1, UNDEFINED, otherData[0], 
                                otherData[1], otherData[2]);
        break;
      case 'W':
        transactionHopper.Setup(instr, otherData[0], otherData[1], -1, 
                                UNDEFINED, otherData[2]);
        break;
      case 'T':
        transactionHopper.Setup(instr, otherData[0], otherData[1], otherData[2],
                                otherData[3], otherData[4]);
        break;
      case 'A':
        transactionHopper.Setup(instr, otherData[0], -1, -1, -1, -1);
        break;
      case 'F':
        transactionHopper.Setup(instr, otherData[0], otherData[1], -1, -1, -1);
        break;      
      default:
        return false;
    }

    //save our work, queue should make a deep copy here
    transactionQueue_.push(transactionHopper);

    //cleanup for next cycle
    transactionHopper.Clear();
    parser.clear();
    parser.str("");

  }

  //pop each obj, execute the instruction

  //TODO: returns
}


// Helper funct. executes the queue
bool BankTree::ExecuteQueue() {
  if(transactionQueue_.size() <= 0){ return false; }
  
  Transaction hopper;

  //peek, execute, pop
  while(transactionQueue_.size() > 0) {
    ExecuteTransaction(transactionQueue_.front());
    transactionQueue_.pop();
  }
  return true;
}


bool BankTree::ExecuteTransaction(Transaction &rhs) {
  switch(rhs.Instruction()){
    case 'O':
      return CreateClient(rhs);
    case 'D':
      return MoveFunds(rhs);
    case 'W':
      return MoveFunds(rhs);
    case 'T':
      return MoveFunds(rhs);
    case 'A':
      return AuditClient(rhs.srcID());
    case 'F':
      return AuditClient(rhs.srcID(), rhs.Fund());
    default:
      return false;
  }
}

//Wrapper for Insert, id must be pos.
bool BankTree::CreateClient(Transaction &rhs) {
  Client *dummy = nullptr;
  if(Insert(rhs.Name(), rhs.ID(), dummy)) { return false; }
}


bool BankTree::MoveFunds(Transaction &rhs) {

  //ptr to clients, if one is not found, create a dummy
  //if both are not found, clean up, leaves

  Client *src = nullptr;
  Client *dst = nullptr;

  //one or both are nullptr, neither can be nullptr if 
  if(!Find(rhs.srcID(), src) && !Find(rhs.dstID(), dst)) {
    return false;
  }

  //node validation checks
  switch(rhs.Instruction()) {
    case 'T':

      //one of them is now null, if its a transfer thats breaking! bail!
      if(rhs.Instruction() == 'T' && (src == nullptr || dst == nullptr)) {
       //write fail, ternary to keep code clean (breaks c++ guidelines)

        Client *errorTgt = nullptr;

        if(src == nullptr) {
          errorTgt = dst;
        } else {
          errorTgt = src;
        }

        rhs.Affirm(false);
        errorTgt->AppendInstruction(rhs);
        return false;
      }

      //nodes exist, attempt transfer
      //src needs to be valid first
      if(!src->Withdrawal(rhs.Amount(), rhs.SrcFund())) {
        return false;
      }

      dst->Deposit(rhs.Amount(), rhs.DstFund());
      break;
    case 'W':

      //Source node does not exist
      if(src == nullptr) { 
        rhs.Affirm(false);
        dst->AppendInstruction(rhs);
        return false;
      }

      //Src node has insufficient funds
      if(!src->Withdrawal(rhs.Amount(), rhs.SrcFund())) {
        rhs.Affirm(false);
        dst->AppendInstruction(rhs);
        src->AppendInstruction(rhs);
        return false;
      }

      //Deposit doesn't work for some reason
      if(!dst->Deposit(rhs.Amount(), rhs.DstFund()) {
        rhs.Affirm(false);
        dst->AppendInstruction(rhs);
        src->AppendInstruction(rhs);
        return false;
      }

      rhs.Affirm(true);
      dst->AppendInstruction(rhs);
      src->AppendInstruction(rhs);
      return true;

      break;
    case 'D':
      if(dst == nullptr) { return false; }

      return dst->Deposit(rhs.Amount(), rhs.DstFund());

      break;

  }




  //progress through transfering, keep checking if valid.
  //tenatively store results

  //TODO check if null or magic number first lmao
  if(rhs.Instruction() == 'W' || rhs.Instruction() == 'T') {
    if(src->Withdrawal(rhs.Amount(), rhs.Fund()) != rhs.Amount()){

    }
  }

  //write the results

}