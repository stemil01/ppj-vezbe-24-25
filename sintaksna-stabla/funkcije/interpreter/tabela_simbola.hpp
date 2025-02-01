#ifndef TABELA_SIMBOLA_HPP
#define TABELA_SIMBOLA_HPP

#include <map>
#include "funkcija.hpp"

class TabelaSimbola {
public:
    ~TabelaSimbola();

    void dodeli_vrednost(const std::string &promenljiva, Funkcija *vrednost);
    Funkcija *vrednost_promenljive(const std::string &promenljiva) const;

private:
    std::map<std::string, Funkcija *> m_tabela;
};

#endif
