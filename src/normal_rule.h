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
#ifndef _NORMAL_RULE_H_
#define _NORMAL_RULE_H_

#include "rule.h"
class Program;

class NormalRule : public Rule
{
  public:
       NormalRule(BasicLiteral*, Body*, variableSet*, Graph&); //constructor for normal rules
	NormalRule(BasicLiteral*, Body*);
       virtual bool isNormalRule(){return true;}
       inline bool isAutoBlocked();
       void evaluate(); // evaluation of a definite non recursive rule
       void evaluateRec();// evaluation of a definite recursive rule
	void evaluate(atomsQueue&);
	void evaluateRec(atomsQueue&); //evaluation of a definite rule
       bool addHead(Program& p, Changes& ch);// apply substitution and add head to the model
       bool addBodyMinus(Program& p, Changes& changes);//apply substitution and exclude body- from the model
       inline void setDelta()	{_bodyPlus->setDelta();};// for a non definite rule
	       
  protected:
       virtual std::ostream& put(std::ostream&);


};

inline bool NormalRule::isAutoBlocked(){
	return _bodyMinus->contains(_head);
}
#endif // _NORMAL_RULE_H_


