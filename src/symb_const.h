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
#ifndef _SYMB_CONST_H_
#define _SYMB_CONST_H_

#include <string>
#include "definition.h"
#include "term.h"


class SymbConst : public Term
{
  public:	  
       SymbConst();
       SymbConst(const std::string*);
       virtual ~SymbConst();
       inline bool isConst();
	inline bool isSymbConst()	{return true;};
       inline const std::string& getStringValue()	{return *_name;}
       inline  bool match(Term* t);
       
       static SymbConst* new_SymbConst(std::string* name);
       static void delete_all();
       inline friend bool operator==(const SymbConst& s1, const SymbConst& s2);
  private:
       inline std::ostream& put(std::ostream&) const;
  protected:
       static mapSymbConst _mapSymbConst;

       const std::string* _name;
};

inline bool SymbConst::isConst(){
	return true;
}

inline  bool SymbConst::match(Term* t){
	return (this == t);
}

std::ostream& SymbConst::put(std::ostream& os) const {
	return os << *_name;
}

bool operator==(const SymbConst& s1, const SymbConst& s2){
	return s1._name == s2._name;
}

#endif // _SYMB_CONST_H_


