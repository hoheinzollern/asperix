/* *************************************************************************
 * Copyright (C) 2009 Claire Lefèvre, Pascal Nicolas
 * 
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 3
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
#ifndef _PROGRAM_H_
#define _PROGRAM_H_

#include "definition.h"
#include "rule.h"
#include "constraint_rule.h"
#include "normal_rule.h"
#include "graph.h"
#include "changes.h"

class Program
{
  public:
       Program();
       virtual ~Program();
       inline void setAnswerNumber(int i) {_answer_number = i;};
       inline void setVerbose(bool b) {_verbose = b;};
       inline void addFactRule(Rule*);
       inline void addNormalRule(Rule*);
       inline void addConstraintRule(Rule*);
       inline void addDeductiveConstraint(Rule*);
       inline void shiftRuleFromNDtoD(Rule* r);// shift r from non-definite rules to definite rules
       inline void shiftRuleFromNDtoDWithoutErasing(Rule* r);
	void initNonDefiniteRules();// initialize the multimap _non_definite_rules
	void addNonDefiniteRule(int sccIndex, Rule* r); // add pair to the multimap _non_definite_rules
	void initBodyPlusRules(); 
	inline ruleSet& getProhibitedRules() {return _prohibited_rules;};
	inline void setCurrentNonDefiniteRule(ruleMultimap::iterator it)	{_current_non_definite_rule = it;};
	inline ruleMultimap::iterator getCurrentNonDefiniteRule() {return _current_non_definite_rule;};
	inline int getCurrentScc()	{return _currentScc;};
	inline void setCurrentScc(int i)	{_currentScc = i;};
	inline void addProhibited(Rule* r,Changes& changes);
       inline bool isDefinite()	{return _normal_rules.empty();};//TODO _constraint_rule can be not empty
       inline Rule* firstNonDefiniteRule();
       inline Rule* nextNonDefiniteRule();
       inline Rule* currentNonDefiniteRule()	{return (*_current_non_definite_rule).second;};
       inline Rule* lastNonDefiniteRule();
       inline Rule* previousNonDefiniteRule();
       inline bool setFirstNonStratifiedScc();// initialize _currentScc and _current_range
       inline bool setNextNonStratifiedScc();
       inline int getNextNonStratifiedScc();
       inline bool setPreviousNonStratifiedScc();
       inline Graph& getGraph()		{return _graph;}
       inline int getChoicePoints()	{return _choice_points;}
       void evaluate();
       bool propagate(Changes& changes);
       bool propagateSolvedPredicates(Changes& changes);
       bool firstApplicationOfNonDefiniteRule(Changes& changes);
       bool nextApplicationOfNonDefiniteRule(Changes& changes);
       bool existsSupportedUnblockedRule(ruleSet&);
       bool existsSupportedNonBlockedProhibitedRule();
	inline void addDefiniteConstraintRules(ruleSet&);//add to ruleSet all definite (clone of) constraints
       inline void prohibiteCurrentInstanceOfNDR(Changes& changes);
	inline void prohibiteCurrentInstanceOfNDRPbMbtDescenteGauche(Changes& changes);
       bool firstChoicePoint(Changes& changes, bool& stop);
       bool nextChoicePoint(Changes& changes, bool& stop);
       bool answerSetSearch(int n);
       Changes* recordState(bool b);
       void restoreState(bool& b);
       void topState(Changes*& ch);
       inline void restoreDeltasCurrentScc();
       inline void printAnswerSet();
	       
  private:
       friend inline std::ostream& operator<<(std::ostream& os, Program& p);

  protected:
       ruleSet _fact_rules;
       ruleSet _definite_rules;
       ruleSet _normal_rules;
       ruleSet _constraint_rules;
       ruleMultimap _non_definite_rules; // pairs (sccIndex, Rule*). All NDrules are s.t. 
       		// all predicates of body- are in the same SCC than the head of the rule
       Graph _graph;
       int _currentScc;// index of current scc
       ruleMultimap::iterator _current_non_definite_rule;
       std::pair<ruleMultimap::iterator, ruleMultimap::iterator> _current_range; // of _non_definite_rules corresponding to _currentScc
	ruleSet _prohibited_rules;
	int _max_answer_number;
	int _answer_number;
	bool _verbose;
	int _choice_points;
	int _bad_choice;
	chanboolStack _chan_bool_stack; // back-track stack
	Changes* _first_state;


	void propagateBis(Changes& changes);
	bool applicationOfNonDefiniteRule(Rule* rule, bool instanceFound, Changes& changes);
	bool choicePoint(Changes& changes, bool& stop, bool f);

};

void Program::addFactRule(Rule* r){
	_fact_rules.insert(r);
	if (_verbose) std::cout<<*r;
}
void Program::addNormalRule(Rule* r){
	if (r->isDefinite()){
		_definite_rules.insert(r);
		r->getHead()->getPred()->addHeadDefiniteRule(r);
	}
	else{
		_normal_rules.insert(r);
		r->getHead()->getPred()->addHeadNonDefiniteRule(r);
		r->createDefiniteClone();// creation of a definite clone of rule r
	}
	if (_verbose) std::cout<<*r;
}
void Program::shiftRuleFromNDtoD(Rule* r){
// [ body-(r) is solved, r can be processed as a definite rule]
// shift r from non-definite rules to definite rules
// i.e., remove r from non-definite rules and add definite clone of r to definite rules
	shiftRuleFromNDtoDWithoutErasing(r);
	// remove r from non-definite rules
	_normal_rules.erase(r);
	delete r;
}
void Program::shiftRuleFromNDtoDWithoutErasing(Rule* r){
// [ body-(r) is solved, r can be processed as a definite rule]
// shift r from non-definite rules to definite rules
// i.e., remove r from non-definite rules and add definite clone of r to definite rules
	// remove r from non-definite rules
	r->getHead()->getPred()->removeHeadNonDefiniteRule(r);
	Rule* clone = r->getClone();// definite clone of r
	r->setClone(NULL);
	// add clone to definite rules
	_definite_rules.insert(clone);
	clone->getHead()->getPred()->addHeadDefiniteRule(clone);
}

void Program::addConstraintRule(Rule* r){
	_constraint_rules.insert(r);
		r->createDefiniteClone();// creation of a definite clone of constraint rule r
	if (_verbose) std::cout<<*r;
}
void Program::addDeductiveConstraint(Rule* r){
// deductive constraint has form "not h :- b+, not b-"
// if b- not empty, create a (classical) constraint ":- h, b+, not b-"
// create a propagation clone rule "_not_h :- b+, _not_b-"
	Rule* clone = r->createDefiniteClone();// creation of a definite clone of rule r
	clone->getBodyPlus()->addBodyPlusDefiniteRule(clone);// A REVOIR !!!!!!!!!!!!!!!!!!
	if (r->isDefinite()){
		r->getHead()->getPred()->addHeadDefiniteRule(clone);
		_definite_rules.insert(clone);
		r->setClone(NULL);
		delete r;
		if (_verbose) std::cout<<*clone;
	}
	else{
		PositiveLiteral* h = new PositiveLiteral(*static_cast<PositiveLiteral*>(r->getHead()));
		delete (r->getHead());
		r->getBody()->addLiteral(h);
		ConstraintRule* constr = new ConstraintRule(r->getBody());//":- h, b+, not b-"
		constr->setClone(clone);
		_constraint_rules.insert(constr);
		r->clear();
		delete r;
	}
}

Rule* Program::firstNonDefiniteRule(){
// _current_range is supposed to be already set
// return the first NDrule in the range corresponding to current scc
	_current_non_definite_rule = _current_range.first;
	if (_current_non_definite_rule != _current_range.second){
		return currentNonDefiniteRule();
	}else{
		return NULL;
	}
}

Rule* Program::nextNonDefiniteRule(){
	_current_non_definite_rule++;
	if (_current_non_definite_rule != _current_range.second){
		return currentNonDefiniteRule();
	}
	else{
		_current_non_definite_rule--;
		return NULL;
	}
}
Rule* Program::previousNonDefiniteRule(){
	if (_current_non_definite_rule == _current_range.first)
		_current_non_definite_rule = _current_range.second;
	_current_non_definite_rule--;
	return currentNonDefiniteRule();
}
Rule* Program::lastNonDefiniteRule(){
// return last NDrule of the current scc and update _current_non_definite_rule
	_current_non_definite_rule = _current_range.second;
	if (_current_non_definite_rule != _current_range.first){
		_current_non_definite_rule--;
		return currentNonDefiniteRule();
	}
	else
		return NULL;
}

bool Program::setFirstNonStratifiedScc(){
// initialize _currentScc and _current_range
	if (_graph.setFirstNonStratifiedScc(_currentScc)){
		_current_range = _non_definite_rules.equal_range(_currentScc);//rules from the scc
		return true;
	}
	else	return false;
}
int Program::getNextNonStratifiedScc(){
// return  the next non locally stratified scc
// return numberOfScc() if _currentScc was the last one
	return _graph.getNextNonStratifiedScc();
}

bool Program::setNextNonStratifiedScc(){
// update _currentScc and _current_range to the next non locally stratified scc
// return false if _currentScc was the last one
	if (_graph.setNextNonStratifiedScc(_currentScc)){
		_current_range = _non_definite_rules.equal_range(_currentScc);//rules from the scc
		return true;
	}
	else{
		return false;
	}
}
bool Program::setPreviousNonStratifiedScc(){
	if (_graph.setPreviousNonStratifiedScc(_currentScc)){
		_current_range = _non_definite_rules.equal_range(_currentScc);//rules from the scc
		return true;
	}
	else	return false;
}
void Program::addProhibited(Rule* r, Changes& changes){
	std::pair<ruleSet::iterator, bool> i_b = _prohibited_rules.insert(r);
	if (i_b.second){ // r was not already prohibited
		changes.addProhibited(r);
		Rule* clone = r->createDefiniteClone();// creation of a definite clone of constraint rule r
		clone->getBodyPlus()->addBodyPlusDefiniteConstraint(clone);
	}
	else
		delete r;
}

inline void Program::addDefiniteConstraintRules(ruleSet& rset){
//add to ruleSet all definite (clone of) constraints
	for (ruleSet::iterator it = _constraint_rules.begin(); it != _constraint_rules.end(); ++it){
		rset.insert((*it)->getClone());
	}
}

void Program::prohibiteCurrentInstanceOfNDR(Changes& ch){
	currentNonDefiniteRule()->prohibiteCurrentInstanceOfNDR(*this,ch);

}
void Program::prohibiteCurrentInstanceOfNDRPbMbtDescenteGauche(Changes& ch){
currentNonDefiniteRule()->prohibiteCurrentInstanceOfNDRPbMbtDescenteGauche(*this,ch);
}


void Program::restoreDeltasCurrentScc(){
//restore deltas for each NDrule of _currentScc
	for (ruleMultimap::iterator it = _current_range.first;  it != _current_range.second; ++it)
		(*it).second->restoreDeltas();
}
void Program::printAnswerSet(){
	if (_verbose) 
		std::cout<<"############### Answer set "<< _answer_number<<" ( "<<_choice_points<<" choice points, "<<_bad_choice<< " bad choice)"<<" ###############"<<std::endl;
	else
		std::cout<<"############### Answer set "<< _answer_number<<" ###############"<<std::endl;

	Predicate::prettyPrintAllInstances();
	std::cout<<std::endl;
}

inline std::ostream& operator<<(std::ostream& os, Program& p){
	os << p._fact_rules;
	os << p._definite_rules;
	os << p._normal_rules;
	return os << p._constraint_rules;
}

#endif // _PROGRAM_H_


