#include "dinamicki_niz.h"
#include <stdexcept>

DinamickiNiz::DinamickiNiz() {
    m_niz = new int[KAPACITET];
    m_velicina = 0;
    m_kapcitet = KAPACITET;
    std::cout << "Prazan konstruktor" << std::endl;
}

DinamickiNiz::DinamickiNiz(int velicina, int vrednost) {
    m_niz = new int[velicina];
    m_velicina = velicina;
    m_kapcitet = velicina;

    for (int i = 0; i < m_velicina; i++) {
        m_niz[i] = vrednost;
    }
    std::cout << "Konstruktor sa parametrima" << std::endl;
}
DinamickiNiz::DinamickiNiz(const DinamickiNiz& drugi) {
    m_velicina = drugi.m_velicina;
    m_kapcitet = drugi.m_kapcitet;

    m_niz = new int[m_kapcitet];
    for (int i = 0; i < m_velicina; i++) {
        m_niz[i] = drugi[i];
    }
    std::cout << "Copy konstruktor" << std::endl;
}

DinamickiNiz::~DinamickiNiz() {
    delete[] m_niz;
    std::cout << "Destruktor" << std::endl;
}

DinamickiNiz& DinamickiNiz::operator=(const DinamickiNiz& drugi) {
    if (&drugi != this) {
        m_velicina = drugi.m_velicina;
        m_kapcitet = drugi.m_kapcitet;

        delete[] m_niz;

        m_niz = new int[m_kapcitet];
        for (int i = 0; i < m_velicina; i++) {
            m_niz[i] = drugi[i];
        }
    }
    return *this;
}

int DinamickiNiz::get_velicina() const {
    return m_velicina;
}

int& DinamickiNiz::operator[](int index) const {
    if (0 <= index && index < m_velicina) {
        return m_niz[index];
    }
    else {
        throw std::runtime_error("pristup van granica niza");
    }
}

void DinamickiNiz::dodaj_na_kraj(int vrednost) {
    if (m_velicina == m_kapcitet) {
        m_kapcitet *= KORAK;
        int *novi_niz = new int[m_kapcitet];

        for (int i = 0; i < m_velicina; i++) {
            novi_niz[i] = m_niz[i];
        }

        delete[] m_niz;
        m_niz = novi_niz;
    }

    m_niz[m_velicina++] = vrednost;
}

std::ostream& operator<<(std::ostream& os, const DinamickiNiz& dn) {
    for (int i = 0; i < dn.get_velicina(); i++) {
        os << dn[i] << " ";
    }
    return os;
}
