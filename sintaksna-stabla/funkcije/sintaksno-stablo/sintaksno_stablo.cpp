#include "sintaksno_stablo.hpp"
#include "funkcija.hpp"
#include <cstddef>

// --------------------------------------------

ASTCvor::~ASTCvor() {}

std::ostream &operator<<(std::ostream &os, const ASTCvor &ast_cvor) {
    ast_cvor.ispisi(os);
    return os;
}

// --------------------------------------------

NizNaredbiCvor::NizNaredbiCvor() {}

NizNaredbiCvor::NizNaredbiCvor(const NizNaredbiCvor &drugi) {
    m_naredbe.resize(drugi.m_naredbe.size());
    for (size_t i = 0; i < drugi.m_naredbe.size(); i++) {
        m_naredbe[i] = drugi.m_naredbe[i]->kloniraj();
    }
}

NizNaredbiCvor::~NizNaredbiCvor() {
    for (ASTCvor *cvor : m_naredbe) {
        delete cvor;
    }
}

void NizNaredbiCvor::dodaj_cvor(ASTCvor *cvor) {
    m_naredbe.push_back(cvor);
}

void NizNaredbiCvor::ispisi(std::ostream &os) const {
    for (ASTCvor *cvor : m_naredbe) {
        os << *cvor << "\n";
    }
}

Funkcija *NizNaredbiCvor::interpretiraj(TabelaSimbola &tabela_simbola) const {
    for (ASTCvor *cvor : m_naredbe) {
        cvor->interpretiraj(tabela_simbola);
    }

    // vracamo neku vrednost samo da bismo
    // se uskladili sa definicijom metoda
    return nullptr;
}

ASTCvor *NizNaredbiCvor::kloniraj() const {
    return new NizNaredbiCvor(*this);
}

// --------------------------------------------

void PrazanCvor::ispisi(std::ostream &os) const {}

Funkcija *PrazanCvor::interpretiraj(TabelaSimbola &tabela_simbola) const {
    // vracamo neku vrednost samo da bismo
    // se uskladili sa definicijom metoda
    return nullptr;
}

ASTCvor *PrazanCvor::kloniraj() const {
    return new PrazanCvor(*this);
}

// --------------------------------------------

PromenljivaCvor::PromenljivaCvor(const std::string &id)
    : m_id(id) {}

void PromenljivaCvor::ispisi(std::ostream &os) const {
    os << m_id;
}

Funkcija *PromenljivaCvor::interpretiraj(TabelaSimbola &tabela_simbola) const {
    return tabela_simbola.vrednost_promenljive(m_id)->kloniraj();
}

ASTCvor *PromenljivaCvor::kloniraj() const {
    return new PromenljivaCvor(*this);
}

// --------------------------------------------

VrednostCvor::VrednostCvor(ASTCvor *izraz, double vrednost)
    : m_izraz(izraz), m_vrednost(vrednost) {}

VrednostCvor::VrednostCvor(const VrednostCvor &drugi) {
    m_izraz = drugi.m_izraz->kloniraj();
    m_vrednost = drugi.m_vrednost;
}

VrednostCvor::~VrednostCvor() {
    delete m_izraz;
}

void VrednostCvor::ispisi(std::ostream &os) const {
    os << *m_izraz << "[" << m_vrednost << "]";
}

Funkcija *VrednostCvor::interpretiraj(TabelaSimbola &tabela_simbola) const {
    Funkcija *funkcija = m_izraz->interpretiraj(tabela_simbola);
    Funkcija *vrednost = new KonstantnaFunkcija(
        funkcija->izracunaj(m_vrednost)
    );

    delete funkcija;

    return vrednost;
}

ASTCvor *VrednostCvor::kloniraj() const {
    return new VrednostCvor(*this);
}

// --------------------------------------------

DodelaCvor::DodelaCvor(const std::string &id, ASTCvor *izraz)
    : m_id(id), m_izraz(izraz) {}

DodelaCvor::DodelaCvor(const DodelaCvor &drugi) {
    m_id = drugi.m_id;
    m_izraz = drugi.m_izraz->kloniraj();
}

DodelaCvor::~DodelaCvor() {
    delete m_izraz;
}

void DodelaCvor::ispisi(std::ostream &os) const {
    os << m_id << " = " << *m_izraz;
}

