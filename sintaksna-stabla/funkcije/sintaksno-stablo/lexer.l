%option noyywrap

%{
    #include <iostream>
    #include <cstdlib>
    #include "sintaksno_stablo.hpp"
    #include "parser.tab.hpp"
%}

PRIR_BROJ 0|[1-9][0-9]*
REAL_BROJ [+-]?{PRIR_BROJ}(\.{PRIR_BROJ}([eE][+-]{PRIR_BROJ})?)?
IDENTIFIKATOR [_a-zA-Z][_a-zA-Z0-9]*

%%

x {
    return PROMENLJIVA;
}

sin {
    return SIN;
}

cos {
    return COS;
}

{IDENTIFIKATOR} {
    yylval.niska = new std::string(yytext);
    return ID;
}

{REAL_BROJ} {
    yylval.realan_broj = atof(yytext);
    return BROJ;
}

[+\-*/()\[\]='\n] {
    return *yytext;
}

[ \t] {

}

. {
    std::cerr << "leksicka greska: " << yytext << std::endl;
    exit(EXIT_FAILURE);
}

%%
