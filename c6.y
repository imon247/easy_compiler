%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include "calc3.h"


/* prototypes */
nodeType *opr(int oper, int nops, ...);
nodeType *id(int index);
nodeType *con(int value);
nodeType *conInt(int value);    /* newly added struct a node for int constant */
nodeType *conChar(char value);  /* newly added struct a node for char constant */
nodeType *conStr(char *value);  /* newly added struct a node for string constant */
nodeType *array1Declare(nodeType *arrayID, int x);
nodeType *array2Declare(nodeType *arrayID, int x, int y);
nodeType *array3Declare(nodeType *arrayID, int x, int y, int z);
nodeType *array1Elem(nodeType *arrayID, int x);
nodeType *array2Elem(nodeType *arrayID, int x, int y);
nodeType *array3Elem(nodeType *arrayID, int x, int y, int z);

void freeNode(nodeType *p);
int ex(nodeType *p);
int yylex(void);

void yyerror(char *s);
int sym[26];                    /* symbol table */
%}

%union {
    int iValue;                 /* integer value */
    int sIndex;                 /* symbol table index VARIABLE */
    nodeType *nPtr;             /* node pointer */
    char cValue;                /* newly added char value */
    char *strValue;             /* newly added str value */
};

%token <iValue> INTEGER
%token <cValue> CHAR            /* newly added char */
%token <strValue> STRING           /* newly added str */
%token <sIndex> VARIABLE
%token <int> FOR WHILE IF PRINT READ PROC RETURN DECLARE ARG ARRAY A1ELEM A2ELEM A3ELEM ASSIGN_ARR1 ASSIGN_ARR2 ASSIGN_ARR3
%nonassoc IFX
%nonassoc ELSE
%left AND OR

%left GE LE EQ NE '>' '<'
%left '+' '-'
%left '*' '/' '%'
%nonassoc UMINUS

%type <nPtr> stmt expr stmt_list vars arguments arrElem

%%

program:
function                {
                          printf("\tend\n");
                          for(int i=0;i<bufferIndex;i++){
                            printf("%s", buffer[i]);
                          }
                          exit(0);  /*remove the exit so that when scanning a function it will not exit */
                        }
        ;

function:
          function stmt         { ex($2); freeNode($2);}
        | /* NULL */
        ;

stmt:
          ';'                            { $$ = opr(';', 2, NULL, NULL); }
        | expr ';'                       { $$ = $1; }
        | PRINT expr ';'                 { $$ = opr(PRINT, 1, $2); }
        | RETURN expr ';'                { $$ = opr(RETURN, 1, $2); }
	      | READ VARIABLE ';'		           { $$ = opr(READ, 1, id($2)); }
        | VARIABLE '=' expr ';'          { $$ = opr('=', 2, id($1), $3);  /* variable assignment */}
        /* | arrElem '=' expr ';'           { $$ = opr(ASSIGN_ARR, 2, $1, $3); } */
        | VARIABLE '[' expr ']' '=' expr ';'                                    { $$ = opr(ASSIGN_ARR1, 3, id($1), $3, $6); }
        | VARIABLE '[' expr ']' '[' expr ']' '=' expr ';'                       { $$ = opr(ASSIGN_ARR2, 4, id($1), $3, $6, $9); }
        | VARIABLE '[' expr ']' '[' expr ']' '[' expr ']' '=' expr ';'          { $$ = opr(ASSIGN_ARR3, 5, id($1), $3, $6, $9, $12); }
        | ARRAY VARIABLE '[' INTEGER ']' ';'                                    { $$ = array1Declare(id($2), $4); }
        | ARRAY VARIABLE '[' INTEGER ']' '[' INTEGER ']' ';'                    { $$ = array2Declare(id($2), $4, $7);}
        | ARRAY VARIABLE '[' INTEGER ']' '[' INTEGER ']' '[' INTEGER ']' ';'    { $$ = array3Declare(id($2), $4, $7, $10);}
	      | FOR '(' stmt stmt stmt ')' stmt                  { $$ = opr(FOR, 4, $3, $4, $5, $7); }
        | WHILE '(' expr ')' stmt                          { $$ = opr(WHILE, 2, $3, $5); }
        | IF '(' expr ')' stmt %prec IFX                   { $$ = opr(IF, 2, $3, $5); }
        | IF '(' expr ')' stmt ELSE stmt                   { $$ = opr(IF, 3, $3, $5, $7); }
        | '{' stmt_list '}'                                { $$ = $2; }
        | VARIABLE '(' vars ')' stmt                       { $$ = opr(DECLARE, 3, id($1), $3, $5);} /*handling function declaration */
        ;

