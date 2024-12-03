#ifndef FUNDTYPE_H_
#define FUNDTYPE_H_

enum FundType {
  UNDEFINED = -1,
  MONEYMARKET, //MM can pull from each other
  PRIMEMONEYMARKET, 
  LONGTERMBOND, //Bonds can pull from each other
  SHORTTERMBOND,
  TOP500INDEX,
  CAPITALVALUE,
  GROWTHEQUITY,
  GROWTHINDEX,
};



#endif FUNDTYPE_H_