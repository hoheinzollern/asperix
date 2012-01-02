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
#include "term.h"
#include "num_const.h"
#include "symb_const.h"
#include "range_term.h"
#include "func_term.h"
#include "operator.h"
#include "arith_expr.h"

// static member
void Term::delete_all(){
// delete all terms except variables 
// variables are specific to each rule (deleted with the rule)
	NumConst::delete_all();
	SymbConst::delete_all();
	RangeTerm::delete_all();
	Operator::delete_all();
	ArithExpr::delete_all();
}


Term::~Term(){
}
	
