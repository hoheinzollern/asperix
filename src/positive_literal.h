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
 /* this file includes PositiveLiteral and PositiveLiteralOfNDR classes     */
 /***************************************************************************/
#ifndef _POSITIVE_LITERAL_H_
#define _POSITIVE_LITERAL_H_

#include "basic_literal.h"
/******** PositiveLiteral is a predicate and an argument list
 ********/
class PositiveLiteral : public BasicLiteral
{
  public:
       PositiveLiteral(); 			  
       PositiveLiteral(const PositiveLiteral&);
       PositiveLiteral(std::string* s, Argument* tv, Graph& g);
       PositiveLiteral(Predicate* pred, Argument* tv);
       inline bool isPositiveLiteral() {return true;};
       virtual Literal* createInstance(); // create a new literal by applying current substitution
        PositiveLiteral* createPositiveClone(MapVariables&);	
       inline virtual bool hasPred(Predicate* p) {return (_pred==p);};// return true if the predicate of this literal is p
       inline void setDelta(); // no sense for positive literal of definite rule
       inline void initDelta(); //  no sense for positive literal of definite rule 

  protected:
};

inline void PositiveLiteral::setDelta(){
// no sense for positive literal of a definite rule
 throw RuntimeExcept("set delta for positive literal of a definite rule");
}
inline void PositiveLiteral::initDelta(){
// no sense for positive literal of a definite rule
 throw RuntimeExcept("init delta for positive literal of a definite rule");
}

/****************************************************************************
******** PositiveLiteralOfNDR is a positive literal that appears in a non-definite rule (NDR) 
								  or a constraint rule
 ********/

class PositiveLiteralOfNDR : public PositiveLiteral
{
  public:
        PositiveLiteralOfNDR(const PositiveLiteralOfNDR&);
	PositiveLiteralOfNDR(Predicate* pred, Argument* tv);
	virtual Literal* createInstance(); // create a new literal by applying current substitution
	inline void setMark(markEnum m);
	inline void setDelta();
	inline void initDelta();
	inline void restoreDelta();
	
  protected:
       int _delta_begin;// index in predicate extension
       int _delta_end;      
       intStack _delta_stack; // back-track stack for _delta_begin and _delta_end

       inline void recordDelta();
};

inline void PositiveLiteralOfNDR::initDelta(){
	_delta_begin = 0;
	_delta_end = _pred->getEndIndex();
}
inline void PositiveLiteralOfNDR::setDelta(){
	recordDelta(); // record delta values (in _delta_stack) before change
	_delta_begin = _delta_end + 1;
	_delta_end = _pred->getEndIndex();
}

inline void PositiveLiteralOfNDR::setMark(markEnum m){
	switch (_mark = m){
		case NON_MARKED : _first_index = _pred->getBeginIndex();
				  _last_index = _delta_end;
				  break;
		case MARKED : _first_index = _delta_begin;
			      _last_index = _delta_end;
			      break;
		case UNMARKED : _first_index = _pred->getBeginIndex();
			      	_last_index = _delta_begin - 1;
			      	break;
	}
}

void PositiveLiteralOfNDR::recordDelta(){ // call by setDelta
	_delta_stack.push(_delta_begin);
	_delta_stack.push(_delta_end);
}
void PositiveLiteralOfNDR::restoreDelta(){
	_delta_end = _delta_stack.top();
	_delta_stack.pop();
	_delta_begin = _delta_stack.top();
	_delta_stack.pop();
}

#endif // _POSITIVE_LITERAL_H_


