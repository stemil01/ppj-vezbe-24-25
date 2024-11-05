%option noyywrap

%{
    #include <stdio.h>
    #include <stdlib.h>

    #define ID              1
    #define KLJUCNA_REC     2
    #define CELOBR_CONST    3
    #define REALNA_CONST    4
    #define OP_DODELE       5
    #define OP_RELACIJA     6
    #define OP_SABIRANJA    7
    #define SEPARATOR       8
%}

PRIR_BR 0|[1-9][0-9]*

%%

var|integer|begin|end|then {
    return KLJUCNA_REC;
}

[_a-zA-Z][_a-zA-Z0-9]* {
    return ID;
}

[+-]?{PRIR_BR} {
    return CELOBR_CONST;
}

[+-]?{PRIR_BR}\.([0-9]+([eE][+-]?{PRIR_BR})?)? {
    return REALNA_CONST;
}

:= {
    return OP_DODELE;
}

\<|\>|<=|>= {
    return OP_RELACIJA;
}

\+ {
    return OP_SABIRANJA;
}

;|:|\.|\(|\)|, {
    return SEPARATOR;
}

[ \t\n] {

}

. {
    fprintf(stderr, "pogresan karakter: %s\n", yytext);
    exit(EXIT_FAILURE);
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


    int token;
    while ((token = yylex()) != 0) {
        switch (token) {
            case ID:
                fprintf(yyout, "%s: ID\n", yytext);
                break;
            case KLJUCNA_REC:
                fprintf(yyout, "%s: KLJUCNA_REC\n", yytext);
                break;
            case CELOBR_CONST:
                fprintf(yyout, "%s: CELOBR_CONST\n", yytext);
                break;
            case REALNA_CONST:
                fprintf(yyout, "%s: REALNA_CONST\n", yytext);
                break;
            case OP_DODELE:
                fprintf(yyout, "%s: OP_DODELE\n", yytext);
                break;
            case OP_RELACIJA:
                fprintf(yyout, "%s: OP_RELACIJA\n", yytext);
                break;
            case OP_SABIRANJA:
                fprintf(yyout, "%s: OP_SABIRANJA\n", yytext);
                break;
            case SEPARATOR:
                fprintf(yyout, "%s: SEPARATOR\n", yytext);
                break;
        }
    }

    if (yyin != stdin) {
        fclose(yyin);
    }
    if (yyout != stdout) {
        fclose(yyout);
    }

    return 0;
}