stmt_list:
          stmt                  { $$ = $1; }
        | stmt_list stmt        { $$ = opr(';', 2, $1, $2); }
        ;

vars:
          VARIABLE              { $$ = opr(',', 2, NULL, id($1)); }
        | vars ',' VARIABLE     { $$ = opr(',', 2, $1, id($3)); }
        |                       { $$ = opr(',', 2, NULL, NULL); }
        ;

arguments:
          expr                  { $$ = opr(ARG, 2, NULL, $1); }
        | arguments ',' expr    { $$ = opr(ARG, 2, $3, $1); }
        |                       { $$ = opr(ARG, 2, NULL, NULL); }

arrElem:
         VARIABLE '[' expr ']'                              { $$ = opr(A1ELEM, 2, id($1), $3); }
        | VARIABLE '[' expr ']' '[' expr ']'                { $$ = opr(A2ELEM, 3, id($1), $3, $6);}
        | VARIABLE '[' expr ']' '[' expr ']' '[' expr ']'   { $$ = opr(A3ELEM, 4, id($1), $3, $6, $9);}


expr:               /* add function call for expression! */
          INTEGER               { $$ = conInt($1); }
        | CHAR                  {
                                  $$ = conChar($1);
                                }
        | STRING                {
                                  $$ = conStr($1);
                                }
        | VARIABLE              {
                                  $$ = id($1);
                                }
        | VARIABLE '(' arguments ')' { $$ = opr(PROC, 2, $3, id($1)); }
        | '-' expr %prec UMINUS { $$ = opr(UMINUS, 1, $2); }
        | expr '+' expr         { $$ = opr('+', 2, $1, $3); }
        | expr '-' expr         { $$ = opr('-', 2, $1, $3); }
        | expr '*' expr         { $$ = opr('*', 2, $1, $3); }
        | expr '%' expr         { $$ = opr('%', 2, $1, $3); }
        | expr '/' expr         { $$ = opr('/', 2, $1, $3); }
        | expr '<' expr         { $$ = opr('<', 2, $1, $3); }
        | expr '>' expr         { $$ = opr('>', 2, $1, $3); }
        | expr GE expr          { $$ = opr(GE, 2, $1, $3); }
        | expr LE expr          { $$ = opr(LE, 2, $1, $3); }
        | expr NE expr          { $$ = opr(NE, 2, $1, $3); }
        | expr EQ expr          { $$ = opr(EQ, 2, $1, $3); }
	      | expr AND expr		      { $$ = opr(AND, 2, $1, $3); }
	      | expr OR expr		      { $$ = opr(OR, 2, $1, $3); }
        | '(' expr ')'          { $$ = $2; }
        | arrElem               { $$ = $1; }
        ;

%%

#define SIZEOF_NODETYPE ((char *)&p->Int - (char *)p)

/* struct a node of constant */
nodeType *conInt(int value) {
    nodeType *p;
    size_t nodeSize;

    /* allocate node */
    nodeSize = SIZEOF_NODETYPE + sizeof(intNodeType);
    if ((p = malloc(nodeSize)) == NULL)
        yyerror("out of memory");

    /* copy information */
    p->type = typeInt;
    p->Int.value = value;

    return p;
}

