#include "kompleksan_broj.hpp"
#include <cmath>
#include <stdexcept>

KompleksanBroj::KompleksanBroj() : m_re(0), m_im(0) {

}

KompleksanBroj::KompleksanBroj(double re, double im)
    : m_re(re), m_im(im) {

}

double KompleksanBroj::get_re() const {
    return m_re;
}

double KompleksanBroj::get_im() const {
    return m_im;
}

void KompleksanBroj::set_re(double re) {
    m_re = re;
}

void KompleksanBroj::set_im(double im) {
    m_im = im;
}

KompleksanBroj KompleksanBroj::operator+(const KompleksanBroj& drugi) const {
    return KompleksanBroj(m_re + drugi.get_re(), m_im + drugi.get_im());
}

KompleksanBroj KompleksanBroj::operator-(const KompleksanBroj& drugi) const {
    return KompleksanBroj(m_re - drugi.get_re(), m_im - drugi.get_im());
}

KompleksanBroj KompleksanBroj::operator*(const KompleksanBroj& drugi) const {
    return KompleksanBroj(
        m_re * drugi.get_re() - m_im * drugi.get_im(),
        m_re * drugi.get_im() + m_im * drugi.get_re()
    );
}

KompleksanBroj KompleksanBroj::operator/(const KompleksanBroj& drugi) const {
    double a = m_re, b = m_im;
    double c = drugi.get_re(), d = drugi.get_im();

    double re = a * c + b * d;
    double im = a * b - b * d;
    double imenilac = c * c + d * d;

    if (imenilac == 0) {
        throw std::runtime_error("deljenje 0");
    }

    return KompleksanBroj(re / imenilac, im / imenilac);
}

KompleksanBroj& KompleksanBroj::operator++() {
    m_re++;
    return *this;
}

KompleksanBroj& KompleksanBroj::operator--() {
    m_re--;
    return *this;
}

KompleksanBroj KompleksanBroj::operator++(int) {
    KompleksanBroj temp = *this;
    m_re++;
    return temp;
}

KompleksanBroj KompleksanBroj::operator--(int) {
    KompleksanBroj temp = *this;
    m_re--;
    return temp;
}

KompleksanBroj& KompleksanBroj::operator+=(const KompleksanBroj& drugi) {
    m_re += drugi.get_re();
    m_im += drugi.get_im();
    return *this;
}

KompleksanBroj& KompleksanBroj::operator-=(const KompleksanBroj& drugi) {
    m_re -= drugi.get_re();
    m_im -= drugi.get_im();
    return *this;
}

bool KompleksanBroj::operator==(const KompleksanBroj& drugi) const {
    return m_re == drugi.get_re() && m_im == drugi.get_im();
}

bool KompleksanBroj::operator!=(const KompleksanBroj& drugi) const {
    return !(*this == drugi);
}

KompleksanBroj KompleksanBroj::operator-() const {
    return KompleksanBroj(- m_re, - m_im);
}

KompleksanBroj KompleksanBroj::operator~() const {
    return KompleksanBroj(m_re, - m_im);
}

double KompleksanBroj::mod() const {
    return std::sqrt(m_re * m_re + m_im * m_im);
}

double KompleksanBroj::arg() const {
    return atan2(m_im, m_re);
}

std::ostream& operator<<(std::ostream& os, const KompleksanBroj& kb) {
    os << kb.get_re();
    if (kb.get_im() < 0) {
        os << " - " << - kb.get_im();
    }
    else {
        os << " + " << kb.get_im();
    }
    os << " * i";

    return os;
}

std::istream& operator>>(std::istream& is, KompleksanBroj& kb) {
    double re, im;
    is >> re >> im;

    kb.set_re(re);
    kb.set_im(im);

    return is;
}
