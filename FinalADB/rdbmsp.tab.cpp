/* A Bison parser, made by GNU Bison 1.875d.  */

/* Skeleton parser for Yacc-like parsing with Bison,
   Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004 Free Software Foundation, Inc.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 59 Temple Place - Suite 330,
   Boston, MA 02111-1307, USA.  */

/* As a special exception, when this file is copied by Bison into a
   Bison output file, you may use that output file without restriction.
   This special exception was added by the Free Software Foundation
   in version 1.24 of Bison.  */

/* Written by Richard Stallman by simplifying the original so called
   ``semantic'' parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Using locations.  */
#define YYLSP_NEEDED 0



/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     SELECT = 258,
     INSERT = 259,
     UPDATE = 260,
     DELETE = 261,
     CREATE = 262,
     DROP = 263,
     ALTER = 264,
     COMMIT = 265,
     EXITST = 266,
     GET = 267,
     TO = 268,
     INTNUM = 269,
     APPROXNUM = 270,
     IDENTIFIER = 271,
     NEWLINE = 272,
     TABLE = 273,
     LEFTPARANTHESIS = 274,
     RIGHTPARANTHESIS = 275,
     INTO = 276,
     DATABASE = 277,
     SHOW = 278,
     CLEAR = 279,
     FROM = 280,
     DOT = 281,
     COMMA = 282,
     CHARACTER = 283,
     INTEGER = 284,
     DATE = 285,
     NOT = 286,
     NULLX = 287,
     UNIQUE = 288,
     PRIMARY = 289,
     KEY = 290,
     DEFAULT = 291,
     ALL = 292,
     DISTINCT = 293,
     STAR = 294,
     WHERE = 295,
     OR = 296,
     AND = 297,
     VALUES = 298,
     ISEQUALTO = 299,
     SET = 300,
     ADD = 301,
     STRING = 302,
     DATELITERAL = 303,
     GREATERTHAN = 304,
     LESSTHAN = 305,
     GREATERTHANE = 306,
     LESSTHANE = 307,
     NOTEQUALTO = 308,
     USE = 309,
     DESC = 310
   };
#endif
#define SELECT 258
#define INSERT 259
#define UPDATE 260
#define DELETE 261
#define CREATE 262
#define DROP 263
#define ALTER 264
#define COMMIT 265
#define EXITST 266
#define GET 267
#define TO 268
#define INTNUM 269
#define APPROXNUM 270
#define IDENTIFIER 271
#define NEWLINE 272
#define TABLE 273
#define LEFTPARANTHESIS 274
#define RIGHTPARANTHESIS 275
#define INTO 276
#define DATABASE 277
#define SHOW 278
#define CLEAR 279
#define FROM 280
#define DOT 281
#define COMMA 282
#define CHARACTER 283
#define INTEGER 284
#define DATE 285
#define NOT 286
#define NULLX 287
#define UNIQUE 288
#define PRIMARY 289
#define KEY 290
#define DEFAULT 291
#define ALL 292
#define DISTINCT 293
#define STAR 294
#define WHERE 295
#define OR 296
#define AND 297
#define VALUES 298
#define ISEQUALTO 299
#define SET 300
#define ADD 301
#define STRING 302
#define DATELITERAL 303
#define GREATERTHAN 304
#define LESSTHAN 305
#define GREATERTHANE 306
#define LESSTHANE 307
#define NOTEQUALTO 308
#define USE 309
#define DESC 310




/* Copy the first part of user declarations.  */
#line 9 "rdbmsp.ypp"

 #include <stdio.h>
 #include <unistd.h>
 #include <stdlib.h>
 #include "DBEngine/VSDBEngine.h"
 #include "DBEngine/BufferManager/standards.h"
 #define DEFINTLEN    5
 #define DEFCHARLEN   6
 #define DEFDATELEN   10
 #define UDBFILE      "udbfile"
 void goToPrompt();
 int yyparse (void *YYPARSE_PARAM);
 void yyerror(char *error);
 int yylex();
 void resetOnError();
 void doORorAND(int);
 void start();
 
 time_t startT;
 time_t endT;
 char  notNullFlag=NO,uniqueFlag=NO,primaryKeyFlag=NO;
 short dataTypeFlag=0;
 int length=0,precision=0; //-1 specifies that the value is not taken
 char *columnName=0;
 char *defaultValue=0;
 char *tableName=0;
 char *dbName=0;
 short position=0;
 createColumns *cColumns=NULL;
 FieldNames *pkeyNames=NULL;
 FieldNames *uniqueNames=NULL;
 FieldNames *tempFieldNames=NULL;
 TLQds *tLQds=0;
 
 short whereExistsFlag=0;
 AttributeValues *aValues=NULL;
 FieldNames      *fNames=NULL;
 RLQds *rLQds=0;
 
 RID *ridList=NULL,*tempRIDList=NULL;
 RID *nextList=NULL;
 int selectsErrFlag=SUCCESS;
  
 //for Database level queriesssssssssss
 int DBQuery(char *dbname,int type);
 int TLQuery(int type);
 int RLQuery(int type);
 void getInputFromFile(char*,int,int);
 
short promptFlag=0;

 UQH *updateHan;
 SQH *selectHan;
 DQH *deleteHan;
 VSDBEngine *dbe;
 VSBufferManager *vSB=NULL;


/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 1
#endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

#if ! defined (YYSTYPE) && ! defined (YYSTYPE_IS_DECLARED)
typedef int YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif



/* Copy the second part of user declarations.  */


/* Line 214 of yacc.c.  */
#line 255 "rdbmsp.tab.cpp"

#if ! defined (yyoverflow) || YYERROR_VERBOSE

# ifndef YYFREE
#  define YYFREE free
# endif
# ifndef YYMALLOC
#  define YYMALLOC malloc
# endif

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   define YYSTACK_ALLOC alloca
#  endif
# else
#  if defined (alloca) || defined (_ALLOCA_H)
#   define YYSTACK_ALLOC alloca
#  else
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning. */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
# else
#  if defined (__STDC__) || defined (__cplusplus)
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   define YYSIZE_T size_t
#  endif
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
# endif
#endif /* ! defined (yyoverflow) || YYERROR_VERBOSE */


#if (! defined (yyoverflow) \
     && (! defined (__cplusplus) \
	 || (defined (YYSTYPE_IS_TRIVIAL) && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  short int yyss;
  YYSTYPE yyvs;
  };

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (short int) + sizeof (YYSTYPE))			\
      + YYSTACK_GAP_MAXIMUM)

/* Copy COUNT objects from FROM to TO.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined (__GNUC__) && 1 < __GNUC__
#   define YYCOPY(To, From, Count) \
      __builtin_memcpy (To, From, (Count) * sizeof (*(From)))
#  else
#   define YYCOPY(To, From, Count)		\
      do					\
	{					\
	  register YYSIZE_T yyi;		\
	  for (yyi = 0; yyi < (Count); yyi++)	\
	    (To)[yyi] = (From)[yyi];		\
	}					\
      while (0)
#  endif
# endif

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack)					\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack, Stack, yysize);				\
	Stack = &yyptr->Stack;						\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (0)

#endif

#if defined (__STDC__) || defined (__cplusplus)
   typedef signed char yysigned_char;
#else
   typedef short int yysigned_char;
#endif

/* YYFINAL -- State number of the termination state. */
#define YYFINAL  3
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   162

/* YYNTOKENS -- Number of terminals. */
#define YYNTOKENS  56
/* YYNNTS -- Number of nonterminals. */
#define YYNNTS  43
/* YYNRULES -- Number of rules. */
#define YYNRULES  105
/* YYNRULES -- Number of states. */
#define YYNSTATES  188

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   310

