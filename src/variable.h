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
#ifndef _VARIABLE_H_
#define _VARIABLE_H_

#include "term.h"
#include "definition.h"
#include <string>
#include <set>

class Variable : public Term
{
  public:
  
       Variable();
       Variable(const std::string*);
       virtual ~Variable();
       inline const std::string* getUserName() {return _userName;}
       inline void addVariables(variableSet& vs);
	inline virtual bool containsVar(Variable* v){return (*v)==(*this);}
       inline void free(); // free the variable
       bool match(Term* t);
       inline Term* applySubstitution();
       inline Variable* getClone(MapVariables&);
       inline void recordSubstitution();
       inline void restoreSubstitution();

  private:
       inline std::ostream& put(std::ostream&) const;
       inline friend bool operator==(const Variable& v1, const Variable& v2);      
  protected:
       static int _nextNumber; // number for the next new variable
       
       const std::string* _userName;
       std::string _name;
       Term* _subst;
       termStack _subst_stack; // back-track stack for substitutions (variables values)
};

inline void Variable::addVariables(variableSet& vs){
	vs.insert(this);
}

inline void Variable::free(){
	_subst = NULL;
}
inline Term* Variable::applySubstitution(){
	if (_subst)
		return _subst;
	else
		return this;
}
inline Variable* Variable::getClone(MapVariables& mapVar){
	MapVariables::iterator it = mapVar.find(this);
	if (it != mapVar.end())
		return (*it).second;
	else
		throw RuntimeExcept("getClone for a variable that does not appear in mapVariables");
}
void Variable::recordSubstitution(){
	_subst_stack.push(_subst);
}
void Variable::restoreSubstitution(){
	_subst = _subst_stack.top();
	_subst_stack.pop();
}

std::ostream& Variable::put(std::ostream& os) const {
	return os << (!_userName->empty() ? *_userName : _name);
}

bool operator==(const Variable& v1, const Variable& v2){
	return v1._subst == v2._subst;
}

inline std::ostream& operator<<(std::ostream& os, variableSet& vs){
	for (variableSet::iterator it = vs.begin(); it != vs.end() ; it++)
		os << (it==vs.begin() ? "" : ",") << *(*it);
	return os;
}



#endif // _VARIABLE_H_


