/* *************************************************************************
 * Copyright (C) 2009 Claire Lef�vre, Pascal Nicolas
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
#include "operator.h"

// static members
// 
mapOperator Operator::_mapOperator;

Operator* Operator::new_Operator(opEnum oper){
	mapOperator::iterator it = _mapOperator.find(oper);
	if (it != _mapOperator.end()) // already exists
		return (*it).second;
	else{   Operator* op;
		switch (oper){
		case PLUS : op = new PlusOperator(oper); break;
		case MINUS : op = new MinusOperator(oper); break;
		case MULT : op = new MultOperator(oper); break;
		case DIV : op = new DivOperator(oper); break;
		case MOD : op = new ModOperator(oper); break;
		case MAX : op = new MaxOperator(oper); break;
		case ABS : op = new AbsOperator(oper); break;
		default : throw RuntimeExcept("Unknown arithmetic operator");
	       }
	       _mapOperator.insert(std::make_pair(oper,op));
	       return op;
	}

}

void Operator::delete_all(){
	for (mapOperator::iterator it = _mapOperator.begin(); it != _mapOperator.end(); it++)
		delete (*it).second;
}

// destructor & constructors
Operator::~Operator(){
}
Operator::Operator(opEnum oper):_oper(oper){
}

PlusOperator::PlusOperator(opEnum oper):Operator(oper){
}
MinusOperator::MinusOperator(opEnum oper):Operator(oper){
}
MultOperator::MultOperator(opEnum oper):Operator(oper){
}
DivOperator::DivOperator(opEnum oper):Operator(oper){
}
ModOperator::ModOperator(opEnum oper):Operator(oper){
}
AbsOperator::AbsOperator(opEnum oper):Operator(oper){
}
MaxOperator::MaxOperator(opEnum oper):Operator(oper){
}
