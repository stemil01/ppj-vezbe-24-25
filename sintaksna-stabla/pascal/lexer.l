%option noyywrap

%{
    #include <iostream>
    #include <cstdlib>
    #include "sintaksno_stablo.hpp"
    #include "parser.tab.hpp"
%}

%%

begin {
    return BEGIN_TOKEN;
}

end {
    return END_TOKEN;
}

if {
    return IF;
}

then {
    return THEN;
}

else {
    return ELSE;
}

while {
    return WHILE;
}

do {
    return DO;
}

print {
    return PRINT;
}

:= {
    return EQ;
}

[_a-zA-Z][_a-zA-Z0-9]* {
    yylval.niska = new std::string(yytext);
    return ID;
}

[1-9][0-9]*|0 {
    yylval.ceo_broj = atoi(yytext);
    return BROJ;
}

[+\-();<>.=] {
    return *yytext;
}

[ \t\n] {

}

. {
    std::cerr << "leksicna greska: " << yytext << std::endl;
    exit(EXIT_FAILURE);
}

%%
