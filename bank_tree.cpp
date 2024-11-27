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
  int otherData[4] = {0};



  while(getline(fileName, ))

  //pop each obj, execute the instruction

}
