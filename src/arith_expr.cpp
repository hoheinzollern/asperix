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
#include "arith_expr.h"

// static members
//

arithExprSet ArithExpr::_arithExprSet;

void ArithExpr::delete_all(){
	for (arithExprSet::iterator it = _arithExprSet.begin(); it != _arithExprSet.end(); it++){				delete (*it);
	}	
}

// destructor - constructors
// 
ArithExpr::ArithExpr(opEnum op, Term* t){
	_operator = Operator::new_Operator(op);
	_right_term = t;
	ArithExpr::_arithExprSet.insert(this);
}
ArithExpr::ArithExpr(Operator* op, Term* t):_operator(op),_right_term(t){
	ArithExpr::_arithExprSet.insert(this);
}

ArithExpr::~ArithExpr(){
}

/************ Binary arithmetic expression ***********/
BinaryArithExpr::BinaryArithExpr(opEnum op, Term* t1, Term* t2):ArithExpr(op,t2){
	_left_term = t1;
}
BinaryArithExpr::BinaryArithExpr(Operator* op, Term* t1, Term* t2):ArithExpr(op,t2),_left_term(t1){
}
BinaryArithExpr::~BinaryArithExpr(){
}
/************ Unary arithmetic expression ***********/
UnaryArithExpr::UnaryArithExpr(opEnum op, Term* t):ArithExpr(op,t){
}
UnaryArithExpr::UnaryArithExpr(Operator* op, Term* t):ArithExpr(op,t){
}
UnaryArithExpr::~UnaryArithExpr(){
}


