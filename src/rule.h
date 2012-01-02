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
#ifndef _RULE_H_
#define _RULE_H_

#include "literal.h"
#include "positive_literal.h"
#include "negative_literal.h"
#include "definition.h"
#include "changes.h"
#include <stack>
#include <algorithm>

class ConstraintRule;
class NormalRule;
/* **********
 * Body class
 * **********/
class Body : public Literal::Vector{
  public:
  	typedef std::stack<Body::iterator> IteratorStack;

	virtual ~Body();
	inline void addLiteral(Literal* l) {push_back(l);
					    l->addVariables(_variables);};
	inline variableSet& getVariables() {return _variables;}	
	inline bool contains(Literal* l);
	bool containsInstance(BasicLiteral* l);//return true if current instance of body contains current instance of literal *l
	bool containsNotLiteral(BasicLiteral* l);//return true if *l appears as negative literal in body (*l and body are not instanciated)
	inline bool containsOnePredFrom(Node::Set& ns);
	inline bool containsOnePredFrom(int scc);
	inline bool containsOnePredNotFrom(int scc);
	inline Literal* isSingleLiteral();// if body contains exactly one literal return it, else return NULL
	void addBodyPlusDefiniteRule(Rule* r);
	void addBodyPlusDefiniteRule(int sccIndex, Rule* r);
	void addBodyPlusNonDefiniteRule(int sccIndex, Rule* r);
	void addBodyPlusDefiniteConstraint(Rule* r);
	void removeBodyPlusDefiniteConstraint(Rule* r);
	void applySubstitutionAndAddNonInstances(Program& p,Changes& ch);
	// "recursive" literals are those whose predicate appears as label of a node in ns
	void split(Node::Set& ns, Body& recBody, Body& nonRecBody);
	// "recursive" literals are those whose predicate is pred
	void split(Predicate* pred, Body& recBody, Body& nonRecBody);
	// "recursive" literals are those which are not already solved
	void split(Body& recBody, Body& nonRecBody);
	void orderPlus(Body& recBody, Body& nonRecBody, Body& ordBody);
	void order(Body& recBody, Body& nonRecBody, Body& ordBody);
	void initVars();
	Body* createInstance();// create a new body by applying current substitution
	void addPositiveClone(Body& b, MapVariables& m);// create clones of literals and add them to b
	inline void setDelta(); // set delta index of literals of the body+ of a non definite rule
	inline void initDelta(); // init delta index of literals of the body+ of a non definite rule
	inline void restoreDeltas();// restore delta indexes of literals of the body
	inline void recordMarks();// record marks of literals of the body
	inline void restoreMarks();// restore marks of literals of the body
	inline void recordIndexesAndStatus();// record current indexes and status of literals of the body
	inline void restoreIndexesAndStatus();// restore current indexes and status of literals of the body
	inline bool isBlocked(); // return true if at least one literal is in the model (all literals must be ground)
	inline bool isSolved();

  protected:
	variableSet _variables;
};

inline bool Body::contains(Literal* lit){
	return (find(begin(),end(),lit)!= end());
}
inline bool Body::containsOnePredFrom(Node::Set& ns){
// return true if body contains at least one predicate that appears as label of a node from ns
	Body::iterator it = begin();
	while (it != end() && !(*it)->hasPredIn(ns)) ++it;
	return (it != end());
}
bool Body::containsOnePredFrom(int scc){
// return true if body contains at least one predicate from scc
	Body::iterator it = begin();
	while (it != end() && (*it)->getSccIndex() != scc) ++it;
	return (it != end());
}
bool Body::containsOnePredNotFrom(int scc){
// return true if body contains at least one predicate from another scc than 'scc'
	
	Body::iterator it = begin();
	while (it != end() && (*it)->getSccIndex() == scc){ 
		++it;}
	return (it != end());
}
inline Literal* Body::isSingleLiteral(){
// if body contains exactly one literal return it, else return NULL
	if (size() == 1) 
		return *begin();
	else
		return NULL;
}

