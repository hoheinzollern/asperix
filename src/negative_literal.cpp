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
#include "negative_literal.h"

NegativeLiteral::NegativeLiteral(const NegativeLiteral& l):BasicLiteral(l){
	
}
NegativeLiteral::NegativeLiteral(Predicate* pred, Argument* tv):BasicLiteral(pred,tv){
}

bool NegativeLiteral::firstTrueMatchBis(){
// try to match atom with some tuple of the extension of the predicate
// return true if no match is found (not-atom is non-blocked)
// else return false (atom is true, so not-atom is false)
	if (_free_vars.empty()) // atom is already ground
		return !isInstance();
	else
		throw RuntimeExcept("Non ground term when evaluating Negative Literal");
}
statusEnum NegativeLiteral::firstSoftMatchBis(statusEnum status){
// try to match atom with some tuple of the extension of the predicate
// return true if no match is found (not-atom is non-blocked)
// else return false (atom is true, so not-atom is false)
	if (_free_vars.empty()) // atom is already ground
		if (!isInstance())
			return status;
		else
			return NO_;
	else
		throw RuntimeExcept("Non ground term when evaluating Negative Literal");
}

bool NegativeLiteral::nextTrueMatch(){
	return false;
}
statusEnum NegativeLiteral::nextSoftMatch(statusEnum){
	return NO_;
}

Literal* NegativeLiteral::createInstance(){
// create a new literal by applying current substitution
	Argument* tv = applySubstitutionOnArgs();
	NegativeLiteral* l = new NegativeLiteral(getPred(),tv);
	return l;
}
PositiveLiteral* NegativeLiteral::createPositiveClone(MapVariables& mapVar){
// create a new positive literal by cloning (using negated_predicate)
	Argument* tv = cloneArgs(mapVar);
	PositiveLiteral* l = new PositiveLiteral(getPred()->getNegatedPredicate(),tv);
	return l;
}

std::ostream& NegativeLiteral::put(std::ostream& os){
	os << "not ";
	return BasicLiteral::put(os);
}


