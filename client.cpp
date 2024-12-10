//Stub header for client 

#include "client.h"

#include <vector>
#include <iostream>
#include <ostream>

#include "transaction.h"
#include "fund_type.h"

std::vector<std::string> Client::SeperatedName() const{
  return name_;
}


Client::Client(const int &ID, std::vector<std::string> name) {
  ID_ = ID;
  name_ = name;
  right_ = nullptr;
  left_ = nullptr;
  history_.resize(kNumberOfFunds);
}


//Saves the transaction to the client history, as long as it is relevant
void Client::AppendTransaction(Transaction &rhs)
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

//Uses the "end caps" provided by fund_type to get the range
bool Client::InLocalFunds(const int &fundID) const{
  return (fundID > kUndefined) && (fundID < kNumberOfFunds);
}


//Simple Concactination
std::string Client::Name() const{
  std::string answer;
  for(int i = 0; i < name_.size(); i++) {
    if(i != 0) { answer += " "; }
    answer += name_[i];
  }
  return answer;
}

int Client::Withdrawl(const int &money, const int &fundID) {
  if(!InLocalFunds(fundID)) { return -2; }
  if(money < 0) { return -2; }
  //simple case, fully covered
  int difference = localFunds_[fundID] - money;

  if(difference >= 0) {
    localFunds_[fundID] -= money;
    return money;
  }

  //If the difference goes negative checks if the fund has overdraft protection
  //Logs if it does.

  if(kOverdraftProtectionAccount.at(fundID) != kUndefined) {
    if(localFunds_[kOverdraftProtectionAccount.at(fundID)] + difference >= 0) {

      //Normally, the higher context handles this. But this special case needs
      //to be logged *right now*.
      Transaction adHoc('T', ID_, kOverdraftProtectionAccount.at(fundID), ID_,
                        fundID, -difference);
      adHoc.Affirm(true);
      AppendTransaction(adHoc);

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

int Client::ID() const {
  return ID_;
}

//TODO: need to make this use const. dont need to edit client instnace
//just prints everything. friend funct
//docs: start with name
std::ostream& operator<<(std::ostream& out, Client &rhs) {
  

  //Loops through all funds
  
  out << "Account Overview for #" << rhs.ID() 
      << ". Owner: "  << rhs.Name() << std::endl;

  for(int i = 0; i < kNumberOfFunds; i++) {
    rhs.PrintFund(out, i, false);
  }

  out << std::endl;
  return out;
}


//TODO, limit to funds that exist

//stupid ass psuedo code because i cant think on the link with 3 hrs of sleep 
//grab name of fund according to fund int
std::ostream& Client::PrintFund(std::ostream& out, const int &fund, 
                            const bool &showHistory) const{
  

  if(!InLocalFunds(fund)) { 
    std::cerr << "Invalid Fund" << std::endl; 
    return out;
  }

  out << "\tFund: " << kFundNames.at(fund) << std::endl;
  out << "\t\tTotal: $" << localFunds_[fund] << std::endl;
  
  if(showHistory && history_.at(fund).size() > 0) {
    out << "\t\tHistory:" << std::endl;
    for(int i = 0; i < history_.at(fund).size(); i++) {
      out << "\t\t  " << history_.at(fund).at(i) << std::endl;
    }
  }
  return out;

}