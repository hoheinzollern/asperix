/* *************************************************************************
 * Copyright (C) 2009 Claire Lefèvre, Pascal Nicolas
 * 
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 *
 * claire.lefevre@univ-angers.fr       pascal.nicolas@univ-angers.fr
 ****************************************************************************/ 
#ifndef _NEGATIVE_LITERAL_H_
#define _NEGATIVE_LITERAL_H_

#include "basic_literal.h"
#include "positive_literal.h"

class NegativeLiteral : public BasicLiteral
{
  public:
       NegativeLiteral(const NegativeLiteral&);	  
       NegativeLiteral(Predicate* pred, Argument* tv);
       inline bool isNegativeLiteral() {return true;};
       bool nextTrueMatch();// idem for the next matching tuple
       statusEnum nextSoftMatch(statusEnum);// idem for the next matching tuple
       virtual Literal* createInstance(); // create a new literal by applying current substitution
       PositiveLiteral* createPositiveClone(MapVariables& mapVar);
       inline void setMark(markEnum m) {_mark = m;};
       inline void setDelta(); // no sense for negative literal

  protected:
       virtual std::ostream& put(std::ostream&);
       bool firstTrueMatchBis();// try to match atom with some tuple of the extension 
       			 // of the predicate ; return true if no match is found
       statusEnum firstSoftMatchBis(statusEnum);
};

inline void NegativeLiteral::setDelta(){
// no sense for negative literal 
  throw RuntimeExcept("set delta for negative literal");
}

#endif // _NEGATIVE_LITERAL_H_


