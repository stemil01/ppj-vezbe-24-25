%option noyywrap

%{
    #include <stdio.h>

    int broj_redova = 0;
%}

%%

\n {
    broj_redova++;
}

%%

// C kod koji poziva lekser
int main() {
    yylex();
    printf("%d\n", broj_redova);
    return 0;
}
