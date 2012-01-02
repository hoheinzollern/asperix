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
#include "fact_rule.h"


FactRule::FactRule(BasicLiteral* a, variableSet* s)throw (LogicExcept)
try{_head = a;
    _body = new Body();
    if (s->empty()){
	if (a->isNegativeLiteral()) 
		a->addNonInstances(*a->getArgs());
	else
		a->addInstances(*a->getArgs(), TRUE_);
    }
   else
  	throw LogicExcept("Non safe rule");
}
catch(LogicExcept){
}

std::ostream& FactRule::put(std::ostream& os){
		return os << *_head << "." << std::endl;
}
