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
     VARIABLE = 260,
     FOR = 261,
     WHILE = 262,
     IF = 263,
     PRINT = 264,
     READ = 265,
     IFX = 266,
     ELSE = 267,
     OR = 268,
     AND = 269,
     NE = 270,
     EQ = 271,
     LE = 272,
     GE = 273,
     UMINUS = 274
   };
#endif
/* Tokens.  */
#define INTEGER 258
#define CHAR 259
#define VARIABLE 260
#define FOR 261
#define WHILE 262
#define IF 263
#define PRINT 264
#define READ 265
#define IFX 266
#define ELSE 267
#define OR 268
#define AND 269
#define NE 270
#define EQ 271
#define LE 272
#define GE 273
#define UMINUS 274




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
#line 22 "c4.y"
{
    int iValue;                 /* integer value */
    char sIndex;                /* symbol table index VARIABLE */
    nodeType *nPtr;             /* node pointer */
    char cValue;                /* char value */
}
/* Line 1529 of yacc.c.  */
#line 94 "y.tab.h"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif

extern YYSTYPE yylval;

