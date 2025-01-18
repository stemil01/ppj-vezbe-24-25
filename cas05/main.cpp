#include <iostream>
#include "polinom.hpp"

int main() {
    Polinom p(5), q;

    p.dodaj_na_kraj(4);
    p.dodaj_na_kraj(3);
    p.dodaj_na_kraj(-1);
    p.dodaj_na_kraj(5);
    p.dodaj_na_kraj(6);

    q = p;

    std::cout << p << std::endl;
    std::cout << q << std::endl;
    std::cout << p + q<< std::endl;
    return 0;
}