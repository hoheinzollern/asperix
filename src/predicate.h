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
#ifndef _PREDICATE_H_
#define _PREDICATE_H_

#include "definition.h"
#include "arguments.h"
#include <string>
#include <iostream>
#include <set>
#include <map>
#include <vector>

class Node;
class Graph;

class Predicate 
{
  public:
       Predicate();
       Predicate(const std::string*, int);
       virtual ~Predicate();
       inline bool addTrueInstance(Argument&);
	inline bool addMbtInstance(Argument&);
       inline bool addNonInstance(Argument&);
	inline bool addTrueInstance(Argument&, atomsQueue&);
	inline bool addMbtInstance(Argument&, atomsQueue&);
	inline bool addNonInstance(Argument&, atomsQueue&);
       virtual statusEnum containInstance(Argument&);
       bool containNonInstance(Argument&);
       virtual statusEnum containInstance(Argument& tv,int begin_i, int end_i);
       inline int getMbtNumber()	{return _mbt_number;};
       void printInstances();
       void prettyPrintInstances();
       void prettyPrintNonInstances();
	void printNonInstances();
       inline const Argument* firstTrueInstance(int& i, int begin_i, int end_i);
       inline const Argument* nextTrueInstance(int& i, int end_i);
       inline std::pair<const Argument*, statusEnum> firstSoftInstance(int& i, int begin_i, int end_i);
       inline std::pair<const Argument*, statusEnum> nextSoftInstance(int& i, int end_i);
       inline ruleSet* getHeadDefiniteRules();
       inline ruleSet* getHeadNonDefiniteRules();
       inline ruleMultimap* getBodyPlusDefiniteRules();
       inline ruleMultimap* getBodyPlusNonDefiniteRules();
       inline ruleSet* getBodyPlusDefiniteConstraints();
       inline void addHeadDefiniteRule(Rule*);
       inline void addHeadNonDefiniteRule(Rule*);
       inline void removeHeadNonDefiniteRule(Rule*);       
       inline void addBodyPlusDefiniteRule(int scc,Rule* r);
       inline void addBodyPlusNonDefiniteRule(int scc,Rule* r);
       inline void addBodyPlusDefiniteConstraint(Rule*);
       inline void removeBodyPlusDefiniteConstraint(Rule*);
       inline Node* getNode()	{return _node;}
       inline void setNode(Node* n)	{_node = n;}
       inline bool isSolved()	{return _solved;}
       inline void setShow(bool b)	{_show = b;}
       inline bool getShow()	{return _show;}
       virtual inline void setSolved(bool b)	{_solved = b; _negated_predicate->setSolved(b);}
       inline Predicate* getNegatedPredicate() {return _negated_predicate;}
       inline void setNegatedPredicate(Predicate* p) {_negated_predicate = p;}
       inline void setDelta();
       inline void initDelta();
       inline bool emptyDelta();
	inline void setDelta(int index);
       inline int getBeginIndex();
       inline int getEndIndex();
       inline int getDeltaBeginIndex();
       inline int getDeltaEndIndex();
       void recordExtension(); // record known extension (for back-track)
       void recordNonExtension();
       void restoreExtensionWithoutPop(); // restore previous extension 
       void restoreNonExtensionWithoutPop();
       void restoreExtension(); // restore previous extension 
       void restoreNonExtension();
       void updateExtension();
       void updateNonExtension();
       
       static Predicate* new_Predicate(std::string*, int, Graph&);
	static Predicate* new_true_predicate(Graph&); 
	static Predicate* getTruePredicate(); 
	static bool initShow(bool defaultShow, stringSet& pset);
	static bool existsMbtInstance();
       static void delete_all(); //delete all predicates
       static void printAllInstances();
       static void prettyPrintAllInstances();
       static void prettyPrintAllNonInstances();
       static void recordExtensions(); // record all known extensions and non-extensions(for back-track)
       static void restoreExtensions(); // restore all previous extensions and non-extensions
	static void restoreExtensionsWithoutPop();

  private:
       friend inline std::ostream& operator<<(std::ostream&, Predicate&);
       
  protected:
       static mapPredicate _mapPredicate;
       static Predicate* _true_predicate;
      
