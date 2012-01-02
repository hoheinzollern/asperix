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
#ifndef _ARGUMENT_H_
#define _ARGUMENT_H_

#include "definition.h"
#include "term.h"
#include "variable.h"
#include <string>
#include <vector>
#include <iostream>

/* An argument is a term vector
 * it can be arguments of a predicate or a function
 */
class Argument : public Term::Vector {
  public:
       Argument();
       Argument(const Argument&);
       virtual ~Argument();
       inline  void addVariables(variableSet& vs);//adds its own variables to vs
       inline void addFreeVar(Variable* v);
       inline void clearVars();
       inline bool match(const Argument* arg);// try to match argument  with the ground terms arg 
       Argument* applySubstitution();
	bool isTheSameInstance(Argument* arg);
	int getMaxDepth(); //depth of the deepest term
	Argument* clone(MapVariables&);// return a copy of _args where each variable is replaced by its correspondant in mapVar

       
  private:
       friend inline std::ostream& operator<<(std::ostream& os,const Argument& tv);
	
};


inline  void Argument::addVariables(variableSet& vs){
//adds its own variables to vs
	for (Argument::iterator it = begin(); it !=end(); it++)
		(*it)->addVariables(vs);
}
inline void Argument::addFreeVar(Variable* v){
// v appears for the first time in this argument
// search in which term it appears first and add v in _free_vars if it is a functional term  
	Argument::iterator it = begin();
	while (it !=end() && !(*it)->containsVar(v)) it++;
	if (it !=end())
		(*it)->addFreeVar(v);
	else
		throw RuntimeExcept("addFreeVar");
}

inline void Argument::clearVars(){
	for (Argument::iterator it = begin(); it !=end(); it++)
		(*it)->clearVars();
}


inline bool Argument::match(const Argument* arg){
// try to match argument with the ground argument arg 
	Argument::iterator i1 = begin();
	Argument::const_iterator i2 = arg->begin();
	while (i1 != end() && (*i1)->match(*i2)){
		i1++; i2++;
	}
	if (i1 ==end())
		return true;
	else
		return false;
}

inline std::ostream& operator<<(std::ostream& os,const Argument& tv){
  if (!tv.empty()){
	os <<"(";
	for (Argument::const_iterator it = tv.begin(); it != tv.end() ; it++)
		os << (it==tv.begin() ? "" : ",") << *(*it);
	os << ")";
  }
  return os;
}


#endif // _ARGUMENT_H_


