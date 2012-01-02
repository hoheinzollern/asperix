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
#ifndef _BASIC_LITERAL_H_
#define _BASIC_LITERAL_H_

#include "literal.h"
/* BasicLiteral is a predicate and an argument list or the negation of this
 */
class BasicLiteral : public Literal
{
  public:
       BasicLiteral(); 	
       BasicLiteral(const BasicLiteral&);
       BasicLiteral(std::string* s, Argument* tv, Graph& g);
	BasicLiteral(Predicate* pred, Argument* tv);
       inline Predicate* getPred();
       inline int getSccIndex();
       bool isTheSameInstance(BasicLiteral* l);// return true if instanciated literals *this and *l are the same
       bool isTheSameLiteral(BasicLiteral* l);// return true if non-instanciated literals *this and *l are the same
       inline bool hasPredIn(Node::Set& ns);// return true if the predicate of this literal appears as label of a node from ns
       virtual bool match(const Argument* tv);// tv are ground terms
       bool nextTrueMatch();// idem for the next matching tuple
       statusEnum nextSoftMatch(statusEnum);// idem for the next matching tuple
       statusEnum isInstance();//return true if atom is in the extension of the predicate (only defined for ground basic literal)
       Literal* createInstance();// create a new literal by applying current substitution
	BasicLiteral* createPositiveClone(MapVariables&);
       	inline virtual void addInstances(Argument& tuple, statusEnum st) ;// add tuple (or all tuples represented by tuple) to extension of predicate _pred with status st
	inline virtual void addNonInstances(Argument& tuple) ;// add tuple (or all tuples represented by tuple) to non-extension of predicate _pred
	inline bool addInstances(Argument& tuple, statusEnum st, atomsQueue& aq) ;// add tuple (or all tuples represented by tuple) to extension of predicate _pred (and index of these tuples in aq)
	virtual bool addNonInstances(Argument& tuple, atomsQueue& naq);// add tuple (or all tuples represented by tuple) to NONextension of predicate _pred (and in naq queue)
       inline bool recursive(Node::Set&); // true if atom predicate is in the current SCC
       inline bool isSolved() {return _pred->isSolved();}; // true if atom predicate is already solved
       inline void setMark(markEnum m);
       inline void setDelta() {};
       inline void initDelta() {};
       inline void recordIndex();
       inline void restoreIndex();
       inline statusEnum getStatus()	{return _status;};
       inline void recordStatus();
       inline void restoreStatus();

  protected:
       Predicate* _pred;
       statusEnum _status; // match status of the current instance of the literal
       		// for a body l1,l2,..ln match status of li is MBT iff at least one literal lj (j<=i) has MBT status, and match status of li is TRUE iff all literals lj (j<=i) have TRUE status
       int _current_index;// current index in predicate extension
       int _first_index;
       int _last_index;
       statusStack _status_stack; // back-track stack for _status
       intStack _index_stack;// back-track stack for _current_index
       
       virtual std::ostream& put(std::ostream&);
       bool firstTrueMatchBis();// try to match atom with some true tuple of the extension 
       			 // of the predicate ; return true if a match is found
       statusEnum firstSoftMatchBis(statusEnum);// idem for true or mbt tuple 
};

inline Predicate* BasicLiteral::getPred(){
	return _pred;
}
int BasicLiteral::getSccIndex(){
	return getPred()->getNode()->getSccIndex();
}
inline bool BasicLiteral::hasPredIn(Node::Set& ns){
// return true if the predicate of this literal appears as label of a node from ns
	return (ns.find(getPred()->getNode()) != ns.end());
}

inline void BasicLiteral::addInstances(Argument& tuple, statusEnum stat){
// add tuple (or all tuples represented by tuple) to extension of predicate _pred with status stat
	switch (stat){
	case TRUE_ : 	
			getPred()->addTrueInstance(tuple);
			break;
	case MBT_ : 	getPred()->addMbtInstance(tuple);
			break;
	default :	throw RuntimeExcept("try to add instance with illegal status");
	}
}
inline void BasicLiteral::addNonInstances(Argument& tuple){
// add tuple (or all tuples represented by tuple) to non-extension of predicate _pred
	getPred()->addNonInstance(tuple);
}

inline bool BasicLiteral::addInstances(Argument& tuple, statusEnum stat, atomsQueue& aq){
// add tuple (or all tuples represented by tuple) to extension of predicate _pred with status stat
// and add index of these tuples in queue aq
// return true if some tuple has been added (or some status modified)
	switch (stat){
	case TRUE_ : 	return getPred()->addTrueInstance(tuple, aq);
	case MBT_ : 	return getPred()->addMbtInstance(tuple, aq);
	default :	throw RuntimeExcept("try to add instance with illegal status");
	}
}

inline bool BasicLiteral::addNonInstances(Argument& tuple, atomsQueue& naq){
// add tuple (or all tuples represented by tuple) to non-extension of predicate _pred
// and add  these tuples in naq queue
// return true if some tuple has been added
	return getPred()->addNonInstance(tuple, naq);
}

inline bool BasicLiteral::recursive(Node::Set& ns){
	return hasPredIn(ns);
}

inline void BasicLiteral::setMark(markEnum m){
	switch (_mark = m){
		case NON_MARKED : _first_index = _pred->getBeginIndex();
				  _last_index = _pred->getDeltaEndIndex();
				  break;
		case MARKED : _first_index = _pred->getDeltaBeginIndex();
			      _last_index = _pred->getDeltaEndIndex();
			      break;
		case UNMARKED : _first_index = _pred->getBeginIndex();
			      	_last_index = _pred->getDeltaBeginIndex() - 1;
			      	break;
	}
}
void BasicLiteral::recordIndex(){
	_index_stack.push(_current_index);
}
void BasicLiteral::restoreIndex(){
	_current_index = _index_stack.top();
	_index_stack.pop();
}
void BasicLiteral::recordStatus(){
	_status_stack.push(_status);
}
void BasicLiteral::restoreStatus(){
	_status = _status_stack.top();
	_status_stack.pop();
}

#endif // _BASIC_LITERAL_H_


