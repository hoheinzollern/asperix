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
#ifndef _OPERATOR_H_
#define _OPERATOR_H_

#include "definition.h"
#include "num_const.h"
#include <iostream>
#include <cstdlib>

class Operator // abstract class
{
  public:    
	Operator(opEnum oper);
	virtual ~Operator();
	virtual inline NumConst* apply(Term* t1, Term* t2);
	virtual inline NumConst* apply(Term* t);
       static Operator* new_Operator(opEnum oper);
       static void delete_all();
  private:
       static mapOperator _mapOperator;
       
       friend inline std::ostream& operator<<(std::ostream& os, Operator& op){return op.put(os);};
       virtual std::ostream& put(std::ostream&) const = 0;
       
  protected:
       opEnum  _oper;      
};

NumConst* Operator::apply(Term* , Term* ){// default method
	throw RuntimeExcept("can not apply non binary operator to 2 arguments");
}
NumConst* Operator::apply(Term* ){// default method
	throw RuntimeExcept("can not apply non unary operator to one argument");
}

class PlusOperator : public Operator
{
  public:
	PlusOperator(opEnum oper);  

	inline NumConst* apply(Term* t1, Term* t2){ return NumConst::new_NumConst(t1->getIntValue() + t2->getIntValue());};
  private:
	inline std::ostream& put(std::ostream& os) const{ return os <<"+";};
};

class MinusOperator : public Operator
{
  public:
	MinusOperator(opEnum oper);  
  
	inline NumConst* apply(Term* t1, Term* t2){ return NumConst::new_NumConst(t1->getIntValue() - t2->getIntValue());};
  private:
	inline std::ostream& put(std::ostream& os) const{ return os <<"-";};	
};

class MultOperator : public Operator
{
  public:
	MultOperator(opEnum oper);  

	inline NumConst* apply(Term* t1, Term* t2){ return NumConst::new_NumConst(t1->getIntValue() * t2->getIntValue());};
  private:
	inline std::ostream& put(std::ostream& os) const{ return os <<"*";};	
};

class DivOperator : public Operator
{
  public:
	DivOperator(opEnum oper);  

	inline NumConst* apply(Term* t1, Term* t2){ return NumConst::new_NumConst(t1->getIntValue() / t2->getIntValue());};//TODO division par 0
  private:
	inline std::ostream& put(std::ostream& os) const{ return os <<"/";};	
};

class ModOperator : public Operator
{
  public:
	ModOperator(opEnum oper);  

	inline NumConst* apply(Term* t1, Term* t2){ return NumConst::new_NumConst(t1->getIntValue() % t2->getIntValue());};//TODO division par 0
  private:
	inline std::ostream& put(std::ostream& os) const{ return os <<" mod ";};	
};

class MaxOperator : public Operator
{
 public:
  MaxOperator(opEnum oper);

  inline NumConst* apply(Term* t1, Term* t2){
    int a = t1->getIntValue(), b = t2->getIntValue();
    if (b > a) a = b;
    return NumConst::new_NumConst( a );
  }
 private:
  inline std::ostream& put(std::ostream &os) const { return os << " max "; };
};

/********** Unary operators ***************/

class AbsOperator : public Operator
{
  public:
	AbsOperator(opEnum oper);  

	inline NumConst* apply(Term* t){ return NumConst::new_NumConst(std::abs(t->getIntValue()));};
  private:
	inline std::ostream& put(std::ostream& os) const{ return os <<"abs ";};	
};
#endif // _OPERATOR_H_


