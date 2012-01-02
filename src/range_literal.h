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
#ifndef _RANGE_LITERAL_H_
#define _RANGE_LITERAL_H_

#include "basic_literal.h"
#include "range_term.h"

/** RangeLiteral has form P(t1,t2,..) where ti are RangeTerms
 *  RangeLiteral can only appear as head of a rule
 * */
class RangeLiteral : public BasicLiteral 
{
  public:
       RangeLiteral(); 			  
       RangeLiteral(std::string* s, Argument* tv, Graph& g);
	RangeLiteral(Predicate* pred, Argument* tv);
	virtual ~RangeLiteral();
       inline statusEnum isInstance();// not defined for range literal TODO devrait être défini
       inline virtual Literal* createInstance();// create a new literal by applying current substitution, no use for a head literal
       RangeLiteral* createPositiveClone(MapVariables& mapVar);
       virtual void addInstances(Argument& tuple, statusEnum st);// add tuple (or all tuples represented by tuple) to extension of predicate _pred
       virtual void addNonInstances(Argument& tuple);// add tuple (or all tuples represented by tuple) to extension of predicate _pred
       virtual bool addInstances(Argument&, statusEnum st, atomsQueue&);
       inline bool blindAddNonInstances(Argument&, atomsQueue&);
       std::vector<Argument*>* expand(Argument& tv);
       inline bool nextTrueMatch();// idem for the next matching tuple
       inline statusEnum nextSoftMatch(statusEnum);// idem for the next matching tuple
       inline bool recursive(); // true if atom predicate is in the current SCC
       				// i.e. the predicate is not already solved
       inline void setMark(markEnum m);
       inline void setDelta(); // no sense for a head literal 
       inline void initDelta(); // no sense for a head literal 

  private:
       std::vector<Argument*>& expand(RangeTerm::Vector& tv);
  protected:
       inline bool firstTrueMatchBis();// try to match atom with some tuple of the extension 
       			 // of the predicate ; return true if a match is found
			 // no sense for a RangeLiteral which is head literal
	inline statusEnum firstSoftMatchBis(statusEnum);
};


inline statusEnum RangeLiteral::isInstance(){
// not defined for a range literal 
 throw RuntimeExcept("test instance for a head range literal");
}
inline Literal* RangeLiteral::createInstance(){
// create a new literal by applying current substitution, no use for a head literal
 throw RuntimeExcept("create instance for a head range literal");
}
/* the following members have no sense for head literals 
 */
inline bool RangeLiteral::firstTrueMatchBis(){
// try to match atom with some tuple of the extension 
// of the predicate ; return true if a match is found
// no sense for a RangeLiteral which is head literal
	throw RuntimeExcept("Request match for a head range literal");
}
inline statusEnum RangeLiteral::firstSoftMatchBis(statusEnum){
	throw RuntimeExcept("Request match for a head range literal");
}

inline bool RangeLiteral::nextTrueMatch(){// idem for the next matching tuple
	throw RuntimeExcept("Request match for a head range literal");
}      
inline statusEnum RangeLiteral::nextSoftMatch(statusEnum){// idem for the next matching tuple
	throw RuntimeExcept("Request match for a head range literal");
}
inline bool RangeLiteral::recursive()	{ 
 // true if atom predicate is in the current SCC
 // i.e. the predicate is not already solved
	throw RuntimeExcept("Test recursive for a head range literal");
}
inline void RangeLiteral::setMark(markEnum)	{
	throw RuntimeExcept("Set mark for a head range literal");
}
inline bool RangeLiteral::blindAddNonInstances(Argument&, atomsQueue&){
	throw RuntimeExcept("try to add non-instances of a head range literal");
}
inline void RangeLiteral::setDelta(){
// no sense for a head literal 
 throw RuntimeExcept("set delta for a head range literal");
}
inline void RangeLiteral::initDelta(){
// no sense for a head literal 
 throw RuntimeExcept("init delta for a head range literal");
}

#endif // _RANGE_LITERAL_H_


