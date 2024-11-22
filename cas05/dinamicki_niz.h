#ifndef DINAMICKI_NIZ_H
#define DINAMICKI_NIZ_H

#include <iostream>

#define KAPACITET   16
#define KORAK       2

class DinamickiNiz {
public:
    DinamickiNiz();
    DinamickiNiz(int velicina, int vrednost = 0);
    ~DinamickiNiz();
    DinamickiNiz(const DinamickiNiz& drugi);
    DinamickiNiz& operator=(const DinamickiNiz& drugi);

    int& operator[](int index) const;

    void dodaj_na_kraj(int vrednost);

    int get_velicina() const;

private:
    int *m_niz;
    int m_kapcitet;
    int m_velicina;
};

std::ostream& operator<<(std::ostream& os, const DinamickiNiz& dn);

#endif