void  Body::setDelta(){
// set delta index of literals of the body+ of a non definite rule
	for (Body::iterator it = begin(); it != end(); it++)
		(*it)->setDelta();
}
void  Body::initDelta(){
// init delta index for literals of the body+ of a non definite rule
	for (Body::iterator it = begin(); it != end(); it++)
		(*it)->initDelta();
}
void Body::restoreDeltas(){// restore delta indexes of literals of the body
	for (Body::iterator it = begin(); it != end(); it++)
		(*it)->restoreDelta();	
}
void Body::recordMarks(){// record marks of literals of the body
	for (Body::iterator it = begin(); it != end(); it++)
		(*it)->recordMark();	
}
void Body::restoreMarks(){// restore marks of literals of the body
	for (Body::iterator it = begin(); it != end(); it++){
		(*it)->restoreMark();
	}
}
void Body::recordIndexesAndStatus(){// record current indexes of literals of the body
	for (Body::iterator it = begin(); it != end(); it++){
		(*it)->recordIndex();	
		(*it)->recordStatus();
	}
}
void Body::restoreIndexesAndStatus(){// restore current indexes of literals of the body
	for (Body::iterator it = begin(); it != end(); it++){
		(*it)->restoreIndex();	
		(*it)->restoreStatus();
	}
}

bool Body::isBlocked(){
// require all literals are ground
// return true if at least one literal is in the model 
	Body::iterator it = begin();
	while (it != end() && !(*it)->isInstance()) it++;
	return (it != end());
}
bool Body::isSolved(){
// return true if all literals'predicates are solved
	Body::iterator it = begin();
	while (it != end() && (*it)->isSolved()) it++;
	return (it == end());
}

/* ***************************************************************
 * Rule class
 * ***************************************************************/
class Rule
{
  public:
//       typedef std::set<Rule*> Set;
	  
       Rule();
	Rule(BasicLiteral*, Body*);//constructor for normal rules
       Rule(BasicLiteral*, Body*, variableSet*, Graph&)throw (LogicExcept) ; //constructor for normal rules
       virtual ~Rule();
       void clear();
       inline BasicLiteral* getHead();
       inline Body* getBody()		{return _body;}
       inline Body* getBodyPlus()	{return _bodyPlus;}
       inline Body* getBodyMinus()	{return _bodyMinus;}
       virtual bool isNormalRule(){return true;}
       inline bool isDefinite(); 
       void orderBody(Node::Set& ns);
	void orderBody(Predicate* pred);
	virtual void orderBody();
	virtual void orderPositiveBody();
       inline void free(); // free each variable of the rule
       bool recursive(Node::Set& ns); // true if the rule is recursive r.t. SCC ns
       inline Literal* firstLiteral(); // can not be NULL
       inline Literal* nextLiteral();
       inline Literal* previousLiteral();
	inline Literal* currentLiteral()	{return *_currentLiteral;};
       inline Literal* firstRecursiveLiteral(); // can not be NULL
       inline Literal* nextRecursiveLiteral();
	inline Literal* recursiveLiteral()	{return *_recursiveLiteral;};
	inline statusEnum previousStatus(); // previous match status
	inline bool isSolved()		{return _solved;};
	inline void setSolved(bool v)	{_solved = v;};
	inline Rule* getClone()	{return _clone;}
	inline void setClone(Rule* r) {_clone = r;}
       virtual void evaluate() {}; 
       virtual void evaluateRec() {};
	virtual void evaluate(atomsQueue&) {}
	virtual void evaluateRec(atomsQueue&) {};
	virtual bool firstInstanceNonDefiniteRule() ;//TODO non défini pour facts 
	virtual bool nextInstanceNonDefiniteRule() ;//TODO non défini pour facts 
	virtual bool existsInstanceNonDefiniteRule() ;//TODO non défini pour facts (en fait défini pour constraint)
	virtual bool existsInstanceDefiniteConstraint() ;//TODO non défini pour facts (en fait défini pour constraint)
	virtual bool existsInstanceDefiniteRuleRec() ;//TODO non défini pour facts 
	virtual bool addHead(Program&,Changes&) {return false;};// apply substitution and add head to the model  TODO non défini pour facts et constraints
	virtual bool addBodyMinus(Program&, Changes&) {return false;};// apply substitution and add body- out of the model  TODO non défini pour facts et constraints
	virtual ConstraintRule* createInstance();// create a new constraint rule by applying current substitution
	void prohibiteCurrentInstanceOfNDR(Program&, Changes&);
	void prohibiteCurrentInstanceOfNDRPbMbtDescenteGauche(Program&, Changes&);
	virtual Rule* createDefiniteClone();// create a new definite rule by cloning
	void shiftLocallySolvedLiteralsFromBMinus2BPlus(int sccIndex);
	inline void initMarks(markEnum);// init atoms iterators in predicate extensions
	virtual void setDelta() {};//TODO non défini pour facts et constraints
	virtual void initDelta() {};//TODO défini seulement pour constraints
	inline void restoreDeltas();// restore delta indexes of literals of the body+
	void recordCurrentInstanceNDR();
	void restorePreviousInstanceNDR();
	bool isBlocked() {return _bodyMinus->isBlocked();};//require _bodyminus is ground
	inline virtual int getSccIndex();//return SCC index of head predicate
			// or, for a constraint rule, max of SCC indexes of body predicates

	       
  private:
       friend inline std::ostream& operator<<(std::ostream&, Rule&);
       
