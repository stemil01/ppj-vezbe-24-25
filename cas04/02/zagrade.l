%option noyywrap

%{
    #include <stdio.h>

    int broj_otvorenih = 0;
%}

%%

\( {
    broj_otvorenih++;
}

\) {
    broj_otvorenih--;
    if (broj_otvorenih < 0) {
        return -1;
    }
}

.|\n {
    ECHO;
}

%%

int main() {
    int povratna_vrednost = yylex();
    if (povratna_vrednost == 0 && broj_otvorenih == 0) {
        printf("dobro su uparene\n");
    }
    else {
        printf("nisu\n");
    }
    return 0;
}
