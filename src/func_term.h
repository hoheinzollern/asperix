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
#ifndef _FUNC_TERM_H_
#define _FUNC_TERM_H_

#include "term.h"
#include "arguments.h"
#include "functor.h"
#include "variable.h"
#include <string>
#include <iostream>
/****************************************************************************
 * functional term has form f(t1,..tn) where f is a constant symbol 
 * 						and ti are terms (i>=1)
 * each Functerm is represented by an unique object
 * except those that contain variables (because _free_vars are different for each instance)
 * ***************************************************************************/


class FuncTerm : public Term
{
  public:
	FuncTerm(Functor*,Argument*, variableSet*, int);
       virtual ~FuncTerm();
	bool isFuncTerm() {return true;}
	bool isConst() {return _variables->empty();}
	inline Functor* getFunctor() {return _functor;}
	inline Argument* getArgs(){ return _args;}
	inline int getDepth() {return _depth;};
	inline void addVariables(variableSet&);// adds its own vars to vs
	inline virtual void addFreeVar(Variable* v);
	inline virtual void clearVars();
	inline virtual bool containsVar(Variable* v); // return true if v in _variables
	bool match(Term* t); // t is a ground term
	Term* applySubstitution();
	inline void free(); // free all variables of _free_vars
	Term* getClone(MapVariables&);
	inline virtual bool containsElement(Term* t);	// return true if t is member of list this
							// t and this must be ground

	static FuncTerm* new_FuncTerm(std::string*,Argument*);
	static FuncTerm* new_FuncTerm(Functor*,Argument*);
	static void setMaxDepth(int n) {_maxDepth = n;}
	static void delete_all();
  private:
       inline virtual std::ostream& put(std::ostream&) const;
  protected:
	static int _maxDepth;

       Functor* _functor;
       Argument* _args;
	variableSet* _variables; // variables that appear in that term
       variableSet _free_vars; // variables that appear for the first time in the atom
	int _depth; //length of the longest branch
};

inline  void FuncTerm::addVariables(variableSet& vs){
//adds its own variables to vs
	for (Argument::iterator it = _args->begin(); it != _args->end(); it++)
		(*it)->addVariables(vs);
}

inline void FuncTerm::addFreeVar(Variable* v){
	_free_vars.insert(v);
	_args->addFreeVar(v);
}
inline void FuncTerm::clearVars(){
	_free_vars.clear();
	_args->clearVars();
}

inline bool FuncTerm::containsVar(Variable* v){
 // return true if v in _variables
	return (_variables->find(v) != _variables->end());
}

inline void FuncTerm::free(){
	for (variableSet::iterator it = _free_vars.begin(); it != _free_vars.end(); it++)
		(*it)->free();
}

inline std::ostream& FuncTerm::put(std::ostream& os) const {
	return os << *_functor << *_args;
}

inline bool FuncTerm::containsElement(Term* t){
// return true if t is member of list 'this'
// t and this must be ground
// ATTENTION : this doit avoir 2 arguments !!!!!!
 	return ((t==_args->at(0)) || (_args->at(1)->containsElement(t)));
}

#endif // _FUNC_TERM_H_


