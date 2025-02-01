#ifndef SINTAKSNO_STABLO_HPP
#define SINTAKSNO_STABLO_HPP

#include <iostream>
#include <vector>
#include "tabela_simbola.hpp"

// --------------------------------------------

class ASTCvor {
public:
    virtual ~ASTCvor();
    virtual void ispisi(std::ostream &os) const = 0;
    virtual Funkcija *interpretiraj(TabelaSimbola &tabela_simbola) const = 0;
    virtual ASTCvor *kloniraj() const = 0;
};

std::ostream &operator<<(std::ostream &os, const ASTCvor &ast_cvor);

// --------------------------------------------

class NizNaredbiCvor : public ASTCvor {
public:
    NizNaredbiCvor();
    NizNaredbiCvor(const NizNaredbiCvor &drugi);
    ~NizNaredbiCvor();

    void dodaj_cvor(ASTCvor *cvor);

    // metode iz natklase
    void ispisi(std::ostream &os) const override;
    Funkcija *interpretiraj(TabelaSimbola &tabela_simbola) const override;
    ASTCvor *kloniraj() const override;

private:
    std::vector<ASTCvor *> m_naredbe;
};

// --------------------------------------------

class PrazanCvor : public ASTCvor {
public:
    // metode iz natklase
    void ispisi(std::ostream &os) const override;
    Funkcija *interpretiraj(TabelaSimbola &tabela_simbola) const override;
    ASTCvor *kloniraj() const override;
};

// --------------------------------------------

class PromenljivaCvor : public ASTCvor {
public:
    PromenljivaCvor(const std::string &id);

    // metode iz natklase
    void ispisi(std::ostream &os) const override;
    Funkcija *interpretiraj(TabelaSimbola &tabela_simbola) const override;
    ASTCvor *kloniraj() const override;

private:
    std::string m_id;
};

// --------------------------------------------

class VrednostCvor : public ASTCvor {
public:
    VrednostCvor(ASTCvor *izraz, double vrednost);
    VrednostCvor(const VrednostCvor &drugi);
    ~VrednostCvor();

    // metode iz natklase
    void ispisi(std::ostream &os) const override;
    Funkcija *interpretiraj(TabelaSimbola &tabela_simbola) const override;
    ASTCvor *kloniraj() const override;

private:
    ASTCvor *m_izraz;
    double m_vrednost;
};

// --------------------------------------------

class DodelaCvor : public ASTCvor {
public:
    DodelaCvor(const std::string &id, ASTCvor *izraz);
    DodelaCvor(const DodelaCvor &drugi);
    ~DodelaCvor();

    // metode iz natklase
    void ispisi(std::ostream &os) const override;
    Funkcija *interpretiraj(TabelaSimbola &tabela_simbola) const override;
    ASTCvor *kloniraj() const override;

private:
    std::string m_id;
    ASTCvor *m_izraz;
};

// --------------------------------------------
class KonstantaCvor : public ASTCvor {
public:
    KonstantaCvor(double vrednost);

    // metode iz natklase
    void ispisi(std::ostream &os) const override;
    Funkcija *interpretiraj(TabelaSimbola &tabela_simbola) const override;
    ASTCvor *kloniraj() const override;

private:
    double m_vrednost;
};

// --------------------------------------------

class IdentitetCvor : public ASTCvor {
public:
    // metode iz natklase
    void ispisi(std::ostream &os) const override;
    Funkcija *interpretiraj(TabelaSimbola &tabela_simbola) const override;
    ASTCvor *kloniraj() const override;
};

// --------------------------------------------

class UnarniCvor : public ASTCvor {
public:
    UnarniCvor(ASTCvor *cvor);
    UnarniCvor(const UnarniCvor &drugi);
    ~UnarniCvor();

    // metode iz natklase
    virtual void ispisi(std::ostream &os) const = 0;
    virtual Funkcija *interpretiraj(TabelaSimbola &tabela_simbola) const = 0;
    virtual ASTCvor *kloniraj() const = 0;

protected:
    ASTCvor *m_cvor;
};

// --------------------------------------------

