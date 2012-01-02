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
#ifndef _NUM_CONST_H_
#define _NUM_CONST_H_

#include "term.h"
#include "definition.h"
#include <iostream>

/* NumConst is a numeric constant (integer) 
 * its value is in range [-_maxInt.._maxInt]
 */
class NumConst : public Term
{
  public:
       NumConst();
       NumConst(int);
       virtual ~NumConst();
       inline  bool match(Term* t);
       inline bool isNumConst();
       inline bool isConst();
       inline int getIntValue();

       static NumConst* new_NumConst(int);
       static void setMaxInt(int n) {_maxInt = n;}
       static void delete_all();
  private:
       inline std::ostream& put(std::ostream&) const;
       inline friend bool operator==(const NumConst& n1, const NumConst& n2);
  protected:
       static mapNumConst _mapNumConst;
       static int _maxInt;
       
       int _val;
};

inline  bool NumConst::match(Term* t){
	return (this == t);
}
inline bool NumConst::isNumConst(){
	return true;
}
inline bool NumConst::isConst(){
	return true;
}

inline int NumConst::getIntValue(){
	return _val;
}
std::ostream& NumConst::put(std::ostream& os) const {
	return os << _val;
}

bool operator==(const NumConst& n1, const NumConst& n2){
	return n1._val == n2._val;
}
#endif // _NUM_CONST_H_


