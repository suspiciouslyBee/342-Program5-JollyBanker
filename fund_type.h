// Centralized header for funds. 
// As this is fixed, this should not be editble in run time as of this version

#ifndef FUNDTYPE_H_
#define FUNDTYPE_H_

#include <utility>


//imply the id by fixed pos
vector<pair<string, int>> kFundTypes = {
  {"Money Market", 0},
}

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



//corresponding global lookup table for fund names with index parity

vector<string> kFundNames = {
  "Money Market",
  "Prime Money Market",
  "Long Term Bond",
  "Short Term Bond",
  "Top 500 Index",
  "Capital Value",
  "Growth Equity",
  "Growth Index",
}


#endif //FUNDTYPE_H_