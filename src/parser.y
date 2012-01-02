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
/* programmes logiques normaux avec variables : la syntaxe d'un programme */ 
%{
//#include <stdlib.h>
#include <iostream>
#include <sstream>
#include <string>
#include <map>
#include "definition.h"
#include "term.h"
#include "variable.h"
#include "num_const.h"
#include "symb_const.h"
#include "operator.h"
#include "arith_expr.h"
#include "range_term.h"
#include "arguments.h"
#include "func_term.h"
#include "literal.h"
#include "basic_literal.h"
#include "positive_literal.h"
#include "negative_literal.h"
#include "relational_literal.h"
#include "affect_literal.h"
#include "range_literal.h"
#include "predicate.h"
#include "rule.h"
#include "fact_rule.h"
#include "constraint_rule.h"
#include "normal_rule.h"
#include "program.h"
#include "graph.h"

#define YYERROR_VERBOSE
void yyerror(std::string mess);
Program* prog = new Program();
Graph& graph = prog->getGraph();
Rule* rule;
FactRule* fact;
ConstraintRule* constraint;
MapStrVar* map = new MapStrVar();
variableSet* set = new variableSet();
Literal::Vector litVect;
bool defaultShow = true; 
stringSet hideSet;
stringSet showSet;
int yylex();
extern int yylineno;
int nregle;
%}

%union{
  std::string* chaine;
  int num;
  opEnum oper;
  Term* pterm;
  Variable* pvar;
  SymbConst* pconst;
  Literal* pliteral;
  BasicLiteral* pbaslit;
  Predicate* ppred;
  Body* pBody;
  Argument* tVect;
}  


%token NOT SI PP EQ NEQ GE GT LE LT AFFECT HIDE SHOW IN NIN
%token<chaine> CONST_SYMB CONST_SYMB_NEG VARIABLE
%token<num> CONST_NUM  
%token<oper> PLUS_OP MINUS_OP MULT_OP DIV_OP MOD_OP MAX_OP ABS_OP

%type<tVect>  liste_termes  liste_termes_etendu liste_range_termes
%type<pterm> terme terme_etendu constant constant_num expr_num expr_arith expr_arith_bis range range_bound  fonction fonction_etendu
%type<pvar> variable 
%type<pconst> constant_symb
%type<pliteral> litteral expr_bool affectation atome_etendu 
%type<pbaslit> tete atome_tete atome_neg range_atome 
%type<chaine>  predicat_arite
%type<pBody> corps 

%left PLUS_OP MINUS_OP
%left MULT_OP DIV_OP MOD_OP MAX_OP

%%

prog :
	/* rien */
	| prog regle 
	| prog commande
	;
regle :
      	tete '.'		{ try{nregle++;
				      fact = new FactRule($1,set);    
				      prog->addFactRule(fact);
				  }
				  catch(ContradictoryConclusion&){
				  	throw ;
				  }
				  catch(LogicExcept& e){
				 	std::cerr<<e.what()<<"\n\t(=>rule n° "<< nregle<<" - line "<< yylineno <<")"<<std::endl;
			 	      	yynerrs++; 
					set->clear();map->clear();
				   }
				}
	| tete SI corps '.'	{ try{nregle++;
				      if ($3->containsNotLiteral($1)){ //body- contains head literal(resp. body+ if head is negative)
						constraint = new ConstraintRule($3, set, graph);
				      		prog->addConstraintRule(constraint);
				      } 
				      else{
				      		rule = new NormalRule($1, $3, set, graph);
				      		if ($1->isNegativeLiteral())
							prog->addDeductiveConstraint(rule);
						else
							prog->addNormalRule(rule);
				      }
				  }
				  catch(LogicExcept& e){
				 	std::cerr<<e.what()<<"\n\t(=>rule n° "<< nregle<<" - line "<< yylineno <<")"<<std::endl;
			 	      	yynerrs++; 
				   }
				   set->clear();map->clear();
				}
	| SI corps '.'		{ try{nregle++;
				      constraint = new ConstraintRule($2, set, graph);
				      prog->addConstraintRule(constraint);
				  }
				  catch(LogicExcept& e){
				 	std::cerr<<e.what()<<"\n\t(=>rule n° "<< nregle<<" - line "<< yylineno <<")"<<std::endl;
			 	      	yynerrs++; 
				   }
				   set->clear();map->clear();
				}
        | error	'.'	{nregle++;map->clear();
	                 std::cerr<<"\t(=>rule n° "<< nregle<<" - line "<< yylineno <<")"<<std::endl;
			 yyerrok;}
	;
tete :
	atome_tete	{$$ = $1;}
	| range_atome	{$$ = $1;}
	| NOT atome_tete {$$ = new NegativeLiteral(*static_cast<NegativeLiteral*>($2));
			 delete $2;}
	;
