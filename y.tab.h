/* A Bison parser, made by GNU Bison 2.3.  */

/* Skeleton interface for Bison's Yacc-like parsers in C

   Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.

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
   Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.  */

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

/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     INTEGER = 258,
     CHAR = 259,
     STRING = 260,
     VARIABLE = 261,
     FOR = 262,
     WHILE = 263,
     IF = 264,
     PRINT = 265,
     READ = 266,
     PROC = 267,
     RETURN = 268,
     DECLARE = 269,
     ARG = 270,
     ARRAY = 271,
     A1ELEM = 272,
     A2ELEM = 273,
     A3ELEM = 274,
     ASSIGN_ARR1 = 275,
     ASSIGN_ARR2 = 276,
     ASSIGN_ARR3 = 277,
     IFX = 278,
     ELSE = 279,
     OR = 280,
     AND = 281,
     NE = 282,
     EQ = 283,
     LE = 284,
     GE = 285,
     UMINUS = 286
   };
#endif
/* Tokens.  */
#define INTEGER 258
#define CHAR 259
#define STRING 260
#define VARIABLE 261
#define FOR 262
#define WHILE 263
#define IF 264
#define PRINT 265
#define READ 266
#define PROC 267
#define RETURN 268
#define DECLARE 269
#define ARG 270
#define ARRAY 271
#define A1ELEM 272
#define A2ELEM 273
#define A3ELEM 274
#define ASSIGN_ARR1 275
#define ASSIGN_ARR2 276
#define ASSIGN_ARR3 277
#define IFX 278
#define ELSE 279
#define OR 280
#define AND 281
#define NE 282
#define EQ 283
#define LE 284
#define GE 285
#define UMINUS 286




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
#line 31 "c5.y"
{
    int iValue;                 /* integer value */
    int sIndex;                 /* symbol table index VARIABLE */
    nodeType *nPtr;             /* node pointer */
    char cValue;                /* newly added char value */
    char *strValue;             /* newly added str value */
}
/* Line 1529 of yacc.c.  */
#line 119 "y.tab.h"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif

extern YYSTYPE yylval;