       const std::string _name;
       int _arity;
       bool _show; 
       bool _solved;
       Predicate* _negated_predicate; // corresponding "not_p" predicate for strong negation
       std::map<Argument, statusEnum> _instances; // extension of the predicate (a tuple is TRUE_, TRU_MBT_, or MBT_)
       std::vector< std::pair<const Argument*, statusEnum> > _orderedInstances; // ordered extension (a tuple is TRUE_, TRUE_MBT_, or MBT_)
       int _mbt_number; // number of MBT tuples in the extension
       int _delta_begin;
       int _delta_end;
       intStack _index_stack; // back-track stack for _instances end index
       ruleSet* _headDefiniteRules; // definite rules that define the predicate
       ruleSet* _headNonDefiniteRules; // normal (but not definite) rules that define the predicate
       ruleMultimap* _bodyPlusDefiniteRules; // definite rules in which predicate appears in body+
       ruleMultimap* _bodyPlusNonDefiniteRules; // normal (but not definite) rules in which predicate appears in body+ 
	ruleSet* _bodyPlusDefiniteConstraints; // constraint rules (with empty body-) in which predicate appears in body+ 
       Node* _node;	// the corresponding node in the dependance graph
};

inline std::ostream& operator<<(std::ostream& os, std::map<Argument, statusEnum>& m){
	os << "{";
	for (std::map<Argument, statusEnum>::iterator it = m.begin(); it != m.end(); it++)
		os << (it==m.begin() ? "" : ",") << (*it).first << (*it).second;
	return os << "}" << std::endl;
}


inline ruleSet* Predicate::getHeadDefiniteRules(){
	return _headDefiniteRules;
}
inline ruleSet* Predicate::getHeadNonDefiniteRules(){
	return _headNonDefiniteRules;
}
inline ruleMultimap* Predicate::getBodyPlusDefiniteRules(){
	return _bodyPlusDefiniteRules;
}
inline ruleMultimap* Predicate::getBodyPlusNonDefiniteRules(){
	return _bodyPlusNonDefiniteRules;
}
ruleSet* Predicate::getBodyPlusDefiniteConstraints(){
	return _bodyPlusDefiniteConstraints;
}

inline void Predicate::addHeadDefiniteRule(Rule* r){
	_headDefiniteRules->insert(r);
}
inline void Predicate::addHeadNonDefiniteRule(Rule* r){
	_headNonDefiniteRules->insert(r);
}
inline void Predicate::removeHeadNonDefiniteRule(Rule* r){
	_headNonDefiniteRules->erase(r);
}

void Predicate::addBodyPlusDefiniteRule(int scc, Rule* r){
	_bodyPlusDefiniteRules->insert(std::make_pair(scc, r));
}

void Predicate::addBodyPlusNonDefiniteRule(int scc,Rule* r){
	_bodyPlusNonDefiniteRules->insert(std::make_pair(scc, r));
}
void Predicate::addBodyPlusDefiniteConstraint(Rule* r){
	_bodyPlusDefiniteConstraints->insert(r);
}
void Predicate::removeBodyPlusDefiniteConstraint(Rule* r){
	_bodyPlusDefiniteConstraints->erase(r);
}

inline bool Predicate::addNonInstance(Argument& tv){
	return _negated_predicate->addTrueInstance(tv);
}
bool Predicate::addTrueInstance(Argument& tv){
// add (or update) tv with TRUE_ status to extension of the predicate
// return true if tv has been added or modified (tv was not already in the extension, or with status MBT_)
	std::map<Argument, statusEnum>::iterator it = _instances.find(tv);
	if (it != _instances.end()){ // tv was already in the extension
		if ((*it).second == MBT_){ // with status MBT
			(*it).second = TRUE_MBT_;
			_mbt_number--;
			_orderedInstances.push_back(std::make_pair(&(*it).first, TRUE_MBT_)); 
			return true;
		}
		else	return false;
	}
	else {
		if (containNonInstance(tv)){// tv is known to be out of the extension
			throw ContradictoryConclusion();
		}else { 
			std::pair<std::map<Argument, statusEnum>::iterator, bool> i_b = _instances.insert(std::make_pair(tv,TRUE_));
			_orderedInstances.push_back(std::make_pair(&(*i_b.first).first, TRUE_));
			return true;
		}
	}
}
bool Predicate::addMbtInstance(Argument& tv){
// add tv with MBT_ status to extension of the predicate
// return true if tv has been added (tv was not already in the extension)
	std::map<Argument, statusEnum>::iterator it = _instances.find(tv);
	if (it != _instances.end()){ // tv was already in the extension
		return false;
	}
	else {
		if (containNonInstance(tv)){// tv is known to be out of the extension
			throw ContradictoryConclusion();
		}
		else {
			std::pair<std::map<Argument, statusEnum>::iterator, bool> i_b = _instances.insert(std::make_pair(tv,MBT_));
			_orderedInstances.push_back(std::make_pair(&(*i_b.first).first, MBT_));
			_mbt_number++;
			return true;
		}
	}
}

