//driver code TODO: need to make sure everything has a guard statemnet/


#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <queue>

#include "fund_type.h"
#include "transaction.h"
#include "client.h"
#include "bank_tree.h"

int main(int argc, char *argv[]) {

  BankTree dummy;

  if(argc != 2) { return 1; }

  std::string argument = argv[1];

  dummy.BuildQueue(argument);
  dummy.ExecuteQueue();

  std::cout << dummy;

  return 0;
}