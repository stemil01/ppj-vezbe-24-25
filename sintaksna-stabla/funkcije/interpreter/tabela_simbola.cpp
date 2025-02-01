#include "tabela_simbola.hpp"

TabelaSimbola::~TabelaSimbola() {
    for (auto &p : m_tabela) {
        delete p.second;
    }
}

void TabelaSimbola::dodeli_vrednost(const std::string &promenjliva, Funkcija *vrednost) {
    auto it = m_tabela.find(promenjliva);
    if (it != m_tabela.end()) {
        delete it->second;
    }
    m_tabela[promenjliva] = vrednost;
}

Funkcija *TabelaSimbola::vrednost_promenljive(const std::string &promenjliva) const {
    auto it = m_tabela.find(promenjliva);
    if (it == m_tabela.end()) {
        std::cerr << "promenjliva " << promenjliva << " nije definisana" << std::endl;
        exit(EXIT_FAILURE);
    }
    return it->second;
}