corps :
	litteral		{ $$ = new Body();
				  for (Literal::Vector::iterator i = litVect.begin(); i != litVect.end(); i++)
					$$->addLiteral(*i);
				  litVect.clear();
				  $$->addLiteral($1);}
	| corps ',' litteral	{ for (Literal::Vector::iterator i = litVect.begin(); i != litVect.end(); i++)
					$1->addLiteral(*i);
				  litVect.clear();
				  $1->addLiteral($3);
				  $$ = $1;}
	;
	;
litteral :
	atome_etendu		{$$ = $1; 
				 }
	| NOT atome_neg	{$$ = new NegativeLiteral(*static_cast<NegativeLiteral*>($2)); 

			 delete $2;
			 }
	;
atome_tete : // atome sans expressions relationnelles ni affectation (tête)
	CONST_SYMB		{$$ = new BasicLiteral($1, NULL, graph);
				 delete $1;}
	| CONST_SYMB '(' liste_termes ')'
				{ $$ = new BasicLiteral($1, $3, graph);
				  delete $1;}
	;
atome_neg : // atome sans expressions relationnelles ni affectation (corps-)
	CONST_SYMB		{$$ = new BasicLiteral($1, NULL, graph);
				 delete $1;}
	| CONST_SYMB '(' liste_termes_etendu ')'
				{ $$ = new BasicLiteral($1, $3, graph);
				  delete $1;}
	;
atome_etendu : // atome avec expressions relationnelles et affectations.(corps+)
	CONST_SYMB		{$$ = new PositiveLiteral($1, NULL, graph);
				 delete $1;}
	| CONST_SYMB '(' liste_termes_etendu ')'
				{ $$ = new PositiveLiteral($1, $3, graph);
				  delete $1;}
	| expr_bool	{$$ = $1;}
	| affectation	{$$ = $1;}
	;	    
liste_termes :
	terme			{$$=new Argument();
				 $$->push_back($1);}
	| liste_termes ',' terme  { $1->push_back($3);
				    $$ = $1;}
	;
terme : 
	constant		{$$=$1;}
	| variable		{$$=$1;}	
	| expr_arith		{$$=$1;}	
	| fonction		{$$=$1;}
 	;
constant :
	constant_symb		{$$= $1;}
	| constant_num		{$$= $1;}
	;

fonction :	
	 CONST_SYMB '(' liste_termes ')'
				{try{ $$= FuncTerm::new_FuncTerm($1, $3);
     				     }
     				 catch(OutOfRangeFuncTerm){
				      std::cerr<<"too deep functional term "<<std::endl;
			 	      yynerrs++; YYERROR;
				  }
				}

	;

liste_termes_etendu : // idem liste_termes mais avec traitement spécial des expressions arithmétiques (sorties des atomes et mises sous forme d'affectations)
	terme_etendu			{$$=new Argument();
					 $$->push_back($1);}
	| liste_termes_etendu ',' terme_etendu  { $1->push_back($3);
				    		  $$ = $1;}
	;
terme_etendu : 
	constant		{$$=$1;}
	| variable		{$$=$1;}
	| expr_arith		{Variable* v = new Variable(NULL);
				 set->insert(v);
				 litVect.push_back(new AffectLiteral(v, $1)); // literal v=$1
				 $$ = v;}	
	| fonction_etendu	{$$=$1;}
 	;
fonction_etendu :	
	 CONST_SYMB '(' liste_termes_etendu ')'
				{try{ $$= FuncTerm::new_FuncTerm($1, $3);
     				     }
     				 catch(OutOfRangeFuncTerm){
				      std::cerr<<"too deep functional term "<<std::endl;
			 	      yynerrs++; YYERROR;
				  }
				}

	;

range_atome :
	CONST_SYMB '(' liste_range_termes ')'
				{ $$ = new RangeLiteral($1, $3, graph);
				  delete $1;
				} 
	;

liste_range_termes :
	range				{$$=new Argument();
				 	 $$->push_back($1);}
	| liste_range_termes ',' range  { $1->push_back($3);
				   	  $$ = $1;}
	;
range :
      range_bound PP range_bound	{ $$ = RangeTerm::new_RangeTerm($1,$3);}
      ;
range_bound :
     constant_num		{$$= $1;}
     | variable			{$$ = $1;}
     ;

