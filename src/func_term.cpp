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
#include "func_term.h"

// static members
//

int FuncTerm::_maxDepth = 16; // default value

FuncTerm* FuncTerm::new_FuncTerm(std::string* s,Argument* a){ // WARNING : a is deleted if already exists
  int n = a->size();
  Functor* f = Functor::new_Functor(s,n);
  return FuncTerm::new_FuncTerm(f,a);
}

FuncTerm* FuncTerm::new_FuncTerm(Functor* f,Argument* a){ // WARNING : a is deleted if already exists
  FuncTerm* t;
  variableSet* vars = new variableSet;
  a->addVariables(*vars); // each term adds its own variables to vars set
  if (vars->empty() && (t = f->existGroundTerm(a))){ // FuncTerm already exists
		delete a;
		delete vars;
  }
  else {// term with vars or first occurence of term
  	int depth = a->getMaxDepth() + 1; //depth of the deepest term
  	if (depth <= _maxDepth){
		t = new FuncTerm(f,a,vars,depth);
		if (vars->empty())
			f->insertGroundTerm(a,t);
		else
			f->insertNonGroundTerm(t);
	  }
	  else{
		delete vars;
		throw OutOfRangeFuncTerm();
 	 }
  }
  return t;
}


/** Constructors, destructors *********/

FuncTerm::FuncTerm(Functor* f,Argument* tv, variableSet* vs, int d):_functor(f),_args(tv),_variables(vs),_depth(d) {
}

FuncTerm::~FuncTerm(){
	_args->clear();
	delete _args;
	_variables->clear();
	delete _variables;
}

/************************************/
	       
Term* FuncTerm::applySubstitution(){
  Argument* args = _args->applySubstitution();
  try {
	Term* t = FuncTerm::new_FuncTerm(_functor, args);
	return t;
  }
  catch (OutOfRange&){
	delete args;
	throw;
  }
}

bool FuncTerm::match(Term* t){// t is a ground term
	if (!t->isFuncTerm() || !(*_functor == *t->getFunctor()))
		return false;
	else if (_args->match(t->getArgs()))
		return true;
	else{
		free();
		return false;
	}
}

Term* FuncTerm::getClone(MapVariables& mv){
	Argument* args =_args->clone(mv);
	Term* t = FuncTerm::new_FuncTerm(_functor, args);
	return t;

}
