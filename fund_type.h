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

/*#include <utility>


//imply the id by fixed pos
vector<pair<string, int>> kFundTypes = {
  {"Money Market", 0},
};
*/
enum FundType {
  UNDEFINED = -1,
  MONEYMARKET, //MM can pull from each other
  PRIMEMONEYMARKET, 
  LONGTERMBOND, //Bonds can pull from each other
  SHORTTERMBOND,
  TOP500INDEX,
  CAPITALVALUE,
  GROWTHEQUITY,
  GROWTHINDEX,  //Insert additional funds after this entry as needed
  NUMBEROFFUNDS, //Abuses enum behavior to get item # (8 in this case)
};


//TODO: make this constant
vector<FundType> kOverdraftProtectionAccount = {
  PRIMEMONEYMARKET,
  MONEYMARKET,
  SHORTTERMBOND,
  LONGTERMBOND,
  UNDEFINED,
  UNDEFINED,
  UNDEFINED,
  UNDEFINED,
};


//corresponding global lookup table for fund names with index parity
//TODO: make this constant
vector<string> kFundNames = {
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