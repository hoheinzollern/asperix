
/* A Bison parser, made by GNU Bison 2.4.1.  */

/* Skeleton implementation for Bison's Yacc-like parsers in C
   
      Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.
   
   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.
   
   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.
   
   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.
   
   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "2.4.1"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1

/* Using locations.  */
#define YYLSP_NEEDED 0



/* Copy the first part of user declarations.  */

/* Line 189 of yacc.c  */
#line 20 "parser.y"

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


/* Line 189 of yacc.c  */
#line 123 "parser.cpp"

/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* Enabling the token table.  */
#ifndef YYTOKEN_TABLE
# define YYTOKEN_TABLE 0
#endif


/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     NOT = 258,
     SI = 259,
     PP = 260,
     EQ = 261,
     NEQ = 262,
     GE = 263,
     GT = 264,
     LE = 265,
     LT = 266,
     AFFECT = 267,
     HIDE = 268,
     SHOW = 269,
     IN = 270,
     NIN = 271,
     CONST_SYMB = 272,
     CONST_SYMB_NEG = 273,
     VARIABLE = 274,
     CONST_NUM = 275,
     PLUS_OP = 276,
     MINUS_OP = 277,
     MULT_OP = 278,
     DIV_OP = 279,
     MOD_OP = 280,
     MAX_OP = 281,
     ABS_OP = 282
   };
#endif



#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{

/* Line 214 of yacc.c  */
#line 69 "parser.y"

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



/* Line 214 of yacc.c  */
#line 202 "parser.cpp"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif


/* Copy the second part of user declarations.  */


/* Line 264 of yacc.c  */
#line 214 "parser.cpp"

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#elif (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
typedef signed char yytype_int8;
#else
typedef short int yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(e) ((void) (e))
#else
# define YYUSE(e) /* empty */
#endif

/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(n) (n)
#else
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static int
YYID (int yyi)
#else
static int
YYID (yyi)
    int yyi;
#endif
{
  return yyi;
}
#endif

