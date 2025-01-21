#include <cmath>
#include <iostream>
#include <map>
#include <stdexcept>

class Okruzenje {
public:
    void postavi_promenljivu(const std::string &promenljiva, double vrednost) {
        m_promenljive[promenljiva] = vrednost;
    }

    double vrednost_promenljive(const std::string &promenljiva) const {
        auto it = m_promenljive.find(promenljiva);
        if (it == m_promenljive.end()) {
            throw std::runtime_error("promenljiva " + promenljiva + " nije definisana");
        }
        return it->second;
    }

    bool je_definisana(const std::string &promenljiva) const {
        return m_promenljive.find(promenljiva) != m_promenljive.end();
    }

private:
    std::map<std::string, double> m_promenljive;
};

// ---------------------------------

class Izraz {
public:
    virtual ~Izraz() {}
    virtual double izracunaj(const Okruzenje &okruzenje) const = 0;
    virtual void ispisi(std::ostream &os) const = 0;
    virtual Izraz *uprosti(const Okruzenje &okruzenje) const = 0;
    virtual Izraz *izvod(const std::string &promenljiva) const = 0;
    virtual Izraz *kloniraj() const = 0;
};

std::ostream &operator<<(std::ostream &os, const Izraz &izraz) {
    izraz.ispisi(os);
    return os;
}

// ---------------------------------

class Konstanta : public Izraz {
public:
    Konstanta(double vrednost)
        : m_vrednost(vrednost) {}

    double izracunaj(const Okruzenje &okruzenje) const override {
        return m_vrednost;
    }

    void ispisi(std::ostream &os) const override {
        os << m_vrednost;
    }
    Izraz *uprosti(const Okruzenje &okruzenje) const override {
        return new Konstanta(*this);
    }

    Izraz *izvod(const std::string &promenljiva) const override {
        return new Konstanta(0);
    }

    Izraz *kloniraj() const override {
        return new Konstanta(*this);
    }
    
private:
    double m_vrednost;
};

// ---------------------------------

class Promenljiva : public Izraz {
public:
    Promenljiva(const std::string &ime)
        : m_ime(ime) {}
    
    double izracunaj(const Okruzenje &okruzenje) const override {
        return okruzenje.vrednost_promenljive(m_ime);
    }

    void ispisi(std::ostream &os) const override {
        os << m_ime;
    }

    Izraz *uprosti(const Okruzenje &okruzenje) const override {
        if (okruzenje.je_definisana(m_ime)) {
            return new Konstanta(okruzenje.vrednost_promenljive(m_ime));
        }
        else {
            return new Promenljiva(*this);
        }
    }
    Izraz *izvod(const std::string &promenljiva) const override {
        if (promenljiva == m_ime) {
            return new Konstanta(1);
        }
        else {
            return new Konstanta(0);
        }
    }

    Izraz *kloniraj() const override {
        return new Promenljiva(*this);
    }

private:
    std::string m_ime;
};

// ---------------------------------

class BinarniOperator : public Izraz {
public:
    BinarniOperator(Izraz *levi, Izraz *desni)
        : m_levi(levi), m_desni(desni) {}

    BinarniOperator(const BinarniOperator &drugi) {
        m_levi = drugi.m_levi->kloniraj();
        m_desni = drugi.m_desni->kloniraj();
    }

    ~BinarniOperator() {
        delete m_levi;
        delete m_desni;
    }

    BinarniOperator &operator=(const BinarniOperator &drugi) {
        if (&drugi != this) {
            delete m_levi;
            delete m_desni;

            m_levi = drugi.m_levi->kloniraj();
            m_desni = drugi.m_desni->kloniraj();
        }
        return *this;
    }

    virtual double izracunaj(const Okruzenje &okruzenje) const = 0;
    virtual void ispisi(std::ostream &os) const = 0;
    virtual Izraz *uprosti(const Okruzenje &okruzenje) const = 0;
    virtual Izraz *izvod(const std::string &promenljiva) const = 0;
    virtual Izraz *kloniraj() const = 0;

protected:
    Izraz *m_levi, *m_desni;
};

// ---------------------------------

class Sabiranje : public BinarniOperator {
public:
    Sabiranje(Izraz *levi, Izraz *desni)
        : BinarniOperator(levi, desni) {}
    
