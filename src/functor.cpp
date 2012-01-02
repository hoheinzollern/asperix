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
#include "functor.h"
#include <sstream>
#include "arguments.h"
#include "func_term.h"

// static members

Functor* Functor::new_Functor(std::string* name, int n){ //WARNING : name is deleted if it already exists
       std::string s;
       std::stringstream ss;
       ss << *name << "/" << n; // cast int2string
       ss >> s;
       mapSymbConst::iterator it = _mapSymbConst.find(s);
       if (it!=_mapSymbConst.end()){
	       delete name;
	       return static_cast<Functor*>((*it).second);
       }
       else{
	       Functor* f = new Functor(name, n);
	       return static_cast<Functor*>((*_mapSymbConst.insert(std::make_pair(s,f)).first).second);
       }
}


//
//
Functor::Functor(){
}

Functor::Functor(const std::string* s, int n): SymbConst(s), _arity(n) {	
}

Functor::~Functor(){
	for (mapFuncTerm::iterator it = _mapFuncTerm.begin(); it != _mapFuncTerm.end(); it++){		
		delete (*it).second;
	}
	for (funcTermSet::iterator it = _funcTermSet.begin(); it != _funcTermSet.end(); it++){				delete (*it);
	}
}
	       
FuncTerm* Functor::existGroundTerm(Argument* a){ 
// if FuncTerm with functor 'this' and ground argument '*a' already exists, return it, else return NULL
	mapFuncTerm::iterator it = _mapFuncTerm.find(*a);
	if (it != _mapFuncTerm.end()) // already exists
		return (*it).second;
	else
		return NULL;
}

void Functor::insertGroundTerm(Argument* a, FuncTerm* t){ 
// insert FuncTerm 't' with functor 'this' and ground argument '*a' in _mapFuncTerm
	 _mapFuncTerm.insert(std::make_pair(*a,t));
}

void Functor::insertNonGroundTerm(FuncTerm* t){ 
// insert FuncTerm 't'  in _funcTermSet
	 _funcTermSet.insert(t);
}

