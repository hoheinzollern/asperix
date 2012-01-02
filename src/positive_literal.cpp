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
#include "positive_literal.h"
#include <stdlib.h>

PositiveLiteral::PositiveLiteral(){
}

PositiveLiteral::PositiveLiteral(const PositiveLiteral& l):BasicLiteral(l){
}

PositiveLiteral::PositiveLiteral(std::string* s, Argument* tv, Graph& g):BasicLiteral(s,tv,g){
}

PositiveLiteral::PositiveLiteral(Predicate* pred, Argument* tv):BasicLiteral(pred,tv){
}

Literal* PositiveLiteral::createInstance(){
// create a new literal by applying current substitution
	Argument* tv = applySubstitutionOnArgs();
	PositiveLiteral* l = new PositiveLiteral(getPred(),tv);
	return l;
}
PositiveLiteral* PositiveLiteral::createPositiveClone(MapVariables& mapVar){
// create a new positive literal by cloning 
	Argument* tv = cloneArgs(mapVar);
	PositiveLiteral* l = new PositiveLiteral(getPred(),tv);
	return l;
}

/******** PositiveLiteralOfNDR is a positive literal that appears in a non-definite rule (NDR)
 ********/
PositiveLiteralOfNDR::PositiveLiteralOfNDR(const PositiveLiteralOfNDR& l):PositiveLiteral(l),_delta_begin(0),_delta_end(-1){
}
PositiveLiteralOfNDR::PositiveLiteralOfNDR(Predicate* pred, Argument* tv):PositiveLiteral(pred,tv),_delta_begin(0),_delta_end(-1){
}

Literal* PositiveLiteralOfNDR::createInstance(){
// create a new literal by applying current substitution
	Argument* tv = applySubstitutionOnArgs();
	PositiveLiteralOfNDR* l = new PositiveLiteralOfNDR(getPred(),tv);
	return l;
}

