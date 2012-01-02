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
#include "negated_predicate.h"

NegatedPredicate::NegatedPredicate(){
}

NegatedPredicate::NegatedPredicate(const std::string* s, int n):Predicate(s,n){
}


/***************************************************************************
 * 	if a predicate is solved, its positive extension is completly known
 *   a term vector tv is then a negative instance iff tv is not a positive instance
 ***************************************************************************/
statusEnum NegatedPredicate::containInstance(Argument& tv){
// return true if tv is a known negative instance of the predicate	
	if (isSolved()){ // return true if tv is not a positive instance
		if (_negated_predicate->containInstance(tv)==NO_)
			return TRUE_;
		else
			return NO_;
	}else{		//return true if tv is a negative instance
		if (_instances.find(tv) != _instances.end())
			return TRUE_;
		else
			return NO_;
	}
}

statusEnum NegatedPredicate::containInstance(Argument& tv, int begin_i, int end_i){
// return true if tv is in _orderedInstance vector in [begin_i,end_i] index interval
	if (isSolved()) // solved predicate can not be "recursive predicate"
			// full extension is considered
		if (_negated_predicate->containInstance(tv)==NO_)
			return TRUE_;
		else
			return NO_;
	else {
		int i = begin_i;
		while (i <= end_i && *(_orderedInstances.at(i).first) != tv) i++;
		if (i <= end_i)
			return TRUE_;
		else
			return NO_;
	}
}