Funkcija *DodelaCvor::interpretiraj(TabelaSimbola &tabela_simbola) const {
    tabela_simbola.dodeli_vrednost(m_id, m_izraz->interpretiraj(tabela_simbola));

    // vracamo neku vrednost samo da bismo
    // se uskladili sa definicijom metoda
    return nullptr;
}

ASTCvor *DodelaCvor::kloniraj() const {
    return new DodelaCvor(*this);
}

// --------------------------------------------

KonstantaCvor::KonstantaCvor(double vrednost) : m_vrednost(vrednost) {}

void KonstantaCvor::ispisi(std::ostream &os) const {
    os << m_vrednost;
}

Funkcija *KonstantaCvor::interpretiraj(TabelaSimbola &tabela_simbola) const {
    return new KonstantnaFunkcija(m_vrednost);
}

ASTCvor *KonstantaCvor::kloniraj() const {
    return new KonstantaCvor(*this);
}

// --------------------------------------------

void IdentitetCvor::ispisi(std::ostream &os) const {
    os << "x";
}

Funkcija *IdentitetCvor::interpretiraj(TabelaSimbola &tabela_simbola) const {
    return new IdentitetFunkcija();
}

ASTCvor *IdentitetCvor::kloniraj() const {
    return new IdentitetCvor(*this);
}

// --------------------------------------------

UnarniCvor::UnarniCvor(ASTCvor *cvor) : m_cvor(cvor) {}

UnarniCvor::UnarniCvor(const UnarniCvor &drugi) {
    m_cvor = drugi.m_cvor->kloniraj();
}

UnarniCvor::~UnarniCvor() {
    delete m_cvor;
}

// --------------------------------------------

BinarniCvor::BinarniCvor(ASTCvor *levi, ASTCvor *desni)
    : m_levi(levi), m_desni(desni) {}

BinarniCvor::BinarniCvor(const BinarniCvor &drugi) {
    m_levi = drugi.m_levi->kloniraj();
    m_desni = drugi.m_desni->kloniraj();
}

BinarniCvor::~BinarniCvor() {
    delete m_levi;
    delete m_desni;
}

// --------------------------------------------

NegacijaCvor::NegacijaCvor(ASTCvor *cvor) : UnarniCvor(cvor) {}

void NegacijaCvor::ispisi(std::ostream &os) const {
    os << "- (" << *m_cvor << ")";
}

Funkcija *NegacijaCvor::interpretiraj(TabelaSimbola &tabela_simbola) const {
    return new Negacija(m_cvor->interpretiraj(tabela_simbola));
}

ASTCvor *NegacijaCvor::kloniraj() const {
    return new NegacijaCvor(*this);
}

// --------------------------------------------

SinCvor::SinCvor(ASTCvor *cvor) : UnarniCvor(cvor) {}

void SinCvor::ispisi(std::ostream &os) const {
    os << "sin(" << *m_cvor << ")";
}

Funkcija *SinCvor::interpretiraj(TabelaSimbola &tabela_simbola) const {
    return new Sin(m_cvor->interpretiraj(tabela_simbola));
}

ASTCvor *SinCvor::kloniraj() const {
    return new SinCvor(*this);
}

// --------------------------------------------

CosCvor::CosCvor(ASTCvor *cvor) : UnarniCvor(cvor) {}

void CosCvor::ispisi(std::ostream &os) const {
    os << "cos(" << *m_cvor << ")";
}

Funkcija *CosCvor::interpretiraj(TabelaSimbola &tabela_simbola) const {
    return new Cos(m_cvor->interpretiraj(tabela_simbola));
}

ASTCvor *CosCvor::kloniraj() const {
    return new CosCvor(*this);
}

// --------------------------------------------

IspisCvor::IspisCvor(ASTCvor *cvor) : UnarniCvor(cvor) {}

void IspisCvor::ispisi(std::ostream &os) const {
    os << *m_cvor;
}

Funkcija *IspisCvor::interpretiraj(TabelaSimbola &tabela_simbola) const {
    Funkcija *vrednost = m_cvor->interpretiraj(tabela_simbola);
    std::cout << *vrednost << std::endl;
    delete vrednost;

    // vracamo neku vrednost samo da bismo
    // se uskladili sa definicijom metoda
    return nullptr;
}

ASTCvor *IspisCvor::kloniraj() const {
    return new IspisCvor(*this);
}