/* newly added struct a node of char */
nodeType *conChar(char value){
    nodeType *p;
    size_t nodeSize;

    nodeSize = SIZEOF_NODETYPE + sizeof(charNodeType);
    if((p=malloc(nodeSize)) == NULL)
        yyerror("out of memory");
    p->type = typeChar;
    p->Char.value = value;

    return p;
}

/* newly added struct a node of string */
nodeType *conStr(char *value){
    nodeType *p;
    size_t nodeSize;
    char *s;

    nodeSize = SIZEOF_NODETYPE + sizeof(strNodeType);
    if((p=malloc(nodeSize)) == NULL)
        yyerror("out of memory");
    if((s=malloc(sizeof(char)*strlen(value))) == NULL)
        yyerror("out of memory");
    s = value;
    p->type = typeStr;
    p->Str.value = s;   /* the last few bits of the address, starting from the base of the heap */

    return p;
}

nodeType *id(int index) {
    nodeType *p;
    size_t nodeSize;

     // allocate node
    nodeSize = SIZEOF_NODETYPE + sizeof(idNodeType);
    if ((p = malloc(nodeSize)) == NULL)
        yyerror("out of memory");

     // copy information
    p->type = typeId;
    p->id.index = index;

    return p;
}
nodeType *opr(int oper, int nops, ...) {
    va_list ap;
    nodeType *p;
    size_t nodeSize;
    int i;

    /* allocate node */
    nodeSize = SIZEOF_NODETYPE + sizeof(oprNodeType) + (nops - 1) * sizeof(nodeType*);
    if ((p = malloc(nodeSize)) == NULL)
        yyerror("out of memory");

    /* copy information */
    p->type = typeOpr;
    p->opr.oper = oper;
    p->opr.nops = nops;
    va_start(ap, nops);
    for (i = 0; i < nops; i++)
        p->opr.op[i] = va_arg(ap, nodeType*);   // append argument to oprerand list of p->opr
    va_end(ap);
    return p;

}

nodeType *array1Declare(nodeType *arrayID, int x){
    nodeType *p;
    size_t nodeSize;
    nodeSize = SIZEOF_NODETYPE + sizeof(array1NodeType);
    if((p = malloc(nodeSize)) == NULL)
        yyerror("out of memeory");

    p->type = typeArray1;
    p->array1.arrayID = arrayID;
    p->array1.x = x;

    return p;
}

nodeType *array2Declare(nodeType *arrayID, int x, int y){
    nodeType *p;
    size_t nodeSize;
    nodeSize = SIZEOF_NODETYPE + sizeof(array2NodeType);
    if((p = malloc(nodeSize)) == NULL)
        yyerror("out of memeory");
    p->type = typeArray2;
    p->array2.arrayID = arrayID;
    p->array2.x = x;
    p->array2.y = y;

    return p;
}

nodeType *array3Declare(nodeType *arrayID, int x, int y, int z){
    nodeType *p;
    size_t nodeSize;
    nodeSize = SIZEOF_NODETYPE + sizeof(array3NodeType);
    if((p = malloc(nodeSize)) == NULL)
        yyerror("out of memeory");
    p->type = typeArray3;
    p->array3.arrayID = arrayID;
    p->array3.x = x;
    p->array3.y = y;
    p->array3.z = z;

    return p;
}
/*
nodeType *array1Elem(nodeType *arrayID, int x){
}
nodeType *array2Elem(nodeType *arrayID, int x, int y){}
nodeType *array3Elem(nodeType *arrayID, int x, int y, int z){}
*/
void freeNode(nodeType *p) {
    int i;

    if (!p) return;
    if (p->type == typeOpr) {
        for (i = 0; i < p->opr.nops; i++)
            freeNode(p->opr.op[i]);
    }
    free (p);
}

void yyerror(char *s) {
    fprintf(stdout, "%s\n", s);
}

int main(int argc, char **argv) {
    bufferIndex = 0;
    for(int i=0;i<50;i++){
      variableSPs[i] = -1;
    }
    extern FILE* yyin;
    yyin = fopen(argv[1], "r");
    yyparse();
    return 0;
}
