////
//  File: Global Fund Types Header
//
//  Author: June
//
//  Description: This file is a collection of constants that are used by all
//  functions associated with Bank_Tree.
//
//  TODO: make compliant with google c++ guidelines. embed into banktree itself
////


#ifndef FUNDTYPE_H_
#define FUNDTYPE_H_

#include <vector>
#include <string>

enum FundType {
  kUndefined = -1,
  kMoneyMarket, //MM can pull from each other
  kPrimeMoneyMarket, 
  kLongTermBond, //Bonds can pull from each other
  kShortTermBond,
  kTop500Index,
  kCapitalValue,
  kGrowthEquity,
  kGrowthIndex,  //Insert additional funds after this entry as needed
  kNumberOfFunds, //Abuses enum behavior to get item # (8 in this case)
};

//TODO: make this constant
const std::vector<FundType> kOverdraftProtectionAccount = {
  kPrimeMoneyMarket,
  kMoneyMarket,
  kShortTermBond,
  kLongTermBond,
  kUndefined,
  kUndefined,
  kUndefined,
  kUndefined,
};


//corresponding global lookup table for fund names with index parity
//TODO: make this constant
const std::vector<std::string> kFundNames = {
  "Money Market",
  "Prime Money Market",
  "Long Term Bond",
  "Short Term Bond",
  "Top 500 Index",
  "Capital Value",
  "Growth Equity",
  "Growth Index",
};


#endif //FUNDTYPE_H_
