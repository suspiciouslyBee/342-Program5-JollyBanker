#include "client.h"
#include "transaction.h"

vector<string> Client::SeperatedName() {
  return name_;
}

// this is going to be stupid.
// go through each one, put into
ostream& Client::ClientAudit() {

}

Client::Client(const int &ID, vector<string> name) {
  ID_ = ID;
  name_ = name;
  right_ = nullptr;
  left_ = nullptr;
  int localFunds_ = {0};
}

void Client::AppendInstruction(Transaction &rhs)
{
  //Determine how the client is related to this transaction

  //Inserts accordingly
  if(rhs.SrcID() == ID_) {
    history_.at(rhs.SrcFund()).push_back(rhs);
  } else if (rhs.DstID() == ID_) {
    history_.at(rhs.DstFund()).push_back(rhs);
  }

  return;
}

bool Client::InLocalFunds(const int &fundID) {
  return (fundID < 0) || (fundID > NUMBEROFFUNDS);
}

string Client::Name() {
  string answer;
  for(int i = 0; i < name_.size(); i++) {
    answer += " " + name_[i];
  }
  return answer;
}

int Client::Withdrawal(const int &money, const int &fundID) {
  if(!InLocalFunds(fundID)) { return -2; }
  if(money < 0) { return -2; }
  //simple case, fully covered
  int difference = localFunds_[fundID] - money;

  if(difference >= 0) {
    localFunds_[fundID] -= money;
    return money;
  }

  //diff is negative check if its got overdraft protection
  if(kOverdraftProtectionAccount.at(fundID) != UNDEFINED) {
    if(localFunds_[kOverdraftProtectionAccount.at(fundID)] + difference >= 0) {
      localFunds_[fundID] = 0;
      localFunds_[kOverdraftProtectionAccount.at(fundID)] += difference;
      return money;
    }
  }

  return -1;

}


int Client::Deposit(const int &money, const int &fundID) {
  if(!InLocalFunds(fundID)) { return -2; }
  if(money < 0) { return -2; }

  localFunds_[fundID] += money;
  return money;
}

int Client::ID() {
  return ID_;
}
