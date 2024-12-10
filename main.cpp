//Jolly banker wrapper

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
  if(argc != 2) { 
    std::cout << "Usage: jolly_banker databasePath" << std::endl;
    return 1; 
  }

  std::string argument = argv[1];
  BankTree dummy;

  if(!dummy.BuildQueue(argument)) {
    std::cout << "Usage: jolly_banker databasePath" << std::endl;
    return 1; 
  }

  dummy.ExecuteQueue();

  std::cout << dummy;

  return 0;
}