  protected:
       BasicLiteral* _head;
       Body* _body;
       Body* _bodyPlus; // positive body
       Body* _bodyMinus;// negative body
       variableSet _variables;
       Body _orderedBody;
       Body::iterator _currentLiteral; // of _orderedBody
       Body _recursiveBody; //recursive literals of _orderedBody
       Body::iterator _recursiveLiteral; // current recursive literal
       bool _solved; // true if each predicate that appears in body+ is already solved
       Rule* _clone; // definite clone of this rule

       Body::IteratorStack _recLit_stack;//back-track stack for current recursive literal _recursiveLiteral
       boolStack _solved_stack;//back-track stack for _solved property

       virtual std::ostream& put(std::ostream&);
       bool trueInstanceNonDefiniteRule(Literal* lit, Literal* recLit, bool matchFound);// search for a true supported and non-blocked instance of a non-definite rule
       statusEnum softInstanceNonDefiniteRule(Literal* lit, Literal* recLit, statusEnum matchFound);// search for a "soft" supported (true or mbt) and non-blocked instance of a non-definite rule

};

inline BasicLiteral* Rule::getHead(){
	return _head;
}
inline bool Rule::isDefinite(){
	return (_bodyMinus->empty());
}

void Rule::free(){
	for (variableSet::iterator i = _variables.begin(); i != _variables.end(); i++)
			(*i)->free();
}

inline Literal* Rule::firstLiteral(){// require _orderedBody not empty
	_currentLiteral = _orderedBody.begin();
	return *_currentLiteral;
}
inline Literal* Rule::nextLiteral(){
	if (++_currentLiteral != _orderedBody.end()){
		return *_currentLiteral;
	}
	else{ 
		_currentLiteral--;
		return NULL;
	}
}

inline Literal* Rule::firstRecursiveLiteral(){// require _recursiveBody not empty
	_recursiveLiteral = _recursiveBody.begin();
	return *_recursiveLiteral;
}
inline Literal* Rule::nextRecursiveLiteral(){
	if (++_recursiveLiteral != _recursiveBody.end())
		return *_recursiveLiteral;
	else{
		_recursiveLiteral--;
		return NULL;
	}
}
	
inline Literal* Rule::previousLiteral(){
	if (_currentLiteral != _orderedBody.begin())
		return *(--_currentLiteral);
	else 
		return NULL;
}

inline statusEnum Rule::previousStatus(){ // previous match status
	if (_currentLiteral != _orderedBody.begin()){
		Body::iterator it = _currentLiteral;
		return (*--it)->getStatus();
	}
	else 
		return TRUE_; // no previous status

}

void Rule::initMarks(markEnum mark){
	for (Body::iterator i = _orderedBody.begin(); i != _orderedBody.end(); i++)
		(*i)->setMark(mark);
}

void Rule::restoreDeltas(){// restore delta indexes of literals of the body+
	_bodyPlus->restoreDeltas();
}

int Rule::getSccIndex(){
//return SCC index of head predicate
	return getHead()->getSccIndex();
}
inline std::ostream& operator<<(std::ostream& os,Rule& r){
	return r.put(os);
}

inline std::ostream& operator<<(std::ostream& os, ruleSet& rs){
	for (ruleSet::iterator it = rs.begin(); it !=  rs.end() ; it++)
		os <<  *(*it);
	return os;
}
inline std::ostream& operator<<(std::ostream& os, ruleMultimap& rm){
	for (ruleMultimap::iterator it = rm.begin(); it !=  rm.end() ; it++)
		os << "(scc "<< (*it).first <<") "<< *(*it).second;
	return os;
}

#endif // _RULE_H_


