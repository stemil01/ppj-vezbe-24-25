%option noyywrap

%{
    #include <stdio.h>
    #include <stdlib.h>

    int broj_redova = 0;
%}

%x V_KOMENTAR
%x J_KOMENTAR

%%

<INITIAL>\/\* {
    BEGIN(V_KOMENTAR);
}

<INITIAL>\/\/ {
    BEGIN(J_KOMENTAR);
}

<J_KOMENTAR>\n {
    BEGIN(INITIAL);
    broj_redova++;
}

<V_KOMENTAR>\n {
    broj_redova++;
}

<J_KOMENTAR,V_KOMENTAR>. {

}

<V_KOMENTAR>\*\/ {
    BEGIN(INITIAL);
}

. {
    ECHO;
}

\n {
    ECHO;
    broj_redova++;
}

%%

int main(int argc, char **argv) {
    if (argc > 1) {
        yyin = fopen(argv[1], "r");
        if (yyin == NULL) {
            fprintf(stderr, "greska pri otvaranju fajla za citanje\n");
            exit(EXIT_FAILURE);
        }
    }
    else {
        yyin = stdin;
    }

    if (argc > 2) {
        yyout = fopen(argv[2], "w");
        if (yyout == NULL) {
            fprintf(stderr, "greska pri otvaranju fajla za pisanje\n");
            exit(EXIT_FAILURE);
        }
    }
    else {
        yyout = stdout;
    }

    yylex();
    printf("%d\n", broj_redova);

    if (yyin != stdin) {
        fclose(yyin);
    }
    if (yyout != stdout) {
        fclose(yyout);
    }

    return 0;
}