%option noyywrap

%{
    #include <iostream>
    #include <cstdlib>
    #include "kompleksan_broj.hpp"
    #include "parser.tab.hpp"
%}

PRIR_BROJ 0|[1-9][0-9]*

%%

def {
    return DEF;
}

print {
    return PRINT;
}

arg {
    return ARG;
}

mod {
    return MOD;
}

re {
    return RE;
}

im {
    return IM;
}

[_a-zA-Z][_a-zA-Z0-9]* {
    yylval.niska = new std::string(yytext);
    return ID;
}

[+-]?{PRIR_BROJ}(\.{PRIR_BROJ}([eE][+-]{PRIR_BROJ})?)? {
    yylval.realan_broj = atof(yytext);
    return BROJ;
}

[+\-*/()~=;<>,] {
    return *yytext;
}

[ \t\n] {

}

. {
    std::cerr << "leksicka greska: " << yytext << std::endl;
    exit(EXIT_FAILURE);
}

%%
