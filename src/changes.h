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
#ifndef _CHANGES_H_
#define _CHANGES_H_

#include "definition.h"
class Program;
#include <iostream>

class Changes
{
  public:
       Changes();
       virtual ~Changes();
       inline void addAtom(atomType);
       inline atomsQueue& getAtomsQueue() {return _atoms_queue;};
       inline void addProhibited(Rule*);
       inline void incNumberNDR();
       void recordState(Program& p);
       void recordExtensions(Program& p);
       void recordCurrentInstanceNDR(ruleMultimap::iterator, int sccIndex);
       void recordIntermediaryExtensions(Program& p, int lastIndex);
       void retropropagate(Program& p);
       void retropropagateSolved(Program& p, int firstScc, int lastScc);
       void restoreAll(Program& p);
       void restoreProhibitedRules(ruleSet&);
       void restorePreviousInstanceNDR(Program& p);
	       
  private:
       friend inline std::ostream& operator<<(std::ostream& os, Changes& ch);

  protected:
       ruleMultimap::iterator _first_NDR;
       int _number_NDR_first_scc;
       int _number_NDR_current_scc;
       int _first_scc;
       int _last_scc; // last  scc to be solved
       bool _intermediary; // true if intermediate state has been recorded 
       ruleSet _added_prohibited;
       atomsQueue _atoms_queue;// atoms added to the model, that need to be propagated
};

inline void Changes::addAtom(atomType a){
	_atoms_queue.push(a);
}

inline void Changes::addProhibited(Rule* r){
	_added_prohibited.insert(r);
}
inline void Changes::incNumberNDR(){
	if (_intermediary)
		_number_NDR_current_scc++;
	else
		_number_NDR_first_scc++;
}

inline std::ostream& operator<<(std::ostream& os, Changes& ch){
	os << "First_NDR : " ;
	os << &*(*(ch._first_NDR)).second ;
	os << " number of NDR : " << ch._number_NDR_first_scc << std::endl;
	os << "Added prohibited : " << &ch._added_prohibited;
	
	return os ;
}

#endif // _CHANGES_H_


