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
#include "changes.h"
#include "program.h"

Changes::Changes():_intermediary(false){
}
Changes::~Changes(){
	for (ruleSet::iterator it = _added_prohibited.begin(); it != _added_prohibited.end(); it++){
		delete (*it);
	}

}
void Changes::recordState(Program& p){
	recordExtensions(p);
	 recordCurrentInstanceNDR(p.getCurrentNonDefiniteRule(), p.getCurrentScc());// record current state of search for NDR
}
void Changes::recordExtensions(Program& p){
	 p.getGraph().recordExtensions(p.getCurrentScc());// record all predicate extensions and non-extensions from SCC >= 'scc' 
}

void Changes::recordCurrentInstanceNDR(ruleMultimap::iterator it, int sccIndex){
	_first_NDR = it;
	_number_NDR_first_scc = 0;
	_number_NDR_current_scc = 0;
	_first_scc = sccIndex;
	_intermediary = false;
	(*it).second->recordCurrentInstanceNDR();
}

void Changes::recordIntermediaryExtensions(Program& p, int lastIndex){
	if (! _intermediary){
		_intermediary = true;
		p.getGraph().recordExtensions(_first_scc); // for predicate from scc >= sccIndex
	}
	else 
		p.getGraph().updateExtensions(_first_scc); // for predicate from scc >= sccIndex
	if (lastIndex != p.getGraph().numberOfScc())
	// on réinitialise _number_NDR_current_scc seulement si il y a une autre SCC à traiter
		_number_NDR_current_scc = 0;
	_last_scc = lastIndex;
}

void Changes::retropropagate(Program& p){
// restore previous extensions and non-extensions
// and clear _atoms_queue and _not_atoms_queue
	while(!_atoms_queue.empty()) _atoms_queue.pop(); // clear _atoms_queue
	p.getGraph().restoreExtensionsWithoutPop(p.getCurrentScc());// restore all predicate extensions and non-extensions 
}

void Changes::retropropagateSolved(Program& p, int firstScc, int lastScc){
// [first, last] has been set solved, retropagate
	p.getGraph().restoreNonSolvedScc(firstScc, lastScc+1);
	while(!_atoms_queue.empty()) _atoms_queue.pop(); // clear _atoms_queue
	p.getGraph().restoreExtensionsWithoutPop(firstScc);
	p.setCurrentScc(firstScc);
}

void Changes::restoreAll(Program& p){
	if (_intermediary) // an intermediary state has been recorded
		p.getGraph().restoreExtensions(_first_scc); 
	p.getGraph().restoreExtensions(_first_scc);// restore all extensions and non-extensions of predicates from SCC >=_first_scc
	restoreProhibitedRules(p.getProhibitedRules());// restore previous prohibited rules
	restorePreviousInstanceNDR(p);// record previous state of search for NDR (scc and rule)
}

void Changes::restoreProhibitedRules(ruleSet& prohib){
	for (ruleSet::iterator it = _added_prohibited.begin(); it != _added_prohibited.end(); it++){
		prohib.erase(*it);
		Rule* clone = (*it)->getClone();
		clone->getBodyPlus()->removeBodyPlusDefiniteConstraint(clone);
		delete (*it);
	}
	_added_prohibited.clear();
}

void Changes::restorePreviousInstanceNDR(Program& p){
	// restore non solved status for scc in [_first_scc, current_scc[
	if (_intermediary)
		p.getGraph().restoreNonSolvedScc(_first_scc, _last_scc); 
	// free current NonDefiniteRule
	Rule* r = p.currentNonDefiniteRule();
	r->free(); // free each variable of rule r
	if (p.getCurrentScc() != _first_scc){
		// restore state of search in currentScc
		for (int i = 0; i < _number_NDR_current_scc; ++i){
			r->restoreDeltas();
			r = p.previousNonDefiniteRule();
		}
		p.setPreviousNonStratifiedScc();
		while (p.getCurrentScc() != _first_scc){
			p.restoreDeltasCurrentScc(); // restore deltas of all NDrules of curretnScc
			p.setPreviousNonStratifiedScc();
		}
		r = p.lastNonDefiniteRule(); // from currentScc (= _first_scc)
	}
	// restore state of search in first scc 
	for (int i = 0; i < _number_NDR_first_scc; ++i){
		r->restoreDeltas();
		r = p.previousNonDefiniteRule();
	}

	p.setCurrentNonDefiniteRule(_first_NDR);
	p.currentNonDefiniteRule()->restorePreviousInstanceNDR();
}


