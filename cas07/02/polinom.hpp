#ifndef POLINOM_HPP
#define POLINOM_HPP

#include <iostream>
#include <vector>

class Polinom {
public:
    Polinom(int stepen = 0);
    Polinom(const std::vector<double>& koeficijenti);

    int get_stepen() const;
    void dodaj_na_kraj(double koeficijent);

    Polinom operator+(const Polinom& drugi) const;
    Polinom operator-(const Polinom& drugi) const;
    Polinom operator*(const Polinom& drugi) const;
    Polinom operator-() const;

    double operator()(double vrednost) const;
    double operator[](int index) const;

    bool operator==(const Polinom& drugi) const;
    bool operator!=(const Polinom& drugi) const;

    Polinom izvod() const;
    Polinom integral(double c) const;

private:
    std::vector<double> m_koeficijenti;

    void izbaci_vodece_nule();
};

std::ostream& operator<<(std::ostream& os, const Polinom& p);

#endif
