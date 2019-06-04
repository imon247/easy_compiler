%{
#include <stdlib.h>
#include <string.h>
#include "calc3.h"
#include "y.tab.h"
#include <stdbool.h>
void yyerror(char *);
static char variableNames[50][12];
static int numOfVariables = 0;
%}

%%

">="            return GE;
"<="            return LE;
"=="            return EQ;
"!="            return NE;
"for"		        return FOR;
"while"         return WHILE;
"if"            return IF;
"else"          return ELSE;
"print"         return PRINT;
"read"		      return READ;
"return"        return RETURN;
"array"         return ARRAY;
"&&"		        return AND;
"||"		        return OR;


[a-zA-Z]+            {
                        bool found = false;
                        for(int i=0;i<numOfVariables;i++){
                          if(strcmp(variableNames[i], yytext)==0){
                            yylval.sIndex = i;
                            found = true;
                            break;
                          }
                        }
                        if(found==false){
                          yylval.sIndex = numOfVariables;
                          sprintf(variableNames[numOfVariables], "%s", yytext);
                          numOfVariables++;
                        }
                        return VARIABLE;
                      }

0           {
                yylval.iValue = atoi(yytext);
                return INTEGER;
            }

'[a-z]'     {
                yylval.cValue = *(yytext+1);
                /* printf("char: %c\n", yylval.cValue); */
                return CHAR;
            }


\"[0-9a-zA-Z' '-()<>=+*\/;:{}.%\',!]*\"    {
                        yytext[strlen(yytext)-1] = '\0';
                        yytext = yytext+1;
                        yylval.strValue = yytext;
                        return STRING;
                    }

[1-9][0-9]* {
                yylval.iValue = atoi(yytext);
                return INTEGER;
            }

[-()\[\]<>=+*\/;{}.%\',] {
                return *yytext;
             }



\/\/.*\n	;	/* skip comments */

[ \t\n]+        ;       /* ignore whitespace */


.               yyerror("Unknown character");
%%
int yywrap(void) {
    return 1;
}
