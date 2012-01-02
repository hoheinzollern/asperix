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
#ifndef _RELATIONAL_LITERAL_H_
#define _RELATIONAL_LITERAL_H_

#include "literal.h"
/** RelationalLiteral has form t1 rel_op t2 
 * where t1 and t2 are terms that must be ground when literal is evaluated
 * */
class RelationalLiteral : public Literal // abstract class
{
  public:
       RelationalLiteral(); 			  
       RelationalLiteral(Term* t1, Term* t2);	
       inline Predicate* getPred()	{return NULL;};//TODO erreur - accès predicat de relation
       inline  bool hasPredIn(Node::Set&) {return false;};
       bool nextTrueMatch();// idem for the next matching tuple
       statusEnum nextSoftMatch(statusEnum);// idem for the next matching tuple
       virtual bool isTrueRelation(Argument* couple) = 0;
       inline bool recursive(Node::Set&)		{return false;}; 
       				// true if atom predicate is in the current SCC
       				// i.e. the predicate is not already solved
       inline void setMark(markEnum m)	{_mark = m;};
       inline statusEnum isInstance();// no sense for relational literal
       inline Literal* createInstance();// create a new literal by applying current substitution - no sense for relational literal
	inline void addInstances(Argument&, statusEnum); // no sense for relational literal
	inline void addNonInstances(Argument&); // no sense for relational literal
       inline bool addInstances(Argument&, statusEnum, atomsQueue&);// no sense for relational literal
       inline bool addNonInstances(Argument&, atomsQueue&);// no sense for relational literal

  protected:
       
       virtual std::ostream& put(std::ostream&) = 0;
       bool firstTrueMatchBis();// try to match atom with some tuple of the extension 
       			 // of the predicate ; return true if a match is found
	statusEnum firstSoftMatchBis(statusEnum);
};

class MemberLiteral : public RelationalLiteral 
{
  public:	  
       MemberLiteral(Term* t1, Term* t2):RelationalLiteral(t1,t2){};	
       bool isTrueRelation(Argument* couple); 
       Literal* createPositiveClone(MapVariables& mapVar);
  protected:
       inline std::ostream& put(std::ostream& os){
	       return os << *_args->at(0) << "@" << *_args->at(1);
       };
};

class NmemberLiteral : public RelationalLiteral 
{
  public:	  
       NmemberLiteral(Term* t1, Term* t2):RelationalLiteral(t1,t2){};	
       bool isTrueRelation(Argument* couple); 
       Literal* createPositiveClone(MapVariables& mapVar);
  protected:
       inline std::ostream& put(std::ostream& os){
	       return os << *_args->at(0) << "!@" << *_args->at(1);
       };
};

class EqLiteral : public RelationalLiteral 
{
  public:	  
       EqLiteral(Term* t1, Term* t2):RelationalLiteral(t1,t2){};	
       bool isTrueRelation(Argument* couple); 
       Literal* createPositiveClone(MapVariables& mapVar);
  protected:
       inline std::ostream& put(std::ostream& os){
	       return os << *_args->at(0) << "==" << *_args->at(1);
       };
};

class NeqLiteral : public RelationalLiteral 
{
  public:	  
       NeqLiteral(Term* t1, Term* t2):RelationalLiteral(t1,t2){};	
       bool isTrueRelation(Argument* couple);   
       Literal* createPositiveClone(MapVariables& mapVar);
  protected:
       inline std::ostream& put(std::ostream& os){
	       return os << *_args->at(0) << "!=" << *_args->at(1);
       };
};

class GeLiteral : public RelationalLiteral 
{
  public:	  
       GeLiteral(Term* t1, Term* t2):RelationalLiteral(t1,t2){};	
       bool isTrueRelation(Argument* couple);       
       Literal* createPositiveClone(MapVariables& mapVar);
  protected:
       inline std::ostream& put(std::ostream& os){
	       return os << *_args->at(0) << ">=" << *_args->at(1);
       };
};

class GtLiteral : public RelationalLiteral 
{
  public:	  
       GtLiteral(Term* t1, Term* t2):RelationalLiteral(t1,t2){};	
       bool isTrueRelation(Argument* couple);      
       Literal* createPositiveClone(MapVariables& mapVar);
  protected:
       inline std::ostream& put(std::ostream& os){
	       return os << *_args->at(0) << ">" << *_args->at(1);
       };
};

inline statusEnum RelationalLiteral::isInstance(){
// no sense for relational literal
	throw RuntimeExcept("Test instance for relational literal");
}
inline Literal* RelationalLiteral::createInstance(){
// create a new literal by applying current substitution - no sense for relational literal
	throw RuntimeExcept("create instance for relational literal");
}
inline void RelationalLiteral::addInstances(Argument&,statusEnum){
// no sense for relational literal
	throw RuntimeExcept("Try to add tuple to relational literal extension");
}
inline void RelationalLiteral::addNonInstances(Argument&){
// no sense for relational literal
	throw RuntimeExcept("Try to add tuple to relational literal non-extension");
}
inline bool RelationalLiteral::addInstances(Argument&, statusEnum, atomsQueue&){
// no sense for relational literal
	throw RuntimeExcept("Try to add tuple to relational literal extension");
}
inline bool RelationalLiteral::addNonInstances(Argument&, atomsQueue&){
// no sense for affectation literal
throw RuntimeExcept("Try to add tuple to relational literal non-extension");
}

#endif // _RELATIONAL_LITERAL_H_


