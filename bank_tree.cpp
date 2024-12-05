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

  return true;
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
      return AuditClient(rhs.SrcID());
    case 'F':
      return AuditClient(rhs.SrcID(), rhs.FundID());
    default:
      return false;
  }
}

//Wrapper for Insert, id must be pos.
bool BankTree::CreateClient(Transaction &rhs) {
  Client *dummy = nullptr;
  if(Insert(rhs.Name(), rhs.SrcID(), dummy)) { return false; }
}


bool BankTree::MoveFunds(Transaction &rhs) {

  //ptr to clients, if one is not found, create a dummy
  //if both are not found, clean up, leaves

  Client *src = nullptr;
  Client *dst = nullptr;


  src = Find(rhs.SrcID(), src);
  dst = Find(rhs.DstID(), dst);

  //Sanity Check: Do either nodes exist?
  //cannot log to a node if not found
  if(!src && !dst) {

    cerr << "ERROR: Neither Account found. Both IDs cannot be invalid." 
          << "Money movement refused: \n";

    cerr << "srcID: ";
    if(rhs.SrcID() == -1) {
      cerr << "Placeholder Deposit ID -1\n";
    } else {
      cerr << rhs.SrcID() << endl;
    }

    cerr << "srcID: ";
    if(rhs.DstID() == -1) {
      cerr << "Placeholder Withdrawl ID -1\n";
    } else {
      cerr << rhs.DstID() << endl;
    }
    
    cerr << endl;
    return false;
  }


  if(rhs.Amount() < 0) {
    cerr << "ERROR: Transaction amount (" << rhs.Amount() 
          << ") cannot be negative Money movement refused: \n";

    rhs.Affirm(false);

    if(src) {
      src->AppendInstruction(rhs);
    }

    if(dst) {
      dst->AppendInstruction(rhs);
    }

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

        cerr << "ERROR: Both Accounts not found. T needs two valid IDs." 
              << "Transferal refused: \n";

        cerr << "srcID: ";
        if(rhs.SrcID() == -1) {
         cerr << "Placeholder Deposit ID -1\n";
        } else {
        cerr << rhs.SrcID() << endl;
        }

        cerr << "srcID: ";
        if(rhs.DstID() == -1) {
          cerr << "Placeholder Withdrawl ID -1\n";
        } else {
          cerr << rhs.DstID() << endl;
        }
    
        cerr << endl;

        return false;
      }

      //Nodes exist. 
      
      //Sanity Check: do the funds exist
      if(!src->InLocalFunds(rhs.SrcFund()) || !dst->InLocalFunds(rhs.DstFund()))
      {
        cerr << "ERROR: Movement to invalid fund. Transferal refused: \n";

        cerr << "Source Fund: ";
        if(src->InLocalFunds(rhs.SrcFund())) {
          cerr << kFundNames.at(rhs.SrcFund()) << endl;
        } else {
          cerr << rhs.SrcFund() << endl;
        }

        cerr << "Destination Fund: ";
        if(dst->InLocalFunds(rhs.DstFund())) {
          cerr << kFundNames.at(rhs.DstFund());
        } else {
          cerr << rhs.DstFund() << endl;
        }
    
        cerr << endl;

        rhs.Affirm(false);
        dst->AppendInstruction(rhs);
        src->AppendInstruction(rhs);

        return false;
      }


      if(src->Withdrawal(rhs.Amount(), rhs.SrcFund()) < 0) {
        cerr << "ERROR: Insufficient funds from " 
          << kFundNames.at(rhs.SrcFund()) << " at " << src->Name()
          << ", " << rhs.SrcID() << endl;
        rhs.Affirm(false);
        dst->AppendInstruction(rhs);
        src->AppendInstruction(rhs);
        return false;
      }

      //By now, dst is VALID, amount is VALID, DstFund is VALID. Assumption time
      dst->Deposit(rhs.Amount(), rhs.DstFund());

      rhs.Affirm(true);
      dst->AppendInstruction(rhs);
      src->AppendInstruction(rhs);
      return true;
      break;
    case 'W':

      //Source node does not exist
      if(src == nullptr) { 
        rhs.Affirm(false);

        cerr << "ERROR: Account not found. Withdrawal refused: \n";

        cerr << "srcID: ";
        if(rhs.SrcID() == -1) {
         cerr << "Placeholder Deposit ID -1\n";
        } else {
        cerr << rhs.SrcID() << endl;
        }
        return false;
      }
      

      //Sanity Check: does the fund exist
      if(!src->InLocalFunds(rhs.SrcFund()))
      {
        cerr << "ERROR: Movement to invalid fund. Withdrawal refused: \n";

        cerr << "Source Fund: ";
        if(src->InLocalFunds(rhs.SrcFund())) {
          cerr << kFundNames.at(rhs.SrcFund()) << endl;
        } else {
          cerr << rhs.SrcFund() << endl;
        }
    
        cerr << endl;
        rhs.Affirm(true);
        src->AppendInstruction(rhs);

        return false;
      }


      if(src->Withdrawal(rhs.Amount(), rhs.SrcFund()) < 0) {
        cerr << "ERROR: Insufficient funds from " 
          << kFundNames.at(rhs.SrcFund()) << " at " << src->Name()
          << ", " << rhs.SrcID() << endl;
        rhs.Affirm(false);
        src->AppendInstruction(rhs);
        return false;
      }


      rhs.Affirm(true);
      src->AppendInstruction(rhs);
      return true;
      break;
    case 'D':


      //Source node does not exist
      if(dst == nullptr) { 
        rhs.Affirm(false);
    
        cerr << "ERROR: Account not found. Deposit refused: \n";

        cerr << "dstID: ";
        if(rhs.DstID() == -1) {
         cerr << "Placeholder Deposit ID -1\n";
        } else {
        cerr << rhs.DstID() << endl;
        }
        return false;
      }

      if(dst->InLocalFunds(rhs.DstFund())) {
        cerr << "ERROR: Deposit to invalid fund. Deposit refused: \n";

        cerr << "Destination Fund: ";
        if(dst->InLocalFunds(rhs.DstFund())) {
          cerr << kFundNames.at(rhs.DstFund());
        } else {
          cerr << rhs.DstFund() << endl;
        }
    
        cerr << endl;

        rhs.Affirm(false);
        dst->AppendInstruction(rhs);

        return false;
      }


      dst->Deposit(rhs.Amount(), rhs.DstID());
      rhs.Affirm(true);
      dst->AppendInstruction(rhs);
      return true;
      break;
  }

  cerr << "ERROR: UNKNOWN ERROR" << endl;
  return false;
}