    double izracunaj(const Okruzenje &okruzenje) const override {
        return m_levi->izracunaj(okruzenje) + m_desni->izracunaj(okruzenje);
    }

    void ispisi(std::ostream &os) const override {
        os << "(";
        m_levi->ispisi(os);
        os << ") + (";
        m_desni->ispisi(os);
        os << ")";
    }

    Izraz *uprosti(const Okruzenje &okruzenje) const override {
        Izraz *levi_uproscen = m_levi->uprosti(okruzenje);
        Izraz *desni_uproscen = m_desni->uprosti(okruzenje);

        if (dynamic_cast<Konstanta *>(levi_uproscen) != nullptr
            && dynamic_cast<Konstanta *>(desni_uproscen) != nullptr) {
            Izraz *rezultat = new Konstanta(
                levi_uproscen->izracunaj(okruzenje)
                + desni_uproscen->izracunaj(okruzenje));
            delete levi_uproscen;
            delete desni_uproscen;
            return rezultat;
        }
        else {
            return new Sabiranje(levi_uproscen, desni_uproscen);
        }
    }

    Izraz *izvod(const std::string &promenljiva) const override {
        return new Sabiranje(m_levi->izvod(promenljiva), m_desni->izvod(promenljiva));
    }

    Izraz *kloniraj() const override {
        return new Sabiranje(*this);
    }
};

// ---------------------------------

class Mnozenje : public BinarniOperator {
public:
    Mnozenje(Izraz *levi, Izraz *desni)
        : BinarniOperator(levi, desni) {}
    
    double izracunaj(const Okruzenje &okruzenje) const override {
        return m_levi->izracunaj(okruzenje) * m_desni->izracunaj(okruzenje);
    }

    void ispisi(std::ostream &os) const override {
        os << "(";
        m_levi->ispisi(os);
        os << ") * (";
        m_desni->ispisi(os);
        os << ")";
    }

    Izraz *uprosti(const Okruzenje &okruzenje) const override {
        Izraz *levi_uproscen = m_levi->uprosti(okruzenje);
        Izraz *desni_uproscen = m_desni->uprosti(okruzenje);

        if (dynamic_cast<Konstanta *>(levi_uproscen) != nullptr
            && dynamic_cast<Konstanta *>(desni_uproscen) != nullptr) {
            Izraz *rezultat = new Konstanta(
                levi_uproscen->izracunaj(okruzenje)
                * desni_uproscen->izracunaj(okruzenje));
            delete levi_uproscen;
            delete desni_uproscen;
            return rezultat;
        }
        else {
            return new Mnozenje(levi_uproscen, desni_uproscen);
        }
    }

    Izraz *izvod(const std::string &promenljiva) const override {
        return new Sabiranje(
            new Mnozenje(
                m_levi->izvod(promenljiva),
                m_desni->kloniraj()
            ),
            new Mnozenje(
                m_levi->kloniraj(),
                m_desni->izvod(promenljiva)
            )
        );
    }

    Izraz *kloniraj() const override {
        return new Mnozenje(*this);
    }
};

// ---------------------------------

class UnarniOperator : public Izraz {
public:
    UnarniOperator(Izraz *izraz)
        : m_izraz(izraz) {}

    UnarniOperator(const UnarniOperator &drugi) {
        m_izraz = drugi.m_izraz->kloniraj();
    }

    ~UnarniOperator() {
        delete m_izraz;
    }

    virtual double izracunaj(const Okruzenje &okruzenje) const = 0;
    virtual void ispisi(std::ostream &os) const = 0;
    virtual Izraz *uprosti(const Okruzenje &okruzenje) const = 0;
    virtual Izraz *izvod(const std::string &promenljiva) const = 0;
    virtual Izraz *kloniraj() const = 0;
    
protected:
    Izraz *m_izraz;
};

// ---------------------------------

class Negacija : public UnarniOperator {
public:
    Negacija(Izraz *izraz)
        : UnarniOperator(izraz) {}

    double izracunaj(const Okruzenje &okruzenje) const override {
        return - m_izraz->izracunaj(okruzenje);
    }

    void ispisi(std::ostream &os) const override {
        os << "- (";
        m_izraz->ispisi(os);
        os << ")";
    }

