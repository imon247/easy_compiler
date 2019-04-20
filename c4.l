%{
#include <stdlib.h>
#include <string.h>
#include "calc3.h"
#include "y.tab.h"
void yyerror(char *);
%}

%%

"print"     {
                return PRINT;
            }


[a-zA-Z]+            {
                        yylval.sIndex = *yytext - 'a';
                        printf("variable: %s\n", yytext);
                        return VARIABLE;
                      }

0           {
                yylval.iValue = atoi(yytext);
                return INTEGER;
            }

'[a-z]'     {
                yylval.cValue = *(yytext+1);
                printf("char: %c\n", yylval.cValue);
                return CHAR;
            }


\"[a-zA-Z' ']*\"    {
                        yytext[strlen(yytext)-1] = '\0';
                        yytext = yytext+1;
                        yylval.strValue = yytext;
                        return STRING;
                    }

[1-9][0-9]* {
                yylval.iValue = atoi(yytext);
                return INTEGER;
            }

[-()<>=+*\/;{}.%\'] {
                return *yytext;
             }



\/\/.*\n	;	/* skip comments */

[ \t\n]+        ;       /* ignore whitespace */

.               yyerror("Unknown character");
%%
int yywrap(void) {
    return 1;
}
