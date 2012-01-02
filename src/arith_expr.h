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
#ifndef _ARITH_EXPR_H_
#define _ARITH_EXPR_H_

#include "definition.h"
#include "operator.h"
#include "term.h"
#include <iostream>
#include <vector>

/* ArithExpr is arithmetic expression formed with NumConst, Variable, +,*,-,/, mod, abs et ()
 * it can appear only in positive body of a rule
 * it must be ground when evalualed
 * */
class ArithExpr : public Term // abstract class
{
  public:
	ArithExpr(opEnum op, Term* t2); // constructor
	ArithExpr(Operator* op, Term* t2);
	virtual ~ArithExpr();
	bool isArithExpr() {return true;}
	virtual void addVariables(variableSet&) = 0;// adds its own vars to vs
	inline virtual bool containsVar(Variable* v)=0;
	inline bool match(Term* t); // t is a ground term
	virtual Term* applySubstitution() = 0;
	virtual Term* getClone(MapVariables&) = 0;
	
	static void delete_all();
       
  private:
       virtual std::ostream& put(std::ostream&) const = 0;
       
  protected:
	static arithExprSet _arithExprSet;

       Operator* _operator;
       Term* _right_term;	       
};

inline bool ArithExpr::match(Term* t){ // t is a ground term
	try{
		return (applySubstitution() == t);
	}
	catch(OutOfRangeNumConst){
		return false;
	}
}

/************ Binary arithmetic expression ***********/
class BinaryArithExpr : public ArithExpr
{
  public:
	BinaryArithExpr(opEnum op, Term* t1, Term* t2); // constructor
	BinaryArithExpr(Operator* op, Term* t1, Term* t2);
	virtual ~BinaryArithExpr();
	inline void addVariables(variableSet&);// adds its own vars to vs
	inline virtual bool containsVar(Variable* v);
	inline Term* applySubstitution();
	inline Term* getClone(MapVariables&);
       
  private:
       inline std::ostream& put(std::ostream&) const;
       
  protected:
       Term* _left_term;
};
inline void BinaryArithExpr::addVariables(variableSet& vs){
	_left_term->addVariables(vs);
	_right_term->addVariables(vs);
}
inline bool  BinaryArithExpr::containsVar(Variable* v){
	return (_left_term->containsVar(v) || _right_term->containsVar(v));
}
inline Term* BinaryArithExpr::applySubstitution(){
	Term* lt = _left_term->applySubstitution();
	Term* rt =  _right_term->applySubstitution();
	if (lt->isNumConst() && rt->isNumConst())
		return _operator->apply(lt, rt);
	else
		throw RuntimeExcept("Non ground arithmetic expression when evaluating it");
}
inline Term* BinaryArithExpr::getClone(MapVariables& mapVar){
	Term* lt = _left_term->getClone(mapVar);
	Term* rt =  _right_term->getClone(mapVar);
	return (new BinaryArithExpr(_operator, lt, rt));
}
inline std::ostream& BinaryArithExpr::put(std::ostream& os) const {
	return os << *_left_term << *_operator << *_right_term;
}

/************ Unary arithmetic expression ***********/
class UnaryArithExpr : public ArithExpr
{
  public:
	UnaryArithExpr(opEnum op, Term* t); // constructor
	UnaryArithExpr(Operator* op, Term* t);
	virtual ~UnaryArithExpr();
	inline void addVariables(variableSet&);// adds its own vars to vs
	inline virtual bool containsVar(Variable* v);
	inline Term* applySubstitution();
	inline Term* getClone(MapVariables&);
	
  private:
       inline std::ostream& put(std::ostream&) const;      
};

inline void UnaryArithExpr::addVariables(variableSet& vs){
	_right_term->addVariables(vs);
}

inline bool UnaryArithExpr::containsVar(Variable* v){
	return (_right_term->containsVar(v));
}

inline Term* UnaryArithExpr::applySubstitution(){
	Term* rt =  _right_term->applySubstitution();
	if (rt->isNumConst())
		return _operator->apply(rt);
	else
		throw RuntimeExcept("Non ground arithmetic expression when evaluating it");
}
inline Term* UnaryArithExpr::getClone(MapVariables& mapVar){
	Term* rt =  _right_term->getClone(mapVar);
	return (new UnaryArithExpr(_operator, rt));
}
inline std::ostream& UnaryArithExpr::put(std::ostream& os) const {
	return os << *_operator << *_right_term;
}

#endif // _ARITH_EXPR_H_