expr_bool :
	expr_num EQ expr_num			{$$ = new EqLiteral($1, $3);}
	| expr_num NEQ expr_num			{$$ = new NeqLiteral($1, $3);}
	| expr_num GE expr_num			{$$ = new GeLiteral($1, $3);}
	| expr_num GT expr_num			{$$ = new GtLiteral($1, $3);}
	| expr_num LE expr_num			{$$ = new GeLiteral($3, $1);}
	| expr_num LT expr_num			{$$ = new GtLiteral($3, $1);}
	| constant_symb EQ constant_symb	{$$ = new EqLiteral($1, $3);}
	| constant_symb NEQ constant_symb	{$$ = new NeqLiteral($1, $3);}
	| constant_symb GE constant_symb	{$$ = new GeLiteral($1, $3);}
	| constant_symb GT constant_symb	{$$ = new GtLiteral($1, $3);}
	| constant_symb LE constant_symb	{$$ = new GeLiteral($3, $1);}
	| constant_symb LT constant_symb	{$$ = new GtLiteral($3, $1);}
	| variable EQ expr_num			{$$ = new EqLiteral($1, $3);}
	| variable EQ constant_symb		{$$ = new EqLiteral($1, $3);}
	| variable EQ fonction			{$$ = new EqLiteral($1, $3);}
	| variable EQ variable			{$$ = new EqLiteral($1, $3);}
	| variable NEQ expr_num			{$$ = new NeqLiteral($1, $3);}
	| variable NEQ constant_symb		{$$ = new NeqLiteral($1, $3);}
	| variable NEQ fonction			{$$ = new NeqLiteral($1, $3);}
	| variable NEQ variable			{$$ = new NeqLiteral($1, $3);}
	| variable GE expr_num			{$$ = new GeLiteral($1, $3);}
	| variable GE constant_symb		{$$ = new GeLiteral($1, $3);}
	| variable GE variable			{$$ = new GeLiteral($1, $3);}
	| variable GT expr_num			{$$ = new GtLiteral($1, $3);}
	| variable GT constant_symb		{$$ = new GtLiteral($1, $3);}
	| variable GT variable			{$$ = new GtLiteral($1, $3);}
	| variable LE expr_num			{$$ = new GeLiteral($3, $1);}
	| variable LE constant_symb		{$$ = new GeLiteral($3, $1);}
	| variable LE variable			{$$ = new GeLiteral($3, $1);}
	| variable LT expr_num			{$$ = new GtLiteral($3, $1);}
	| variable LT constant_symb		{$$ = new GtLiteral($3, $1);}
	| variable LT variable			{$$ = new GtLiteral($3, $1);}
	| expr_num EQ variable 			{$$ = new EqLiteral($1, $3);}
	| constant_symb EQ variable		{$$ = new EqLiteral($1, $3);}
	| fonction_etendu EQ variable		{$$ = new EqLiteral($1, $3);}
	| fonction_etendu EQ fonction		{$$ = new EqLiteral($1, $3);}
	| expr_num NEQ variable 		{$$ = new NeqLiteral($1, $3);}
	| constant_symb	NEQ variable 		{$$ = new NeqLiteral($1, $3);}
	| fonction_etendu NEQ variable		{$$ = new NeqLiteral($1, $3);}
	| fonction_etendu NEQ fonction		{$$ = new NeqLiteral($1, $3);}
	| expr_num GE variable  		{$$ = new GeLiteral($1, $3);}
	| constant_symb GE variable		{$$ = new GeLiteral($1, $3);}
	| expr_num GT variable			{$$ = new GtLiteral($1, $3);}
	| constant_symb GT variable		{$$ = new GtLiteral($1, $3);}
	| expr_num LE variable			{$$ = new GeLiteral($3, $1);}
	| constant_symb LE variable		{$$ = new GeLiteral($3, $1);}
	| expr_num LT variable			{$$ = new GtLiteral($3, $1);}
	| constant_symb LT variable		{$$ = new GtLiteral($3, $1);}
	| expr_num IN fonction			{$$ = new MemberLiteral($1,$3);}
	| expr_num IN variable			{$$ = new MemberLiteral($1,$3);}
	| constant_symb IN fonction		{$$ = new MemberLiteral($1,$3);}
	| constant_symb IN variable		{$$ = new MemberLiteral($1,$3);}
	| variable IN fonction			{$$ = new MemberLiteral($1,$3);}
	| variable IN variable			{$$ = new MemberLiteral($1,$3);}
	| fonction_etendu IN fonction		{$$ = new MemberLiteral($1,$3);}
	| fonction_etendu IN variable		{$$ = new MemberLiteral($1,$3);}
	| expr_num NIN fonction			{$$ = new NmemberLiteral($1,$3);}
	| expr_num NIN variable			{$$ = new NmemberLiteral($1,$3);}
	| constant_symb NIN fonction		{$$ = new NmemberLiteral($1,$3);}
	| constant_symb NIN variable		{$$ = new NmemberLiteral($1,$3);}
	| variable NIN fonction			{$$ = new NmemberLiteral($1,$3);}
	| variable NIN variable			{$$ = new NmemberLiteral($1,$3);}
	| fonction_etendu NIN fonction		{$$ = new NmemberLiteral($1,$3);}
	| fonction_etendu NIN variable		{$$ = new NmemberLiteral($1,$3);}	;

