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
 /* programmes logiques normaux avec variables : le lexique  */ 
%option nounput
%option yylineno

lettre_min	[a-z]
lettre_maj	[A-Z]
lettre		[a-zA-Z_]
chiffre		[0-9]
const_symb	({lettre_min}({lettre}|{chiffre})*)|(\"[^"]*\")
const_num	[0-9]+
variable	{lettre_maj}({lettre}|{chiffre})*
comment		%.*
 
%%
not		return(NOT);
:-		return (SI);
".."		return(PP);
[,.()]		return(yytext[0]);
"+"		{yylval.oper = PLUS; return(PLUS_OP);}
"-"		{yylval.oper = MINUS; return(MINUS_OP);}
"*"		{yylval.oper = MULT; return(MULT_OP);}
"/"		{yylval.oper = DIV; return(DIV_OP);}
mod		{yylval.oper = MOD; return(MOD_OP);}
max             {yylval.oper = MAX; return(MAX_OP);}
abs		{yylval.oper = ABS; return(ABS_OP);}
"@"		{return IN;}
"!@"		{return NIN;}
"=="		{return EQ;}
"!="		{return NEQ;}
">="		{return GE;}
">"		{return GT;}
"<="		{return LE;}
"<"		{return LT;}
"="		{return AFFECT;}
{variable}	{yylval.chaine = new std::string(yytext); return(VARIABLE);}
{const_symb} 	{yylval.chaine = new std::string(yytext); return(CONST_SYMB);}
-{const_symb}	{yylval.chaine = new std::string(yytext); return(CONST_SYMB_NEG);}
{const_num}	{yylval.num = atoi(yytext);
		 return(CONST_NUM);}
#hide		{return HIDE;}
#show		{return SHOW;}
{comment}	; /* commentaire, ne rien faire */
[ \r\t\n]		; /* séparateur, ne rien faire */ 

.		return(yytext[0]); /* caractère non reconnu */ 
%%

