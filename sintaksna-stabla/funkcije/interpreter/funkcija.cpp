#include "funkcija.hpp"
#include <cmath>

// --------------------------------------------

Funkcija::~Funkcija() {}

std::ostream &operator<<(std::ostream &os, const Funkcija &funkcija) {
    funkcija.ispisi(os);
    return os;
}

// --------------------------------------------

KonstantnaFunkcija::KonstantnaFunkcija(double vrednost)
    : m_vrednost(vrednost) {}


double KonstantnaFunkcija::izracunaj(double vrednost) const {
    return m_vrednost;
}

void KonstantnaFunkcija::ispisi(std::ostream &os) const {
    os << m_vrednost;
}

Funkcija *KonstantnaFunkcija::izvod() const {
    return new KonstantnaFunkcija(0);
}

Funkcija *KonstantnaFunkcija::komponuj(Funkcija *funkcija) const {
    return new KonstantnaFunkcija(*this);
}

Funkcija *KonstantnaFunkcija::kloniraj() const {
    return new KonstantnaFunkcija(*this);
}

// --------------------------------------------

double IdentitetFunkcija::izracunaj(double vrednost) const {
    return vrednost;
}

void IdentitetFunkcija::ispisi(std::ostream &os) const {
    os << "x";
}

Funkcija *IdentitetFunkcija::izvod() const {
    return new KonstantnaFunkcija(1);
}

Funkcija *IdentitetFunkcija::komponuj(Funkcija *funkcija) const {
    // mora kloniraj zbog kompozicije kod npr. binarnih funkcija
    return funkcija->kloniraj();
}

Funkcija *IdentitetFunkcija::kloniraj() const {
    return new IdentitetFunkcija(*this);
}

// --------------------------------------------

UnarnaFunkcija::UnarnaFunkcija(Funkcija *funkcija)
    : m_funkcija(funkcija) {}

UnarnaFunkcija::UnarnaFunkcija(const UnarnaFunkcija &druga) {
    m_funkcija = druga.m_funkcija->kloniraj();
}

UnarnaFunkcija::~UnarnaFunkcija() {
    delete m_funkcija;
}

// --------------------------------------------

BinarnaFunkcija::BinarnaFunkcija(Funkcija *leva, Funkcija *desna)
    : m_leva(leva), m_desna(desna) {}

BinarnaFunkcija::BinarnaFunkcija(const BinarnaFunkcija &druga) {
    m_leva = druga.m_leva->kloniraj();
    m_desna = druga.m_desna->kloniraj();
}

BinarnaFunkcija::~BinarnaFunkcija() {
    delete m_leva;
    delete m_desna;
}

// --------------------------------------------

Negacija::Negacija(Funkcija *funkcija)
    : UnarnaFunkcija(funkcija) {}

double Negacija::izracunaj(double vrednost) const {
    return - m_funkcija->izracunaj(vrednost);
}

void Negacija::ispisi(std::ostream &os) const {
    os << "- (";
    m_funkcija->ispisi(os);
    os << ")";
}

Funkcija *Negacija::izvod() const {
    return new Negacija(m_funkcija->izvod());
}

Funkcija *Negacija::komponuj(Funkcija *funkcija) const {
    return new Negacija(m_funkcija->komponuj(funkcija));
}

Funkcija *Negacija::kloniraj() const {
    return new Negacija(*this);
}

// --------------------------------------------

Sin::Sin(Funkcija *funkcija)
    : UnarnaFunkcija(funkcija) {}

double Sin::izracunaj(double vrednost) const {
    return sin(m_funkcija->izracunaj(vrednost));
}

void Sin::ispisi(std::ostream &os) const {
    os << "sin(";
    m_funkcija->ispisi(os);
    os << ")";
}

Funkcija *Sin::izvod() const {
    return new Mnozenje(
        new Cos(m_funkcija->kloniraj()),
        m_funkcija->izvod()
    );
}

Funkcija *Sin::komponuj(Funkcija *funkcija) const {
    return new Sin(m_funkcija->komponuj(funkcija));
}

Funkcija *Sin::kloniraj() const {
    return new Sin(*this);
}

// --------------------------------------------

Cos::Cos(Funkcija *funkcija)
    : UnarnaFunkcija(funkcija) {}

double Cos::izracunaj(double vrednost) const {
    return cos(m_funkcija->izracunaj(vrednost));
}

void Cos::ispisi(std::ostream &os) const {
    os << "cos(";
    m_funkcija->ispisi(os);
    os << ")";
}