#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#     ifndef _STDLIB_H
#      define _STDLIB_H 1
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (YYID (0))
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined _STDLIB_H \
       && ! ((defined YYMALLOC || defined malloc) \
	     && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef _STDLIB_H
#    define _STDLIB_H 1
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
	 || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

/* Copy COUNT objects from FROM to TO.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(To, From, Count) \
      __builtin_memcpy (To, From, (Count) * sizeof (*(From)))
#  else
#   define YYCOPY(To, From, Count)		\
      do					\
	{					\
	  YYSIZE_T yyi;				\
	  for (yyi = 0; yyi < (Count); yyi++)	\
	    (To)[yyi] = (From)[yyi];		\
	}					\
      while (YYID (0))
#  endif
# endif

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)				\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack_alloc, Stack, yysize);			\
	Stack = &yyptr->Stack_alloc;					\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  2
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   346

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  32
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  30
/* YYNRULES -- Number of rules.  */
#define YYNRULES  133
/* YYNRULES -- Number of states.  */
#define YYNSTATES  218

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   282

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
      30,    31,     2,     2,    29,     2,    28,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     4,     7,    10,    13,    18,    22,    25,
      27,    29,    32,    34,    38,    40,    43,    45,    50,    52,
      57,    59,    64,    66,    68,    70,    74,    76,    78,    80,
      82,    84,    86,    91,    93,    97,    99,   101,   103,   105,
     110,   115,   117,   121,   125,   127,   129,   133,   137,   141,
     145,   149,   153,   157,   161,   165,   169,   173,   177,   181,
     185,   189,   193,   197,   201,   205,   209,   213,   217,   221,
     225,   229,   233,   237,   241,   245,   249,   253,   257,   261,
     265,   269,   273,   277,   281,   285,   289,   293,   297,   301,
     305,   309,   313,   317,   321,   325,   329,   333,   337,   341,
     345,   349,   353,   357,   361,   365,   369,   373,   377,   381,
     385,   387,   389,   393,   397,   401,   405,   409,   413,   417,
     421,   425,   430,   434,   436,   438,   440,   442,   444,   447,
     449,   452,   456,   460
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      33,     0,    -1,    -1,    33,    34,    -1,    33,    60,    -1,
      35,    28,    -1,    35,     4,    36,    28,    -1,     4,    36,
      28,    -1,     1,    28,    -1,    38,    -1,    48,    -1,     3,
      38,    -1,    37,    -1,    36,    29,    37,    -1,    40,    -1,
       3,    39,    -1,    17,    -1,    17,    30,    41,    31,    -1,
      17,    -1,    17,    30,    45,    31,    -1,    17,    -1,    17,
      30,    45,    31,    -1,    52,    -1,    54,    -1,    42,    -1,
      41,    29,    42,    -1,    43,    -1,    59,    -1,    55,    -1,
      44,    -1,    57,    -1,    58,    -1,    17,    30,    41,    31,
      -1,    46,    -1,    45,    29,    46,    -1,    43,    -1,    59,
      -1,    55,    -1,    47,    -1,    17,    30,    45,    31,    -1,
      17,    30,    49,    31,    -1,    50,    -1,    49,    29,    50,
      -1,    51,     5,    51,    -1,    58,    -1,    59,    -1,    53,
       6,    53,    -1,    53,     7,    53,    -1,    53,     8,    53,
      -1,    53,     9,    53,    -1,    53,    10,    53,    -1,    53,
      11,    53,    -1,    57,     6,    57,    -1,    57,     7,    57,
      -1,    57,     8,    57,    -1,    57,     9,    57,    -1,    57,
      10,    57,    -1,    57,    11,    57,    -1,    59,     6,    53,
      -1,    59,     6,    57,    -1,    59,     6,    44,    -1,    59,
       6,    59,    -1,    59,     7,    53,    -1,    59,     7,    57,
      -1,    59,     7,    44,    -1,    59,     7,    59,    -1,    59,
       8,    53,    -1,    59,     8,    57,    -1,    59,     8,    59,
      -1,    59,     9,    53,    -1,    59,     9,    57,    -1,    59,
       9,    59,    -1,    59,    10,    53,    -1,    59,    10,    57,
      -1,    59,    10,    59,    -1,    59,    11,    53,    -1,    59,
      11,    57,    -1,    59,    11,    59,    -1,    53,     6,    59,
      -1,    57,     6,    59,    -1,    47,     6,    59,    -1,    47,
       6,    44,    -1,    53,     7,    59,    -1,    57,     7,    59,
      -1,    47,     7,    59,    -1,    47,     7,    44,    -1,    53,
       8,    59,    -1,    57,     8,    59,    -1,    53,     9,    59,
      -1,    57,     9,    59,    -1,    53,    10,    59,    -1,    57,
      10,    59,    -1,    53,    11,    59,    -1,    57,    11,    59,
      -1,    53,    15,    44,    -1,    53,    15,    59,    -1,    57,
      15,    44,    -1,    57,    15,    59,    -1,    59,    15,    44,
      -1,    59,    15,    59,    -1,    47,    15,    44,    -1,    47,
      15,    59,    -1,    53,    16,    44,    -1,    53,    16,    59,
      -1,    57,    16,    44,    -1,    57,    16,    59,    -1,    59,
      16,    44,    -1,    59,    16,    59,    -1,    47,    16,    44,
      -1,    47,    16,    59,    -1,    58,    -1,    55,    -1,    59,
      12,    56,    -1,    59,    12,    44,    -1,    59,    12,    57,
      -1,    56,    21,    56,    -1,    56,    22,    56,    -1,    56,
      23,    56,    -1,    56,    24,    56,    -1,    56,    25,    56,
      -1,    56,    26,    56,    -1,    27,    30,    56,    31,    -1,
      30,    56,    31,    -1,    58,    -1,    59,    -1,    55,    -1,
      17,    -1,    20,    -1,    22,    20,    -1,    19,    -1,    13,
      28,    -1,    13,    61,    28,    -1,    14,    61,    28,    -1,
      17,    24,    20,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   103,   103,   105,   106,   109,   122,   141,   151,   156,
     157,   158,   162,   167,   175,   177,   183,   185,   190,   192,
     197,   199,   202,   203,   206,   208,   212,   213,   214,   215,
     218,   219,   223,   235,   237,   241,   242,   243,   247,   250,
     262,   269,   271,   275,   278,   279,   283,   284,   285,   286,
     287,   288,   289,   290,   291,   292,   293,   294,   295,   296,
     297,   298,   299,   300,   301,   302,   303,   304,   305,   306,
     307,   308,   309,   310,   311,   312,   313,   314,   315,   316,
     317,   318,   319,   320,   321,   322,   323,   324,   325,   326,
     327,   328,   329,   330,   331,   332,   333,   334,   335,   336,
     337,   338,   339,   340,   341,   342,   343,   344,   345,   346,
     349,   350,   354,   355,   356,   359,   360,   361,   362,   363,
     364,   365,   366,   369,   370,   371,   375,   379,   386,   397,
     412,   413,   414,   417
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "NOT", "SI", "PP", "EQ", "NEQ", "GE",
  "GT", "LE", "LT", "AFFECT", "HIDE", "SHOW", "IN", "NIN", "CONST_SYMB",
  "CONST_SYMB_NEG", "VARIABLE", "CONST_NUM", "PLUS_OP", "MINUS_OP",
  "MULT_OP", "DIV_OP", "MOD_OP", "MAX_OP", "ABS_OP", "'.'", "','", "'('",
  "')'", "$accept", "prog", "regle", "tete", "corps", "litteral",
  "atome_tete", "atome_neg", "atome_etendu", "liste_termes", "terme",
  "constant", "fonction", "liste_termes_etendu", "terme_etendu",
  "fonction_etendu", "range_atome", "liste_range_termes", "range",
  "range_bound", "expr_bool", "expr_num", "affectation", "expr_arith",
  "expr_arith_bis", "constant_symb", "constant_num", "variable",
  "commande", "predicat_arite", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,    46,    44,
      40,    41
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    32,    33,    33,    33,    34,    34,    34,    34,    35,
      35,    35,    36,    36,    37,    37,    38,    38,    39,    39,
      40,    40,    40,    40,    41,    41,    42,    42,    42,    42,
      43,    43,    44,    45,    45,    46,    46,    46,    46,    47,
      48,    49,    49,    50,    51,    51,    52,    52,    52,    52,
      52,    52,    52,    52,    52,    52,    52,    52,    52,    52,
      52,    52,    52,    52,    52,    52,    52,    52,    52,    52,
      52,    52,    52,    52,    52,    52,    52,    52,    52,    52,
      52,    52,    52,    52,    52,    52,    52,    52,    52,    52,
      52,    52,    52,    52,    52,    52,    52,    52,    52,    52,
      52,    52,    52,    52,    52,    52,    52,    52,    52,    52,
      53,    53,    54,    54,    54,    55,    55,    55,    55,    55,
      55,    55,    55,    56,    56,    56,    57,    58,    58,    59,
      60,    60,    60,    61
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     0,     2,     2,     2,     4,     3,     2,     1,
       1,     2,     1,     3,     1,     2,     1,     4,     1,     4,
       1,     4,     1,     1,     1,     3,     1,     1,     1,     1,
       1,     1,     4,     1,     3,     1,     1,     1,     1,     4,
       4,     1,     3,     3,     1,     1,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       1,     1,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     4,     3,     1,     1,     1,     1,     1,     2,     1,
       2,     3,     3,     3
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       2,     0,     1,     0,     0,     0,     0,     0,    16,     3,
       0,     9,    10,     4,     8,    16,    11,     0,   126,   129,
     127,     0,     0,     0,     0,    12,    14,     0,    22,     0,
      23,   111,     0,     0,   110,   124,     0,   130,     0,     0,
       0,     0,     5,     0,    18,    15,     0,   128,     0,   125,
       0,   123,   124,     7,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   131,   132,   126,     0,    24,    26,    29,     0,    41,
       0,   125,    30,   123,   124,     0,   123,   124,     0,   126,
      35,     0,    33,    38,   125,   124,     0,   122,    13,     0,
      81,    80,    85,    84,   100,   101,   108,   109,    46,   124,
      47,   124,    48,   124,    49,   124,    50,   124,    51,   124,
      94,    95,   102,   103,   115,   116,   117,   118,   119,   120,
     126,    52,    79,    53,    83,    54,    87,    55,    89,    56,
      91,    57,    93,    96,    97,   104,   105,    60,    58,    59,
     124,    64,    62,    63,   124,    66,    67,   124,    69,    70,
     124,    72,    73,   124,    75,    76,   124,   113,   112,   114,
      98,    99,   106,   107,   133,     0,     0,    17,     0,    40,
       0,     6,     0,     0,     0,    39,   121,     0,    25,    42,
      44,    45,    43,    19,     0,    34,    32,    39
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,     1,     9,    10,    24,    25,    11,    45,    26,    94,
      95,    96,    97,   111,   112,   113,    12,    98,    99,   100,
      28,    29,    30,    31,    32,   102,    34,    52,    13,    38
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -107
static const yytype_int16 yypact[] =
{
    -107,   247,  -107,   -13,     6,   204,    -7,     7,     1,  -107,
       5,  -107,  -107,  -107,  -107,    56,  -107,    78,    98,  -107,
    -107,    99,   127,    -8,    38,  -107,  -107,   118,  -107,   291,
    -107,    22,   179,   302,   320,   280,   107,  -107,   126,   157,
      74,   204,  -107,    74,   130,  -107,   235,  -107,    -8,  -107,
     298,  -107,  -107,  -107,   204,    15,    15,    15,    15,    -8,
      -8,    -8,    -8,    -8,    -8,    15,    15,    -8,    -8,    -8,
      -8,    -8,    -8,    45,    45,    45,    45,    45,    45,    15,
      15,    74,    74,   255,   255,   255,   255,    74,    15,    15,
     189,  -107,  -107,   192,    58,  -107,  -107,  -107,    71,  -107,
     220,    91,  -107,     8,    11,   145,   101,   120,   235,   202,
    -107,   124,  -107,  -107,   132,   135,   309,  -107,  -107,   192,
    -107,  -107,  -107,  -107,  -107,  -107,  -107,  -107,  -107,   186,
    -107,   188,  -107,   199,  -107,   201,  -107,   207,  -107,   215,
    -107,  -107,  -107,  -107,    82,    82,  -107,  -107,  -107,  -107,
    -107,  -107,  -107,  -107,  -107,  -107,  -107,  -107,  -107,  -107,
    -107,  -107,  -107,  -107,  -107,  -107,  -107,  -107,  -107,  -107,
     230,  -107,  -107,  -107,   238,  -107,  -107,   240,  -107,  -107,
     252,  -107,  -107,   265,  -107,  -107,   275,  -107,   179,  -107,
    -107,  -107,  -107,  -107,  -107,    74,    74,  -107,    -2,  -107,
      -2,  -107,   153,   235,   235,   286,  -107,   163,  -107,  -107,
    -107,  -107,  -107,  -107,   177,  -107,  -107,  -107
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -107,  -107,  -107,  -107,   198,   187,   229,  -107,  -107,    54,
      57,   -45,   131,  -106,    52,   111,  -107,  -107,    65,    73,
    -107,   -56,  -107,    75,    69,    94,    42,    -5,  -107,   269
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -126
static const yytype_int16 yytable[] =
{
      35,   110,   202,   128,   130,   132,   134,   136,   138,    41,
      36,    19,    20,   -44,    21,    14,   -45,    19,    20,    22,
      21,    37,    23,    15,    36,   168,   172,   175,   178,   181,
     184,    40,   119,    42,    19,   104,    35,   -31,   107,   -31,
     -27,   115,   -27,  -125,  -125,  -125,  -125,  -125,  -125,    35,
     121,   123,   125,   127,   129,   131,   133,   135,   137,   139,
     141,   143,   150,   110,    19,    51,    53,    54,   152,   154,
     156,   158,   160,   162,   164,   166,   170,   174,   177,   180,
     183,   186,   103,   191,   193,   106,    43,   196,   106,   197,
      51,    93,    50,    19,    20,    44,    21,   214,    49,    33,
     198,    22,   199,   115,    23,    69,    70,    71,    72,    51,
      51,    51,    51,    51,    51,   101,    27,   116,   101,    47,
     -28,   114,   -28,    49,    55,    56,   -20,   -20,    46,    51,
     -31,    90,   -31,    57,    58,    33,   144,   145,   146,   147,
     148,   149,    49,    49,    49,    49,    49,    49,    33,   -27,
     106,   -27,    27,   204,    91,   205,   188,    48,   110,   110,
     108,   -37,    49,   -37,   -36,    27,   -36,   151,   153,   155,
     157,   159,   161,   201,    54,   169,   173,   176,   179,   182,
     185,   189,   204,   114,   213,    92,   120,   122,   124,   126,
     107,   107,   196,   211,   216,   211,   140,   142,   115,   115,
      67,    68,    69,    70,    71,    72,   204,    17,   217,   194,
     163,   165,   167,   171,   -78,   -78,   -82,   -82,   187,   190,
     192,    18,   195,    19,    20,   200,    21,   -86,   -86,   -88,
     -88,    22,   203,    16,    23,   -90,   -90,   106,   106,   105,
     210,   118,   210,   -92,   -92,   106,   106,     2,     3,   207,
       4,     5,   109,   208,    19,    20,   215,    21,   -61,   -61,
       6,     7,    22,   209,     8,    23,   -65,   -65,   -68,   -68,
     101,   101,   150,   212,    19,    20,    39,    21,   114,   114,
     -71,   -71,    22,     0,     0,    23,    81,    82,    83,    84,
      85,    86,    87,   -74,   -74,    88,    89,    59,    60,    61,
      62,    63,    64,   -77,   -77,     0,    65,    66,    73,    74,
      75,    76,    77,    78,   -21,   -21,     0,    79,    80,    67,
      68,    69,    70,    71,    72,     0,     0,     0,     0,   117,
      67,    68,    69,    70,    71,    72,     0,     0,     0,     0,
     206,  -123,  -123,  -123,  -123,  -123,  -123
};

static const yytype_int16 yycheck[] =
{
       5,    46,   108,    59,    60,    61,    62,    63,    64,     4,
      17,    19,    20,     5,    22,    28,     5,    19,    20,    27,
      22,    28,    30,    17,    17,    81,    82,    83,    84,    85,
      86,    30,    17,    28,    19,    40,    41,    29,    43,    31,
      29,    46,    31,    21,    22,    23,    24,    25,    26,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    17,   108,    19,    23,    28,    29,    73,    74,
      75,    76,    77,    78,    79,    80,    81,    82,    83,    84,
      85,    86,    40,    88,    89,    43,    30,    29,    46,    31,
      48,    17,    23,    19,    20,    17,    22,   203,    23,     5,
      29,    27,    31,   108,    30,    23,    24,    25,    26,    67,
      68,    69,    70,    71,    72,    40,     5,    48,    43,    20,
      29,    46,    31,    48,     6,     7,    28,    29,    30,    87,
      29,    24,    31,    15,    16,    41,    67,    68,    69,    70,
      71,    72,    67,    68,    69,    70,    71,    72,    54,    29,
     108,    31,    41,    29,    28,    31,    87,    30,   203,   204,
      30,    29,    87,    31,    29,    54,    31,    73,    74,    75,
      76,    77,    78,    28,    29,    81,    82,    83,    84,    85,
      86,    87,    29,   108,    31,    28,    55,    56,    57,    58,
     195,   196,    29,   198,    31,   200,    65,    66,   203,   204,
      21,    22,    23,    24,    25,    26,    29,     3,    31,    20,
      79,    80,    81,    82,    28,    29,    28,    29,    87,    88,
      89,    17,    30,    19,    20,     5,    22,    28,    29,    28,
      29,    27,    30,     4,    30,    28,    29,   195,   196,    41,
     198,    54,   200,    28,    29,   203,   204,     0,     1,   195,
       3,     4,    17,   196,    19,    20,   204,    22,    28,    29,
      13,    14,    27,   198,    17,    30,    28,    29,    28,    29,
     195,   196,    17,   200,    19,    20,     7,    22,   203,   204,
      28,    29,    27,    -1,    -1,    30,     6,     7,     8,     9,
      10,    11,    12,    28,    29,    15,    16,     6,     7,     8,
       9,    10,    11,    28,    29,    -1,    15,    16,     6,     7,
       8,     9,    10,    11,    28,    29,    -1,    15,    16,    21,
      22,    23,    24,    25,    26,    -1,    -1,    -1,    -1,    31,
      21,    22,    23,    24,    25,    26,    -1,    -1,    -1,    -1,
      31,    21,    22,    23,    24,    25,    26
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    33,     0,     1,     3,     4,    13,    14,    17,    34,
      35,    38,    48,    60,    28,    17,    38,     3,    17,    19,
      20,    22,    27,    30,    36,    37,    40,    47,    52,    53,
      54,    55,    56,    57,    58,    59,    17,    28,    61,    61,
      30,     4,    28,    30,    17,    39,    30,    20,    30,    55,
      56,    58,    59,    28,    29,     6,     7,    15,    16,     6,
       7,     8,     9,    10,    11,    15,    16,    21,    22,    23,
      24,    25,    26,     6,     7,     8,     9,    10,    11,    15,
      16,     6,     7,     8,     9,    10,    11,    12,    15,    16,
      24,    28,    28,    17,    41,    42,    43,    44,    49,    50,
      51,    55,    57,    58,    59,    36,    58,    59,    30,    17,
      43,    45,    46,    47,    55,    59,    56,    31,    37,    17,
      44,    59,    44,    59,    44,    59,    44,    59,    53,    59,
      53,    59,    53,    59,    53,    59,    53,    59,    53,    59,
      44,    59,    44,    59,    56,    56,    56,    56,    56,    56,
      17,    57,    59,    57,    59,    57,    59,    57,    59,    57,
      59,    57,    59,    44,    59,    44,    59,    44,    53,    57,
      59,    44,    53,    57,    59,    53,    57,    59,    53,    57,
      59,    53,    57,    59,    53,    57,    59,    44,    56,    57,
      44,    59,    44,    59,    20,    30,    29,    31,    29,    31,
       5,    28,    45,    30,    29,    31,    31,    41,    42,    50,
      58,    59,    51,    31,    45,    46,    31,    31
};

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		(-2)
#define YYEOF		0

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrorlab


/* Like YYERROR except do call yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  */

#define YYFAIL		goto yyerrlab

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)					\
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    {								\
      yychar = (Token);						\
      yylval = (Value);						\
      yytoken = YYTRANSLATE (yychar);				\
      YYPOPSTACK (1);						\
      goto yybackup;						\
    }								\
  else								\
    {								\
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;							\
    }								\
while (YYID (0))


#define YYTERROR	1
#define YYERRCODE	256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#define YYRHSLOC(Rhs, K) ((Rhs)[K])
#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)				\
    do									\
      if (YYID (N))                                                    \
	{								\
	  (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;	\
	  (Current).first_column = YYRHSLOC (Rhs, 1).first_column;	\
	  (Current).last_line    = YYRHSLOC (Rhs, N).last_line;		\
	  (Current).last_column  = YYRHSLOC (Rhs, N).last_column;	\
	}								\
      else								\
	{								\
	  (Current).first_line   = (Current).last_line   =		\
	    YYRHSLOC (Rhs, 0).last_line;				\
	  (Current).first_column = (Current).last_column =		\
	    YYRHSLOC (Rhs, 0).last_column;				\
	}								\
    while (YYID (0))
#endif


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if YYLTYPE_IS_TRIVIAL
#  define YY_LOCATION_PRINT(File, Loc)			\
     fprintf (File, "%d.%d-%d.%d",			\
	      (Loc).first_line, (Loc).first_column,	\
	      (Loc).last_line,  (Loc).last_column)
# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
#endif


/* YYLEX -- calling `yylex' with the right arguments.  */

#ifdef YYLEX_PARAM
# define YYLEX yylex (YYLEX_PARAM)
#else
# define YYLEX yylex ()
#endif

/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)			\
do {						\
  if (yydebug)					\
    YYFPRINTF Args;				\
} while (YYID (0))

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)			  \
do {									  \
  if (yydebug)								  \
    {									  \
      YYFPRINTF (stderr, "%s ", Title);					  \
      yy_symbol_print (stderr,						  \
		  Type, Value); \
      YYFPRINTF (stderr, "\n");						  \
    }									  \
} while (YYID (0))


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# else
  YYUSE (yyoutput);
