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
#include "affect_literal.h"

AffectLiteral::AffectLiteral(){
}

AffectLiteral::AffectLiteral(Variable* v, Term* t){
	_left_member = v;	
	_args = new Argument();
	_args->push_back(t);
	_variables = new variableSet;
	// each term adds its own vars to _variables
	v->addVariables(*_variables); 
	t->addVariables(*_variables);
	_mark = NON_MARKED;
}

AffectLiteral::~AffectLiteral(){
}

bool AffectLiteral::firstTrueMatchBis(){
	Term* t = _args->at(0)->applySubstitution();// right term
	if (t->isConst()){
		return _left_member->match(t);	
	}
	else
		throw RuntimeExcept(" Non ground right term when evaluating affectation literal"); 
}
statusEnum AffectLiteral::firstSoftMatchBis(statusEnum status){
	if (firstTrueMatchBis())
		return status;
	else
		return NO_;
}
bool AffectLiteral::nextTrueMatch(){
	return false;
}
statusEnum AffectLiteral::nextSoftMatch(statusEnum){
	return NO_;
}

Literal*  AffectLiteral::createPositiveClone(MapVariables& mapVar){ 
	return (new AffectLiteral(_left_member->getClone(mapVar), _args->at(0)->getClone(mapVar)));
}

