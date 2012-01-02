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
#include "normal_rule.h"
#include "constraint_rule.h"
#include "program.h"

NormalRule::NormalRule(BasicLiteral* a, Body* v, variableSet* s, Graph& g) : Rule(a,v,s,g) {
	Node* n = a->getPred()->getNode();
	for (Body::iterator it = v->begin(); it != v->end(); it++){
		if ((*it)->isNegativeLiteral()){
			n->addNegSucc((*it)->getPred()->getNode());
		}
		else if ((*it)->isPositiveLiteral()){
			n->addPosSucc((*it)->getPred()->getNode());
		}
	}
}
NormalRule::NormalRule(BasicLiteral* a, Body* v):Rule(a,v){
}

void NormalRule::evaluate(){ // evaluation of a definite non recursive rule
	initMarks(NON_MARKED);
	Literal* lit = firstLiteral();
	bool matchFound = lit->firstTrueMatch();
	do {
	   Literal* lit0 = lit;
	   if (matchFound)
		   if ((lit = nextLiteral())){ // NULL if it was the last one
			   matchFound = lit->firstTrueMatch();
		   }
		   else{
			   lit = lit0;
			   try {
				Argument* tuple = getHead()->applySubstitutionOnArgs();
			   	getHead()->addInstances(*tuple, TRUE_);
			  	delete tuple;
			   }
			   catch (OutOfRange&){ //out of range funcTerm or numConst
				// nothing to do
			   }
		  	   lit->free();
		     	   matchFound = lit->nextTrueMatch();
		   }
	   else if ((lit = previousLiteral())){ // NULL if it was the first one
		   lit->free();
		   matchFound = lit->nextTrueMatch();
	   }
	}while (lit);
}

void NormalRule::evaluateRec(){// evaluation of a definite recursive rule
	initMarks(NON_MARKED);//
	Literal* lit = firstLiteral();
	Literal* recLit = firstRecursiveLiteral();
	recLit->setMark(MARKED);
	bool matchFound = lit->firstTrueMatch();
	do {
	   Literal* lit0 = lit;
	   if (matchFound)
		   if ((lit = nextLiteral())){ // NULL if it was the last one
			   matchFound = lit->firstTrueMatch();
		   }
		   else{
			   lit = lit0;
			   try {
				Argument* tuple = getHead()->applySubstitutionOnArgs();
			   	getHead()->addInstances(*tuple, TRUE_);
			  	delete tuple;
			   }
			   catch (OutOfRange&){ //out of range funcTerm or numConst
				// nothing to do
			   }
			   lit->free();
			   matchFound = lit->nextTrueMatch();
		   }
	   else if ((lit = previousLiteral())){ // NULL if it was the first one
		   lit->free();
		   matchFound = lit->nextTrueMatch();
	        }
	   	else {
		   recLit->setMark(UNMARKED);	
		   if ((recLit = nextRecursiveLiteral())){
		   	lit = lit0; // first literal
		   	recLit->setMark(MARKED); // next recursive literal
			matchFound = lit->firstTrueMatch();
		   }
		}
	}while (lit);
//	std::cout<<"fin evaluateRec(rule)"<<std::endl;
}
void NormalRule::evaluate(atomsQueue& aq){ 
// soft evaluation of a definite rule containing "_not_p(t)" after predicate "p" has been set solved
   Literal* lit = NULL;
   Argument* tuple = NULL;
   try {
	initMarks(NON_MARKED);
	lit = firstLiteral();
	statusEnum matchStatus = lit->firstSoftMatch(TRUE_);
	do {
	   Literal* lit0 = lit;
	   if (matchStatus) // a match is found
		   if ((lit = nextLiteral())){ // NULL if it was the last one
			   matchStatus = lit->firstSoftMatch(matchStatus);
		   }
		   else{
			   lit = lit0;// last literal
			   try {
				tuple = getHead()->applySubstitutionOnArgs();
			   	getHead()->addInstances(*tuple, matchStatus, aq);			  		     delete tuple;
			   }
			   catch (OutOfRange&){ //out of range funcTerm or numConst
				// nothing to do
			   }
			   lit->free();
			   matchStatus = lit->nextSoftMatch(previousStatus());
		   }
	   else if ((lit = previousLiteral())){ // NULL if it was the first one
		   lit->free();
		   matchStatus = lit->nextSoftMatch(previousStatus());
	   }
	}while (lit);
   }
   catch (ContradictoryConclusion&){
	delete tuple;
	do {
		lit->free();
		lit = previousLiteral();
	}while(lit);
	throw; //exception relancée, récupérée par 
   }
}


