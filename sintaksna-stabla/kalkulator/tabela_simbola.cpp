#include <iostream>
#include "tabela_simbola.hpp"

void TabelaSimbola::definisi_promenljivu(const std::string &promenljiva, double vrednost) {
    if (m_tabela.find(promenljiva) != m_tabela.end()) {
        std::cerr << "promenljiva " << promenljiva << " je vec deklarisana" << std::endl;
        exit(EXIT_FAILURE);
    }
    m_tabela[promenljiva] = vrednost;
}

void TabelaSimbola::dodeli_vrednost(const std::string &promenljiva, double vrednost) {
    if (m_tabela.find(promenljiva) == m_tabela.end()) {
        std::cerr << "promenljiva " << promenljiva << " nije prethodno definisana" << std::endl;
        exit(EXIT_FAILURE);
    }
    m_tabela[promenljiva] = vrednost;
}

double TabelaSimbola::vrednost_promenljive(const std::string &promenljiva) const {
    auto it = m_tabela.find(promenljiva);
    if (it == m_tabela.end()) {
        std::cerr << "promenljiva " << promenljiva << " nije prethodno definisana" << std::endl;
        exit(EXIT_FAILURE);
    }
    return it->second;
}
