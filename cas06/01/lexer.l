%option noyywrap

%{
    #include <iostream>
    #include <cstdlib>
    #include "parser.tab.hpp"
%}

%%

0|[1-9][0-9]* {
    yylval = atoi(yytext);
    return BROJ;
}

[+\-*/();] {
    return *yytext;
}

[ \t\n] {

}

. {
    std::cerr << "leksicka greska: " << yytext << std::endl;
    exit(EXIT_FAILURE);
}

%%