expr_num :
     constant_num		{$$= $1;}
     | expr_arith		{$$ = $1;}
     ;

affectation :
	variable AFFECT expr_arith_bis	{$$ = new AffectLiteral($1, $3);}
	| variable AFFECT fonction {$$ = new AffectLiteral($1, $3);}
	| variable AFFECT constant_symb {$$ = new AffectLiteral($1, $3);}
	;
expr_arith :
     expr_arith_bis PLUS_OP expr_arith_bis	{$$ = new BinaryArithExpr($2, $1, $3);}
     | expr_arith_bis MINUS_OP expr_arith_bis	{$$ = new BinaryArithExpr($2, $1, $3);}
     | expr_arith_bis MULT_OP expr_arith_bis	{$$ = new BinaryArithExpr($2, $1, $3);}
     | expr_arith_bis DIV_OP expr_arith_bis	{$$ = new BinaryArithExpr($2, $1, $3);}
     | expr_arith_bis MOD_OP expr_arith_bis	{$$ = new BinaryArithExpr($2, $1, $3);}
     | expr_arith_bis MAX_OP expr_arith_bis	{$$ = new BinaryArithExpr($2, $1, $3);}
     | ABS_OP '(' expr_arith_bis ')'		{$$ = new UnaryArithExpr($1, $3);}
     | '(' expr_arith_bis ')'			{$$ = $2;}
     ;
expr_arith_bis :
     constant_num		{$$= $1;}
     | variable			{$$ = $1;}
     | expr_arith		{$$ = $1;}
     ;

constant_symb :
	CONST_SYMB		{$$= SymbConst::new_SymbConst($1);}
	;

constant_num :
     CONST_NUM			{try{ $$= NumConst::new_NumConst($1);
     				 }
     				 catch(OutOfRangeNumConst){
				      std::cerr<<"Out of range numeric constant "<<std::endl;
			 	      yynerrs++; YYERROR;
				  }
				 }
     | MINUS_OP CONST_NUM	{try{ $$= NumConst::new_NumConst(-$2);
     				 }
     				 catch(OutOfRangeNumConst){
				      std::cerr<<"Out of range numeric constant "<<std::endl;
			 	      yynerrs++; YYERROR;
				  }
				 }
				 
     ;		     
     
variable :
	VARIABLE		{MapStrVar::iterator it = map->find(*$1);
				 if (it != map->end()){
				 	$$ = (*it).second;
					delete $1;
				 }
				 else {
					Variable* v = new Variable($1);
					$$ = v;
					map->insert(std::make_pair(*$1,v));
					set->insert(v);
				  }
				 }
	;

commande :
	HIDE '.'		{defaultShow = false;}
	| HIDE predicat_arite '.'	{hideSet.insert($2);}
	| SHOW predicat_arite '.'	{showSet.insert($2);}
	;
predicat_arite :
	CONST_SYMB DIV_OP CONST_NUM 	{$$ = new std::string;
       					 std::stringstream ss;
       				  	 ss << *($1) << "/" << $3; // cast int2string
       					 ss >> *$$ ;
					 delete $1;}
	
%%
#include "parser.lex.cpp"

Program* readProg(char* fileName, bool verbose){  
 FILE* f = NULL;
 try{
  if(fileName){
    f = fopen(fileName,"r");
    if (!f){
    	std::cerr << "can not open " << fileName << std::endl;
	return NULL;
    }
    yyin = f;
  } 	
  prog->setVerbose(verbose);
  yyparse();
  if (defaultShow){
	if (!Predicate::initShow(true, hideSet)) // return false if some name does not appear anywhere else in the program
		std::cerr << "*** Warning : hide directive for unknown predicate " << std::endl;
	if (!showSet.empty())
		std::cerr<<"*** Warning : show directive for some predicate while default show is active"<<std::endl;
  }
  else{
	if (!Predicate::initShow(false, showSet))// return false if some name does not appear anywhere else in the program
		std::cerr << "*** Warning : show directive for unknown predicate " << std::endl;
	if (!hideSet.empty())
		std::cerr<<"*** Warning : hide directive for some predicate while default hide is active"<<std::endl;
  }
  if(fileName) fclose(f);
  delete map;
  delete set;
  for (stringSet::iterator i = hideSet.begin(); i != hideSet.end(); ++i) delete (*i);
  for (stringSet::iterator i = showSet.begin(); i != showSet.end(); ++i) delete (*i);
  if (yynerrs) return NULL;
//std::cout << "fin readProg" <<std::endl;
  return prog;
 }
 catch (ContradictoryConclusion&){
  if(fileName) fclose(f);
  delete map;
  delete set;
  throw;
 }
}

void yyerror(std::string mess){
  std::cerr<< mess << std::endl ;
}