    Izraz *uprosti(const Okruzenje &okruzenje) const override {
        Izraz *uproscen = m_izraz->uprosti(okruzenje);

        if (dynamic_cast<Konstanta *>(uproscen) != nullptr) {
            Izraz *rezultat = new Konstanta(- uproscen->izracunaj(okruzenje));
            delete uproscen;
            return rezultat;
        }
        else {
            return new Negacija(uproscen);
        }
    }

    Izraz *izvod(const std::string &promenljiva) const override {
        return new Negacija(m_izraz->izvod(promenljiva));
    }

    Izraz *kloniraj() const override {
        return new Negacija(*this);
    }
};

// ---------------------------------

class Sin : public UnarniOperator {
public:
    Sin(Izraz *izraz)
        : UnarniOperator(izraz) {}

    double izracunaj(const Okruzenje &okruzenje) const override {
        return sin(m_izraz->izracunaj(okruzenje));
    }

    void ispisi(std::ostream &os) const override {
        os << "sin(";
        m_izraz->ispisi(os);
        os << ")";
    }

    Izraz *uprosti(const Okruzenje &okruzenje) const override {
        Izraz *uproscen = m_izraz->uprosti(okruzenje);

        if (dynamic_cast<Konstanta *>(uproscen) != nullptr) {
            Izraz *rezultat = new Konstanta(sin(uproscen->izracunaj(okruzenje)));
            delete uproscen;
            return rezultat;
        }
        else {
            return new Sin(uproscen);
        }
    }

    Izraz *izvod(const std::string &promenljiva) const override;

    Izraz *kloniraj() const override {
        return new Sin(*this);
    }
};

// ---------------------------------

class Cos : public UnarniOperator {
public:
    Cos(Izraz *izraz)
        : UnarniOperator(izraz) {}

    double izracunaj(const Okruzenje &okruzenje) const override {
        return cos(m_izraz->izracunaj(okruzenje));
    }

    void ispisi(std::ostream &os) const override {
        os << "cos(";
        m_izraz->ispisi(os);
        os << ")";
    }

    Izraz *uprosti(const Okruzenje &okruzenje) const override {
        Izraz *uproscen = m_izraz->uprosti(okruzenje);

        if (dynamic_cast<Konstanta *>(uproscen) != nullptr) {
            Izraz *rezultat = new Konstanta(cos(uproscen->izracunaj(okruzenje)));
            delete uproscen;
            return rezultat;
        }
        else {
            return new Cos(uproscen);
        }
    }

    Izraz *izvod(const std::string &promenljiva) const override {
        return new Negacija(
            new Mnozenje(
                new Sin(
                    m_izraz->kloniraj()
                ),
                m_izraz->izvod(promenljiva)
            )
        );
    }

    Izraz *kloniraj() const override {
        return new Cos(*this);
    }
};

Izraz *Sin::izvod(const std::string &promenljiva) const {
    return new Mnozenje(
        new Cos(
            m_izraz->kloniraj()
        ),
        m_izraz->izvod(promenljiva)
    );
}

// ---------------------------------

class IzrazOmotac {
public:
    IzrazOmotac(Izraz *izraz)
        : m_izraz(izraz) {}

    ~IzrazOmotac() {
        delete m_izraz;
    }

    double izracunaj(const Okruzenje &okruzenje) const {
        return m_izraz->izracunaj(okruzenje);
    }

    void ispisi(std::ostream &os) const {
        m_izraz->ispisi(os);
    }

    IzrazOmotac uprosti(const Okruzenje &okruzenje) const {
        return IzrazOmotac(m_izraz->uprosti(okruzenje));
    }

    IzrazOmotac izvod(const std::string &promenljiva) const {
        return IzrazOmotac(m_izraz->izvod(promenljiva));
    }

private:
    Izraz *m_izraz;
};

std::ostream &operator<<(std::ostream &os, const IzrazOmotac &izraz_omotac) {
    izraz_omotac.ispisi(os);
    return os;
}

// ---------------------------------

int main() {
    Okruzenje okruzenje;

    IzrazOmotac izraz(new Mnozenje(
        new Sabiranje(
            new Konstanta(1),
            new Konstanta(3)
        ),
        new Mnozenje(
            new Promenljiva("x"),
            new Cos(
                new Promenljiva("y")
            )
        )
    ));

    std::cout << izraz << std::endl;
    std::cout << izraz.uprosti(okruzenje) << std::endl;
    std::cout << izraz.izvod("x").uprosti(okruzenje) << std::endl;

    return 0;
}