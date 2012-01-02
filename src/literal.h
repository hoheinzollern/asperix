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
#ifndef _LITERAL_H_
#define _LITERAL_H_

#include "definition.h"
#include "variable.h"
#include "predicate.h"
#include "graph.h"
#include <string>
#include <vector>
#include <iostream>

class PositiveLiteral;
class BasicLiteral;

class Literal // abstract class - no instance
{
  public:
       typedef std::vector<Literal*> Vector;
	  
       Literal();
       Literal(const Literal&);
       Literal(Argument*);
       virtual ~Literal();
       inline Argument* getArgs();
       inline variableSet* getVariables();
       inline  void addVariables(variableSet& vs);//adds its own variables to vs
       inline void addFreeVar(Variable* v);
       inline bool isFreeVar(Variable* v);
       inline void addPreviousVar(Variable* v);
       inline void clearVars();
       inline void free(); // free variables of _free_vars
       virtual Predicate* getPred() = 0;
       virtual int getSccIndex()	{return -1;}; //default method
       virtual statusEnum getStatus() {return TRUE_;}; // default method
       virtual bool isTheSameInstance(BasicLiteral*) {return false;};// return true if instanciated literals *this and *l are the same
       									// default : return false
       virtual bool isTheSameLiteral(BasicLiteral*) {return false;};// return true if non-instanciated literals *this and *l are the same
          								// default : return false
       virtual bool hasPredIn(Node::Set& ns) = 0;// return true if the predicate of this literal appears as label of a node from ns
       inline virtual bool hasPred(Predicate*) {return false;};// return true if the predicate of this literal is p
       inline virtual bool isPositiveLiteral() {return false;};
       inline virtual bool isNegativeLiteral() {return false;};
       inline bool firstTrueMatch();// try to match atom with some true tuple of the extension 
       			 // of the predicate ; return true if a match is found
       virtual bool nextTrueMatch() = 0;// idem for the next matching tuple
       inline statusEnum firstSoftMatch(statusEnum);// try to match atom with some true or mbt tuple of the extension 
       			 // of the predicate ; return true if a match is found
       virtual statusEnum nextSoftMatch(statusEnum) = 0;// idem for the next matching tuple
       virtual statusEnum isInstance() = 0;// return true if atom is in the extension of the predicate (only defined for ground basic literal)
       virtual Literal* createInstance()=0; // create a new literal by applying current substitution
	virtual Literal* createPositiveClone(MapVariables&)=0; // create a new literal by cloning
       virtual void addInstances(Argument& tuple, statusEnum) = 0;// add tuple (or all tuples represented by tuple) to extension of predicate _pred
       virtual void addNonInstances(Argument& tuple) = 0;// add tuple (or all tuples represented by tuple) to non-extension of predicate _pred
	virtual bool addInstances(Argument& tuple,statusEnum st, atomsQueue& aq) = 0;// add tuple (or all tuples represented by tuple) to extension of predicate _pred (and index of these tuples in aq) . Return true if at least one tuple has been added
	virtual bool addNonInstances(Argument& tuple, atomsQueue& naq) = 0;// add tuple (or all tuples represented by tuple) to NONextension of predicate _pred (and in naq queue)
        inline Argument* applySubstitutionOnArgs();
	inline Argument* cloneArgs(MapVariables&);// return a copy of _args where each variable is replaced by its correspondant in mapVar
       virtual bool recursive(Node::Set&) = 0; // true if atom predicate is in the current SCC
	inline virtual bool isSolved() {return true;}; // true if atom predicate is already solved
       virtual void setMark(markEnum m) = 0;
       inline markEnum getMark();
       virtual void setDelta() {}; // default : no effect
	virtual void initDelta() {};// default : no effect
	virtual void restoreDelta() {};// default : no effect (used by PositiveLiteralOfNDR)
	virtual inline void recordIndex() {};// default : no effect (used by BasicLiteral)
       virtual inline void restoreIndex() {};// default : no effect (used by BasicLiteral)
       inline void recordMark();
       inline void restoreMark(); // restore _mark and _first/_last_index
       virtual void recordStatus(){};// default : no effect (used by BasicLiteral)
       virtual void restoreStatus(){};// default : no effect (used by BasicLiteral)

       
  private:
       friend inline std::ostream& operator<<(std::ostream& os, Literal& l);
	
  protected:
       Argument* _args;
       variableSet* _variables; // variables that appear in that atom
       variableSet _free_vars; // variables that appear for the first time in body
       variableSet _previous_vars; // variables that appear in a previous atom of the body
       markEnum _mark; //NON_MARKED, MARKED, or UNMARKED
       markStack _mark_stack;// back-track stack for _mark
       
       virtual std::ostream& put(std::ostream&) = 0;
       virtual bool firstTrueMatchBis() = 0;// try to match atom with some true tuple of the extension 
       			 // of the predicate ; return true if a match is found
       virtual statusEnum firstSoftMatchBis(statusEnum) = 0;// idem for true or mbt tuple of the extension 
};

inline Argument* Literal::getArgs(){
	return _args;
}

inline variableSet* Literal::getVariables(){
	return _variables;
}
inline  void Literal::addVariables(variableSet& vs){
//adds its own variables to vs
	for (variableSet::iterator it = _variables->begin(); it != _variables->end(); it++)
		vs.insert(*it);
}
inline void Literal::addFreeVar(Variable* v){
	_free_vars.insert(v);
}

inline bool Literal::isFreeVar(Variable* v){
	return _free_vars.find(v) != _free_vars.end();
}
	
inline void Literal::addPreviousVar(Variable* v){
	_previous_vars.insert(v);
}

inline void Literal::clearVars(){
	_free_vars.clear();
	_previous_vars.clear();
}

inline void Literal::free(){
	for (variableSet::iterator it = _free_vars.begin(); it != _free_vars.end(); it++)
		(*it)->free();
}

inline bool Literal::firstTrueMatch(){
// try to match atom with some true tuple of the extension of the predicate ; 
// return true if a match is found ; else return false
// return false if actual substitution on literal leads to out of range integer or function
	try{
		return firstTrueMatchBis();
	}
	catch(OutOfRange){
		return false;
	}
}
inline statusEnum Literal::firstSoftMatch(statusEnum st){
// try to match atom with some true or mbt tuple of the extension of the predicate ; 
// return true if a match is found ; else return false
// return false if actual substitution on literal leads to out of range integer
	try{
		return firstSoftMatchBis(st);
	}
	catch(OutOfRange){
		return NO_;
	}
}

Argument* Literal::applySubstitutionOnArgs(){
	return _args->applySubstitution();
}

Argument* Literal::cloneArgs(MapVariables& mapVar){
// return a copy of _args where each variable is replaced by its correspondant in mapVar
	return _args->clone(mapVar);
}


inline markEnum Literal::getMark(){
	return _mark;
}

void Literal::recordMark(){
	_mark_stack.push(_mark);
}
void Literal::restoreMark(){// restore _mark and _first/_last_index
	markEnum m = _mark_stack.top();
	_mark_stack.pop();
	setMark(m); // set mark and set _first_index and _last_index
}

inline std::ostream& operator<<(std::ostream& os, Literal& a){
	return a.put(os);
}

inline std::ostream& operator<<(std::ostream& os, Literal::Vector& av){
	for (Literal::Vector::iterator it = av.begin(); it != av.end() ; it++)
		os << (it==av.begin() ? "" : ",") << *(*it);
	return os;
}
#endif // _LITERAL_H_


