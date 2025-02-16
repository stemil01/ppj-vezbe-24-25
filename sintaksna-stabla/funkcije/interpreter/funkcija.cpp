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
    return funkcija->kloniraj(); // moramo da pravimo kopiju!
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

NegacijaFunkcija::NegacijaFunkcija(Funkcija *funkcija)
    : UnarnaFunkcija(funkcija) {}

double NegacijaFunkcija::izracunaj(double vrednost) const {
    return - m_funkcija->izracunaj(vrednost);
}

void NegacijaFunkcija::ispisi(std::ostream &os) const {
    os << "- (" << *m_funkcija << ")";
}

Funkcija *NegacijaFunkcija::izvod() const {
    return new NegacijaFunkcija(m_funkcija->izvod());
}

Funkcija *NegacijaFunkcija::komponuj(Funkcija *funkcija) const {
    return new NegacijaFunkcija(m_funkcija->komponuj(funkcija));
}

Funkcija *NegacijaFunkcija::kloniraj() const {
    return new NegacijaFunkcija(*this);
}

// --------------------------------------------

SinFunkcija::SinFunkcija(Funkcija *funkcija)
    : UnarnaFunkcija(funkcija) {}

double SinFunkcija::izracunaj(double vrednost) const {
    return sin(m_funkcija->izracunaj(vrednost));
}

void SinFunkcija::ispisi(std::ostream &os) const {
    os << "sin(" << *m_funkcija << ")";
}

Funkcija *SinFunkcija::izvod() const {
    return new MnozenjeFunkcija(
        new CosFunkcija(m_funkcija->kloniraj()),
        m_funkcija->izvod()
    );
}

Funkcija *SinFunkcija::komponuj(Funkcija *funkcija) const {
    return new SinFunkcija(m_funkcija->komponuj(funkcija));
}

Funkcija *SinFunkcija::kloniraj() const {
    return new SinFunkcija(*this);
}

// --------------------------------------------

CosFunkcija::CosFunkcija(Funkcija *funkcija)
    : UnarnaFunkcija(funkcija) {}

double CosFunkcija::izracunaj(double vrednost) const {
    return cos(m_funkcija->izracunaj(vrednost));
}

void CosFunkcija::ispisi(std::ostream &os) const {
    os << "cos(" << *m_funkcija << ")";
}

Funkcija *CosFunkcija::izvod() const {
    return new NegacijaFunkcija(
        new MnozenjeFunkcija(
            new SinFunkcija(m_funkcija->kloniraj()),
            m_funkcija->izvod()
        )
    );
}

Funkcija *CosFunkcija::komponuj(Funkcija *funkcija) const {
    return new CosFunkcija(m_funkcija->komponuj(funkcija));
}

Funkcija *CosFunkcija::kloniraj() const {
    return new CosFunkcija(*this);
}

// --------------------------------------------

SabiranjeFunkcija::SabiranjeFunkcija(Funkcija *leva, Funkcija *desna)
    : BinarnaFunkcija(leva, desna) {}

double SabiranjeFunkcija::izracunaj(double vrednost) const {
    return m_leva->izracunaj(vrednost) + m_desna->izracunaj(vrednost);
}

void SabiranjeFunkcija::ispisi(std::ostream &os) const {
    os << "(" << *m_leva << ") + (" << *m_desna << ")";
}

Funkcija *SabiranjeFunkcija::izvod() const {
    return new SabiranjeFunkcija(
        m_leva->izvod(),
        m_desna->izvod()
    );
}

Funkcija *SabiranjeFunkcija::komponuj(Funkcija *funkcija) const {
    return new SabiranjeFunkcija(
        m_leva->komponuj(funkcija),
        m_desna->komponuj(funkcija)
    );
}

Funkcija *SabiranjeFunkcija::kloniraj() const {
    return new SabiranjeFunkcija(*this);
}

// --------------------------------------------

OduzimanjeFunkcija::OduzimanjeFunkcija(Funkcija *leva, Funkcija *desna)
    : BinarnaFunkcija(leva, desna) {}

double OduzimanjeFunkcija::izracunaj(double vrednost) const {
    return m_leva->izracunaj(vrednost) - m_desna->izracunaj(vrednost);
}

void OduzimanjeFunkcija::ispisi(std::ostream &os) const {
    os << "(" << *m_leva << ") - (" << *m_desna << ")";
}

Funkcija *OduzimanjeFunkcija::izvod() const {
    return new OduzimanjeFunkcija(
        m_leva->izvod(),
        m_desna->izvod()
    );
}

Funkcija *OduzimanjeFunkcija::komponuj(Funkcija *funkcija) const {
    return new OduzimanjeFunkcija(
        m_leva->komponuj(funkcija),
        m_desna->komponuj(funkcija)
    );
}

Funkcija *OduzimanjeFunkcija::kloniraj() const {
    return new OduzimanjeFunkcija(*this);
}

// --------------------------------------------

MnozenjeFunkcija::MnozenjeFunkcija(Funkcija *leva, Funkcija *desna)
    : BinarnaFunkcija(leva, desna) {}

double MnozenjeFunkcija::izracunaj(double vrednost) const {
    return m_leva->izracunaj(vrednost) * m_desna->izracunaj(vrednost);
}

void MnozenjeFunkcija::ispisi(std::ostream &os) const {
    os << "(" << *m_leva << ") * (" << *m_desna << ")";
}

Funkcija *MnozenjeFunkcija::izvod() const {
    return new SabiranjeFunkcija(
        new MnozenjeFunkcija(
            m_leva->izvod(),
            m_desna->kloniraj()
        ),
        new MnozenjeFunkcija(
            m_leva->kloniraj(),
            m_desna->izvod()
        )
    );
}

Funkcija *MnozenjeFunkcija::komponuj(Funkcija *funkcija) const {
    return new MnozenjeFunkcija(
        m_leva->komponuj(funkcija),
        m_desna->komponuj(funkcija)
    );
}

Funkcija *MnozenjeFunkcija::kloniraj() const {
    return new MnozenjeFunkcija(*this);
}

// --------------------------------------------

DeljenjeFunkcija::DeljenjeFunkcija(Funkcija *leva, Funkcija *desna)
    : BinarnaFunkcija(leva, desna) {}

double DeljenjeFunkcija::izracunaj(double vrednost) const {
    return m_leva->izracunaj(vrednost) / m_desna->izracunaj(vrednost);
}

void DeljenjeFunkcija::ispisi(std::ostream &os) const {
    os << "(" << *m_leva << ") / (" << *m_desna << ")";
}

Funkcija *DeljenjeFunkcija::izvod() const {
    return new DeljenjeFunkcija(
        new OduzimanjeFunkcija(
            new MnozenjeFunkcija(
                m_leva->izvod(),
                m_desna->kloniraj()
            ),
            new MnozenjeFunkcija(
                m_leva->kloniraj(),
                m_desna->izvod()
            )
        ),
        new MnozenjeFunkcija(
            m_desna->kloniraj(),
            m_desna->kloniraj()
        )
    );
}

Funkcija *DeljenjeFunkcija::komponuj(Funkcija *funkcija) const {
    return new DeljenjeFunkcija(
        m_leva->komponuj(funkcija),
        m_desna->komponuj(funkcija)
    );
}

Funkcija *DeljenjeFunkcija::kloniraj() const {
    return new DeljenjeFunkcija(*this);
}

// --------------------------------------------
