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
#ifndef _GRAPH_H_
#define _GRAPH_H_

#include "definition.h"
#include "predicate.h"
#include <string>
#include <iostream>
#include <stack>
#include <set>
#include <vector>
/**********************************************************************************
 * The dependency graph is a graph whose vertices are predicates nodes.
 * There is a positive edge from p1 to p2 iff there is a rule whose head is p1 
 * 							and whose body+ contains p2
 * ********************************************************************************/
class Program;
class Graph;

class Node 
{
  public:
       typedef std::set<Node*> Set;
	  
       Node(Predicate* p);
       virtual ~Node();
       inline Node::Set& getPosSucc()	{return _posSucc;}
       inline Node::Set& getNegSucc()	{return _negSucc;}
       inline void addPosSucc(Node* n) 	{_posSucc.insert(n);}
       inline void addNegSucc(Node* n)	{_negSucc.insert(n);}
       inline bool isVisited() 		{return _visited;} 
       inline void setOutStack() 	{_onStack = false;}
       void tarjan(Graph& g);
       void visitSuccessors(Node::Set& succ, Graph& graph);
       void addRules(ruleSet& recRules, ruleSet& exitRules, Node::Set& scc, Program& prog);
       void addDefiniteRulesContainingNotP(ruleMultimap& rmap);
       void addConstraintsContainingNotP(ruleSet& rset);
       inline bool existsMbtInstance();
       bool isLocallyStratified(int index);// true if all negative successors are outer the scc
       bool checkSolveness();
       inline bool isSolved()		{return _pred->isSolved();}
       inline void setSolved(bool b)		{_pred->setSolved(b);}
       inline void setDelta()		{_pred->setDelta();}
       inline void initDelta()		{_pred->initDelta();}
       inline bool emptyDelta()		{return _pred->emptyDelta();}
       inline void setSccIndex(int n)	{_sccIndex = n;}
       inline int getSccIndex()		{return _sccIndex;}
       inline bool inScc(int n)		{return _sccIndex == n;}
       inline void recordExtensions();// record known extensions and non-extensions of _pred (for back-track)
       inline void restoreExtensions();// restore previous extensions and non-extensions of _pred
       inline void restoreExtensionsWithoutPop();   
       inline void updateExtensions();
  private:
       friend std::ostream& operator<<(std::ostream&, Node&);

  protected:
       Predicate* _pred;
       Node::Set _posSucc;
       Node::Set _negSucc;
       int _visited; 
       int _lowLink;
       bool _onStack;
       int _sccIndex; // index of SCC in which the node is
};

bool Node::existsMbtInstance(){
// return true if the predicate (label of the node) has an instance with MBT status
	return (_pred->getMbtNumber() != 0);
}
void Node::recordExtensions(){
// record known extensions and non-extensions of _pred (for back-track)
	_pred->recordExtension();
	_pred->recordNonExtension();
}
void Node::restoreExtensions(){
// restore previous extensions and non-extensions of _pred
	_pred->restoreExtension();
	_pred->restoreNonExtension();
}
void Node::restoreExtensionsWithoutPop(){
	_pred->restoreExtensionWithoutPop();
	_pred->restoreNonExtensionWithoutPop();
}
void Node::updateExtensions(){
	_pred->updateExtension();
	_pred->updateNonExtension();
}

/*********************************************************************************/
/*********************************************************************************/
class Graph
{
  public:
	Graph();
	virtual ~Graph();
	Node* new_Node(Predicate*);  
	void computeSCC();
	inline int nextDate()		{return ++_date;}
	inline void pushStack(Node* n)	{_stack.push(n);}
	inline void popStack()		{_stack.pop();}
	inline Node* topStack()		{return _stack.top();}
	inline void addNode2scc(Node* n){_scc.insert(n);}
	inline void saveAndClearSCC()	{_sccVector.push_back(_scc);
					 setSccIndex(_sccVector.size()-1);
					 _scc.clear();}
	inline int numberOfScc()	{return _sccVector.size();}
	inline void setSccIndex(int n); 
	inline bool firstScc(int& index);
	inline bool nextScc(int& index);
	inline void getNodesFromScc(int index, Node::Set& ns);
	void getRulesFromScc(int index, ruleSet& recRules, ruleSet& exitRules, Program&);
	bool existsMbtInstance(int index);
	void addDefiniteRulesContainingNotP(int index, ruleMultimap& rmap);
	void addConstraintsContainingNotP(int index, ruleSet& rset);
	void initNonStratifiedSccVector();
	bool isLocallyStratified(int index);// true if scc does not contain internal negative arc
	inline int getFirstNonStratifiedScc();
	inline int getNextNonStratifiedScc();
	inline int getPreviousNonStratifiedScc();
	inline bool setFirstNonStratifiedScc(int& index);
	inline bool setNextNonStratifiedScc(int& index);
	inline bool setPreviousNonStratifiedScc(int& index);
	inline int getCurrentSccIndex();
	void setSolvedIfItIsTheCase(int index);
	void setSolved(bool b, int index);
	inline bool isSolved(int index); // return true if predicates of scc (index) are solved
	inline bool nextNonSolvedScc(int& index, int maxIndex); // search for the next non solved scc, less then maxIndex
	void setDelta(int index);
	void initDelta(int index);
	bool emptyDelta(int index);
	void recordExtensions(int sccIndex);// record known extensions and non-extensions of predicates whose scc is greater or equal than 'sccIndex' (for back-track)
	void restoreExtensions(int sccIndex);// restore previous extensions and non-extensions of predicates whose scc is greater or equal than 'sccIndex' 
	void restoreExtensionsWithoutPop(int sccIndex);
	void updateExtensions(int sccIndex);
	void restoreNonSolvedScc(int first, int last);

