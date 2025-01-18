#ifndef TABELA_SIMBOLA_HPP
#define TABELA_SIMBOLA_HPP

#include <string> 
#include <map>

class TabelaSimbola {
public:
    void definisi_promenljivu(const std::string &promenljiva, double vrednost);
    void dodeli_vrednost(const std::string &promenljiva, double vrednost);
    double vrednost_promenljive(const std::string &promenljiva) const;

private:
    std::map<std::string, double> m_tabela;
};

#endif
