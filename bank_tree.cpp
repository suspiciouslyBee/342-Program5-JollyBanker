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
bool BankTree::BuildTree(string &fileName) {

  //open file, if cant then bail
  ifstream file(fileName);


  //parse each line, create new object. push to queue
  char instr_ = 0;
  int otherData[5] = {0};
  string hopper;
  string nameHopper[2];
  stringstream parser;
  queue<Transaction> transactionQueue;  
  Transaction transactionHopper;

  //load lines sucessively
  while(getline(file, hopper)){
    //loop within each line
    //Assumes the format is correct. grabs the first char
    parser << hopper;
    parser >> instr_;


    

    //Parses int because all args have second int (an id)
    parser >> otherData[0];


    if(instr_ == 'O'){ 
      parser >> nameHopper[0];
      parser >> nameHopper[1];
      transactionHopper.SetName(nameHopper[0], nameHopper[1]);
    } else {
      //Keeps parsing until it fails or reaches the max amount of vals
      //Jank as hell
      for(int i = 1; !parser.fail() && i < 5; i++) {
        parser >> otherData[i];
      }
    }
    
    //build insert transaction into queue

    switch(instr_){
      case 'O': //one int, two strs,
      //node is special and instruction will have to be reconstructed by context
      //during printing
      //this command isnt "saved"
      

      case 'W': //three int

      case 'T': //five int

      case 'F': //two int
      //this command isnt "saved"

      break;

      case 'D': //three int

      case 'A': //one int
      //this command isnt "saved"

      default: //uhhhhh

    }



  }

  //pop each obj, execute the instruction

}
