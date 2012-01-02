/* *************************************************************************
 * Copyright (C) 2008 Claire Lefèvre, Pascal Nicolas
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
#ifndef _DEFINITION_H_
#define _DEFINITION_H_

#include "exceptions.h"
#include <string>
#include <map>
#include <set>
#include <vector>
#include <queue>
#include <stack>

class Literal;
class Term;
class SymbConst;
class NumConst;
class Rule;
class Predicate;
class Operator;
class Variable;
class RangeTerm;
class Argument;
class FuncTerm;
class ArithExpr;
class Changes;

//using namespace std;

struct eqstr
{
  bool operator()(const std::string s1, const std::string s2) const
  {
    return s1.compare(s2) == 0;
  }
};

struct ltstr
{
  bool operator()(const std::string s1, const std::string s2) const
  {
    return s1.compare(s2) < 0;
  }
};
struct ltrule
{
  bool operator()(Rule* r1, Rule* r2)
  {
    return r1 < r2;
  }
};

typedef enum {NON_MARKED, MARKED, UNMARKED} markEnum;
typedef enum {PLUS, MINUS, MULT, DIV, MOD, MAX, ABS} opEnum;
typedef enum {NO_ = 0, MBT_, TRUE_, TRUE_MBT_} statusEnum;// status of a tuple w.r.t. a predicate extension
		// not in the extension (NO_), or in the extension with status :
		// "must be true" (true without support : MBT_), true with support (TRUE_)
		// or true with support after being MBT (TRUE_MBT_)

typedef  std::map<const std::string, SymbConst*,  ltstr> mapSymbConst;
typedef  std::map<int, NumConst*, std::less<int> > mapNumConst;
typedef  std::map<const std::string, Predicate*, ltstr> mapPredicate;
typedef  std::map<opEnum, Operator*, std::less<int> > mapOperator;
typedef  std::map<std::pair<Term*,Term*>, RangeTerm*> mapRangeTerm;
typedef std::map<std::string, Variable*, ltstr> MapStrVar;
typedef std::map<Variable*, Variable*> MapVariables;
typedef std::map<Argument,FuncTerm*> mapFuncTerm;

typedef std::multimap<int, Rule*> ruleMultimap;

typedef std::set<Rule*> ruleSet;
typedef std::set<Variable*> variableSet;
typedef std::set<FuncTerm*> funcTermSet;
typedef std::set<ArithExpr*> arithExprSet;
typedef std::set<std::string*> stringSet;

typedef std::pair<Predicate*,int> atomType;
typedef std::queue<atomType> atomsQueue;

typedef std::pair<Changes*, bool> chanboolPair;
typedef std::stack<chanboolPair> chanboolStack;



typedef std::stack<int> intStack;
typedef std::stack<bool> boolStack;
typedef std::stack<markEnum> markStack;
typedef std::stack<Term*> termStack;
typedef std::stack<statusEnum> statusStack;
#endif //_DEFINITION_H_
