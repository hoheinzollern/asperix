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
#ifndef _NEGATED_PREDICATE_H_
#define _NEGATED_PREDICATE_H_

#include "predicate.h"

class NegatedPredicate : public Predicate 
{
  public:
       NegatedPredicate();
       NegatedPredicate(const std::string*, int);
       virtual inline void setSolved(bool b)	{_solved = b;}
       virtual statusEnum containInstance(Argument&);
       virtual statusEnum containInstance(Argument& tv,int begin_i, int end_i);
};

#endif // _NEGATED_PREDICATE_H_


