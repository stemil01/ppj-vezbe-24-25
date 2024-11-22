#ifndef KOMPLEKSAN_BROJ_HPP
#define KOMPLEKSAN_BROJ_HPP

#include <iostream>
#include <cmath>

class KompleksanBroj {
public:
    KompleksanBroj();
    KompleksanBroj(double re, double im = 0.0);

    double get_re() const;
    double get_im() const;

    void set_re(double re);
    void set_im(double im);

    KompleksanBroj operator+(const KompleksanBroj& drugi) const;
    KompleksanBroj operator-(const KompleksanBroj& drugi) const; 
    KompleksanBroj operator*(const KompleksanBroj& drugi) const;
    KompleksanBroj operator/(const KompleksanBroj& drugi) const;

    KompleksanBroj& operator++();
    KompleksanBroj& operator--();

    KompleksanBroj operator++(int);
    KompleksanBroj operator--(int);

    KompleksanBroj& operator+=(const KompleksanBroj& drugi);
    KompleksanBroj& operator-=(const KompleksanBroj& drugi);

    KompleksanBroj operator-() const;
    KompleksanBroj operator~() const;

    bool operator==(const KompleksanBroj& drugi) const;
    bool operator!=(const KompleksanBroj& drugi) const;

    double mod() const;
    double arg() const;

private:
    double m_re, m_im;
};

std::ostream& operator<<(std::ostream& os, const KompleksanBroj& kb);
std::istream& operator>>(std::istream& is, KompleksanBroj& kb);

#endif
