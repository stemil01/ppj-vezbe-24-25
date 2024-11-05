%option noyywrap

%{
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>

    int vrednost = 0;
%}

JEDINICE    I{1,3}|IV|VI{0,3}|IX
DESETICE    X{1,3}|XL|LX{0,3}|XC
STOTINE     C{1,3}|CD|DC{0,3}|CM
HILJADE     M{1,3}

%%

{HILJADE} {
    vrednost = strlen(yytext) * 1000;
}

{STOTINE} {
    if (strcmp(yytext, "C") == 0) {
        vrednost += 100;
    }
    else if (strcmp(yytext, "CC") == 0) {
        vrednost += 200;
    }
    else if (strcmp(yytext, "CCC") == 0) {
        vrednost += 300;
    }
    else if (strcmp(yytext, "CD") == 0) {
        vrednost += 400;
    }
    else if (strcmp(yytext, "D") == 0) {
        vrednost += 500;
    }
    else if (strcmp(yytext, "DC") == 0) {
        vrednost += 600;
    }
    else if (strcmp(yytext, "DCC") == 0) {
        vrednost += 700;
    }
    else if (strcmp(yytext, "DCCC") == 0) {
        vrednost += 800;
    }
    else if (strcmp(yytext, "CM") == 0) {
        vrednost += 900;
    }
}

{DESETICE} {
    if (strcmp(yytext, "X") == 0) {
        vrednost += 10;
    }
    else if (strcmp(yytext, "XX") == 0) {
        vrednost += 20;
    }
    else if (strcmp(yytext, "XXX") == 0) {
        vrednost += 30;
    }
    else if (strcmp(yytext, "XL") == 0) {
        vrednost += 40;
    }
    else if (strcmp(yytext, "L") == 0) {
        vrednost += 50;
    }
    else if (strcmp(yytext, "LX") == 0) {
        vrednost += 60;
    }
    else if (strcmp(yytext, "LXX") == 0) {
        vrednost += 70;
    }
    else if (strcmp(yytext, "LXXX") == 0) {
        vrednost += 80;
    }
    else if (strcmp(yytext, "XC") == 0) {
        vrednost += 90;
    }
}

{JEDINICE} {
    if (strcmp(yytext, "I") == 0) {
        vrednost += 1;
    }
    else if (strcmp(yytext, "II") == 0) {
        vrednost += 2;
    }
    else if (strcmp(yytext, "III") == 0) {
        vrednost += 3;
    }
    else if (strcmp(yytext, "IV") == 0) {
        vrednost += 4;
    }
    else if (strcmp(yytext, "V") == 0) {
        vrednost += 5;
    }
    else if (strcmp(yytext, "VI") == 0) {
        vrednost += 6;
    }
    else if (strcmp(yytext, "VII") == 0) {
        vrednost += 7;
    }
    else if (strcmp(yytext, "VIII") == 0) {
        vrednost += 8;
    }
    else if (strcmp(yytext, "IX") == 0) {
        vrednost += 9;
    }
}

.|\n {
    if (vrednost > 0) {
        printf("%d%s", vrednost, yytext);
        vrednost = 0;
    }
    else {
        printf("%s", yytext);
    }
}

%%

int main(int argc, char **argv) {
    if (argc > 1) {
        yyin = fopen(argv[1], "r");
        if (yyin == NULL) {
            fprintf(stderr, "greska pri otvaranju za citanje\n");
            exit(EXIT_FAILURE);
        }
    }
    else {
        yyin = stdin;
    }

    if (argc > 2) {
        yyout = fopen(argv[2], "w");
        if (yyout == NULL) {
            fprintf(stderr, "greska pri otvaranju za citanje\n");
            exit(EXIT_FAILURE);
        }
    }
    else {
        yyout = stdout;
    }
    
    yylex();

    if (yyin != stdin) {
        fclose(yyin);
    }
    if (yyout != stdout) {
        fclose(yyout);
    }

    return 0;
}
