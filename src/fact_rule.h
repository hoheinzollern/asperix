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
#ifndef _FACT_RULE_H_
#define _FACT_RULE_H_

#include "rule.h"
#include "negative_literal.h"



class FactRule : public Rule
{
  public:
       FactRule(BasicLiteral*, variableSet* s)throw (LogicExcept);
       virtual bool isNormalRule(){return false;}
     
  protected:
       virtual std::ostream& put(std::ostream&);
};

#endif // _FACT_RULE_H_


