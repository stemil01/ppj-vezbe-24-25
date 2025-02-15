#ifndef FUNKCIJA_HPP
#define FUNKCIJA_HPP

#include <iostream>

// --------------------------------------------

class Funkcija {
public:
    virtual ~Funkcija();
    virtual double izracunaj(double vrednost) const = 0;
    virtual void ispisi(std::ostream &os) const = 0;
    virtual Funkcija *izvod() const = 0;
    virtual Funkcija *komponuj(Funkcija *funkcija) const = 0;
    virtual Funkcija *kloniraj() const = 0;
};

std::ostream &operator<<(std::ostream &os, const Funkcija &funkcija);

// --------------------------------------------

class KonstantnaFunkcija : public Funkcija {
public:
    KonstantnaFunkcija(double vrednost);

    // metode iz natklase
    double izracunaj(double vrednost) const override;
    void ispisi(std::ostream &os) const override;
    Funkcija *izvod() const override;
    Funkcija *komponuj(Funkcija *funkcija) const override;
    Funkcija *kloniraj() const override;

private:
    double m_vrednost;
};

// --------------------------------------------

class IdentitetFunkcija : public Funkcija {
public:
    // metode iz natklase
    double izracunaj(double vrednost) const override;
    void ispisi(std::ostream &os) const override;
    Funkcija *izvod() const override;
    Funkcija *komponuj(Funkcija *funkcija) const override;
    Funkcija *kloniraj() const override;
};

// --------------------------------------------

class UnarnaFunkcija : public Funkcija {
public:
    UnarnaFunkcija(Funkcija *funkcija);
    UnarnaFunkcija(const UnarnaFunkcija &druga);
    ~UnarnaFunkcija();

    // metode iz natklase
    virtual double izracunaj(double vrednost) const = 0;
    virtual void ispisi(std::ostream &os) const = 0;
    virtual Funkcija *izvod() const = 0;
    virtual Funkcija *komponuj(Funkcija *funkcija) const = 0;
    virtual Funkcija *kloniraj() const = 0;

protected:
    Funkcija *m_funkcija;
};

// --------------------------------------------

class BinarnaFunkcija : public Funkcija {
public:
    BinarnaFunkcija(Funkcija *leva, Funkcija *desna);
    BinarnaFunkcija(const BinarnaFunkcija &druga);
    ~BinarnaFunkcija();

    // metode iz natklase
    virtual double izracunaj(double vrednost) const = 0;
    virtual void ispisi(std::ostream &os) const = 0;
    virtual Funkcija *izvod() const = 0;
    virtual Funkcija *komponuj(Funkcija *funkcija) const = 0;
    virtual Funkcija *kloniraj() const = 0;

protected:
    Funkcija *m_leva, *m_desna;
};

// --------------------------------------------

class NegacijaFunkcija : public UnarnaFunkcija {
public:
    NegacijaFunkcija(Funkcija *funkcija);

    // metode iz natklase
    double izracunaj(double vrednost) const override;
    void ispisi(std::ostream &os) const override;
    Funkcija *izvod() const override;
    Funkcija *komponuj(Funkcija *funkcija) const override;
    Funkcija *kloniraj() const override;
};

// --------------------------------------------

class SinFunkcija : public UnarnaFunkcija {
public:
    SinFunkcija(Funkcija *funkcija);

    // metode iz natklase
    double izracunaj(double vrednost) const override;
    void ispisi(std::ostream &os) const override;
    Funkcija *izvod() const override;
    Funkcija *komponuj(Funkcija *funkcija) const override;
    Funkcija *kloniraj() const override;
};

// --------------------------------------------

class CosFunkcija : public UnarnaFunkcija {
public:
    CosFunkcija(Funkcija *funkcija);

    // metode iz natklase
    double izracunaj(double vrednost) const override;
    void ispisi(std::ostream &os) const override;
    Funkcija *izvod() const override;
    Funkcija *komponuj(Funkcija *funkcija) const override;
    Funkcija *kloniraj() const override;
};

// --------------------------------------------

class SabiranjeFunkcija : public BinarnaFunkcija {
public:
    SabiranjeFunkcija(Funkcija *leva, Funkcija *desna);

    // metode iz natklase
    double izracunaj(double vrednost) const override;
    void ispisi(std::ostream &os) const override;
    Funkcija *izvod() const override;
    Funkcija *komponuj(Funkcija *funkcija) const override;
    Funkcija *kloniraj() const override;
};

// --------------------------------------------

class OduzimanjeFunkcija : public BinarnaFunkcija {
public:
    OduzimanjeFunkcija(Funkcija *leva, Funkcija *desna);

    // metode iz natklase
    double izracunaj(double vrednost) const override;
    void ispisi(std::ostream &os) const override;
    Funkcija *izvod() const override;
    Funkcija *komponuj(Funkcija *funkcija) const override;
    Funkcija *kloniraj() const override;
};

// --------------------------------------------

class MnozenjeFunkcija : public BinarnaFunkcija {
public:
    MnozenjeFunkcija(Funkcija *leva, Funkcija *desna);

    // metode iz natklase
    double izracunaj(double vrednost) const override;
    void ispisi(std::ostream &os) const override;
    Funkcija *izvod() const override;
    Funkcija *komponuj(Funkcija *funkcija) const override;
    Funkcija *kloniraj() const override;
};

// --------------------------------------------

class DeljenjeFunkcija : public BinarnaFunkcija {
public:
    DeljenjeFunkcija(Funkcija *leva, Funkcija *desna);

    // metode iz natklase
    double izracunaj(double vrednost) const override;
    void ispisi(std::ostream &os) const override;
    Funkcija *izvod() const override;
    Funkcija *komponuj(Funkcija *funkcija) const override;
    Funkcija *kloniraj() const override;
};

// --------------------------------------------

#endif
