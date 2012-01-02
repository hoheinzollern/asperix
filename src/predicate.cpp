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
#include "negated_predicate.h"
#include "graph.h"
#include <sstream>

// static members
mapPredicate Predicate::_mapPredicate;
Predicate* Predicate::_true_predicate = NULL;


Predicate* Predicate::new_Predicate(std::string* s, int n, Graph& graph){
       std::string sn;
       std::stringstream ss;
       ss << *s << "/" << n; // cast int2string
       ss >> sn;
       mapPredicate::iterator it = _mapPredicate.find(sn);
       if (it!=_mapPredicate.end())
	       return (*it).second;
       else{
	       Predicate* p = new Predicate(s,n);
	       _mapPredicate.insert(std::make_pair(sn,p));
	       p->_node = graph.new_Node(p);
	       // create the negated predicate
	       std::string name ="__not__" + *s;
	       Predicate* np = new NegatedPredicate(&name,n);
	       p->setNegatedPredicate(np);
	       np->setNegatedPredicate(p);
	       np->initDelta();
	       return p;
       }
}

Predicate* Predicate::new_true_predicate(Graph& g){
// create _true_predicate if it does not exist
	if (! _true_predicate){
		std::string name = "";
		_true_predicate = new Predicate(&name,0); // no name, arity 0
		_true_predicate->_node = g.new_Node(_true_predicate);
	       // create the negated predicate
	       name ="__not__";
	       Predicate* np = new NegatedPredicate(&name,0);
	       _true_predicate->setNegatedPredicate(np);
	       np->setNegatedPredicate(_true_predicate);
	       np->initDelta();
	       // true instance
		Argument tv; 
		_true_predicate->addTrueInstance(tv);// the only one instance is true
		_true_predicate->setSolved(true);    // no other instance can appear
	}
	return _true_predicate;
}
Predicate* Predicate::getTruePredicate(){
	return _true_predicate;
}

bool Predicate::initShow(bool defaultShow, stringSet& pset){
// initialize _show property of each predicate (if different from default = true)
	if (!defaultShow){ // set default to false	
       		for (mapPredicate::iterator it = _mapPredicate.begin(); it != _mapPredicate.end(); ++it)
			(*it).second->setShow(false);
	}
	// set exceptions to default value
	bool allExist = true;
	for (stringSet::iterator i = pset.begin(); i != pset.end(); ++i){
       		mapPredicate::iterator it = _mapPredicate.find(**i);
       		if (it!=_mapPredicate.end())
			(*it).second->setShow(!defaultShow);
		else
			allExist = false;
	}
	return allExist;
}
bool Predicate::existsMbtInstance(){
	mapPredicate::iterator it = _mapPredicate.begin();
	while (it != _mapPredicate.end() && (*it).second->getMbtNumber() == 0) it++;
	return (it != _mapPredicate.end());
}

void Predicate::delete_all(){
	for (mapPredicate::iterator it = _mapPredicate.begin(); it != _mapPredicate.end(); it++){
		delete (*it).second->getNegatedPredicate();
		delete (*it).second;	
	}
	_mapPredicate.clear();
	if (_true_predicate){
		delete _true_predicate->getNegatedPredicate();
		delete _true_predicate;
	}
}

void Predicate::printAllInstances(){
	for (mapPredicate::iterator it = _mapPredicate.begin(); it != _mapPredicate.end(); it++){
		(*it).second->printInstances();
		(*it).second->printNonInstances();
	}
}
void Predicate::prettyPrintAllInstances(){
	for (mapPredicate::iterator it = _mapPredicate.begin(); it != _mapPredicate.end(); it++){
		if ((*it).second->getShow())
			(*it).second->prettyPrintInstances();
	}
	std::cout<< std::endl;
}
void Predicate::prettyPrintAllNonInstances(){
	for (mapPredicate::iterator it = _mapPredicate.begin(); it != _mapPredicate.end(); it++){
		if ((*it).second->getShow())
			(*it).second->prettyPrintNonInstances();
	}
	std::cout<< std::endl;
}

void Predicate::recordExtensions(){
	for (mapPredicate::iterator it = _mapPredicate.begin(); it != _mapPredicate.end(); it++){
		(*it).second->recordExtension();
		(*it).second->recordNonExtension();
	}
}
void Predicate::restoreExtensions(){
	for (mapPredicate::iterator it = _mapPredicate.begin(); it != _mapPredicate.end(); it++){
		(*it).second->restoreExtension();
		(*it).second->restoreNonExtension();
	}
}
void Predicate::restoreExtensionsWithoutPop(){
	for (mapPredicate::iterator it = _mapPredicate.begin(); it != _mapPredicate.end(); it++){
		(*it).second->restoreExtensionWithoutPop();
		(*it).second->restoreNonExtensionWithoutPop();
	}
}


