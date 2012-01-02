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
#include "literal.h"
#include <stdlib.h>

Literal::Literal(){
}

Literal::Literal(const Literal& l){
	_args = new Argument(*l._args);
	_variables = new variableSet(*l._variables);
}

Literal::Literal(Argument* tv):_mark(NON_MARKED){
	if (tv) _args = tv;
	else _args = new Argument();
	_variables = new variableSet;
	_args->addVariables(*_variables); // each term adds its own vars to _variables
}
	

Literal::~Literal(){
	delete _args;
	_variables->clear();
	delete _variables;
}