inline bool Predicate::addTrueInstance(Argument& tv, atomsQueue& aq){
// return true if tv has been added or modified (i.e. it was not already in the extension or with status MBT)
// throw exception "ContradictoryConclusion" if tv was known to be out of the extension
	bool added = addTrueInstance(tv);
	if (added) 
		aq.push(std::make_pair(this, _orderedInstances.size()-1));
	return added;
}
inline bool Predicate::addMbtInstance(Argument& tv, atomsQueue& aq){
// return true if tv has been added (i.e. it was not already in the extension)
// throw exception "ContradictoryConclusion" if tv was known to be out of the extension
	bool added = addMbtInstance(tv);
	if (added) 
		aq.push(std::make_pair(this, _orderedInstances.size()-1));
	return added;
}

inline bool Predicate::addNonInstance(Argument& tv, atomsQueue& naq){
//add tv as non-instance of the predicate, and push it in naq queue
// return true if tv has been added
// throw exception "ContradictoryConclusion" if tv was known to be in the extension
	return _negated_predicate->addTrueInstance(tv,naq);
}
inline  const Argument* Predicate::firstTrueInstance(int& i, int begin_i, int end_i){
	i = begin_i;
	while (i <= end_i && _orderedInstances.at(i).second == MBT_) i++;
	if (i <= end_i)
		return _orderedInstances.at(i).first;
	else 
		return NULL;
}
inline const Argument* Predicate::nextTrueInstance(int& i, int end_i){
	i++;
	while (i <= end_i && _orderedInstances.at(i).second == MBT_) i++;
	if (i <= end_i) 
		return _orderedInstances.at(i).first;
	else 
		return NULL;
}
inline  std::pair<const Argument*, statusEnum> Predicate::firstSoftInstance(int& i, int begin_i, int end_i){
	i = begin_i;
	if (i <= end_i) 
		return _orderedInstances.at(i);
	else {
		const Argument* p = NULL;
		return (std::make_pair(p,NO_));
	}
}
inline std::pair<const Argument*, statusEnum> Predicate::nextSoftInstance(int& i, int end_i){
	i++;
	if (i <= end_i) 
		return _orderedInstances.at(i);
	else {
		const Argument* p = NULL;
		return std::make_pair(p,NO_);
	}
}

inline void Predicate::setDelta(){
	_delta_begin = _delta_end + 1;
	_delta_end = _orderedInstances.size() - 1;
}
inline void Predicate::initDelta(){
	_delta_begin = 0; //_orderedInstances.size();
	_delta_end = _orderedInstances.size() - 1;
}
inline bool Predicate::emptyDelta(){
	return (_delta_begin > _delta_end);
}

inline void Predicate::setDelta(int index){
	_delta_begin = index; 
	_delta_end = index;
}

inline int Predicate::getBeginIndex(){
	return 0;
}
inline int Predicate::getEndIndex(){
	return (_orderedInstances.size() - 1);
}
inline int Predicate::getDeltaBeginIndex(){
	return _delta_begin;
}
inline int Predicate::getDeltaEndIndex(){
	return _delta_end;
}

inline std::ostream& operator<<(std::ostream& os, Predicate& p){
	return os << p._name ;
}



#endif // _PREDICATE_H_