Funkcija *Cos::izvod() const {
    return new Negacija(
        new Mnozenje(
            new Sin(m_funkcija->kloniraj()),
            m_funkcija->izvod()
        )
    );
}

Funkcija *Cos::komponuj(Funkcija *funkcija) const {
    return new Cos(m_funkcija->komponuj(funkcija));
}

Funkcija *Cos::kloniraj() const {
    return new Cos(*this);
}

// --------------------------------------------

Sabiranje::Sabiranje(Funkcija *leva, Funkcija *desna)
    : BinarnaFunkcija(leva, desna) {}

double Sabiranje::izracunaj(double vrednost) const {
    return m_leva->izracunaj(vrednost) + m_desna->izracunaj(vrednost);
}

void Sabiranje::ispisi(std::ostream &os) const {
    os << "(";
    m_leva->ispisi(os);
    os << ") + (";
    m_desna->ispisi(os);
    os << ")";
}

Funkcija *Sabiranje::izvod() const {
    return new Sabiranje(
        m_leva->izvod(),
        m_desna->izvod()
    );
}

Funkcija *Sabiranje::komponuj(Funkcija *funkcija) const {
    return new Sabiranje(
        m_leva->komponuj(funkcija),
        m_desna->komponuj(funkcija)
    );
}

Funkcija *Sabiranje::kloniraj() const {
    return new Sabiranje(*this);
}

// --------------------------------------------

Oduzimanje::Oduzimanje(Funkcija *leva, Funkcija *desna)
    : BinarnaFunkcija(leva, desna) {}

double Oduzimanje::izracunaj(double vrednost) const {
    return m_leva->izracunaj(vrednost) - m_desna->izracunaj(vrednost);
}

void Oduzimanje::ispisi(std::ostream &os) const {
    os << "(";
    m_leva->ispisi(os);
    os << ") - (";
    m_desna->ispisi(os);
    os << ")";
}

Funkcija *Oduzimanje::izvod() const {
    return new Oduzimanje(
        m_leva->izvod(),
        m_desna->izvod()
    );
}

Funkcija *Oduzimanje::komponuj(Funkcija *funkcija) const {
    return new Oduzimanje(
        m_leva->komponuj(funkcija),
        m_desna->komponuj(funkcija)
    );
}

Funkcija *Oduzimanje::kloniraj() const {
    return new Oduzimanje(*this);
}

// --------------------------------------------

Mnozenje::Mnozenje(Funkcija *leva, Funkcija *desna)
    : BinarnaFunkcija(leva, desna) {}

double Mnozenje::izracunaj(double vrednost) const {
    return m_leva->izracunaj(vrednost) * m_desna->izracunaj(vrednost);
}

void Mnozenje::ispisi(std::ostream &os) const {
    os << "(";
    m_leva->ispisi(os);
    os << ") * (";
    m_desna->ispisi(os);
    os << ")";
}

Funkcija *Mnozenje::izvod() const {
    return new Sabiranje(
        new Mnozenje(
            m_leva->izvod(),
            m_desna->kloniraj()
        ),
        new Mnozenje(
            m_leva->kloniraj(),
            m_desna->izvod()
        )
    );
}

Funkcija *Mnozenje::komponuj(Funkcija *funkcija) const {
    return new Mnozenje(
        m_leva->komponuj(funkcija),
        m_desna->komponuj(funkcija)
    );
}

Funkcija *Mnozenje::kloniraj() const {
    return new Mnozenje(*this);
}

// --------------------------------------------

Deljenje::Deljenje(Funkcija *leva, Funkcija *desna)
    : BinarnaFunkcija(leva, desna) {}

double Deljenje::izracunaj(double vrednost) const {
    return m_leva->izracunaj(vrednost) / m_desna->izracunaj(vrednost);
}

void Deljenje::ispisi(std::ostream &os) const {
    os << "(";
    m_leva->ispisi(os);
    os << ") / (";
    m_desna->ispisi(os);
    os << ")";
}

Funkcija *Deljenje::izvod() const {
    return new Deljenje(
        new Oduzimanje(
            new Mnozenje(
                m_leva->izvod(),
                m_desna->kloniraj()
            ),
            new Mnozenje(
                m_leva->kloniraj(),
                m_desna->izvod()
            )
        ),
        new Mnozenje(
            m_desna->kloniraj(),
            m_desna->kloniraj()
        )
    );
}

Funkcija *Deljenje::komponuj(Funkcija *funkcija) const {
    return new Deljenje(
        m_leva->komponuj(funkcija),
        m_desna->komponuj(funkcija)
    );
}

Funkcija *Deljenje::kloniraj() const {
    return new Deljenje(*this);
}

// --------------------------------------------
