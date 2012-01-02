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
#include "variable.h"
#include <sstream>

int Variable::_nextNumber = 0; // initialization of static variable

Variable::Variable(const std::string* s){
	if (s) 	_userName = s;
	else	_userName = new std::string("");
	// generate the next variable name
	std::stringstream ss;
	ss << "__" << _nextNumber++; // cast int2string
	ss >> _name;
	_subst = NULL;
}

Variable::Variable(){
}

Variable::~Variable(){
	delete _userName;
}

bool Variable::match(Term* t){
	if (_subst)
		return (_subst == t);
	else 
		return (_subst = t);
}
