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
#ifndef _AFFECT_LITERAL_H_
#define _AFFECT_LITERAL_H_

#include "literal.h"
/** AffectLiteral has form X = t 
 * where X is a Variable and t is a term that must be ground when literal is evaluated
 * AffectLiteral can only appear in the positive body of a rule
 * */
class AffectLiteral : public Literal 
{
  public:
       AffectLiteral(); 			  
       AffectLiteral(Variable* v, Term* t);
	virtual ~AffectLiteral();
       inline Predicate* getPred();//erreur - accès predicat de affectation
       inline  bool hasPredIn(Node::Set&) {return false;};
       bool nextTrueMatch();// idem for the next matching tuple
       statusEnum nextSoftMatch(statusEnum);// idem for the next matching tuple
       inline bool recursive(Node::Set&)	{return false;}; 
       				// true if atom predicate is in the current SCC
       				// i.e. the predicate is not already solved
       inline void setMark(markEnum m)	{_mark = m;};
       inline statusEnum isInstance();// no sense for affectation literal
       inline Literal* createInstance();// create a new literal by applying current substitution - no sense for affectation literal
       Literal* createPositiveClone(MapVariables& mapVar);
	inline void addInstances(Argument&, statusEnum);// no sense for affectation literal
	inline void addNonInstances(Argument&);// no sense for affectation literal
       inline bool addInstances(Argument&, statusEnum, atomsQueue&);// no sense for affectation literal
	inline bool addNonInstances(Argument& tuple, atomsQueue& naq);// no sense for affectation literal

  protected:
       Variable* _left_member;
       
       inline std::ostream& put(std::ostream& os){
	       return os << *_left_member << "=" << *_args->at(0);
       };
       bool firstTrueMatchBis();// try to match atom with some tuple of the extension 
       			 // of the predicate ; return true if a match is found
       statusEnum firstSoftMatchBis(statusEnum);
};

inline Predicate* AffectLiteral::getPred(){
// erreur - accès predicat de affectation
	throw RuntimeExcept("Acces to predicate of affectation literal");
};
inline statusEnum AffectLiteral::isInstance(){
// no sense for affect literal
	throw RuntimeExcept("Test instance for affectation literal");
}
inline Literal* AffectLiteral::createInstance(){
// create a new literal by applying current substitution - no sense for affectation literal
	throw RuntimeExcept("create instance for affectation literal");
}
inline void AffectLiteral::addInstances(Argument&, statusEnum){
// no sense for affect literal
	throw RuntimeExcept("Try to add tuple to affectation literal extension");
}
inline void AffectLiteral::addNonInstances(Argument&){
// no sense for affect literal
	throw RuntimeExcept("Try to add tuple to affectation literal non-extension");
}
inline bool AffectLiteral::addInstances(Argument&, statusEnum, atomsQueue&){
// no sense for affect literal
	throw RuntimeExcept("Try to add tuple to affectation literal extension");
}
inline bool AffectLiteral::addNonInstances(Argument&, atomsQueue&){
// no sense for affectation literal
throw RuntimeExcept("Try to add tuple to affectation literal non-extension");
}

#endif // _AFFECT_LITERAL_H_


