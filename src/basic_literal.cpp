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
#include "basic_literal.h"
#include <stdlib.h>
#include <algorithm>

BasicLiteral::BasicLiteral(){
}

BasicLiteral::BasicLiteral(const BasicLiteral& l):Literal(l),_pred(l._pred),_status(NO_){
}


BasicLiteral::BasicLiteral(std::string* s, Argument* tv, Graph& g):Literal(tv),_status(NO_){
	_pred = Predicate::new_Predicate(s, _args->size(), g);	
}
BasicLiteral::BasicLiteral(Predicate* p, Argument* tv):Literal(tv),_pred(p),_status(NO_){
}

bool BasicLiteral::isTheSameInstance(BasicLiteral* l){
// return true if grounded basic literals *this and *l are the same
	if (getPred() == l->getPred()){ //same predicate symbol and same args (after applying substitution)
		 return (_args->isTheSameInstance(l->getArgs()));
	}
	else{
		return false;
	}
}
bool BasicLiteral::isTheSameLiteral(BasicLiteral* l){
// return true if non-instanciated literals *this and *l are the same
	return (getPred() == l->getPred()) && (*getArgs() == *l->getArgs());
}

bool BasicLiteral::match(const Argument* tv){ // tv are ground terms
	if (_args->match(tv))
		return true;
	else{
		free();// free all free_vars of this atom
		return false;
	}
}

bool BasicLiteral::firstTrueMatchBis(){
	if (_free_vars.empty()){ // atom is already ground
		Argument* tv = applySubstitutionOnArgs();
		statusEnum status = getPred()->containInstance(*tv,_first_index, _last_index);
		delete tv;
		return (status >= TRUE_); // TRUE or TRUE_MBT
	}
	else{	
		const Argument* tuple = getPred()->firstTrueInstance(_current_index, _first_index, _last_index);
		while (tuple && !match(tuple)){
			tuple = getPred()->nextTrueInstance(_current_index, _last_index);
		}
		return (tuple!= NULL);
	}
}

bool BasicLiteral::nextTrueMatch(){
	if (_free_vars.empty()){ // atom was already ground
		return false;
	}
	else{
		const Argument* tuple;
		do{
			tuple = getPred()->nextTrueInstance(_current_index, _last_index);
		}while (tuple && !match(tuple));
		return (tuple!= NULL);
	}
}
statusEnum BasicLiteral::firstSoftMatchBis(statusEnum previousStatus){
// previousStatus is the match status of previous literals in the body
// if a true or mbt match is found for this literal, return the minimum value between match status of this literal and the previous ones (MBT < TRUE)
	if (_free_vars.empty()){ // atom is already ground
		Argument* tv = applySubstitutionOnArgs();
		statusEnum status = getPred()->containInstance(*tv,_first_index, _last_index);
		delete tv;
		_status = std::min(status, previousStatus);
		return _status;
	}
	else{	
		std::pair<const Argument*, statusEnum> t_s = getPred()->firstSoftInstance(_current_index, _first_index, _last_index);
		while (t_s.second && !match(t_s.first)){
			t_s = getPred()->nextSoftInstance(_current_index, _last_index);
		}
		_status = std::min(t_s.second, previousStatus);
		return _status;
	}
}

statusEnum BasicLiteral::nextSoftMatch(statusEnum previousStatus){
	if (_free_vars.empty()){ // atom was already ground
		return NO_;
	}
	else{
		std::pair<const Argument*, statusEnum> t_s;
		do{
			t_s = getPred()->nextSoftInstance(_current_index, _last_index);
		}while (t_s.second && !match(t_s.first));
		_status = std::min(t_s.second, previousStatus);
		return _status;
	}
}

statusEnum BasicLiteral::isInstance(){
// require atom is already ground
// return status if atom is in the extension of the predicate
	Argument* tv = applySubstitutionOnArgs();
	statusEnum ok = getPred()->containInstance(*tv);
	delete tv;
	return ok;
}

Literal* BasicLiteral::createInstance(){
// create a new literal by applying current substitution
	Argument* tv = applySubstitutionOnArgs();
	BasicLiteral* l = new BasicLiteral(getPred(),tv);
	return l;
}
BasicLiteral* BasicLiteral::createPositiveClone(MapVariables& mapVar){
// create a new positive literal by cloning 
	Argument* tv = cloneArgs(mapVar);
	BasicLiteral* l = new BasicLiteral(getPred(),tv);
	return l;
}

std::ostream& BasicLiteral::put(std::ostream& os){
	return os << *_pred << *_args;
}