#define YYTRANSLATE(YYX) 						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const unsigned char yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
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
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const unsigned short int yyprhs[] =
{
       0,     0,     3,     4,     8,    10,    12,    14,    16,    18,
      20,    22,    24,    30,    34,    38,    41,    44,    46,    48,
      50,    52,    54,    56,    58,    60,    62,    64,    66,    73,
      75,    79,    81,    85,    87,    89,    93,    95,   100,   102,
     107,   109,   118,   119,   122,   125,   129,   132,   135,   138,
     140,   142,   144,   146,   148,   153,   159,   161,   165,   169,
     172,   177,   179,   183,   190,   194,   197,   202,   203,   205,
     207,   209,   211,   213,   217,   220,   223,   224,   227,   231,
     235,   238,   240,   244,   248,   252,   256,   260,   264,   270,
     271,   275,   280,   282,   286,   288,   290,   292,   299,   300,
     302,   306,   310,   314,   318,   323
};

/* YYRHS -- A `-1'-separated list of the rules' RHS. */
static const yysigned_char yyrhs[] =
{
      57,     0,    -1,    -1,    57,    58,    17,    -1,    17,    -1,
      60,    -1,    61,    -1,    59,    -1,    62,    -1,    63,    -1,
      11,    -1,    24,    -1,    12,    16,    14,    13,    14,    -1,
       7,    22,    16,    -1,     8,    22,    16,    -1,    54,    16,
      -1,    23,    16,    -1,    23,    -1,    54,    -1,    64,    -1,
      75,    -1,    77,    -1,    76,    -1,    80,    -1,    89,    -1,
      97,    -1,    94,    -1,    98,    -1,     7,    18,    65,    19,
      66,    20,    -1,    16,    -1,    16,    26,    16,    -1,    67,
      -1,    66,    27,    67,    -1,    68,    -1,    73,    -1,    16,
      69,    70,    -1,    28,    -1,    28,    19,    14,    20,    -1,
      29,    -1,    29,    19,    14,    20,    -1,    30,    -1,    30,
      19,    14,    27,    14,    27,    14,    20,    -1,    -1,    70,
      71,    -1,    31,    32,    -1,    31,    32,    33,    -1,    34,
      35,    -1,    36,    72,    -1,    36,    32,    -1,    33,    -1,
      14,    -1,    15,    -1,    47,    -1,    48,    -1,    33,    19,
      74,    20,    -1,    34,    35,    19,    74,    20,    -1,    16,
      -1,    74,    27,    16,    -1,     8,    18,    65,    -1,    55,
      65,    -1,     9,    18,    65,    78,    -1,    79,    -1,    78,
      27,    79,    -1,    46,    16,    69,    45,    36,    93,    -1,
      46,    16,    69,    -1,     8,    16,    -1,     3,    81,    82,
      84,    -1,    -1,    37,    -1,    38,    -1,    39,    -1,    83,
      -1,    16,    -1,    83,    27,    16,    -1,    85,    86,    -1,
      25,    65,    -1,    -1,    40,    87,    -1,    87,    41,    87,
      -1,    87,    42,    87,    -1,    31,    87,    -1,    88,    -1,
      16,    50,    72,    -1,    16,    52,    72,    -1,    16,    49,
      72,    -1,    16,    51,    72,    -1,    16,    53,    72,    -1,
      16,    44,    72,    -1,     4,    21,    65,    90,    91,    -1,
      -1,    19,    83,    20,    -1,    43,    19,    92,    20,    -1,
      93,    -1,    92,    27,    93,    -1,    72,    -1,    32,    -1,
      36,    -1,     5,    65,    45,    95,    40,    87,    -1,    -1,
      96,    -1,    95,    27,    96,    -1,    16,    44,    72,    -1,
      16,    44,    32,    -1,    16,    44,    36,    -1,     6,    25,
      65,    86,    -1,    10,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const unsigned short int yyrline[] =
{
       0,    81,    81,    82,    83,    86,    87,    88,    89,    91,
      92,   100,   103,   113,   114,   115,   116,   117,   118,   121,
     122,   123,   124,   127,   128,   129,   130,   139,   145,   153,
     159,   167,   168,   171,   172,   175,   210,   214,   219,   223,
     228,   232,   247,   248,   251,   252,   253,   254,   259,   264,
     269,   270,   271,   272,   275,   276,   279,   280,   284,   293,
     302,   305,   306,   309,   310,   311,   316,   324,   325,   326,
     329,   330,   332,   333,   335,   338,   341,   342,   345,   346,
     347,   349,   352,   364,   375,   386,   397,   408,   421,   429,
     430,   433,   436,   437,   440,   441,   442,   446,   449,   450,
     451,   454,   455,   456,   460,   469
};
#endif

#if YYDEBUG || YYERROR_VERBOSE
/* YYTNME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals. */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "SELECT", "INSERT", "UPDATE", "DELETE",
  "CREATE", "DROP", "ALTER", "COMMIT", "EXITST", "GET", "TO", "INTNUM",
  "APPROXNUM", "IDENTIFIER", "NEWLINE", "TABLE", "LEFTPARANTHESIS",
  "RIGHTPARANTHESIS", "INTO", "DATABASE", "SHOW", "CLEAR", "FROM", "DOT",
  "COMMA", "CHARACTER", "INTEGER", "DATE", "NOT", "NULLX", "UNIQUE",
  "PRIMARY", "KEY", "DEFAULT", "ALL", "DISTINCT", "STAR", "WHERE", "OR",
  "AND", "VALUES", "ISEQUALTO", "SET", "ADD", "STRING", "DATELITERAL",
  "GREATERTHAN", "LESSTHAN", "GREATERTHANE", "LESSTHANE", "NOTEQUALTO",
  "USE", "DESC", "$accept", "s", "start", "getcommand_statement",
  "databaselevel_statements", "tablelevel_statements",
  "recordlevel_statements", "misc_statements", "create_statement", "table",
  "new_table_elements", "new_table_element", "column_defination",
  "data_type", "column_defination_options", "column_defination_option",
  "literal", "table_constraints_defination", "columnsT", "drop_statement",
  "desc_statement", "alter_statement", "alters", "alter",
  "select_statement", "optional_allordistinct", "selection", "columns",
  "table_expression", "from_clause", "whereClause", "conditionStatement",
  "comparision", "insert_statement", "optional_columns", "values_must",
  "values", "value", "update_statement", "assignments", "assignment",
  "delete_statement", "commit_statement", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const unsigned short int yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308,   309,   310
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const unsigned char yyr1[] =
{
       0,    56,    57,    57,    57,    58,    58,    58,    58,    58,
      58,    58,    59,    60,    60,    60,    60,    60,    60,    61,
      61,    61,    61,    62,    62,    62,    62,    63,    64,    65,
      65,    66,    66,    67,    67,    68,    69,    69,    69,    69,
      69,    69,    70,    70,    71,    71,    71,    71,    71,    71,
      72,    72,    72,    72,    73,    73,    74,    74,    75,    76,
      77,    78,    78,    79,    79,    79,    80,    81,    81,    81,
      82,    82,    83,    83,    84,    85,    86,    86,    87,    87,
      87,    87,    88,    88,    88,    88,    88,    88,    89,    90,
      90,    91,    92,    92,    93,    93,    93,    94,    95,    95,
      95,    96,    96,    96,    97,    98
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const unsigned char yyr2[] =
{
       0,     2,     0,     3,     1,     1,     1,     1,     1,     1,
       1,     1,     5,     3,     3,     2,     2,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     6,     1,
       3,     1,     3,     1,     1,     3,     1,     4,     1,     4,
       1,     8,     0,     2,     2,     3,     2,     2,     2,     1,
       1,     1,     1,     1,     4,     5,     1,     3,     3,     2,
       4,     1,     3,     6,     3,     2,     4,     0,     1,     1,
       1,     1,     1,     3,     2,     2,     0,     2,     3,     3,
       2,     1,     3,     3,     3,     3,     3,     3,     5,     0,
       3,     4,     1,     3,     1,     1,     1,     6,     0,     1,
       3,     3,     3,     3,     4,     1
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const unsigned char yydefact[] =
{
       2,     4,     0,     1,    67,     0,     0,     0,     0,     0,
       0,   105,    10,     0,    17,    11,    18,     0,     0,     7,
       5,     6,     8,     9,    19,    20,    22,    21,    23,    24,
      26,    25,    27,    68,    69,     0,     0,    29,     0,     0,
       0,     0,     0,     0,     0,     0,    16,    15,    59,     3,
      72,    70,     0,    71,    89,     0,    98,    76,     0,    13,
      58,    14,     0,     0,     0,    66,    76,     0,     0,     0,
      30,     0,     0,    99,     0,   104,     0,     0,     0,    60,
      61,     0,    75,    74,    73,     0,     0,    88,     0,     0,
       0,     0,     0,    77,    81,     0,     0,     0,     0,    31,
      33,    34,    65,     0,     0,    12,    90,     0,    50,    51,
     102,   103,    52,    53,   101,   100,    97,     0,     0,     0,
       0,     0,     0,    80,     0,     0,    36,    38,    40,    42,
       0,     0,    28,     0,    64,    62,    95,    96,    94,     0,
      92,    87,    84,    82,    85,    83,    86,    78,    79,     0,
       0,     0,    35,    56,     0,     0,    32,     0,    91,     0,
       0,     0,     0,     0,    49,     0,     0,    43,    54,     0,
       0,     0,    93,    37,    39,     0,    44,    46,    48,    47,
      57,    55,    63,     0,    45,     0,     0,    41
};

/* YYDEFGOTO[NTERM-NUM]. */
static const short int yydefgoto[] =
{
      -1,     2,    18,    19,    20,    21,    22,    23,    24,    38,
      98,    99,   100,   129,   152,   167,   138,   101,   154,    25,
      26,    27,    79,    80,    28,    35,    52,    53,    65,    66,
      75,    93,    94,    29,    69,    87,   139,   140,    30,    72,
      73,    31,    32
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -107
static const short int yypact[] =
{
      -3,  -107,     1,  -107,    64,     2,    75,     3,    49,    54,
      44,  -107,  -107,    81,    89,  -107,    90,    75,    91,  -107,
    -107,  -107,  -107,  -107,  -107,  -107,  -107,  -107,  -107,  -107,
    -107,  -107,  -107,  -107,  -107,     6,    75,    83,    65,    75,
      75,    95,    75,    96,    75,    93,  -107,  -107,  -107,  -107,
    -107,  -107,    88,    87,    97,    99,   101,    78,   100,  -107,
    -107,  -107,    -6,   107,    75,  -107,    78,   105,   106,    80,
    -107,    82,    34,  -107,    26,  -107,   -13,   108,   109,   102,
    -107,   113,  -107,  -107,  -107,    46,   111,  -107,    12,   101,
      26,    33,    26,    62,  -107,    70,   112,    98,    48,  -107,
    -107,  -107,  -107,    70,    -6,  -107,  -107,    22,  -107,  -107,
    -107,  -107,  -107,  -107,  -107,  -107,    62,     4,     4,     4,
       4,     4,     4,    62,    26,    26,   115,   116,   117,  -107,
     121,   119,  -107,   -13,    94,  -107,  -107,  -107,  -107,    61,
    -107,  -107,  -107,  -107,  -107,  -107,  -107,    62,    62,   114,
     118,   126,    59,  -107,    67,   121,  -107,   110,  -107,    22,
     122,   123,   120,   124,  -107,   125,    32,  -107,  -107,   128,
      69,    22,  -107,  -107,  -107,   127,   129,  -107,  -107,  -107,
    -107,  -107,  -107,   130,  -107,   131,   132,  -107
};

/* YYPGOTO[NTERM-NUM].  */
static const yysigned_char yypgoto[] =
{
    -107,  -107,  -107,  -107,  -107,  -107,  -107,  -107,  -107,    -1,
    -107,    15,  -107,    47,  -107,  -107,   -88,  -107,    -4,  -107,
    -107,  -107,  -107,    45,  -107,  -107,  -107,    85,  -107,  -107,
      92,   -75,  -107,  -107,  -107,  -107,  -107,  -106,  -107,  -107,
      66,  -107,  -107
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -1
static const unsigned char yytable[] =
{
     114,     3,    77,    95,     4,     5,     6,     7,     8,     9,
      10,    11,    12,    13,     1,   116,    48,   123,   108,   109,
      96,    97,    50,    36,    14,    15,   108,   109,    39,   141,
     142,   143,   144,   145,   146,    54,   108,   109,    57,    58,
      78,    60,    91,    62,   110,    51,   108,   109,   111,   147,
     148,   112,   113,   172,   136,    16,    17,    92,   137,   112,
     113,    89,    44,    82,   178,   182,   106,    40,   132,   112,
     113,    41,    42,    67,    90,   133,    43,   117,   179,   112,
     113,   158,   118,   119,   120,   121,   122,   168,   159,   181,
     163,    37,   164,   165,   169,   166,   169,    45,   126,   127,
     128,    33,    34,   124,   125,    46,    47,    63,    49,    55,
      56,    59,    61,    64,    67,    70,    68,    71,    74,    76,
      81,    84,    50,    86,   102,   103,    88,   105,   160,   104,
     107,   130,   161,   131,   149,   150,   151,   153,   155,   157,
     162,   183,   173,   174,   180,   186,   171,   175,   156,   135,
     134,   170,   187,    85,     0,   115,   176,   185,    83,     0,
     177,     0,   184
};

static const short int yycheck[] =
{
      88,     0,     8,    16,     3,     4,     5,     6,     7,     8,
       9,    10,    11,    12,    17,    90,    17,    92,    14,    15,
      33,    34,    16,    21,    23,    24,    14,    15,    25,   117,
     118,   119,   120,   121,   122,    36,    14,    15,    39,    40,
      46,    42,    16,    44,    32,    39,    14,    15,    36,   124,
     125,    47,    48,   159,    32,    54,    55,    31,    36,    47,
      48,    27,    18,    64,    32,   171,    20,    18,    20,    47,
      48,    22,    18,    27,    40,    27,    22,    44,   166,    47,
      48,    20,    49,    50,    51,    52,    53,    20,    27,    20,
      31,    16,    33,    34,    27,    36,    27,    16,    28,    29,
      30,    37,    38,    41,    42,    16,    16,    14,    17,    26,
      45,    16,    16,    25,    27,    16,    19,    16,    40,    19,
      13,    16,    16,    43,    16,    16,    44,    14,    14,    27,
      19,    19,    14,    35,    19,    19,    19,    16,    19,    45,
      14,    14,    20,    20,    16,    14,    36,    27,   133,   104,
     103,   155,    20,    68,    -1,    89,    32,    27,    66,    -1,
      35,    -1,    33
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const unsigned char yystos[] =
{
       0,    17,    57,     0,     3,     4,     5,     6,     7,     8,
       9,    10,    11,    12,    23,    24,    54,    55,    58,    59,
      60,    61,    62,    63,    64,    75,    76,    77,    80,    89,
      94,    97,    98,    37,    38,    81,    21,    16,    65,    25,
      18,    22,    18,    22,    18,    16,    16,    16,    65,    17,
      16,    39,    82,    83,    65,    26,    45,    65,    65,    16,
      65,    16,    65,    14,    25,    84,    85,    27,    19,    90,
      16,    16,    95,    96,    40,    86,    19,     8,    46,    78,
      79,    13,    65,    86,    16,    83,    43,    91,    44,    27,
      40,    16,    31,    87,    88,    16,    33,    34,    66,    67,
      68,    73,    16,    16,    27,    14,    20,    19,    14,    15,
      32,    36,    47,    48,    72,    96,    87,    44,    49,    50,
      51,    52,    53,    87,    41,    42,    28,    29,    30,    69,
      19,    35,    20,    27,    69,    79,    32,    36,    72,    92,
      93,    72,    72,    72,    72,    72,    72,    87,    87,    19,
      19,    19,    70,    16,    74,    19,    67,    45,    20,    27,
      14,    14,    14,    31,    33,    34,    36,    71,    20,    27,
      74,    36,    93,    20,    20,    27,    32,    35,    32,    72,
      16,    20,    93,    14,    33,    27,    14,    20
};

#if ! defined (YYSIZE_T) && defined (__SIZE_TYPE__)
# define YYSIZE_T __SIZE_TYPE__
#endif
#if ! defined (YYSIZE_T) && defined (size_t)
# define YYSIZE_T size_t
#endif
#if ! defined (YYSIZE_T)
# if defined (__STDC__) || defined (__cplusplus)
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# endif
#endif
#if ! defined (YYSIZE_T)
# define YYSIZE_T unsigned int
#endif

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
      YYPOPSTACK;						\
      goto yybackup;						\
    }								\
  else								\
    { 								\
      yyerror ("syntax error: cannot back up");\
      YYERROR;							\
    }								\
while (0)

#define YYTERROR	1
#define YYERRCODE	256

/* YYLLOC_DEFAULT -- Compute the default location (before the actions
   are run).  */

#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)		\
   ((Current).first_line   = (Rhs)[1].first_line,	\
    (Current).first_column = (Rhs)[1].first_column,	\
    (Current).last_line    = (Rhs)[N].last_line,	\
    (Current).last_column  = (Rhs)[N].last_column)
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
} while (0)

# define YYDSYMPRINT(Args)			\
do {						\
  if (yydebug)					\
    yysymprint Args;				\
} while (0)

# define YYDSYMPRINTF(Title, Token, Value, Location)		\
do {								\
  if (yydebug)							\
    {								\
      YYFPRINTF (stderr, "%s ", Title);				\
      yysymprint (stderr, 					\
                  Token, Value);	\
      YYFPRINTF (stderr, "\n");					\
    }								\
} while (0)

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if defined (__STDC__) || defined (__cplusplus)
static void
yy_stack_print (short int *bottom, short int *top)
#else
static void
yy_stack_print (bottom, top)
    short int *bottom;
    short int *top;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (/* Nothing. */; bottom <= top; ++bottom)
    YYFPRINTF (stderr, " %d", *bottom);
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if defined (__STDC__) || defined (__cplusplus)
static void
yy_reduce_print (int yyrule)
#else
static void
yy_reduce_print (yyrule)
    int yyrule;
#endif
{
  int yyi;
  unsigned int yylno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %u), ",
             yyrule - 1, yylno);
  /* Print the symbols being reduced, and their result.  */
  for (yyi = yyprhs[yyrule]; 0 <= yyrhs[yyi]; yyi++)
    YYFPRINTF (stderr, "%s ", yytname [yyrhs[yyi]]);
  YYFPRINTF (stderr, "-> %s\n", yytname [yyr1[yyrule]]);
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (Rule);		\
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YYDSYMPRINT(Args)
# define YYDSYMPRINTF(Title, Token, Value, Location)
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
   SIZE_MAX < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#if defined (YYMAXDEPTH) && YYMAXDEPTH == 0
# undef YYMAXDEPTH
#endif

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif



#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined (__GLIBC__) && defined (_STRING_H)
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
static YYSIZE_T
#   if defined (__STDC__) || defined (__cplusplus)
yystrlen (const char *yystr)
#   else
yystrlen (yystr)
     const char *yystr;
#   endif
{
  register const char *yys = yystr;

  while (*yys++ != '\0')
    continue;

  return yys - yystr - 1;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined (__GLIBC__) && defined (_STRING_H) && defined (_GNU_SOURCE)
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
#   if defined (__STDC__) || defined (__cplusplus)
yystpcpy (char *yydest, const char *yysrc)
#   else
yystpcpy (yydest, yysrc)
     char *yydest;
     const char *yysrc;
#   endif
{
  register char *yyd = yydest;
  register const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

#endif /* !YYERROR_VERBOSE */



#if YYDEBUG
/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if defined (__STDC__) || defined (__cplusplus)
static void
yysymprint (FILE *yyoutput, int yytype, YYSTYPE *yyvaluep)
#else
static void
yysymprint (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE *yyvaluep;
#endif
{
  /* Pacify ``unused variable'' warnings.  */
  (void) yyvaluep;

  if (yytype < YYNTOKENS)
    {
      YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
# ifdef YYPRINT
      YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# endif
    }
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  switch (yytype)
    {
      default:
        break;
    }
  YYFPRINTF (yyoutput, ")");
}

#endif /* ! YYDEBUG */
/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

#if defined (__STDC__) || defined (__cplusplus)
static void
yydestruct (int yytype, YYSTYPE *yyvaluep)
#else
static void
yydestruct (yytype, yyvaluep)
    int yytype;
    YYSTYPE *yyvaluep;
#endif
{
  /* Pacify ``unused variable'' warnings.  */
  (void) yyvaluep;

  switch (yytype)
    {

      default:
        break;
    }
}


/* Prevent warnings from -Wmissing-prototypes.  */

#ifdef YYPARSE_PARAM
# if defined (__STDC__) || defined (__cplusplus)
int yyparse (void *YYPARSE_PARAM);
# else
int yyparse ();
# endif
#else /* ! YYPARSE_PARAM */
#if defined (__STDC__) || defined (__cplusplus)
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



/*----------.
| yyparse.  |
`----------*/

#ifdef YYPARSE_PARAM
# if defined (__STDC__) || defined (__cplusplus)
int yyparse (void *YYPARSE_PARAM)
# else
int yyparse (YYPARSE_PARAM)
  void *YYPARSE_PARAM;
# endif
#else /* ! YYPARSE_PARAM */
#if defined (__STDC__) || defined (__cplusplus)
int
yyparse (void)
#else
int
yyparse ()

#endif
#endif
{
  
  register int yystate;
  register int yyn;
  int yyresult;
  /* Number of tokens to shift before error messages enabled.  */
  int yyerrstatus;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;

  /* Three stacks and their tools:
     `yyss': related to states,
     `yyvs': related to semantic values,
     `yyls': related to locations.

     Refer to the stacks thru separate pointers, to allow yyoverflow
     to reallocate them elsewhere.  */

  /* The state stack.  */
  short int yyssa[YYINITDEPTH];
  short int *yyss = yyssa;
  register short int *yyssp;

  /* The semantic value stack.  */
  YYSTYPE yyvsa[YYINITDEPTH];
  YYSTYPE *yyvs = yyvsa;
  register YYSTYPE *yyvsp;



#define YYPOPSTACK   (yyvsp--, yyssp--)

  YYSIZE_T yystacksize = YYINITDEPTH;

  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;


  /* When reducing, the number of symbols on the RHS of the reduced
     rule.  */
  int yylen;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY;		/* Cause a token to be read.  */

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
     have just been pushed. so pushing a state here evens the stacks.
     */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
	/* Give user a chance to reallocate the stack. Use copies of
	   these so that the &'s don't force the real ones into
	   memory.  */
	YYSTYPE *yyvs1 = yyvs;
	short int *yyss1 = yyss;


	/* Each stack pointer address is followed by the size of the
	   data in use in that stack, in bytes.  This used to be a
	   conditional around just the two extra args, but that might
	   be undefined if yyoverflow is a macro.  */
	yyoverflow ("parser stack overflow",
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),

		    &yystacksize);

	yyss = yyss1;
	yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyoverflowlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
	goto yyoverflowlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
	yystacksize = YYMAXDEPTH;

      {
	short int *yyss1 = yyss;
	union yyalloc *yyptr =
	  (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
	if (! yyptr)
	  goto yyoverflowlab;
	YYSTACK_RELOCATE (yyss);
	YYSTACK_RELOCATE (yyvs);

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

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

/* Do appropriate processing given the current state.  */
/* Read a lookahead token if we need one and don't already have one.  */
/* yyresume: */

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
      YYDSYMPRINTF ("Next token is", yytoken, &yylval, &yylloc);
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

  if (yyn == YYFINAL)
    YYACCEPT;

  /* Shift the lookahead token.  */
  YYDPRINTF ((stderr, "Shifting token %s, ", yytname[yytoken]));

  /* Discard the token being shifted unless it is eof.  */
  if (yychar != YYEOF)
    yychar = YYEMPTY;

  *++yyvsp = yylval;


  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  yystate = yyn;
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
        case 3:
#line 82 "rdbmsp.ypp"
    { if(promptFlag==1)	goToPrompt(); ;}
    break;

  case 4:
#line 83 "rdbmsp.ypp"
    { if(promptFlag==1)	goToPrompt(); ;}
    break;

  case 10:
#line 92 "rdbmsp.ypp"
    {
			  FILE *tt1=fopen(UDBFILE,"w");
			  fprintf(tt1,"%s",DLQH::dBName);
			  fclose(tt1);
			  dbe->~VSDBEngine(); 
			  printf("\n\t\t\t Thank Q\n"); 
			  exit(0);
			  ;}
    break;

  case 11:
#line 100 "rdbmsp.ypp"
    {system("clear");;}
    break;

  case 12:
#line 103 "rdbmsp.ypp"
    { 
								printf("\n\t\"%s\" is file requested for input and from line %s  to  line %s\n",
										(char*)yyvsp[-3],(char*)yyvsp[-2],(char*)yyvsp[0]);
								if(access((char*)yyvsp[-3],F_OK)!=0) 
									printf("\n\t\tSorry! \"%s\" file doesnot exist to input\n",(char*)yyvsp[-3]);
								else
									getInputFromFile((char*)yyvsp[-3],atoi((char*)yyvsp[-2]),atoi((char*)yyvsp[0]));	
								;}
    break;

  case 13:
#line 113 "rdbmsp.ypp"
    {DBQuery((char*)yyvsp[0],CREATEDATABASE);;}
    break;

  case 14:
#line 114 "rdbmsp.ypp"
    {DBQuery((char*)yyvsp[0],DROPDATABASE);;}
    break;

  case 15:
#line 115 "rdbmsp.ypp"
    {DBQuery((char*)yyvsp[0],USEDATABASE);;}
    break;

  case 16:
#line 116 "rdbmsp.ypp"
    {DBQuery((char*)yyvsp[0],SHOWDATABASE);;}
    break;

  case 17:
#line 117 "rdbmsp.ypp"
    {DBQuery(NULL     ,SHOWDATABASE);;}
    break;

  case 18:
#line 118 "rdbmsp.ypp"
    {DBQuery(NULL     ,SHOWD);;}
    break;

  case 28:
#line 145 "rdbmsp.ypp"
    {
												time(&startT);	
												TLQuery(CREATETABLE);		
												time(&endT);
												printf("\nExecution Time %lf seconds \n",difftime(endT,startT));
												;}
    break;

  case 29:
#line 153 "rdbmsp.ypp"
    { 
				       if(dbName==0)	dbName=(char*)MSF::myMalloc(strlen(DLQH::dBName));
				       strcpy(dbName,DLQH::dBName);	
				       if(tableName==0)	tableName=(char*)MSF::myMalloc(strlen((char*)yyvsp[0]));
				       strcpy(tableName,(char*)yyvsp[0]);
				       ;}
    break;

  case 30:
#line 159 "rdbmsp.ypp"
    {
				       if(dbName==0)	dbName=(char*)MSF::myMalloc(strlen((char*)yyvsp[-2]));
				       strcpy(dbName,(char*)yyvsp[-2]);
				       if(tableName==0)	tableName=(char*)MSF::myMalloc(strlen((char*)yyvsp[0]));
				       strcpy(tableName,(char*)yyvsp[0]);
				       ;}
    break;

  case 35:
#line 175 "rdbmsp.ypp"
    { 
									if(columnName==0)	
										columnName=(char*)MSF::myMalloc(strlen((char*)yyvsp[-2]));
									strcpy(columnName,(char*)yyvsp[-2]);	
									position++;
									if(length==0)
										{
										if(dataTypeFlag==DBINTTYPE)
											length=DEFINTLEN;
										else if(dataTypeFlag==DBCHARTYPE)
											length=DEFCHARLEN;
										else if(dataTypeFlag==DBDATETYPE)
											length=DEFDATELEN;
										}
									TLQH::InsertToList(&cColumns,columnName,dataTypeFlag,length,precision,
									               defaultValue,notNullFlag,uniqueFlag,primaryKeyFlag,position);
									if(columnName!=0)
										{	
										MSF::myFree(columnName);
										columnName=0;
										}
									if(defaultValue!=0)
										{
										MSF::myFree(defaultValue);
										defaultValue=0;	
										}
									precision=0;
									length=0;
									dataTypeFlag=0;	
									if(notNullFlag==YES)	notNullFlag=NO;
									if(primaryKeyFlag==YES)	primaryKeyFlag=NO;
									if(uniqueFlag==YES)	uniqueFlag=NO;	
									;}
    break;

  case 36:
#line 210 "rdbmsp.ypp"
    {
									dataTypeFlag=DBCHARTYPE; 
									length=0;precision=0;
									;}
    break;

  case 37:
#line 214 "rdbmsp.ypp"
    { 
		   							dataTypeFlag=DBCHARTYPE;
									length=atoi((char*)yyvsp[-1]);
									precision=0;
									;}
    break;

  case 38:
#line 219 "rdbmsp.ypp"
    { 
		   							dataTypeFlag=DBINTTYPE;
									length=0;precision=0;
									;}
    break;

  case 39:
#line 223 "rdbmsp.ypp"
    {
		   							dataTypeFlag=DBINTTYPE;
									length=atoi((char*)yyvsp[-1]);
									precision=0;
									;}
    break;

  case 40:
#line 228 "rdbmsp.ypp"
    {
		   							dataTypeFlag=DBDATETYPE;
									length=0;precision=0;
									;}
    break;

  case 41:
#line 232 "rdbmsp.ypp"
    {
		   										  dataTypeFlag=DBDATETYPE;
												  if(defaultValue==0) 
													defaultValue=(char*)MSF::myMalloc(strlen((char*)yyvsp[-5])
																	 +strlen((char*)yyvsp[-3])
										                                                         +strlen((char*)yyvsp[-1])+2);
												  strcpy(defaultValue,(char*)yyvsp[-5]);
												  strcat(defaultValue,"\\");
												  strcat(defaultValue,(char*)yyvsp[-3]);
												  strcat(defaultValue,"\\");
												  strcat(defaultValue,(char*)yyvsp[-1]);
												  length=0;precision=0;
												  ;}
    break;

  case 44:
#line 251 "rdbmsp.ypp"
    {notNullFlag=YES;;}
    break;

  case 45:
#line 252 "rdbmsp.ypp"
    {notNullFlag=YES;uniqueFlag=YES;;}
    break;

  case 46:
#line 253 "rdbmsp.ypp"
    {primaryKeyFlag=YES;;}
    break;

  case 47:
#line 254 "rdbmsp.ypp"
    {
			  				if(defaultValue==0)	defaultValue=(char*)MSF::myMalloc(strlen((char*)yyvsp[0]));
							strcpy(defaultValue,(char*)yyvsp[0]);	
							//printf("\nHERE %s\n",defaultValue);	
							;}
    break;

  case 48:
#line 259 "rdbmsp.ypp"
    {
			  				if(defaultValue==0)	defaultValue=(char*)MSF::myMalloc(strlen((char*)yyvsp[0]));
							strcpy(defaultValue,(char*)yyvsp[0]);	
							//printf("\nHERE %s\n",defaultValue);
			  				;}
    break;

  case 49:
#line 264 "rdbmsp.ypp"
    {
			  				uniqueFlag=YES;
			  				;}
    break;

  case 54:
#line 275 "rdbmsp.ypp"
    { uniqueNames=tempFieldNames;tempFieldNames=NULL ;}
    break;

  case 55:
#line 276 "rdbmsp.ypp"
    { pkeyNames=tempFieldNames;  tempFieldNames=NULL ;}
    break;

  case 56:
#line 279 "rdbmsp.ypp"
    {RLQH::insertToFdList(&tempFieldNames,  (char*)yyvsp[0]);   ;}
    break;

  case 57:
#line 280 "rdbmsp.ypp"
    {RLQH::insertToFdList(&tempFieldNames,(char*)yyvsp[0]);     ;}
    break;

  case 58:
#line 284 "rdbmsp.ypp"
    {
						time(&startT);	
						TLQuery(DROPTABLE);	
						time(&endT);
						printf("\nExecution Time %lf seconds \n",difftime(endT,startT));
						;}
    break;

  case 59:
#line 293 "rdbmsp.ypp"
    {
						time(&startT);	
						TLQuery(SHOWTABLE);	
						time(&endT);
						printf("\nExecution Time %lf seconds \n",difftime(endT,startT));
						;}
    break;

  case 60:
#line 302 "rdbmsp.ypp"
    {;}
    break;

  case 66:
#line 316 "rdbmsp.ypp"
    {
									     time(&startT);
									     RLQuery(SELECTQUERY);
									     time(&endT);
									     printf("\nExecution Time %lf seconds \n",difftime(endT,startT));
									     ;}
    break;

  case 72:
#line 332 "rdbmsp.ypp"
    {	RLQH::insertToFdList(&fNames,(char*)yyvsp[0]);	;}
    break;

  case 73:
#line 333 "rdbmsp.ypp"
    {	RLQH::insertToFdList(&fNames,(char*)yyvsp[0]);	;}
    break;

  case 75:
#line 338 "rdbmsp.ypp"
    {;}
    break;

  case 77:
#line 342 "rdbmsp.ypp"
    {whereExistsFlag=1;;}
    break;

  case 78:
#line 345 "rdbmsp.ypp"
    {doORorAND(1);;}
    break;

  case 79:
#line 346 "rdbmsp.ypp"
    {doORorAND(2);;}
    break;

  case 80:
#line 347 "rdbmsp.ypp"
    {doORorAND(3);;}
    break;

  case 82:
#line 353 "rdbmsp.ypp"
    {
						if(ridList==NULL)      selectsErrFlag=selectHan->getRIDs(tableName,dbName,(char*)yyvsp[-2],LT,(char*)yyvsp[0],&ridList);
						else		       selectsErrFlag=selectHan->getRIDs(tableName,dbName,(char*)yyvsp[-2],LT,(char*)yyvsp[0],&tempRIDList);	
						if(selectsErrFlag==FAILED)
							{
							fflush(stdin);
							resetOnError();
							goToPrompt();
							}
							
						;}
    break;

  case 83:
#line 365 "rdbmsp.ypp"
    {
						if(ridList==NULL)	selectsErrFlag=selectHan->getRIDs(tableName,dbName,(char*)yyvsp[-2],LE,(char*)yyvsp[0],&ridList);
						else			selectsErrFlag=selectHan->getRIDs(tableName,dbName,(char*)yyvsp[-2],LE,(char*)yyvsp[0],&tempRIDList);
						if(selectsErrFlag==FAILED)
							{
							fflush(stdin);
							resetOnError();
							goToPrompt();
							}
						;}
    break;

  case 84:
#line 376 "rdbmsp.ypp"
    {
						if(ridList==NULL)	selectsErrFlag=selectHan->getRIDs(tableName,dbName,(char*)yyvsp[-2],GT,(char*)yyvsp[0],&ridList);
						else			selectsErrFlag=selectHan->getRIDs(tableName,dbName,(char*)yyvsp[-2],GT,(char*)yyvsp[0],&tempRIDList);
						if(selectsErrFlag==FAILED)
							{
							fflush(stdin);
							resetOnError();
							goToPrompt();
							}
						;}
    break;

  case 85:
#line 387 "rdbmsp.ypp"
    {
						if(ridList==NULL)	selectsErrFlag=selectHan->getRIDs(tableName,dbName,(char*)yyvsp[-2],GE,(char*)yyvsp[0],&ridList);
						else			selectsErrFlag=selectHan->getRIDs(tableName,dbName,(char*)yyvsp[-2],GE,(char*)yyvsp[0],&tempRIDList);
						if(selectsErrFlag==FAILED)
							{
							fflush(stdin);
							resetOnError();
							goToPrompt();
							}
						;}
    break;

  case 86:
#line 398 "rdbmsp.ypp"
    {
						if(ridList==NULL)	selectsErrFlag=selectHan->getRIDs(tableName,dbName,(char*)yyvsp[-2],NE,(char*)yyvsp[0],&ridList);
						else			selectsErrFlag=selectHan->getRIDs(tableName,dbName,(char*)yyvsp[-2],NE,(char*)yyvsp[0],&tempRIDList);
						if(selectsErrFlag==FAILED)
							{
							fflush(stdin);
							resetOnError();
							goToPrompt();
							}
						;}
    break;

  case 87:
#line 409 "rdbmsp.ypp"
    {
						if(ridList==NULL)	selectsErrFlag=selectHan->getRIDs(tableName,dbName,(char*)yyvsp[-2],EQ,(char*)yyvsp[0],&ridList);
						else			selectsErrFlag=selectHan->getRIDs(tableName,dbName,(char*)yyvsp[-2],EQ,(char*)yyvsp[0],&tempRIDList);
						if(selectsErrFlag==FAILED)
							{
							resetOnError();
							goToPrompt();
							}
						;}
    break;

  case 88:
#line 421 "rdbmsp.ypp"
    {
									time(&startT);	
									RLQuery(INSERTQUERY);	
									time(&endT);
									printf("\nExecution Time %lf seconds \n",difftime(endT,startT));
									;}
    break;

  case 92:
#line 436 "rdbmsp.ypp"
    {	RLQH::insertToAttList(&aValues,(char*)yyvsp[0]);	;}
    break;

  case 93:
#line 437 "rdbmsp.ypp"
    {	RLQH::insertToAttList(&aValues,(char*)yyvsp[0]);	;}
    break;

  case 97:
#line 446 "rdbmsp.ypp"
    {;}
    break;

  case 101:
#line 454 "rdbmsp.ypp"
    {RLQH::insertToFdList(&fNames,(char*)yyvsp[-2]);RLQH::insertToAttList(&aValues,(char*)yyvsp[0]);;}
    break;

  case 102:
#line 455 "rdbmsp.ypp"
    {RLQH::insertToFdList(&fNames,(char*)yyvsp[-2]);RLQH::insertToAttList(&aValues,(char*)yyvsp[0]);;}
    break;

  case 103:
#line 456 "rdbmsp.ypp"
    {RLQH::insertToFdList(&fNames,(char*)yyvsp[-2]);RLQH::insertToAttList(&aValues,(char*)yyvsp[0]);;}
    break;

  case 104:
#line 460 "rdbmsp.ypp"
    {
							time(&startT);	
							RLQuery(DELETEQUERY);	
							time(&endT);
							printf("\nExecution Time %lf seconds \n",difftime(endT,startT));
							;}
    break;

  case 105:
#line 469 "rdbmsp.ypp"
    {
				time(&startT);
				vSB->commitBufferPool();
				FILE *tt1=fopen(UDBFILE,"w");
			  	fprintf(tt1,"%s",DLQH::dBName);
			  	fclose(tt1);	
				time(&endT);		  
				printf("\nExecution Time %lf seconds \n",difftime(endT,startT));
				;}
    break;


    }

/* Line 1010 of yacc.c.  */
#line 1791 "rdbmsp.tab.cpp"

  yyvsp -= yylen;
  yyssp -= yylen;


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
#if YYERROR_VERBOSE
      yyn = yypact[yystate];

      if (YYPACT_NINF < yyn && yyn < YYLAST)
	{
	  YYSIZE_T yysize = 0;
	  int yytype = YYTRANSLATE (yychar);
	  const char* yyprefix;
	  char *yymsg;
	  int yyx;

	  /* Start YYX at -YYN if negative to avoid negative indexes in
	     YYCHECK.  */
	  int yyxbegin = yyn < 0 ? -yyn : 0;

	  /* Stay within bounds of both yycheck and yytname.  */
	  int yychecklim = YYLAST - yyn;
	  int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
	  int yycount = 0;

	  yyprefix = ", expecting ";
	  for (yyx = yyxbegin; yyx < yyxend; ++yyx)
	    if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
	      {
		yysize += yystrlen (yyprefix) + yystrlen (yytname [yyx]);
		yycount += 1;
		if (yycount == 5)
		  {
		    yysize = 0;
		    break;
		  }
	      }
	  yysize += (sizeof ("syntax error, unexpected ")
		     + yystrlen (yytname[yytype]));
	  yymsg = (char *) YYSTACK_ALLOC (yysize);
	  if (yymsg != 0)
	    {
	      char *yyp = yystpcpy (yymsg, "syntax error, unexpected ");
	      yyp = yystpcpy (yyp, yytname[yytype]);

	      if (yycount < 5)
		{
		  yyprefix = ", expecting ";
		  for (yyx = yyxbegin; yyx < yyxend; ++yyx)
		    if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
		      {
			yyp = yystpcpy (yyp, yyprefix);
			yyp = yystpcpy (yyp, yytname[yyx]);
			yyprefix = " or ";
		      }
		}
	      yyerror (yymsg);
	      YYSTACK_FREE (yymsg);
	    }
	  else
	    yyerror ("syntax error; also virtual memory exhausted");
	}
      else
#endif /* YYERROR_VERBOSE */
	yyerror ("syntax error");
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
	 error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* If at end of input, pop the error token,
	     then the rest of the stack, then return failure.  */
	  if (yychar == YYEOF)
	     for (;;)
	       {
		 YYPOPSTACK;
		 if (yyssp == yyss)
		   YYABORT;
		 YYDSYMPRINTF ("Error: popping", yystos[*yyssp], yyvsp, yylsp);
		 yydestruct (yystos[*yyssp], yyvsp);
	       }
        }
      else
	{
	  YYDSYMPRINTF ("Error: discarding", yytoken, &yylval, &yylloc);
	  yydestruct (yytoken, &yylval);
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

#ifdef __GNUC__
  /* Pacify GCC when the user code never invokes YYERROR and the label
     yyerrorlab therefore never appears in user code.  */
  if (0)
     goto yyerrorlab;
#endif

  yyvsp -= yylen;
  yyssp -= yylen;
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

      YYDSYMPRINTF ("Error: popping", yystos[*yyssp], yyvsp, yylsp);
      yydestruct (yystos[yystate], yyvsp);
      YYPOPSTACK;
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  if (yyn == YYFINAL)
    YYACCEPT;

  YYDPRINTF ((stderr, "Shifting error token, "));

  *++yyvsp = yylval;


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

#ifndef yyoverflow
/*----------------------------------------------.
| yyoverflowlab -- parser overflow comes here.  |
`----------------------------------------------*/
yyoverflowlab:
  yyerror ("parser stack overflow");
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
  return yyresult;
}


#line 494 "rdbmsp.ypp"

void resetOnError()
 	{
	if(notNullFlag!=NO)	notNullFlag=NO;
	if(uniqueFlag!=NO)	uniqueFlag=NO; 
	if(primaryKeyFlag!=NO)  primaryKeyFlag=NO;
	if(columnName!=0) 	MSF::myFree(columnName);
	   columnName=0;
	if(defaultValue!=0)	MSF::myFree(defaultValue);
	   defaultValue=0;	
	if(tableName!=0)	MSF::myFree(tableName);	
	   tableName=0;	
	if(dbName!=0)		MSF::myFree(dbName);	
	   dbName=0;	
	if(position!=0)		position=0;
	if(cColumns!=NULL)	
		{
		createColumns *temp;
		while(cColumns!=NULL)
			{
			temp=cColumns;
			cColumns=(cColumns)->next;
			MSF::myFree(temp->columnName);
			if(temp->defaultValue!=0)	
			MSF::myFree(temp->defaultValue);
			MSF::myFree(temp);	
			}
		cColumns=NULL;	
		}   
	if(pkeyNames!=NULL)	
		{
		RLQH::freeFdList(pkeyNames);
		pkeyNames=NULL;
		}
	if(uniqueNames!=NULL)	
		{
		RLQH::freeFdList(uniqueNames);
		uniqueNames=NULL;
		}
	if(tempFieldNames!=NULL)	
		{
		RLQH::freeFdList(tempFieldNames);
		tempFieldNames=NULL;
		}		
	if(whereExistsFlag!=0)	whereExistsFlag=0;
	if(aValues!=NULL)	
		{
		RLQH::freeAttList(aValues);
		aValues=NULL;
		}
	if(fNames!=NULL)	
		{
		RLQH::freeFdList(fNames);
		fNames=NULL;
		}
	if(ridList!=NULL)	RH::freeRIDList(ridList);
	if(tempRIDList!=NULL)	RH::freeRIDList(tempRIDList);
	if(nextList!=NULL)	RH::freeRIDList(nextList);
	nextList=NULL;
	ridList=NULL;	
	tempRIDList=NULL;
	selectsErrFlag=SUCCESS;			
	}
	
/* Write the code for main function to solve the problem set */
extern FILE *yyin;

void yyerror(char *s)
	{
	printf("\nSyntax Error\n");
        //fprintf(stderr,"syntax error! check your syntax\n",s);
	resetOnError();
	goToPrompt();
        }
	
void goToPrompt()
	{
	fflush(stdin);
	printf("\nRDBMSP>");
        yyin=stdin;
        yyparse();
	}

	
void doORorAND(int optype)
 	{
	RID *temp1,*temp2;
	//RH::displayRIDList(ridList);
	//RH::displayRIDList(tempRIDList);
	temp1=ridList;
	temp2=tempRIDList;
	if(optype==1)//OR
		{
		while(temp1!=NULL)
			{
			RH::insertToRIDList(&nextList,temp1->pageNumber,temp1->slotID);
			temp1=temp1->next;
			}
			
		temp1=ridList;
		while(temp1!=NULL)
			{
			while(temp2!=NULL)
				{
				if(temp1->pageNumber==temp2->pageNumber && temp1->slotID==temp2->slotID) {}//do nothing
				else	RH::insertToRIDList(&nextList,temp2->pageNumber,temp2->slotID);
				temp2=temp2->next;
				}
			temp1=temp1->next;
			}	
		}
	else if(optype==2)//AND
		{
		while(temp1!=NULL)
			{
			temp2=tempRIDList;
			while(temp2!=NULL)
				{
				//printf("\nTEMP1 %ld %d; TEMP2 %ld %d",temp1->pageNumber,temp1->slotID,temp2->pageNumber,temp1->slotID);
				if(temp1->pageNumber==temp2->pageNumber && temp1->slotID==temp2->slotID) 
					RH::insertToRIDList(&nextList,temp2->pageNumber,temp2->slotID);
				temp2=temp2->next;
				}
			temp1=temp1->next;	
			}
		}
	else		//NOT
		{
		
		}
	if(ridList!=NULL)	RH::freeRIDList(ridList);
	ridList=NULL;
	if(tempRIDList!=NULL)	RH::freeRIDList(tempRIDList);
	tempRIDList=NULL;
	}	
	
int RLQuery(int type)
	{
	int retValue=SUCCESS;
	if(whereExistsFlag==1)
		{
		//code to handle the where clause tree structure
		//printf("\n venki is here");
		//RH::displayRIDList(nextList);
		//RH::displayRIDList(ridList);
		if(type==SELECTQUERY)
			{
			if(nextList!=NULL)	selectHan->displayRIDListOnRetreival(tableName,dbName,fNames,nextList);
			else			selectHan->displayRIDListOnRetreival(tableName,dbName,fNames,ridList);
			fNames=NULL;
			nextList=NULL;
			ridList=NULL;
			}
		else if(type==UPDATEQUERY)
			{
			}
		else if(type==DELETEQUERY)
			{
			if(nextList!=NULL)	deleteHan->executeDelete(nextList,tableName,dbName);
			else			deleteHan->executeDelete(ridList,tableName,dbName);
			nextList=NULL;
			ridList=NULL;
			}
		}
	else
		{	
		//printf("\nIN RLQH HANDLER %s is tableName and %s is dbName\n",tableName,dbName);
		//RLQH ::displayList(aValues,fNames);
		rLQds=(RLQds*)MSF::myMalloc(sizeof(RLQds));
		rLQds->queryType=type;
		rLQds->values=aValues;
		rLQds->names=fNames;
		rLQds->objectName=(char*)MSF::myMalloc(strlen(tableName));
		//printf("\n venki after allocating tablename");
		strcpy(rLQds->objectName,tableName);
		if(dbName!=0)
			{
			rLQds->dbname=(char*)MSF::myMalloc(strlen(dbName));
			strcpy(rLQds->dbname,dbName);
			MSF::myFree(dbName);
			dbName=0;
			//printf("\n venki is here After freeing memory");
			}	
		else
			{
			rLQds->dbname=(char*)MSF::myMalloc(strlen(DLQH::dBName));
			strcpy(rLQds->dbname,DLQH::dBName);
			//printf("\n venki after allocating dbname");
			}
		if(type==UPDATEQUERY)	
					{
					if(nextList!=NULL)	updateHan->updateQueryHandler(rLQds,nextList);
					else			updateHan->updateQueryHandler(rLQds,ridList);
					fNames=NULL;
					nextList=NULL;
					ridList=NULL;
					}
		else	
			{
			//int i=0;
			//for(i=0;i<100000;i++)
			retValue=dbe->executeQuery(rLQds,NULL);//calling the DBEngine Facade Interface		
			}
		RLQH::freeList(rLQds); //problem to be solved	
		//printf("\n After freeing the rLQDS");
		fNames=NULL;
		aValues=NULL;
		rLQds=0;
		MSF::myFree(tableName);
		tableName=0;
		printf("\n\n");
		}
	vSB->displayBufferStatisitics();	
	vSB->queryStats();	
	resetOnError();	
	}	
	
int TLQuery(int type)
	{
	int retValue=SUCCESS;
	tLQds=(TLQds*)MSF::myMalloc(sizeof(TLQds));
	tLQds->queryType=type;
	if(dbName!=0)
		{
		tLQds->dbname=(char*)MSF::myMalloc(strlen(dbName));
		strcpy(tLQds->dbname,dbName);
		MSF::myFree(dbName);
		dbName=0;
		}
	else
		{
		tLQds->dbname=(char*)MSF::myMalloc(strlen(DLQH::dBName));
		strcpy(tLQds->dbname,DLQH::dBName);
		}	
	tLQds->objectName=(char*)MSF::myMalloc(strlen(tableName));
	strcpy(tLQds->objectName,tableName);
	MSF::myFree(tableName);
	tableName=0;
	printf("\n\tDataBaseName %s",tLQds->dbname);
	printf("\n\tTableName %s",tLQds->objectName);
	TLQH::displayList(cColumns);
	if(pkeyNames!=NULL)	tLQds->pKeyFields=pkeyNames;
	else			tLQds->pKeyFields=NULL;
	if(uniqueNames!=NULL)	tLQds->uniqueFields=uniqueNames;
	else			tLQds->uniqueFields=NULL;
	tLQds->columns=cColumns;
	
	retValue=dbe->executeQuery(tLQds);//calling the DBEngine Facade Interface	
	
	TLQH::freeList(tLQds); //problem to be solved
	position=0;
	cColumns=NULL;
	pkeyNames=NULL;
	uniqueNames=NULL;
	printf("\n");
	resetOnError();
	vSB->displayBufferStatisitics();
	vSB->queryStats();
	return retValue;
	}
			
int DBQuery(char *dbname,int type)
	{
	int retValue=SUCCESS;
	DLQds *d;
	d=(DLQds*)MSF::myMalloc(sizeof(DLQds));
	if(dbname!=NULL)
		{
		d->objectName=(char*)MSF::myMalloc(strlen(dbname));
		strcpy(d->objectName,dbname);
		}
	else 
		d->objectName=NULL;	
	d->queryType=type;
	retValue=dbe->executeQuery(d);//calling the DBEngine Facade Interface
	MSF::myFree(d->objectName);
	MSF::myFree(d);
	printf("\n");
	resetOnError();
	vSB->displayBufferStatisitics();
	vSB->queryStats();
	return retValue;
	}
	
void start()
	{
	dbe=VSDBEngine::getInstance(DBFILENAME,1500);
	selectHan=SQH::getInstance();
	deleteHan=DQH::getInstance();
	updateHan=UQH::getInstance();
	vSB=VSBufferManager::getInstance();
	}
			
int main(int argc,char *argv[])
        {
	//system("clear");
	char tts[100];
	start();
	FILE *tt=fopen(UDBFILE,"r");	
	if(tt!=NULL)	
		{
		fscanf(tt,"%s",&tts);
		MSF::myFree(DLQH::dBName);
		DLQH::dBName=(char*)MSF::myMalloc(strlen(tts));
		strcpy(DLQH::dBName,tts);
		fclose(tt);	
		}
	FILE *fp;
	if(argc>1)              // input file is given .sql file with DDL DML statements
		{
		fp=fopen(argv[1],"r");
		if(fp==NULL)
			{
			printf("\n Invalied input file! \"%s\"\n",argv[1]);
			goto END;
			}
		yyin=fp;
        	do
          		{
          		yyparse();
          		}while(feof(yyin)==0);
		fclose(yyin);
		fclose(fp);	
		printf("\n venki ");	
		goToPrompt();	
		goto END;
		}
	else                    // If Command Interpreter is preferred  
		{
		//system("clear");
		promptFlag=1;
	        //printf("\n\t Welcome to My RDBMS Software.... type help to know the commands available-->\n");	
		goToPrompt();
		goto END;
		}
END:	                             //single point exit
	resetOnError();
	tt=fopen(UDBFILE,"w");
	fprintf(tt,"%s",DLQH::dBName);
	fclose(tt);	
	exit(0);
	}

	
void getInputFromFile(char *fileName,int from,int upto)
	{
	printf("\n Inside the func: %s %d %d\n",fileName,from,upto);
	FILE *fp;
	fp=fopen(fileName,"r");
	fclose(yyin);
	yyin=fp;
	printf("\n venki here\n");
        //do
          //	{
          	yyparse();
          //	}while(feof(yyin)==0);
	fclose(yyin);
	printf("\n I am here");	
	goToPrompt();
	printf("\n I am here");
	/*	
	char command[300];
	int index=0,i;
	FILE *tempFile;
	long ln=0;
	char ch;
	FILE *fp=fopen(fileName,"r");
	while((ch=fgetc(fp))!=EOF)
		{
		if(ch!=';')
			{
			if(ch!='\n')	 
			command[index++]=ch;
			}
		if(ch==';')
			{
			tempFile=fopen("temp","w");
			command[index]='\0';	
			printf("\tCOMMAND is  \"%s\"\n",command);
			fprintf(tempFile,"%s",command);
			fclose(tempFile);
			tempFile=fopen("temp","r");
			fclose(yyin);
			yyin=tempFile;
        		yyparse();
			fclose(tempFile);
			index=0;				
			}
		}
	goToPrompt();
	printf("\n Here\n");
	*/
	}		
		 

  '7