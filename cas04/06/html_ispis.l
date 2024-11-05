%option noyywrap

%{
    #include <stdio.h>
    #include <stdlib.h>

    void ispisi_karakter(const char c);
    void ispisi_string(const char *s, const char *boja);
%}

%%

\/\*([^*]|\*+[^*/])*\*+\/ {
    ispisi_string(yytext, "green");
}

\/\/.* {
    ispisi_string(yytext, "green");
}

#(\\\n|.)* {
    ispisi_string(yytext, "purple");
}

int|double|char|if|else|const {
    ispisi_string(yytext, "blue");
}

.|\n {
    ispisi_string(yytext, "black");
}

%%

void ispisi_karakter(const char c) {
    switch (c) {
        case ' ':
            fprintf(yyout, "&nbsp;");
            break;
        case '\n':
            fprintf(yyout, "<br>");
            break;
        case '<':
            fprintf(yyout, "&lt;");
            break;
        case '>':
            fprintf(yyout, "&gt;");
            break;
        default:
            fprintf(yyout, "%c", c);
    }
}

void ispisi_string(const char *s, const char *boja) {
    fprintf(yyout, "<span style=\"color:%s\">", boja);
    for (int i = 0; s[i] != '\0'; i++) {
        ispisi_karakter(s[i]);
    }
    fprintf(yyout, "</span>");
}

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

    fprintf(yyout, "<html>");
    yylex();
    fprintf(yyout, "</html>");

    if (yyin != stdin) {
        fclose(yyin);
    }
    if (yyout != stdout) {
        fclose(yyout);
    }

    return 0;
}
