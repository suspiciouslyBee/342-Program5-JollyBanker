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
  char instr_ = 0;
  int otherData[5] = {-1};
  string hopper;
  string nameHopper[2];
  stringstream parser;
  Transaction transactionHopper;  //should be fresh and not need clearing first

  //load lines sucessively
  while(getline(file, hopper)){


    //loop within each line
    //Assumes the format is correct. grabs the first char
    
    parser << hopper;
    parser >> instr_;

    //Parses int because all args have second int (an id)
    parser >> otherData[0];


    //Special split here if the data is an O
    if(instr_ == 'O'){ 
      parser >> nameHopper[0];
      parser >> nameHopper[1];
      transactionHopper.Setup(nameHopper[0], nameHopper[1], otherData[0]);
    } else {
      //Keeps parsing until it fails or reaches the max amount of vals
      //Jank as hell. might have UB if parser still puts stuff in in a fail
      for(int i = 1; !parser.fail() && i < 5; i++) {
        parser >> otherData[i];
      }
      //build the transactionHopper with our data. passing array and length 
      transactionHopper.Setup(otherData, 5);
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
  return Insert(rhs, rhs.ID(), dummy);
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

  //one of them is now null
  if(rhs.Instruction() == 'T' && (src == nullptr || dst == nullptr)) {
    //write fail, ternary to keep code clean (breaks c++ guidelines)

    Client *errorTgt = nullptr;

    if(src == nullptr) {
      errorTgt = dst;
    } else {
      errorTgt = src;
    }

    rhs.SetFail();
    src->history_.push_back(rhs);

  }

  //make the transfer


  //write the results

}