//todo, print name for these

bool BankTree::AuditClient(const int &clientID, ostream &out) {
  //find the client

  Client *result = nullptr;

  result = Find(clientID, result);

  // no match? bail! TODO: make print for missing thing
  if(result == nullptr) { return false; }

  for(int i = 0; i < NUMBEROFFUNDS; i++) {
    result->PrintFund(out, i, true);
  }

  return true;
}

bool BankTree::AuditClient(const int &clientID, const int &fundID, 
                            ostream &out) {
  //find the client

  Client *result = nullptr;

  result = Find(clientID, result);

  // no match? bail! TODO: make print for missing thing
  if(result == nullptr) { return false; }

  if(result->InLocalFunds(fundID)) {
    result->PrintFund(out, fundID, true);
    return true;
  }

  return false;

}

bool BankTree::Insert(vector<string> name, const int &ID, Client *node) {
	////
	// check for match first, should return nullptr. if we dont have a 
	// nullptr that means a match was found
	////
	bool latch = true;

	if (root_ == nullptr) {
		root_ = new Client(ID, name);
    count++;
		return true;
	}
	if (Find(ID, node) != nullptr) { return false; } //match
	while (latch) {
		if (ID > node->ID()) {
			if (node->right_) {
				node = node->right_;
			}
			else {
				node->right_ = new Client(ID, name);
        count++;
				latch = false;
			}
		}

		if (ID < node->ID()) {
			if (node->left_) {
				node = node->left_;
			}
			else {
				node->left_ = new Client(ID, name);
        count++;
				latch = false;
			}
		}
	}
	if (latch) {
		return false;
	}
	return true;
}

Client* BankTree::Find(const int &ID, Client* node) const {

		if (root_ == nullptr || node == nullptr) { return nullptr; }

		if (ID == node->ID()) { return node; }

		if (ID > node->ID()) {
			if (node->right_) {
				return Find(ID, node->right_);
			}
		}

		if (ID < node->ID()) {
			if (node->left_) {
				return Find(ID, node->left_);
			}
		}

		////
		// When here: if node has a value, and the value is greater or less 
		// than all other values, we can then take node and use that for insert
		////

		return nullptr;
	}

void BankTree::PrintTree(Client* t, std::ostream& out) const {
	if (t->left_) { //check here first
		PrintTree(t->left_, out);
	}

	//we are now at the middle of the chain, the node cant continue to wait
	out << *t << endl;

	if (t->right_) {
		PrintTree(t->right_, out);
	}
}