class BinarniCvor : public ASTCvor {
public:
    BinarniCvor(ASTCvor *levi, ASTCvor *desni);
    BinarniCvor(const BinarniCvor &drugi);
    ~BinarniCvor();

    // metode iz natklase
    virtual void ispisi(std::ostream &os) const = 0;
    virtual Funkcija *interpretiraj(TabelaSimbola &tabela_simbola) const = 0;
    virtual ASTCvor *kloniraj() const = 0;

protected:
    ASTCvor *m_levi, *m_desni;
};

// --------------------------------------------

class NegacijaCvor : public UnarniCvor {
public:
    NegacijaCvor(ASTCvor *cvor);

    // metode iz natklase
    void ispisi(std::ostream &os) const override;
    Funkcija *interpretiraj(TabelaSimbola &tabela_simbola) const override;
    ASTCvor *kloniraj() const override;
};

// --------------------------------------------

class SinCvor : public UnarniCvor {
public:
    SinCvor(ASTCvor *cvor);

    // metode iz natklase
    void ispisi(std::ostream &os) const override;
    Funkcija *interpretiraj(TabelaSimbola &tabela_simbola) const override;
    ASTCvor *kloniraj() const override;
};

// --------------------------------------------

class CosCvor : public UnarniCvor {
public:
    CosCvor(ASTCvor *cvor);

    // metode iz natklase
    void ispisi(std::ostream &os) const override;
    Funkcija *interpretiraj(TabelaSimbola &tabela_simbola) const override;
    ASTCvor *kloniraj() const override;
};

// --------------------------------------------

class IspisCvor : public UnarniCvor {
public:
    IspisCvor(ASTCvor *cvor);

    // metode iz natklase
    void ispisi(std::ostream &os) const override;
    Funkcija *interpretiraj(TabelaSimbola &tabela_simbola) const override;
    ASTCvor *kloniraj() const override;
};

// --------------------------------------------

class IzvodCvor : public UnarniCvor {
public:
    IzvodCvor(ASTCvor *cvor);

    // metode iz natklase
    void ispisi(std::ostream &os) const override;
    Funkcija *interpretiraj(TabelaSimbola &tabela_simbola) const override;
    ASTCvor *kloniraj() const override;
};

// --------------------------------------------

class SabiranjeCvor : public BinarniCvor {
public:
    SabiranjeCvor(ASTCvor *levi, ASTCvor *desni);

    // metode iz natklase
    void ispisi(std::ostream &os) const override;
    Funkcija *interpretiraj(TabelaSimbola &tabela_simbola) const override;
    ASTCvor *kloniraj() const override;
};

// --------------------------------------------

class OduzimanjeCvor : public BinarniCvor {
public:
    OduzimanjeCvor(ASTCvor *levi, ASTCvor *desni);

    // metode iz natklase
    void ispisi(std::ostream &os) const override;
    Funkcija *interpretiraj(TabelaSimbola &tabela_simbola) const override;
    ASTCvor *kloniraj() const override;
};

// --------------------------------------------

class MnozenjeCvor : public BinarniCvor {
public:
    MnozenjeCvor(ASTCvor *levi, ASTCvor *desni);

    // metode iz natklase
    void ispisi(std::ostream &os) const override;
    Funkcija *interpretiraj(TabelaSimbola &tabela_simbola) const override;
    ASTCvor *kloniraj() const override;
};

// --------------------------------------------

class DeljenjeCvor : public BinarniCvor {
public:
    DeljenjeCvor(ASTCvor *levi, ASTCvor *desni);

    // metode iz natklase
    void ispisi(std::ostream &os) const override;
    Funkcija *interpretiraj(TabelaSimbola &tabela_simbola) const override;
    ASTCvor *kloniraj() const override;
};

// --------------------------------------------

class KompozicijaCvor : public BinarniCvor {
public:
    KompozicijaCvor(ASTCvor *levi, ASTCvor *desni);

    // metode iz natklase
    void ispisi(std::ostream &os) const override;
    Funkcija *interpretiraj(TabelaSimbola &tabela_simbola) const override;
    ASTCvor *kloniraj() const override;
};

// --------------------------------------------

#endif
