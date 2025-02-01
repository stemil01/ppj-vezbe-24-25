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

class Negacija : public UnarnaFunkcija {
public:
    Negacija(Funkcija *funkcija);

    // metode iz natklase
    double izracunaj(double vrednost) const override;
    void ispisi(std::ostream &os) const override;
    Funkcija *izvod() const override;
    Funkcija *komponuj(Funkcija *funkcija) const override;
    Funkcija *kloniraj() const override;
};

// --------------------------------------------

class Sin : public UnarnaFunkcija {
public:
    Sin(Funkcija *funkcija);

    // metode iz natklase
    double izracunaj(double vrednost) const override;
    void ispisi(std::ostream &os) const override;
    Funkcija *izvod() const override;
    Funkcija *komponuj(Funkcija *funkcija) const override;
    Funkcija *kloniraj() const override;
};

// --------------------------------------------

class Cos : public UnarnaFunkcija {
public:
    Cos(Funkcija *funkcija);

    // metode iz natklase
    double izracunaj(double vrednost) const override;
    void ispisi(std::ostream &os) const override;
    Funkcija *izvod() const override;
    Funkcija *komponuj(Funkcija *funkcija) const override;
    Funkcija *kloniraj() const override;
};

// --------------------------------------------

class Sabiranje : public BinarnaFunkcija {
public:
    Sabiranje(Funkcija *leva, Funkcija *desna);

    // metode iz natklase
    double izracunaj(double vrednost) const override;
    void ispisi(std::ostream &os) const override;
    Funkcija *izvod() const override;
    Funkcija *komponuj(Funkcija *funkcija) const override;
    Funkcija *kloniraj() const override;
};

// --------------------------------------------

class Oduzimanje : public BinarnaFunkcija {
public:
    Oduzimanje(Funkcija *leva, Funkcija *desna);

    // metode iz natklase
    double izracunaj(double vrednost) const override;
    void ispisi(std::ostream &os) const override;
    Funkcija *izvod() const override;
    Funkcija *komponuj(Funkcija *funkcija) const override;
    Funkcija *kloniraj() const override;
};

// --------------------------------------------

class Mnozenje : public BinarnaFunkcija {
public:
    Mnozenje(Funkcija *leva, Funkcija *desna);

    // metode iz natklase
    double izracunaj(double vrednost) const override;
    void ispisi(std::ostream &os) const override;
    Funkcija *izvod() const override;
    Funkcija *komponuj(Funkcija *funkcija) const override;
    Funkcija *kloniraj() const override;
};

// --------------------------------------------

class Deljenje : public BinarnaFunkcija {
public:
    Deljenje(Funkcija *leva, Funkcija *desna);

    // metode iz natklase
    double izracunaj(double vrednost) const override;
    void ispisi(std::ostream &os) const override;
    Funkcija *izvod() const override;
    Funkcija *komponuj(Funkcija *funkcija) const override;
    Funkcija *kloniraj() const override;
};

// --------------------------------------------

#endif
