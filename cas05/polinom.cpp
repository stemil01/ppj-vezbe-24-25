#include "polinom.hpp"
#include <stdexcept>

Polinom::Polinom(int stepen)
    : m_koeficijenti(stepen + 1, 0) {

}

Polinom::Polinom(const std::vector<double>& koeficijenti)
    : m_koeficijenti(koeficijenti) {

}

int Polinom::get_stepen() const {
    return m_koeficijenti.size() - 1;
}

void Polinom::dodaj_na_kraj(double koeficijent) {
    m_koeficijenti.push_back(koeficijent);
}

void Polinom::izbaci_vodece_nule() {
    int i = get_stepen();
    while (i >= 0 && m_koeficijenti[i] == 0) {
        m_koeficijenti.pop_back();
        i--;
    }
}

double Polinom::operator[](int index) const {
    if (0 <= index && index <= get_stepen()) {
        return m_koeficijenti[index];
    }
    throw std::runtime_error("pristup van granica niza");
}

Polinom Polinom::operator+(const Polinom& drugi) const {
    int ovaj_stepen = get_stepen();
    int drugi_stepen = drugi.get_stepen();
    int max_stepen = std::max(ovaj_stepen, drugi_stepen);

    Polinom rezultat(max_stepen);

    for (int i = 0; i <= max_stepen; i++) {
        if (i <= ovaj_stepen) {
            rezultat.m_koeficijenti[i] += m_koeficijenti[i];
        }

        if (i <= drugi_stepen) {
            rezultat.m_koeficijenti[i] += drugi.m_koeficijenti[i];
        }
    }

    rezultat.izbaci_vodece_nule();
    return rezultat;
}

Polinom Polinom::operator-(const Polinom& drugi) const {
    int ovaj_stepen = get_stepen();
    int drugi_stepen = drugi.get_stepen();
    int max_stepen = std::max(ovaj_stepen, drugi_stepen);

    Polinom rezultat(max_stepen);

    for (int i = 0; i <= max_stepen; i++) {
        if (i <= ovaj_stepen) {
            rezultat.m_koeficijenti[i] += m_koeficijenti[i];
        }

        if (i <= drugi_stepen) {
            rezultat.m_koeficijenti[i] -= drugi.m_koeficijenti[i];
        }
    }

    rezultat.izbaci_vodece_nule();
    return rezultat;
}

Polinom Polinom::operator*(const Polinom& drugi) const {
    int ovaj_stepen = get_stepen();
    int drugi_stepen = drugi.get_stepen();
    Polinom rezultat(ovaj_stepen + drugi_stepen);

    for (int i = 0; i <= ovaj_stepen; i++) {
        for (int j = 0; j <= drugi_stepen; j++) {
            rezultat.m_koeficijenti[i + j] += m_koeficijenti[i] * drugi.m_koeficijenti[j];
        }
    }

    rezultat.izbaci_vodece_nule();
    return rezultat;
}

Polinom Polinom::operator-() const {
    Polinom rezultat(*this);
    for (int i = 0; i <= get_stepen(); i++) {
        rezultat.m_koeficijenti[i] = - m_koeficijenti[i];
    }
    return rezultat;
}

double Polinom::operator()(double vrednost) const {
    double rezultat = 0.0;
    for (int i = get_stepen(); i >= 0; i--) {
        rezultat = rezultat * vrednost + m_koeficijenti[i];
    }
    return rezultat;
}

Polinom Polinom::izvod() const {
    int stepen = get_stepen();
    if (stepen == 0) {
        return Polinom(0);
    }

    Polinom rezultat(stepen - 1);
    for (int i = 1; i <= stepen; i++) {
        rezultat.m_koeficijenti[i - 1] = i * m_koeficijenti[i];
    }

    rezultat.izbaci_vodece_nule();
    return rezultat;
}

bool Polinom::operator==(const Polinom& drugi) const {
    if (get_stepen() != drugi.get_stepen()) {
        return false;
    }

    for (int i = 0; i <= get_stepen(); i++) {
        if (m_koeficijenti[i] != drugi.m_koeficijenti[i]) {
            return false;
        }
    }

    return true;
}

bool Polinom::operator!=(const Polinom& drugi) const {
    return !(*this == drugi);
}

Polinom Polinom::integral(double c) const {
    int stepen = get_stepen();
    Polinom rezultat(stepen + 1);

    rezultat.m_koeficijenti[0] = c;
    for (int i = 0; i <= stepen; i++) {
        rezultat.m_koeficijenti[i + 1] = m_koeficijenti[i] / (i + 1);
    }

    rezultat.izbaci_vodece_nule();
    return rezultat;
}

std::ostream& operator<<(std::ostream& os, const Polinom& polinom) {
    for (int i = polinom.get_stepen(); i > 0; i--) {
        os << polinom[i] << "*x^" << i << " + ";
    }
    os << polinom[0];
    return os;
}