// --------------------------------------------

IzvodCvor::IzvodCvor(ASTCvor *cvor) : UnarniCvor(cvor) {}

void IzvodCvor::ispisi(std::ostream &os) const {
    os << "(" << *m_cvor << ")'";
}

Funkcija *IzvodCvor::interpretiraj(TabelaSimbola &tabela_simbola) const {
    Funkcija *vrednost = m_cvor->interpretiraj(tabela_simbola);
    Funkcija *izvod = vrednost->izvod();
    delete vrednost;

    return izvod;
}

ASTCvor *IzvodCvor::kloniraj() const {
    return new IzvodCvor(*this);
}

// --------------------------------------------

SabiranjeCvor::SabiranjeCvor(ASTCvor *levi, ASTCvor *desni)
    : BinarniCvor(levi, desni) {}

void SabiranjeCvor::ispisi(std::ostream &os) const {
    os << "(" << *m_levi << ") + (" << *m_desni << ")";
}

Funkcija *SabiranjeCvor::interpretiraj(TabelaSimbola &tabela_simbola) const {
    return new Sabiranje(
        m_levi->interpretiraj(tabela_simbola),
        m_desni->interpretiraj(tabela_simbola)
    );
}

ASTCvor *SabiranjeCvor::kloniraj() const {
    return new SabiranjeCvor(*this);
}

// --------------------------------------------

OduzimanjeCvor::OduzimanjeCvor(ASTCvor *levi, ASTCvor *desni)
    : BinarniCvor(levi, desni) {}

void OduzimanjeCvor::ispisi(std::ostream &os) const {
    os << "(" << *m_levi << ") - (" << *m_desni << ")";
}

Funkcija *OduzimanjeCvor::interpretiraj(TabelaSimbola &tabela_simbola) const {
    return new Oduzimanje(
        m_levi->interpretiraj(tabela_simbola),
        m_desni->interpretiraj(tabela_simbola)
    );
}

ASTCvor *OduzimanjeCvor::kloniraj() const {
    return new OduzimanjeCvor(*this);
}

// --------------------------------------------

MnozenjeCvor::MnozenjeCvor(ASTCvor *levi, ASTCvor *desni)
    : BinarniCvor(levi, desni) {}

void MnozenjeCvor::ispisi(std::ostream &os) const {
    os << "(" << *m_levi << ") * (" << *m_desni << ")";
}

Funkcija *MnozenjeCvor::interpretiraj(TabelaSimbola &tabela_simbola) const {
    return new Mnozenje(
        m_levi->interpretiraj(tabela_simbola),
        m_desni->interpretiraj(tabela_simbola)
    );
}

ASTCvor *MnozenjeCvor::kloniraj() const {
    return new MnozenjeCvor(*this);
}

// --------------------------------------------

DeljenjeCvor::DeljenjeCvor(ASTCvor *levi, ASTCvor *desni)
    : BinarniCvor(levi, desni) {}

void DeljenjeCvor::ispisi(std::ostream &os) const {
    os << "(" << *m_levi << ") / (" << *m_desni << ")";
}

Funkcija *DeljenjeCvor::interpretiraj(TabelaSimbola &tabela_simbola) const {
    return new Deljenje(
        m_levi->interpretiraj(tabela_simbola),
        m_desni->interpretiraj(tabela_simbola)
    );
}

ASTCvor *DeljenjeCvor::kloniraj() const {
    return new DeljenjeCvor(*this);
}

// --------------------------------------------

KompozicijaCvor::KompozicijaCvor(ASTCvor *levi, ASTCvor *desni)
    : BinarniCvor(levi, desni) {}

void KompozicijaCvor::ispisi(std::ostream &os) const {
    os << *m_levi << "(" << *m_desni << ")";
}

Funkcija *KompozicijaCvor::interpretiraj(TabelaSimbola &tabela_simbola) const {
    Funkcija *leva = m_levi->interpretiraj(tabela_simbola);
    Funkcija *desna = m_desni->interpretiraj(tabela_simbola);

    Funkcija *kompozicija = leva->komponuj(desna);

    delete leva;
    delete desna;

    return kompozicija;
}

ASTCvor *KompozicijaCvor::kloniraj() const {
    return new KompozicijaCvor(*this);
}

// --------------------------------------------