# endif
  switch (yytype)
    {
      default:
	break;
    }
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
#else
static void
yy_stack_print (yybottom, yytop)
    yytype_int16 *yybottom;
    yytype_int16 *yytop;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (YYID (0))


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_reduce_print (YYSTYPE *yyvsp, int yyrule)
#else
static void
yy_reduce_print (yyvsp, yyrule)
    YYSTYPE *yyvsp;
    int yyrule;
#endif
{
  int yynrhs = yyr2[yyrule];
  int yyi;
  unsigned long int yylno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
	     yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       		       );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, Rule); \
} while (YYID (0))

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef	YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif



#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static YYSIZE_T
yystrlen (const char *yystr)
#else
static YYSIZE_T
yystrlen (yystr)
    const char *yystr;
#endif
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static char *
yystpcpy (char *yydest, const char *yysrc)
#else
static char *
yystpcpy (yydest, yysrc)
    char *yydest;
    const char *yysrc;
#endif
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
	switch (*++yyp)
	  {
	  case '\'':
	  case ',':
	    goto do_not_strip_quotes;

	  case '\\':
	    if (*++yyp != '\\')
	      goto do_not_strip_quotes;
	    /* Fall through.  */
	  default:
	    if (yyres)
	      yyres[yyn] = *yyp;
	    yyn++;
	    break;

	  case '"':
	    if (yyres)
	      yyres[yyn] = '\0';
	    return yyn;
	  }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into YYRESULT an error message about the unexpected token
   YYCHAR while in state YYSTATE.  Return the number of bytes copied,
   including the terminating null byte.  If YYRESULT is null, do not
   copy anything; just return the number of bytes that would be
   copied.  As a special case, return 0 if an ordinary "syntax error"
   message will do.  Return YYSIZE_MAXIMUM if overflow occurs during
   size calculation.  */
