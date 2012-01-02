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
#ifndef _CONSTRAINT_RULE_H_
#define _CONSTRAINT_RULE_H_

#include "rule.h"


class ConstraintRule : public Rule
{
  public:
       ConstraintRule(Body*, variableSet*, Graph&); 
       ConstraintRule(BasicLiteral*,Body* v);
       ConstraintRule(Body* v);
       virtual ~ConstraintRule();
	virtual bool isNormalRule(){return false;};
	virtual void orderBody();
	Rule* createDefiniteClone();
	inline virtual void initDelta();
	
  protected:
       virtual std::ostream& put(std::ostream&);
};


void ConstraintRule::initDelta(){
	_bodyPlus->initDelta();
}
#endif // _CONSTRAINT_RULE_H_


