#include <iostream>
#include "sintaksno_stablo.hpp"

int main() {
    NizNaredbi *niz_naredbi = new NizNaredbi();
    
    // def x = 2.5;
    niz_naredbi->dodaj_cvor(
        new Definicija("x", new Konstanta(2.5))
    );

    // x = x * x + 2;
    niz_naredbi->dodaj_cvor(
        new Dodela(
            "x",
            new Sabiranje(
                new Mnozenje(new Promenljiva("x"), new Promenljiva("x")),
                new Konstanta(2)
            )
        )
    );

    // print(- x);
    niz_naredbi->dodaj_cvor(
        new Ispis(new Negacija(new Promenljiva("x")))
    );

    // 16.5 == 2 * x;
    niz_naredbi->dodaj_cvor(
        new Poredjenje(
            new Konstanta(16.5),
            new Mnozenje(new Konstanta(2), new Promenljiva("x"))
        )
    );

    ASTCvor *ast = niz_naredbi;

    std::cout << *ast << std::endl;

    TabelaSimbola tabela_simbola;
    ast->interpretiraj(tabela_simbola);

    delete ast;

    return 0;
}
