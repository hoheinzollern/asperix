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
#ifndef _TERM_H_
#define _TERM_H_

#include "definition.h"
#include <iostream>
#include <vector>
class Argument;

class Term // abstract class 
{
  public:
       typedef  std::vector<Term*> Vector;

       virtual ~Term();
       inline virtual void addVariables(variableSet&){};// adds its own vars to vs
	inline virtual bool containsVar(Variable* ) {return false;}; //default value
	inline virtual void addFreeVar(Variable* ){}; //default method, only defined for FuncTerm
	inline virtual void clearVars(){};//default method, only defined for FuncTerm
       virtual bool match(Term* t) = 0; // t is a ground term
       virtual bool isNumConst(){return false;}// default value
       inline virtual bool isSymbConst()	{return false;};// default value
	virtual bool isConst(){return false;}// default value
       virtual bool isArithExpr() {return false;}// default value
	virtual bool isFuncTerm() {return false;} // default value
	inline virtual SymbConst* getFunctor(); // default method
	inline virtual Argument* getArgs(); // default method
	inline virtual int getDepth() {return 0;}; // default value
	inline virtual bool containsElement(Term* t){return false;};//default method
       virtual int getIntValue() {return 0;};//TODO erreur , pas de valeur entière par défaut
       inline virtual const std::string& getStringValue(); // default method
       inline virtual Term* applySubstitution();
	inline virtual Term* getClone(MapVariables&);
       static void delete_all();

  private:
       friend inline std::ostream& operator<<(std::ostream& os, Term& t);
       virtual std::ostream& put(std::ostream&) const = 0;
	       
};

inline Term* Term::applySubstitution(){ // default method
	return this;
}
inline Term* Term::getClone(MapVariables&){ // default method
	return this;
}

inline std::ostream& operator<<(std::ostream& os, Term& t){
	return t.put(os);
}

const std::string& Term::getStringValue() { // default method
	throw RuntimeExcept("get string value for non symbolic constant");
}
SymbConst* Term::getFunctor() {// default method
	throw RuntimeExcept("get functor for non functional term");
}
Argument* Term::getArgs(){ // default method
	throw RuntimeExcept("get arguments for non functional term");
}



#endif // _TERM_H_


