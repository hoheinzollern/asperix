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
#include "relational_literal.h"
#include <stdlib.h>

RelationalLiteral::RelationalLiteral(){
}

RelationalLiteral::RelationalLiteral(Term* t1, Term* t2){
	_args = new Argument();
	_args->push_back(t1);
	_args->push_back(t2);
	_variables = new variableSet;
	// each term adds its own vars to _variables
	t1->addVariables(*_variables); 
	t2->addVariables(*_variables);
	_mark = NON_MARKED;
}

bool RelationalLiteral::firstTrueMatchBis(){
	if (_free_vars.empty()){ // atom is already ground
		Argument* tv = applySubstitutionOnArgs();
		bool ok = isTrueRelation(tv);
		delete tv;
		return ok;
	}
	else
		throw RuntimeExcept(" Non ground term when evaluating relational literal");
}
statusEnum RelationalLiteral::firstSoftMatchBis(statusEnum st){
	if (firstTrueMatchBis())
		return st;
	else
		return NO_;
}
bool RelationalLiteral::nextTrueMatch(){
	return false;
}
statusEnum RelationalLiteral::nextSoftMatch(statusEnum){
	return NO_;
}

// specific relations
// 
bool MemberLiteral::isTrueRelation(Argument* couple){
	Term* t1 = couple->at(0);
	Term* t2 = couple->at(1);
	if (t1->isConst() && t2->isConst()) // numeric constants, symbolic constants or functional terms
		return (t2->containsElement(t1)); // return true iff t1 appears as a member of list t2 
	else 
		throw RuntimeExcept(" Non constant term when evaluating relational literal");
}
Literal*  MemberLiteral::createPositiveClone(MapVariables& mapVar){ 
	return (new MemberLiteral(_args->at(0)->getClone(mapVar), _args->at(1)->getClone(mapVar)));
}
bool NmemberLiteral::isTrueRelation(Argument* couple){
	Term* t1 = couple->at(0);
	Term* t2 = couple->at(1);
	if (t1->isConst() && t2->isConst()) // numeric constants, symbolic constants or functional terms
		return !(t2->containsElement(t1)); // return true iff t1 does not appear as a member of list t2 
	else 
		throw RuntimeExcept(" Non constant term when evaluating relational literal");
}
Literal*  NmemberLiteral::createPositiveClone(MapVariables& mapVar){ 
	return (new NmemberLiteral(_args->at(0)->getClone(mapVar), _args->at(1)->getClone(mapVar)));
}


bool EqLiteral::isTrueRelation(Argument* couple){
	Term* t1 = couple->at(0);
	Term* t2 = couple->at(1);
	if (t1->isConst() && t2->isConst()) // numeric constants, symbolic constants or functional terms
		return (t1 == t2);
	else 
		throw RuntimeExcept(" Non constant term when evaluating relational literal");
}
Literal*  EqLiteral::createPositiveClone(MapVariables& mapVar){ 
	return (new EqLiteral(_args->at(0)->getClone(mapVar), _args->at(1)->getClone(mapVar)));
}

bool NeqLiteral::isTrueRelation(Argument* couple){
	Term* t1 = couple->at(0);
	Term* t2 = couple->at(1);
	if (t1->isConst() && t2->isConst()) // numeric constants, symbolic constants or functional terms
		return (t1 != t2);
	else
		throw RuntimeExcept(" Non constant term when evaluating relational literal");
}
Literal*  NeqLiteral::createPositiveClone(MapVariables& mapVar){ 
	return (new NeqLiteral(_args->at(0)->getClone(mapVar), _args->at(1)->getClone(mapVar)));
}

bool GeLiteral::isTrueRelation(Argument* couple){
	Term* t1 = couple->at(0);
	Term* t2 = couple->at(1);
	if (t1->isNumConst() && t2->isNumConst())
		return (t1->getIntValue() >= t2->getIntValue());
	else if (t1->isSymbConst() && t2->isSymbConst()) // symbolic constants
		return (t1->getStringValue() >= t2->getStringValue());
	else
		throw RuntimeExcept(" Non constant or incorrect term when evaluating relational literal");
}
Literal*  GeLiteral::createPositiveClone(MapVariables& mapVar){ 
	return (new GeLiteral(_args->at(0)->getClone(mapVar), _args->at(1)->getClone(mapVar)));
}

bool GtLiteral::isTrueRelation(Argument* couple){
	Term* t1 = couple->at(0);
	Term* t2 = couple->at(1);
	if (t1->isNumConst() && t2->isNumConst())
		return (t1->getIntValue() > t2->getIntValue());
	else if (t1->isSymbConst() && t2->isSymbConst()) // symbolic constants
		return (t1->getStringValue() > t2->getStringValue());
	else
		throw RuntimeExcept(" Non constant or incorrect term when evaluating relational literal");
}
Literal*  GtLiteral::createPositiveClone(MapVariables& mapVar){ 
	return (new GtLiteral(_args->at(0)->getClone(mapVar), _args->at(1)->getClone(mapVar)));
}

