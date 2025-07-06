#include "tabela_simbola.hpp"
#include <iostream>

void TabelaSimbola::dodeli_vrednost(const std::string &promenljiva, int vrednost) {
    m_tabela[promenljiva] = vrednost;
}

int TabelaSimbola::vrednost_promenljive(const std::string &promenljiva) const {
    auto it = m_tabela.find(promenljiva);
    if (it == m_tabela.end()) {
        std::cerr << "promenljiva " << promenljiva << " nije definisana" << std::endl;
        exit(EXIT_FAILURE);
    }

    // ne mozemo da uradimo
    // return m_tabela[promenljiva];
    // jer je metoda const, a operator[] potencijalno menja mapu
    return it->second;
}