// true members

Predicate::Predicate(){
}

Predicate::Predicate(const std::string* s, int n):_name(*s), _arity(n),_show(true),_solved(false),
						_mbt_number(0),_node(NULL){
	_headDefiniteRules = new ruleSet();
	_headNonDefiniteRules = new ruleSet();
	_bodyPlusDefiniteRules = new ruleMultimap();
	_bodyPlusNonDefiniteRules = new ruleMultimap();
	_bodyPlusDefiniteConstraints = new ruleSet();
}

Predicate::~Predicate(){
	_instances.clear();
	_orderedInstances.clear();
	_headDefiniteRules->clear();
	delete _headDefiniteRules;
	_headNonDefiniteRules->clear();
	delete _headNonDefiniteRules;
	_bodyPlusDefiniteRules->clear();
	delete 	_bodyPlusDefiniteRules;
	_bodyPlusNonDefiniteRules->clear();
	delete 	_bodyPlusNonDefiniteRules;
	_bodyPlusDefiniteConstraints->clear();
	delete 	_bodyPlusDefiniteConstraints;
}



statusEnum Predicate::containInstance(Argument& tv){
// return status of tv if it is a known instance of the predicate
// else return 0
	std::map<Argument, statusEnum>::iterator it = _instances.find(tv);
	if (it != _instances.end()) // tv is in the extension
		return (*it).second; //status
	else
		return NO_;
}
bool Predicate::containNonInstance(Argument& tv){
// return true if tv is tv is a known non-instance of the predicate
	
	return _negated_predicate->containInstance(tv) != NO_;
}

statusEnum Predicate::containInstance(Argument& tv, int begin_i, int end_i){
// return status of tv if it is in _orderedInstance vector in [begin_i,end_i] index interval
// WARNING : tv can appear first with MBT and next with TRUE_MBT status, return the last one
	int i = end_i; // start at the end in order to find first the last status of tv
	while (i >= begin_i && *(_orderedInstances.at(i).first) != tv) i--;
	if (i >= begin_i)
		return (_orderedInstances.at(i).second); // status of tv
	else
		return NO_;
}

void Predicate::recordExtension(){ // record known extension (for back-track)
	_index_stack.push(getEndIndex());
}
void Predicate::recordNonExtension(){ // record known non_extension (for back-track)
	_negated_predicate->recordExtension();
}

void Predicate::restoreExtension(){ // restore previous extension
	restoreExtensionWithoutPop();
	_index_stack.pop();
}
void Predicate::restoreNonExtension(){ // restore previous non_extension
	_negated_predicate->restoreExtension();
}

void Predicate::restoreExtensionWithoutPop(){ // restore previous extension 
	int endi = _index_stack.top(); // previous end_index for _ordered_instances
	for (int i = getEndIndex(); i > endi; i--){
		std::pair<const Argument*, statusEnum> tv_s = _orderedInstances.at(i);
		switch (tv_s.second){ // status
		case MBT_ :
				_instances.erase(*tv_s.first);
				_mbt_number--;
				break;
		case TRUE_ : 
				_instances.erase(*tv_s.first);
				break;
		case TRUE_MBT_ : {std::map<Argument, statusEnum>::iterator it = _instances.find(*tv_s.first);
				(*it).second = MBT_;} // update status
				_mbt_number++;
				break;
		default : throw RuntimeExcept("instance with NO_ status in extension of a predicate");
		}
		_orderedInstances.pop_back();
	}
	_delta_begin = endi + 1;
	_delta_end = endi;
}
void Predicate::restoreNonExtensionWithoutPop(){ // restore previous non_extension
	_negated_predicate->restoreExtensionWithoutPop();
}
void Predicate::updateExtension(){ // update extension (for back-track)
	_index_stack.pop(); // pop old value
	_index_stack.push(getEndIndex()); // push new one
}
void Predicate::updateNonExtension(){ // update non_extension (for back-track)
	_negated_predicate->updateExtension();
}

void Predicate::printInstances(){
	std::cout<< *this <<"[solved : "<<_solved<<"]"<<_instances;
}
void Predicate::prettyPrintInstances(){
	for (std::map<Argument, statusEnum>::iterator it = _instances.begin(); it != _instances.end(); it++)
		std::cout <<  *this << (*it).first<<" ";
}
void Predicate::prettyPrintNonInstances(){
	_negated_predicate->prettyPrintInstances();
}
void Predicate::printNonInstances(){
	_negated_predicate->printInstances();
}


