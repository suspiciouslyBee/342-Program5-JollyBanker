#include "client.h"
#include "transaction.h"

vector<string> Client::SeperatedName() {
  return name_;
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
  }

  if (rhs.DstID() == ID_) {
    history_.at(rhs.DstFund()).push_back(rhs);
  }

  return;
}

bool Client::InLocalFunds(const int &fundID) {
  return (fundID < 0) || (fundID > NUMBEROFFUNDS);
}

string Client::Name(){
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
  //need to log the coverage

  //srcfund 
  if(kOverdraftProtectionAccount.at(fundID) != UNDEFINED) {
    if(localFunds_[kOverdraftProtectionAccount.at(fundID)] + difference >= 0) {

      //Normally, the higher context handles this. But this special case needs
      //to be logged *right now*.
      Transaction adHoc('T', ID_, kOverdraftProtectionAccount.at(fundID), ID_,
                        fundID, -difference);
      AppendInstruction(adHoc);

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

//TODO: need to make this use const. dont need to edit client instnace
//just prints everything. friend funct
//docs: start with name
ostream& operator<<(ostream& out, Client &rhs) {
  out << "Balances of Account #" << rhs.ID_ << ": " << rhs.Name() << endl;

  //Loops through all funds
  for(int i = 0; i < NUMBEROFFUNDS; i++) {
    rhs.PrintFund(out, i, false);
  }

  out << endl;
  return out;
}


//TODO, limit to funds that exist

//stupid ass psuedo code because i cant think on the link with 3 hrs of sleep 
//grab name of fund according to fund int
ostream& Client::PrintFund(ostream& out, const int &fund, 
                            const bool &showHistory) {
  out << "\tFund: " << kFundNames.at(fund) << endl;
  out << "\t\tTotal: " << localFunds_[fund] << "$" << endl;
  out << "\t\tHistory:" << endl;

  if(showHistory) {
    for(int i = 0; i < history_.at(fund).size(); i++) {
      out << "\t\t\t" << history_.at(fund).at(i) << endl;
    }
    out << endl;
  }

  out << endl;
  return out;

}