void NormalRule::evaluateRec(atomsQueue& aq){// "soft" evaluation of a definite rule
// recursive literals are those whose body+ contains a predicate whose extension has been modified
   Literal* lit = NULL;
   Argument* tuple = NULL;
   try {
	initMarks(NON_MARKED);//
	lit = firstLiteral();
	Literal* recLit = firstRecursiveLiteral();
	recLit->setMark(MARKED);
	statusEnum matchStatus= lit->firstSoftMatch(TRUE_);
	do {
	   Literal* lit0 = lit;
	   if (matchStatus) // a match is found (TRUE_ or MBT_)
		   if ((lit = nextLiteral())){ // NULL if it was the last one
			   matchStatus = lit->firstSoftMatch(matchStatus);
		   }
		   else{
			   lit = lit0;
			   try {
				tuple = getHead()->applySubstitutionOnArgs();
			   	getHead()->addInstances(*tuple, matchStatus, aq);			  		     delete tuple;
			   }
			   catch (OutOfRange&){ //out of range funcTerm or numConst
				// nothing to do
			   }
			   lit->free();
			   matchStatus = lit->nextSoftMatch(previousStatus());
		   }
	   else if ((lit = previousLiteral())){ // NULL if it was the first one
		   lit->free();
		   matchStatus = lit->nextSoftMatch(previousStatus());
	        }
	   	else {
		   recLit->setMark(UNMARKED);	
		   if ((recLit = nextRecursiveLiteral())){
		   	lit = lit0; // first literal
		   	recLit->setMark(MARKED); // next recursive literal
			matchStatus = lit->firstSoftMatch(TRUE_);
		   }
		}
	}while (lit);
   }
   catch (ContradictoryConclusion&){
	delete tuple;
	do {
		lit->free();
		lit = previousLiteral();
	}while(lit);
	throw; //exception relancée, récupérée par program::propagate
   }
}

bool NormalRule::addHead(Program& p, Changes& changes){
// a substitution that makes the rule "true" supported and non-blocked is found
// apply substitution and add head to the model
// return false if head was already in or known to be out 
try{
    Argument* headTuple = getHead()->applySubstitutionOnArgs();	
    try{	
	bool added = getHead()->addInstances(*headTuple, TRUE_, changes.getAtomsQueue());
	delete headTuple;
	return added;
    }
    catch (ContradictoryConclusion&){
        // create an instance of the rule with current substitution, and prohibite it
	prohibiteCurrentInstanceOfNDRPbMbtDescenteGauche(p, changes); 
	delete headTuple;
	return false;
    }
}
catch (OutOfRange&){ // out of range funcTerm or numConst in headTuple
    	// nothing to do
    	return false;
}
}
bool NormalRule::addBodyMinus(Program& p, Changes& changes){
// a substitution that makes the "true" rule supported and non-blocked is found, head has been added to the model
// apply substitution and exclude body- from the model
// return false if contradiction : body- contains head
    try{	
    	_bodyMinus->applySubstitutionAndAddNonInstances(p, changes);
	return true;
    }
    catch (ContradictoryConclusion&){        
    	// create an instance of the rule with current substitution, and prohibite it
	prohibiteCurrentInstanceOfNDRPbMbtDescenteGauche(p, changes); 
	return false;
    }

}
std::ostream& NormalRule::put(std::ostream& os){
		return os << *_head << ":-" << *_body << "." << std::endl;
}
