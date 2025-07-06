#ifndef TABELA_SIMBOLA_HPP
#define TABELA_SIMBOLA_HPP

#include <string>
#include <map>

class TabelaSimbola {
public:
    void dodeli_vrednost(const std::string &promenljiva, int vrednost);
    int vrednost_promenljive(const std::string &promenljiva) const;

private:
    std::map<std::string, int> m_tabela;
};

#endif