static YYSIZE_T
yysyntax_error (char *yyresult, int yystate, int yychar)
{
  int yyn = yypact[yystate];

  if (! (YYPACT_NINF < yyn && yyn <= YYLAST))
    return 0;
  else
    {
      int yytype = YYTRANSLATE (yychar);
      YYSIZE_T yysize0 = yytnamerr (0, yytname[yytype]);
      YYSIZE_T yysize = yysize0;
      YYSIZE_T yysize1;
      int yysize_overflow = 0;
      enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
      char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
      int yyx;

# if 0
      /* This is so xgettext sees the translatable formats that are
	 constructed on the fly.  */
      YY_("syntax error, unexpected %s");
      YY_("syntax error, unexpected %s, expecting %s");
      YY_("syntax error, unexpected %s, expecting %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s");
# endif
      char *yyfmt;
      char const *yyf;
      static char const yyunexpected[] = "syntax error, unexpected %s";
      static char const yyexpecting[] = ", expecting %s";
      static char const yyor[] = " or %s";
      char yyformat[sizeof yyunexpected
		    + sizeof yyexpecting - 1
		    + ((YYERROR_VERBOSE_ARGS_MAXIMUM - 2)
		       * (sizeof yyor - 1))];
      char const *yyprefix = yyexpecting;

      /* Start YYX at -YYN if negative to avoid negative indexes in
	 YYCHECK.  */
      int yyxbegin = yyn < 0 ? -yyn : 0;

      /* Stay within bounds of both yycheck and yytname.  */
      int yychecklim = YYLAST - yyn + 1;
      int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
      int yycount = 1;

      yyarg[0] = yytname[yytype];
      yyfmt = yystpcpy (yyformat, yyunexpected);

      for (yyx = yyxbegin; yyx < yyxend; ++yyx)
	if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
	  {
	    if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
	      {
		yycount = 1;
		yysize = yysize0;
		yyformat[sizeof yyunexpected - 1] = '\0';
		break;
	      }
	    yyarg[yycount++] = yytname[yyx];
	    yysize1 = yysize + yytnamerr (0, yytname[yyx]);
	    yysize_overflow |= (yysize1 < yysize);
	    yysize = yysize1;
	    yyfmt = yystpcpy (yyfmt, yyprefix);
	    yyprefix = yyor;
	  }

      yyf = YY_(yyformat);
      yysize1 = yysize + yystrlen (yyf);
      yysize_overflow |= (yysize1 < yysize);
      yysize = yysize1;

      if (yysize_overflow)
	return YYSIZE_MAXIMUM;

      if (yyresult)
	{
	  /* Avoid sprintf, as that infringes on the user's name space.
	     Don't have undefined behavior even if the translation
	     produced a string with the wrong number of "%s"s.  */
	  char *yyp = yyresult;
	  int yyi = 0;
	  while ((*yyp = *yyf) != '\0')
	    {
	      if (*yyp == '%' && yyf[1] == 's' && yyi < yycount)
		{
		  yyp += yytnamerr (yyp, yyarg[yyi++]);
		  yyf += 2;
		}
	      else
		{
		  yyp++;
		  yyf++;
		}
	    }
	}
      return yysize;
    }
}
#endif /* YYERROR_VERBOSE */


/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
#else
static void
yydestruct (yymsg, yytype, yyvaluep)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
#endif
{
  YYUSE (yyvaluep);

  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  switch (yytype)
    {

      default:
	break;
    }
}

/* Prevent warnings from -Wmissing-prototypes.  */
#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int yyparse (void *YYPARSE_PARAM);
#else
int yyparse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int yyparse (void);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */


/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;

/* Number of syntax errors so far.  */
int yynerrs;



/*-------------------------.
| yyparse or yypush_parse.  |
`-------------------------*/

#ifdef YYPARSE_PARAM
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void *YYPARSE_PARAM)
#else
int
yyparse (YYPARSE_PARAM)
    void *YYPARSE_PARAM;
#endif
#else /* ! YYPARSE_PARAM */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void)
#else
int
yyparse ()

