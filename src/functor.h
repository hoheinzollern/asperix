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
#ifndef _FUNCTOR_H_
#define _FUNCTOR_H_

#include "definition.h"
#include "symb_const.h"


class Functor : public SymbConst
{
  public:	  
       Functor();
       Functor(const std::string*, int);
       virtual ~Functor();
       FuncTerm* existGroundTerm(Argument* a);// return FuncTerm corresponding to argument *a if it exists
	void insertGroundTerm(Argument* a, FuncTerm* t); // insert t in _mapFuncTerm
	void insertNonGroundTerm(FuncTerm* t); // insert t in _funcTermSet
       static Functor* new_Functor(std::string* name, int n);

  protected:
       int _arity;
       mapFuncTerm _mapFuncTerm; // ground FuncTerms
       funcTermSet _funcTermSet; // FuncTerms with variables
};


#endif // _FUNCTOR_H_