  private:
       friend inline std::ostream& operator<<(std::ostream&, Graph&);
	
  protected:
	Node::Set _nodes;
	std::stack<Node*> _stack;
	Node::Set _scc; // current SCC 
	std::vector<Node::Set> _sccVector; // all SCC
	std::vector<bool> _solved; // true at index 'i' iff scc 'i' is solved (stratified)
	int _date; //visit of a node 
	std::vector<int> _non_stratified_sccVector; // indexes in _sccVector of non stratified scc
	std::vector<int>::iterator _current_non_stratified_scc; // current iterator in _non_stratified_sccVector
};

inline bool Graph::firstScc(int& index){
	index = 0 ;
	return !(_sccVector.empty());
}

inline bool Graph::nextScc(int& index){
	index++;
	return (_sccVector.size() - index > 0);
}

inline void Graph::setSccIndex(int n){
	for (Node::Set::iterator it = _scc.begin(); it != _scc.end(); it++)
		(*it)->setSccIndex(n);
}

inline void Graph::getNodesFromScc(int index, Node::Set& ns){
	ns = _sccVector.at(index);
}
inline int Graph::getFirstNonStratifiedScc(){
// 
	if (_non_stratified_sccVector.begin() != _non_stratified_sccVector.end()){
		return getCurrentSccIndex();
	}
	else	return numberOfScc();
}

inline bool Graph::setFirstNonStratifiedScc(int& index){
// 
	_current_non_stratified_scc = _non_stratified_sccVector.begin() ;
	if (_current_non_stratified_scc != _non_stratified_sccVector.end()){
		index = getCurrentSccIndex();
		return true;
	}
	else	return false;
}
inline int Graph::getNextNonStratifiedScc(){
	_current_non_stratified_scc++;
	int scc;
	if (_current_non_stratified_scc != _non_stratified_sccVector.end()){
		scc = getCurrentSccIndex();
	}
	else{
		scc = numberOfScc();
	}
	_current_non_stratified_scc--;
	return scc;
}

inline bool Graph::setNextNonStratifiedScc(int& index){
	_current_non_stratified_scc++;
	if (_current_non_stratified_scc != _non_stratified_sccVector.end()){
		index = getCurrentSccIndex();
		return true;
	}
	else{
		_current_non_stratified_scc--;
		return false;
	}
}
inline int Graph::getPreviousNonStratifiedScc(){
	if (_current_non_stratified_scc == _non_stratified_sccVector.begin())
		return numberOfScc();
	else{
		_current_non_stratified_scc--;
		int index = getCurrentSccIndex();
		_current_non_stratified_scc++;
		return index;
	}
}

inline bool Graph::setPreviousNonStratifiedScc(int& index){
	if (_current_non_stratified_scc == _non_stratified_sccVector.begin())
		return false;
	else{
		_current_non_stratified_scc--;
		index = getCurrentSccIndex();
		return true;
	}
}
inline int Graph::getCurrentSccIndex(){
// return index in _sccVector of the current non stratified scc
	return *_current_non_stratified_scc;
}

bool Graph::isSolved(int index){
// return true if predicates of scc (index) are solved (stratified)
	return _solved.at(index);
}
bool Graph::nextNonSolvedScc(int& index, int maxIndex){
// search for the next non (initialy) solved scc, less than 'maxIndex'
	do {
		++index;
	} while (index < maxIndex && isSolved(index));
	return (index < maxIndex);
}
inline std::ostream& operator<<(std::ostream& os, Node::Set& ns){
	os << "{";
	for (Node::Set::iterator it = ns.begin(); it !=  ns.end() ; it++)
		os << (it==ns.begin() ? "" : ",") << *(*it);
	return os << "}";
}

inline std::ostream& operator<<(std::ostream& os , Graph& g){
	for (Node::Set::iterator it = g._nodes.begin(); it !=  g._nodes.end() ; it++)
		os << *(*it) << " + "<< (*it)->getPosSucc() << "-" << (*it)->getNegSucc() << std::endl;
	return os;
	
}

inline std::ostream& operator<<(std::ostream& os, std::vector<Node::Set>& v){
	os << "SCC : ";
	for (std::vector<Node::Set>::iterator it = v.begin(); it !=  v.end() ; it++)
		os << (it==v.begin() ? "" : " ; ") << (*it);
	return os << std::endl;
}


#endif // _GRAPH_H_


