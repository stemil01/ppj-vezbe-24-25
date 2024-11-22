%option noyywrap

%{
    #include <iostream>
    #include <cstdlib>
    #include "polinom.hpp"
    #include "parser.tab.hpp"
%}

PRIR_BROJ 0|[1-9][0-9]*
REAL_BROJ [+-]?{PRIR_BROJ}(\.{PRIR_BROJ}([eE][+-]{PRIR_BROJ})?)?
IDENT [_a-zA-Z][_a-zA-Z0-9]*

%%

\%.* {

}

print {
    return PRINT;
}

poly {
    return POLY;
}

deg {
    return DEG;
}

int {
    return INT;
}

== {
    return EQ;
}

!= {
    return NEQ;
}

{IDENT} {
    yylval.niska = new std::string(yytext);
    return ID;
}

{REAL_BROJ} {
    yylval.realan_broj = atof(yytext);
    return BROJ;
}

[+\-*()\';,=<>] {
    return *yytext;
}

[ \t\n] {

}

. {
    std::cerr << "leksicka greska: " << yytext << std::endl;
    exit(EXIT_FAILURE);
}

%%
