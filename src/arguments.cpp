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
#include "arguments.h"
#include <stdlib.h>

Argument::Argument(): Term::Vector(){
}

Argument::Argument(const Argument& a): Term::Vector(a){

}

Argument::~Argument(){
	clear();
}

Argument* Argument::applySubstitution(){
  Argument* args = new Argument();
  try {
	for (Argument::iterator it = begin(); it != end(); it++)
		args->push_back((*it)->applySubstitution());
	return args;
  }
  catch (OutOfRange&){
	delete args;
	throw;
  }
}

bool Argument::isTheSameInstance(Argument* arg){
// return true if grounded arguments *this and *arg are the same
	Argument::iterator i1 = begin();
	Argument::const_iterator i2 = arg->begin();
	while (i1 != end() && (*i1)->applySubstitution()==(*i2)->applySubstitution()){
		i1++; i2++;
	}
	return (i1 == end());
}

int Argument::getMaxDepth(){
 //return the depth of the deepest term
 int maxi = 0;
 for (Argument::iterator it = begin(); it != end(); it++)
	if ((*it)->getDepth()>maxi) maxi = (*it)->getDepth();
 return maxi;
}

Argument* Argument::clone(MapVariables& mapVar){
// return a copy of _args where each variable is replaced by its correspondant in mapVar
	Argument* args = new Argument();
	for (Argument::iterator it = begin(); it != end(); it++)
		args->push_back((*it)->getClone(mapVar));
	return args;
}


