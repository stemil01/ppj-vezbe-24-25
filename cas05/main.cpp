#include <iostream>
#include "polinom.h"

int main() {
    Polinom p(5), q;

    p.dodaj_koeficijent(4);
    p.dodaj_koeficijent(3);
    p.dodaj_koeficijent(-1);
    p.dodaj_koeficijent(5);
    p.dodaj_koeficijent(6);

    q = p;

    std::cout << p << std::endl;
    std::cout << q << std::endl;
    std::cout << p + q<< std::endl;
    return 0;
}