#endif
#endif
{


    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       `yyss': related to states.
       `yyvs': related to semantic values.

       Refer to the stacks thru separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yytoken = 0;
  yyss = yyssa;
  yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */
  yyssp = yyss;
  yyvsp = yyvs;

  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
	/* Give user a chance to reallocate the stack.  Use copies of
	   these so that the &'s don't force the real ones into
	   memory.  */
	YYSTYPE *yyvs1 = yyvs;
	yytype_int16 *yyss1 = yyss;

	/* Each stack pointer address is followed by the size of the
	   data in use in that stack, in bytes.  This used to be a
	   conditional around just the two extra args, but that might
	   be undefined if yyoverflow is a macro.  */
	yyoverflow (YY_("memory exhausted"),
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),
		    &yystacksize);

	yyss = yyss1;
	yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
	goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
	yystacksize = YYMAXDEPTH;

      {
	yytype_int16 *yyss1 = yyss;
	union yyalloc *yyptr =
	  (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
	if (! yyptr)
	  goto yyexhaustedlab;
	YYSTACK_RELOCATE (yyss_alloc, yyss);
	YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
	if (yyss1 != yyssa)
	  YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
		  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
	YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yyn == YYPACT_NINF)
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = YYLEX;
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yyn == 0 || yyn == YYTABLE_NINF)
	goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  *++yyvsp = yylval;

  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     `$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 5:

/* Line 1455 of yacc.c  */
#line 109 "parser.y"
    { try{nregle++;
				      fact = new FactRule((yyvsp[(1) - (2)].pbaslit),set);    
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
				;}
    break;

  case 6:

/* Line 1455 of yacc.c  */
#line 122 "parser.y"
    { try{nregle++;
				      if ((yyvsp[(3) - (4)].pBody)->containsNotLiteral((yyvsp[(1) - (4)].pbaslit))){ //body- contains head literal(resp. body+ if head is negative)
						constraint = new ConstraintRule((yyvsp[(3) - (4)].pBody), set, graph);
				      		prog->addConstraintRule(constraint);
				      } 
				      else{
				      		rule = new NormalRule((yyvsp[(1) - (4)].pbaslit), (yyvsp[(3) - (4)].pBody), set, graph);
				      		if ((yyvsp[(1) - (4)].pbaslit)->isNegativeLiteral())
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
				;}
    break;

  case 7:

/* Line 1455 of yacc.c  */
#line 141 "parser.y"
    { try{nregle++;
				      constraint = new ConstraintRule((yyvsp[(2) - (3)].pBody), set, graph);
				      prog->addConstraintRule(constraint);
				  }
				  catch(LogicExcept& e){
				 	std::cerr<<e.what()<<"\n\t(=>rule n° "<< nregle<<" - line "<< yylineno <<")"<<std::endl;
			 	      	yynerrs++; 
				   }
				   set->clear();map->clear();
				;}
    break;

  case 8:

/* Line 1455 of yacc.c  */
#line 151 "parser.y"
    {nregle++;map->clear();
	                 std::cerr<<"\t(=>rule n° "<< nregle<<" - line "<< yylineno <<")"<<std::endl;
			 yyerrok;;}
    break;

  case 9:

/* Line 1455 of yacc.c  */
#line 156 "parser.y"
    {(yyval.pbaslit) = (yyvsp[(1) - (1)].pbaslit);;}
    break;

  case 10:

/* Line 1455 of yacc.c  */
#line 157 "parser.y"
    {(yyval.pbaslit) = (yyvsp[(1) - (1)].pbaslit);;}
    break;

  case 11:

/* Line 1455 of yacc.c  */
#line 158 "parser.y"
    {(yyval.pbaslit) = new NegativeLiteral(*static_cast<NegativeLiteral*>((yyvsp[(2) - (2)].pbaslit)));
			 delete (yyvsp[(2) - (2)].pbaslit);;}
    break;

  case 12:

/* Line 1455 of yacc.c  */
#line 162 "parser.y"
    { (yyval.pBody) = new Body();
				  for (Literal::Vector::iterator i = litVect.begin(); i != litVect.end(); i++)
					(yyval.pBody)->addLiteral(*i);
				  litVect.clear();
				  (yyval.pBody)->addLiteral((yyvsp[(1) - (1)].pliteral));;}
    break;

  case 13:

/* Line 1455 of yacc.c  */
#line 167 "parser.y"
    { for (Literal::Vector::iterator i = litVect.begin(); i != litVect.end(); i++)
					(yyvsp[(1) - (3)].pBody)->addLiteral(*i);
				  litVect.clear();
				  (yyvsp[(1) - (3)].pBody)->addLiteral((yyvsp[(3) - (3)].pliteral));
				  (yyval.pBody) = (yyvsp[(1) - (3)].pBody);;}
    break;

  case 14:

/* Line 1455 of yacc.c  */
#line 175 "parser.y"
    {(yyval.pliteral) = (yyvsp[(1) - (1)].pliteral); 
				 ;}
    break;

  case 15:

/* Line 1455 of yacc.c  */
#line 177 "parser.y"
    {(yyval.pliteral) = new NegativeLiteral(*static_cast<NegativeLiteral*>((yyvsp[(2) - (2)].pbaslit))); 

			 delete (yyvsp[(2) - (2)].pbaslit);
			 ;}
    break;

  case 16:

/* Line 1455 of yacc.c  */
#line 183 "parser.y"
    {(yyval.pbaslit) = new BasicLiteral((yyvsp[(1) - (1)].chaine), NULL, graph);
				 delete (yyvsp[(1) - (1)].chaine);;}
    break;

  case 17:

/* Line 1455 of yacc.c  */
#line 186 "parser.y"
    { (yyval.pbaslit) = new BasicLiteral((yyvsp[(1) - (4)].chaine), (yyvsp[(3) - (4)].tVect), graph);
				  delete (yyvsp[(1) - (4)].chaine);;}
    break;

  case 18:

/* Line 1455 of yacc.c  */
#line 190 "parser.y"
    {(yyval.pbaslit) = new BasicLiteral((yyvsp[(1) - (1)].chaine), NULL, graph);
				 delete (yyvsp[(1) - (1)].chaine);;}
    break;

  case 19:

/* Line 1455 of yacc.c  */
#line 193 "parser.y"
    { (yyval.pbaslit) = new BasicLiteral((yyvsp[(1) - (4)].chaine), (yyvsp[(3) - (4)].tVect), graph);
				  delete (yyvsp[(1) - (4)].chaine);;}
    break;

  case 20:

/* Line 1455 of yacc.c  */
#line 197 "parser.y"
    {(yyval.pliteral) = new PositiveLiteral((yyvsp[(1) - (1)].chaine), NULL, graph);
				 delete (yyvsp[(1) - (1)].chaine);;}
    break;

  case 21:

/* Line 1455 of yacc.c  */
#line 200 "parser.y"
    { (yyval.pliteral) = new PositiveLiteral((yyvsp[(1) - (4)].chaine), (yyvsp[(3) - (4)].tVect), graph);
				  delete (yyvsp[(1) - (4)].chaine);;}
    break;

  case 22:

/* Line 1455 of yacc.c  */
#line 202 "parser.y"
    {(yyval.pliteral) = (yyvsp[(1) - (1)].pliteral);;}
    break;

  case 23:

/* Line 1455 of yacc.c  */
#line 203 "parser.y"
    {(yyval.pliteral) = (yyvsp[(1) - (1)].pliteral);;}
    break;

  case 24:

/* Line 1455 of yacc.c  */
#line 206 "parser.y"
    {(yyval.tVect)=new Argument();
				 (yyval.tVect)->push_back((yyvsp[(1) - (1)].pterm));;}
    break;

  case 25:

/* Line 1455 of yacc.c  */
#line 208 "parser.y"
    { (yyvsp[(1) - (3)].tVect)->push_back((yyvsp[(3) - (3)].pterm));
				    (yyval.tVect) = (yyvsp[(1) - (3)].tVect);;}
    break;

  case 26:

/* Line 1455 of yacc.c  */
#line 212 "parser.y"
    {(yyval.pterm)=(yyvsp[(1) - (1)].pterm);;}
    break;

  case 27:

/* Line 1455 of yacc.c  */
#line 213 "parser.y"
    {(yyval.pterm)=(yyvsp[(1) - (1)].pvar);;}
    break;

  case 28:

/* Line 1455 of yacc.c  */
#line 214 "parser.y"
    {(yyval.pterm)=(yyvsp[(1) - (1)].pterm);;}
    break;

  case 29:

/* Line 1455 of yacc.c  */
#line 215 "parser.y"
    {(yyval.pterm)=(yyvsp[(1) - (1)].pterm);;}
    break;

  case 30:

/* Line 1455 of yacc.c  */
#line 218 "parser.y"
    {(yyval.pterm)= (yyvsp[(1) - (1)].pconst);;}
    break;

  case 31:

/* Line 1455 of yacc.c  */
#line 219 "parser.y"
    {(yyval.pterm)= (yyvsp[(1) - (1)].pterm);;}
    break;

  case 32:

/* Line 1455 of yacc.c  */
#line 224 "parser.y"
    {try{ (yyval.pterm)= FuncTerm::new_FuncTerm((yyvsp[(1) - (4)].chaine), (yyvsp[(3) - (4)].tVect));
     				     }
     				 catch(OutOfRangeFuncTerm){
				      std::cerr<<"too deep functional term "<<std::endl;
			 	      yynerrs++; YYERROR;
				  }
				;}
    break;

  case 33:

/* Line 1455 of yacc.c  */
#line 235 "parser.y"
    {(yyval.tVect)=new Argument();
					 (yyval.tVect)->push_back((yyvsp[(1) - (1)].pterm));;}
    break;

  case 34:

/* Line 1455 of yacc.c  */
#line 237 "parser.y"
    { (yyvsp[(1) - (3)].tVect)->push_back((yyvsp[(3) - (3)].pterm));
				    		  (yyval.tVect) = (yyvsp[(1) - (3)].tVect);;}
    break;

  case 35:

/* Line 1455 of yacc.c  */
#line 241 "parser.y"
    {(yyval.pterm)=(yyvsp[(1) - (1)].pterm);;}
    break;

  case 36:

/* Line 1455 of yacc.c  */
#line 242 "parser.y"
    {(yyval.pterm)=(yyvsp[(1) - (1)].pvar);;}
    break;

  case 37:

/* Line 1455 of yacc.c  */
#line 243 "parser.y"
    {Variable* v = new Variable(NULL);
				 set->insert(v);
				 litVect.push_back(new AffectLiteral(v, (yyvsp[(1) - (1)].pterm))); // literal v=$1
				 (yyval.pterm) = v;;}
    break;

  case 38:

/* Line 1455 of yacc.c  */
#line 247 "parser.y"
    {(yyval.pterm)=(yyvsp[(1) - (1)].pterm);;}
    break;

  case 39:

/* Line 1455 of yacc.c  */
#line 251 "parser.y"
    {try{ (yyval.pterm)= FuncTerm::new_FuncTerm((yyvsp[(1) - (4)].chaine), (yyvsp[(3) - (4)].tVect));
     				     }
     				 catch(OutOfRangeFuncTerm){
				      std::cerr<<"too deep functional term "<<std::endl;
			 	      yynerrs++; YYERROR;
				  }
				;}
    break;

  case 40:

/* Line 1455 of yacc.c  */
#line 263 "parser.y"
    { (yyval.pbaslit) = new RangeLiteral((yyvsp[(1) - (4)].chaine), (yyvsp[(3) - (4)].tVect), graph);
				  delete (yyvsp[(1) - (4)].chaine);
				;}
    break;

  case 41:

/* Line 1455 of yacc.c  */
#line 269 "parser.y"
    {(yyval.tVect)=new Argument();
				 	 (yyval.tVect)->push_back((yyvsp[(1) - (1)].pterm));;}
    break;

  case 42:

/* Line 1455 of yacc.c  */
#line 271 "parser.y"
    { (yyvsp[(1) - (3)].tVect)->push_back((yyvsp[(3) - (3)].pterm));
				   	  (yyval.tVect) = (yyvsp[(1) - (3)].tVect);;}
    break;

  case 43:

/* Line 1455 of yacc.c  */
#line 275 "parser.y"
    { (yyval.pterm) = RangeTerm::new_RangeTerm((yyvsp[(1) - (3)].pterm),(yyvsp[(3) - (3)].pterm));;}
    break;

  case 44:

/* Line 1455 of yacc.c  */
#line 278 "parser.y"
    {(yyval.pterm)= (yyvsp[(1) - (1)].pterm);;}
    break;

  case 45:

/* Line 1455 of yacc.c  */
#line 279 "parser.y"
    {(yyval.pterm) = (yyvsp[(1) - (1)].pvar);;}
    break;

  case 46:

/* Line 1455 of yacc.c  */
#line 283 "parser.y"
    {(yyval.pliteral) = new EqLiteral((yyvsp[(1) - (3)].pterm), (yyvsp[(3) - (3)].pterm));;}
    break;

  case 47:

/* Line 1455 of yacc.c  */
#line 284 "parser.y"
    {(yyval.pliteral) = new NeqLiteral((yyvsp[(1) - (3)].pterm), (yyvsp[(3) - (3)].pterm));;}
    break;

  case 48:

/* Line 1455 of yacc.c  */
#line 285 "parser.y"
    {(yyval.pliteral) = new GeLiteral((yyvsp[(1) - (3)].pterm), (yyvsp[(3) - (3)].pterm));;}
    break;

  case 49:

/* Line 1455 of yacc.c  */
#line 286 "parser.y"
    {(yyval.pliteral) = new GtLiteral((yyvsp[(1) - (3)].pterm), (yyvsp[(3) - (3)].pterm));;}
    break;

  case 50:

/* Line 1455 of yacc.c  */
#line 287 "parser.y"
    {(yyval.pliteral) = new GeLiteral((yyvsp[(3) - (3)].pterm), (yyvsp[(1) - (3)].pterm));;}
    break;

  case 51:

/* Line 1455 of yacc.c  */
#line 288 "parser.y"
    {(yyval.pliteral) = new GtLiteral((yyvsp[(3) - (3)].pterm), (yyvsp[(1) - (3)].pterm));;}
    break;

  case 52:

/* Line 1455 of yacc.c  */
#line 289 "parser.y"
    {(yyval.pliteral) = new EqLiteral((yyvsp[(1) - (3)].pconst), (yyvsp[(3) - (3)].pconst));;}
    break;

  case 53:

/* Line 1455 of yacc.c  */
#line 290 "parser.y"
    {(yyval.pliteral) = new NeqLiteral((yyvsp[(1) - (3)].pconst), (yyvsp[(3) - (3)].pconst));;}
    break;

  case 54:

/* Line 1455 of yacc.c  */
#line 291 "parser.y"
    {(yyval.pliteral) = new GeLiteral((yyvsp[(1) - (3)].pconst), (yyvsp[(3) - (3)].pconst));;}
    break;

  case 55:

/* Line 1455 of yacc.c  */
#line 292 "parser.y"
    {(yyval.pliteral) = new GtLiteral((yyvsp[(1) - (3)].pconst), (yyvsp[(3) - (3)].pconst));;}
    break;

  case 56:

/* Line 1455 of yacc.c  */
#line 293 "parser.y"
    {(yyval.pliteral) = new GeLiteral((yyvsp[(3) - (3)].pconst), (yyvsp[(1) - (3)].pconst));;}
    break;

  case 57:

/* Line 1455 of yacc.c  */
#line 294 "parser.y"
    {(yyval.pliteral) = new GtLiteral((yyvsp[(3) - (3)].pconst), (yyvsp[(1) - (3)].pconst));;}
    break;

  case 58:

/* Line 1455 of yacc.c  */
#line 295 "parser.y"
    {(yyval.pliteral) = new EqLiteral((yyvsp[(1) - (3)].pvar), (yyvsp[(3) - (3)].pterm));;}
    break;

  case 59:

/* Line 1455 of yacc.c  */
#line 296 "parser.y"
    {(yyval.pliteral) = new EqLiteral((yyvsp[(1) - (3)].pvar), (yyvsp[(3) - (3)].pconst));;}
    break;

  case 60:

/* Line 1455 of yacc.c  */
#line 297 "parser.y"
    {(yyval.pliteral) = new EqLiteral((yyvsp[(1) - (3)].pvar), (yyvsp[(3) - (3)].pterm));;}
    break;

  case 61:

/* Line 1455 of yacc.c  */
#line 298 "parser.y"
    {(yyval.pliteral) = new EqLiteral((yyvsp[(1) - (3)].pvar), (yyvsp[(3) - (3)].pvar));;}
    break;

  case 62:

/* Line 1455 of yacc.c  */
#line 299 "parser.y"
    {(yyval.pliteral) = new NeqLiteral((yyvsp[(1) - (3)].pvar), (yyvsp[(3) - (3)].pterm));;}
    break;

  case 63:

/* Line 1455 of yacc.c  */
#line 300 "parser.y"
    {(yyval.pliteral) = new NeqLiteral((yyvsp[(1) - (3)].pvar), (yyvsp[(3) - (3)].pconst));;}
    break;

  case 64:

/* Line 1455 of yacc.c  */
#line 301 "parser.y"
    {(yyval.pliteral) = new NeqLiteral((yyvsp[(1) - (3)].pvar), (yyvsp[(3) - (3)].pterm));;}
    break;

  case 65:

/* Line 1455 of yacc.c  */
#line 302 "parser.y"
    {(yyval.pliteral) = new NeqLiteral((yyvsp[(1) - (3)].pvar), (yyvsp[(3) - (3)].pvar));;}
    break;

  case 66:

/* Line 1455 of yacc.c  */
#line 303 "parser.y"
    {(yyval.pliteral) = new GeLiteral((yyvsp[(1) - (3)].pvar), (yyvsp[(3) - (3)].pterm));;}
    break;

  case 67:

/* Line 1455 of yacc.c  */
#line 304 "parser.y"
    {(yyval.pliteral) = new GeLiteral((yyvsp[(1) - (3)].pvar), (yyvsp[(3) - (3)].pconst));;}
    break;

  case 68:

/* Line 1455 of yacc.c  */
#line 305 "parser.y"
    {(yyval.pliteral) = new GeLiteral((yyvsp[(1) - (3)].pvar), (yyvsp[(3) - (3)].pvar));;}
    break;

  case 69:

/* Line 1455 of yacc.c  */
#line 306 "parser.y"
    {(yyval.pliteral) = new GtLiteral((yyvsp[(1) - (3)].pvar), (yyvsp[(3) - (3)].pterm));;}
    break;

  case 70:

/* Line 1455 of yacc.c  */
#line 307 "parser.y"
    {(yyval.pliteral) = new GtLiteral((yyvsp[(1) - (3)].pvar), (yyvsp[(3) - (3)].pconst));;}
    break;

  case 71:

/* Line 1455 of yacc.c  */
#line 308 "parser.y"
    {(yyval.pliteral) = new GtLiteral((yyvsp[(1) - (3)].pvar), (yyvsp[(3) - (3)].pvar));;}
    break;

  case 72:

/* Line 1455 of yacc.c  */
#line 309 "parser.y"
    {(yyval.pliteral) = new GeLiteral((yyvsp[(3) - (3)].pterm), (yyvsp[(1) - (3)].pvar));;}
    break;

  case 73:

/* Line 1455 of yacc.c  */
#line 310 "parser.y"
    {(yyval.pliteral) = new GeLiteral((yyvsp[(3) - (3)].pconst), (yyvsp[(1) - (3)].pvar));;}
    break;

  case 74:

/* Line 1455 of yacc.c  */
#line 311 "parser.y"
    {(yyval.pliteral) = new GeLiteral((yyvsp[(3) - (3)].pvar), (yyvsp[(1) - (3)].pvar));;}
    break;

  case 75:

/* Line 1455 of yacc.c  */
#line 312 "parser.y"
    {(yyval.pliteral) = new GtLiteral((yyvsp[(3) - (3)].pterm), (yyvsp[(1) - (3)].pvar));;}
    break;

  case 76:

/* Line 1455 of yacc.c  */
#line 313 "parser.y"
    {(yyval.pliteral) = new GtLiteral((yyvsp[(3) - (3)].pconst), (yyvsp[(1) - (3)].pvar));;}
    break;

  case 77:

/* Line 1455 of yacc.c  */
#line 314 "parser.y"
    {(yyval.pliteral) = new GtLiteral((yyvsp[(3) - (3)].pvar), (yyvsp[(1) - (3)].pvar));;}
    break;

  case 78:

/* Line 1455 of yacc.c  */
#line 315 "parser.y"
    {(yyval.pliteral) = new EqLiteral((yyvsp[(1) - (3)].pterm), (yyvsp[(3) - (3)].pvar));;}
    break;

  case 79:

/* Line 1455 of yacc.c  */
#line 316 "parser.y"
    {(yyval.pliteral) = new EqLiteral((yyvsp[(1) - (3)].pconst), (yyvsp[(3) - (3)].pvar));;}
    break;

  case 80:

/* Line 1455 of yacc.c  */
#line 317 "parser.y"
    {(yyval.pliteral) = new EqLiteral((yyvsp[(1) - (3)].pterm), (yyvsp[(3) - (3)].pvar));;}
    break;

  case 81:

/* Line 1455 of yacc.c  */
#line 318 "parser.y"
    {(yyval.pliteral) = new EqLiteral((yyvsp[(1) - (3)].pterm), (yyvsp[(3) - (3)].pterm));;}
    break;

  case 82:

/* Line 1455 of yacc.c  */
#line 319 "parser.y"
    {(yyval.pliteral) = new NeqLiteral((yyvsp[(1) - (3)].pterm), (yyvsp[(3) - (3)].pvar));;}
    break;

  case 83:

/* Line 1455 of yacc.c  */
#line 320 "parser.y"
    {(yyval.pliteral) = new NeqLiteral((yyvsp[(1) - (3)].pconst), (yyvsp[(3) - (3)].pvar));;}
    break;

  case 84:

/* Line 1455 of yacc.c  */
#line 321 "parser.y"
    {(yyval.pliteral) = new NeqLiteral((yyvsp[(1) - (3)].pterm), (yyvsp[(3) - (3)].pvar));;}
    break;

  case 85:

/* Line 1455 of yacc.c  */
#line 322 "parser.y"
    {(yyval.pliteral) = new NeqLiteral((yyvsp[(1) - (3)].pterm), (yyvsp[(3) - (3)].pterm));;}
    break;

  case 86:

/* Line 1455 of yacc.c  */
#line 323 "parser.y"
    {(yyval.pliteral) = new GeLiteral((yyvsp[(1) - (3)].pterm), (yyvsp[(3) - (3)].pvar));;}
    break;

  case 87:

/* Line 1455 of yacc.c  */
#line 324 "parser.y"
    {(yyval.pliteral) = new GeLiteral((yyvsp[(1) - (3)].pconst), (yyvsp[(3) - (3)].pvar));;}
    break;

  case 88:

/* Line 1455 of yacc.c  */
#line 325 "parser.y"
    {(yyval.pliteral) = new GtLiteral((yyvsp[(1) - (3)].pterm), (yyvsp[(3) - (3)].pvar));;}
    break;

  case 89:

/* Line 1455 of yacc.c  */
#line 326 "parser.y"
    {(yyval.pliteral) = new GtLiteral((yyvsp[(1) - (3)].pconst), (yyvsp[(3) - (3)].pvar));;}
    break;

  case 90:

/* Line 1455 of yacc.c  */
#line 327 "parser.y"
    {(yyval.pliteral) = new GeLiteral((yyvsp[(3) - (3)].pvar), (yyvsp[(1) - (3)].pterm));;}
    break;

  case 91:

/* Line 1455 of yacc.c  */
#line 328 "parser.y"
    {(yyval.pliteral) = new GeLiteral((yyvsp[(3) - (3)].pvar), (yyvsp[(1) - (3)].pconst));;}
    break;

  case 92:

/* Line 1455 of yacc.c  */
#line 329 "parser.y"
    {(yyval.pliteral) = new GtLiteral((yyvsp[(3) - (3)].pvar), (yyvsp[(1) - (3)].pterm));;}
    break;

  case 93:

/* Line 1455 of yacc.c  */
#line 330 "parser.y"
    {(yyval.pliteral) = new GtLiteral((yyvsp[(3) - (3)].pvar), (yyvsp[(1) - (3)].pconst));;}
    break;

  case 94:

/* Line 1455 of yacc.c  */
#line 331 "parser.y"
    {(yyval.pliteral) = new MemberLiteral((yyvsp[(1) - (3)].pterm),(yyvsp[(3) - (3)].pterm));;}
    break;

  case 95:

/* Line 1455 of yacc.c  */
#line 332 "parser.y"
    {(yyval.pliteral) = new MemberLiteral((yyvsp[(1) - (3)].pterm),(yyvsp[(3) - (3)].pvar));;}
    break;

  case 96:

/* Line 1455 of yacc.c  */
#line 333 "parser.y"
    {(yyval.pliteral) = new MemberLiteral((yyvsp[(1) - (3)].pconst),(yyvsp[(3) - (3)].pterm));;}
    break;

  case 97:

/* Line 1455 of yacc.c  */
#line 334 "parser.y"
    {(yyval.pliteral) = new MemberLiteral((yyvsp[(1) - (3)].pconst),(yyvsp[(3) - (3)].pvar));;}
    break;

  case 98:

/* Line 1455 of yacc.c  */
#line 335 "parser.y"
    {(yyval.pliteral) = new MemberLiteral((yyvsp[(1) - (3)].pvar),(yyvsp[(3) - (3)].pterm));;}
    break;

  case 99:

/* Line 1455 of yacc.c  */
#line 336 "parser.y"
    {(yyval.pliteral) = new MemberLiteral((yyvsp[(1) - (3)].pvar),(yyvsp[(3) - (3)].pvar));;}
    break;

  case 100:

/* Line 1455 of yacc.c  */
#line 337 "parser.y"
    {(yyval.pliteral) = new MemberLiteral((yyvsp[(1) - (3)].pterm),(yyvsp[(3) - (3)].pterm));;}
    break;

  case 101:

/* Line 1455 of yacc.c  */
#line 338 "parser.y"
    {(yyval.pliteral) = new MemberLiteral((yyvsp[(1) - (3)].pterm),(yyvsp[(3) - (3)].pvar));;}
    break;

  case 102:

/* Line 1455 of yacc.c  */
#line 339 "parser.y"
    {(yyval.pliteral) = new NmemberLiteral((yyvsp[(1) - (3)].pterm),(yyvsp[(3) - (3)].pterm));;}
    break;

  case 103:

/* Line 1455 of yacc.c  */
#line 340 "parser.y"
    {(yyval.pliteral) = new NmemberLiteral((yyvsp[(1) - (3)].pterm),(yyvsp[(3) - (3)].pvar));;}
    break;

  case 104:

/* Line 1455 of yacc.c  */
#line 341 "parser.y"
    {(yyval.pliteral) = new NmemberLiteral((yyvsp[(1) - (3)].pconst),(yyvsp[(3) - (3)].pterm));;}
    break;

  case 105:

/* Line 1455 of yacc.c  */
#line 342 "parser.y"
    {(yyval.pliteral) = new NmemberLiteral((yyvsp[(1) - (3)].pconst),(yyvsp[(3) - (3)].pvar));;}
    break;

  case 106:

/* Line 1455 of yacc.c  */
#line 343 "parser.y"
    {(yyval.pliteral) = new NmemberLiteral((yyvsp[(1) - (3)].pvar),(yyvsp[(3) - (3)].pterm));;}
    break;

  case 107:

/* Line 1455 of yacc.c  */
#line 344 "parser.y"
    {(yyval.pliteral) = new NmemberLiteral((yyvsp[(1) - (3)].pvar),(yyvsp[(3) - (3)].pvar));;}
    break;

  case 108:

/* Line 1455 of yacc.c  */
#line 345 "parser.y"
    {(yyval.pliteral) = new NmemberLiteral((yyvsp[(1) - (3)].pterm),(yyvsp[(3) - (3)].pterm));;}
    break;

  case 109:

/* Line 1455 of yacc.c  */
#line 346 "parser.y"
    {(yyval.pliteral) = new NmemberLiteral((yyvsp[(1) - (3)].pterm),(yyvsp[(3) - (3)].pvar));;}
    break;

  case 110:

/* Line 1455 of yacc.c  */
#line 349 "parser.y"
    {(yyval.pterm)= (yyvsp[(1) - (1)].pterm);;}
    break;

  case 111:

/* Line 1455 of yacc.c  */
#line 350 "parser.y"
    {(yyval.pterm) = (yyvsp[(1) - (1)].pterm);;}
    break;

  case 112:

/* Line 1455 of yacc.c  */
#line 354 "parser.y"
    {(yyval.pliteral) = new AffectLiteral((yyvsp[(1) - (3)].pvar), (yyvsp[(3) - (3)].pterm));;}
    break;

  case 113:

/* Line 1455 of yacc.c  */
#line 355 "parser.y"
    {(yyval.pliteral) = new AffectLiteral((yyvsp[(1) - (3)].pvar), (yyvsp[(3) - (3)].pterm));;}
    break;

  case 114:

/* Line 1455 of yacc.c  */
#line 356 "parser.y"
    {(yyval.pliteral) = new AffectLiteral((yyvsp[(1) - (3)].pvar), (yyvsp[(3) - (3)].pconst));;}
    break;

  case 115:

/* Line 1455 of yacc.c  */
#line 359 "parser.y"
    {(yyval.pterm) = new BinaryArithExpr((yyvsp[(2) - (3)].oper), (yyvsp[(1) - (3)].pterm), (yyvsp[(3) - (3)].pterm));;}
    break;

  case 116:

/* Line 1455 of yacc.c  */
#line 360 "parser.y"
    {(yyval.pterm) = new BinaryArithExpr((yyvsp[(2) - (3)].oper), (yyvsp[(1) - (3)].pterm), (yyvsp[(3) - (3)].pterm));;}
    break;

  case 117:

/* Line 1455 of yacc.c  */
#line 361 "parser.y"
    {(yyval.pterm) = new BinaryArithExpr((yyvsp[(2) - (3)].oper), (yyvsp[(1) - (3)].pterm), (yyvsp[(3) - (3)].pterm));;}
    break;

  case 118:

/* Line 1455 of yacc.c  */
#line 362 "parser.y"
    {(yyval.pterm) = new BinaryArithExpr((yyvsp[(2) - (3)].oper), (yyvsp[(1) - (3)].pterm), (yyvsp[(3) - (3)].pterm));;}
    break;

  case 119:

/* Line 1455 of yacc.c  */
#line 363 "parser.y"
    {(yyval.pterm) = new BinaryArithExpr((yyvsp[(2) - (3)].oper), (yyvsp[(1) - (3)].pterm), (yyvsp[(3) - (3)].pterm));;}
    break;

  case 120:

/* Line 1455 of yacc.c  */
#line 364 "parser.y"
    {(yyval.pterm) = new BinaryArithExpr((yyvsp[(2) - (3)].oper), (yyvsp[(1) - (3)].pterm), (yyvsp[(3) - (3)].pterm));;}
    break;

  case 121:

/* Line 1455 of yacc.c  */
#line 365 "parser.y"
    {(yyval.pterm) = new UnaryArithExpr((yyvsp[(1) - (4)].oper), (yyvsp[(3) - (4)].pterm));;}
    break;

  case 122:

/* Line 1455 of yacc.c  */
#line 366 "parser.y"
    {(yyval.pterm) = (yyvsp[(2) - (3)].pterm);;}
    break;

  case 123:

/* Line 1455 of yacc.c  */
#line 369 "parser.y"
    {(yyval.pterm)= (yyvsp[(1) - (1)].pterm);;}
    break;

  case 124:

/* Line 1455 of yacc.c  */
#line 370 "parser.y"
    {(yyval.pterm) = (yyvsp[(1) - (1)].pvar);;}
    break;

  case 125:

/* Line 1455 of yacc.c  */
#line 371 "parser.y"
    {(yyval.pterm) = (yyvsp[(1) - (1)].pterm);;}
    break;

  case 126:

/* Line 1455 of yacc.c  */
#line 375 "parser.y"
    {(yyval.pconst)= SymbConst::new_SymbConst((yyvsp[(1) - (1)].chaine));;}
    break;

  case 127:

/* Line 1455 of yacc.c  */
#line 379 "parser.y"
    {try{ (yyval.pterm)= NumConst::new_NumConst((yyvsp[(1) - (1)].num));
     				 }
     				 catch(OutOfRangeNumConst){
				      std::cerr<<"Out of range numeric constant "<<std::endl;
			 	      yynerrs++; YYERROR;
				  }
				 ;}
    break;

  case 128:

/* Line 1455 of yacc.c  */
#line 386 "parser.y"
    {try{ (yyval.pterm)= NumConst::new_NumConst(-(yyvsp[(2) - (2)].num));
     				 }
     				 catch(OutOfRangeNumConst){
				      std::cerr<<"Out of range numeric constant "<<std::endl;
			 	      yynerrs++; YYERROR;
				  }
				 ;}
    break;

  case 129:

/* Line 1455 of yacc.c  */
#line 397 "parser.y"
    {MapStrVar::iterator it = map->find(*(yyvsp[(1) - (1)].chaine));
				 if (it != map->end()){
				 	(yyval.pvar) = (*it).second;
					delete (yyvsp[(1) - (1)].chaine);
				 }
				 else {
					Variable* v = new Variable((yyvsp[(1) - (1)].chaine));
					(yyval.pvar) = v;
					map->insert(std::make_pair(*(yyvsp[(1) - (1)].chaine),v));
					set->insert(v);
				  }
				 ;}
    break;

  case 130:

/* Line 1455 of yacc.c  */
#line 412 "parser.y"
    {defaultShow = false;;}
    break;

  case 131:

/* Line 1455 of yacc.c  */
#line 413 "parser.y"
    {hideSet.insert((yyvsp[(2) - (3)].chaine));;}
    break;

  case 132:

/* Line 1455 of yacc.c  */
#line 414 "parser.y"
    {showSet.insert((yyvsp[(2) - (3)].chaine));;}
    break;

  case 133:

/* Line 1455 of yacc.c  */
#line 417 "parser.y"
    {(yyval.chaine) = new std::string;
       					 std::stringstream ss;
       				  	 ss << *((yyvsp[(1) - (3)].chaine)) << "/" << (yyvsp[(3) - (3)].num); // cast int2string
       					 ss >> *(yyval.chaine) ;
					 delete (yyvsp[(1) - (3)].chaine);;}
    break;



/* Line 1455 of yacc.c  */
#line 2652 "parser.cpp"
      default: break;
    }
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
yyerrlab:
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
      {
	YYSIZE_T yysize = yysyntax_error (0, yystate, yychar);
	if (yymsg_alloc < yysize && yymsg_alloc < YYSTACK_ALLOC_MAXIMUM)
	  {
	    YYSIZE_T yyalloc = 2 * yysize;
	    if (! (yysize <= yyalloc && yyalloc <= YYSTACK_ALLOC_MAXIMUM))
	      yyalloc = YYSTACK_ALLOC_MAXIMUM;
	    if (yymsg != yymsgbuf)
	      YYSTACK_FREE (yymsg);
	    yymsg = (char *) YYSTACK_ALLOC (yyalloc);
	    if (yymsg)
	      yymsg_alloc = yyalloc;
	    else
	      {
		yymsg = yymsgbuf;
		yymsg_alloc = sizeof yymsgbuf;
	      }
	  }

	if (0 < yysize && yysize <= yymsg_alloc)
	  {
	    (void) yysyntax_error (yymsg, yystate, yychar);
	    yyerror (yymsg);
	  }
	else
	  {
	    yyerror (YY_("syntax error"));
	    if (yysize != 0)
	      goto yyexhaustedlab;
	  }
      }
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
	 error, discard it.  */

      if (yychar <= YYEOF)
	{
	  /* Return failure if at end of input.  */
	  if (yychar == YYEOF)
	    YYABORT;
	}
      else
	{
	  yydestruct ("Error: discarding",
		      yytoken, &yylval);
	  yychar = YYEMPTY;
	}
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  /* Do not reclaim the symbols of the rule which action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;	/* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (yyn != YYPACT_NINF)
	{
	  yyn += YYTERROR;
	  if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
	    {
	      yyn = yytable[yyn];
	      if (0 < yyn)
		break;
	    }
	}

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
	YYABORT;


      yydestruct ("Error: popping",
		  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  *++yyvsp = yylval;


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#if !defined(yyoverflow) || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
     yydestruct ("Cleanup: discarding lookahead",
		 yytoken, &yylval);
  /* Do not reclaim the symbols of the rule which action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
		  yystos[*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  /* Make sure YYID is used.  */
  return YYID (yyresult);
}



/* Line 1675 of yacc.c  */
#line 423 "parser.y"

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





