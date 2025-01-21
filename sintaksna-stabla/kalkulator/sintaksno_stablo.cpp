#include "sintaksno_stablo.hpp"

int indeks_slobodnog_registra = 1;
int indeks_slobodne_labele = 0;

// --------------------------------------------

ASTCvor::~ASTCvor() {}

std::ostream &operator<<(std::ostream &os, const ASTCvor &ast_cvor) {
    ast_cvor.ispisi(os);
    return os;
}

// --------------------------------------------

NizNaredbi::NizNaredbi() {}

NizNaredbi::NizNaredbi(const NizNaredbi &drugi) {
    m_naredbe.resize(drugi.m_naredbe.size());
    for (size_t i = 0; i < drugi.m_naredbe.size(); i++) {
        m_naredbe[i] = drugi.m_naredbe[i]->kloniraj();
    }
}

NizNaredbi::~NizNaredbi() {
    for (ASTCvor *cvor : m_naredbe) {
        delete cvor;
    }
}

void NizNaredbi::dodaj_cvor(ASTCvor *cvor) {
    m_naredbe.push_back(cvor);
}

void NizNaredbi::ispisi(std::ostream& os) const {
    for (ASTCvor *cvor : m_naredbe) {
        cvor->ispisi(os);
        os << "\n";
    }
}

double NizNaredbi::interpretiraj(TabelaSimbola &tabela_simbola) const {
    for (ASTCvor *cvor : m_naredbe) {
        cvor->interpretiraj(tabela_simbola);
    }

    // vracamo neku vrednost samo da bismo
    // se uskladili sa definicijom metoda
    return 0;
}

int NizNaredbi::prevedi(std::ofstream &fajl) const {
    for (ASTCvor *cvor : m_naredbe) {
        cvor->prevedi(fajl);
        fajl << "\n";
    }

    // vracamo neku vrednost samo da bismo
    // se uskladili sa definicijom metoda
    return 0;
}

ASTCvor *NizNaredbi::kloniraj() const {
    return new NizNaredbi(*this);
}

// --------------------------------------------

Definicija::Definicija(const std::string &id, ASTCvor *izraz)
    : m_id(id), m_izraz(izraz) {}

Definicija::Definicija(const Definicija &drugi) {
    m_id = drugi.m_id;
    m_izraz = drugi.m_izraz->kloniraj();
}

Definicija::~Definicija() {
    delete m_izraz;
}

void Definicija::ispisi(std::ostream& os) const {
    os << "def " << m_id << " = ";
    m_izraz->ispisi(os);
    os << ";";
}

double Definicija::interpretiraj(TabelaSimbola &tabela_simbola) const {
    double vrednost = m_izraz->interpretiraj(tabela_simbola);
    tabela_simbola.definisi_promenljivu(m_id, vrednost);

    // vracamo neku vrednost samo da bismo
    // se uskladili sa definicijom metoda
    return vrednost;
}

int Definicija::prevedi(std::ofstream &fajl) const {
    int izraz_registar = m_izraz->prevedi(fajl);
    fajl << "store r" << izraz_registar << ", [" << m_id << "]\n";

    // vracamo neku vrednost samo da bismo
    // se uskladili sa definicijom metoda
    return 0;
}

ASTCvor *Definicija::kloniraj() const {
    return new Definicija(*this);
}

// --------------------------------------------

Dodela::Dodela(const std::string &id, ASTCvor *izraz)
    : m_id(id), m_izraz(izraz) {}

Dodela::Dodela(const Dodela &drugi) {
    m_id = drugi.m_id;
    m_izraz = drugi.m_izraz->kloniraj();
}

Dodela::~Dodela() {
    delete m_izraz;
}

void Dodela::ispisi(std::ostream& os) const {
    os << m_id << " = ";
    m_izraz->ispisi(os);
    os << ";";
}

double Dodela::interpretiraj(TabelaSimbola &tabela_simbola) const {
    double vrednost = m_izraz->interpretiraj(tabela_simbola);
    tabela_simbola.dodeli_vrednost(m_id, vrednost);

    // vracamo neku vrednost samo da bismo
    // se uskladili sa definicijom metoda
    return vrednost;
}

int Dodela::prevedi(std::ofstream &fajl) const {
    int izraz_registar = m_izraz->prevedi(fajl);
    fajl << "store r" << izraz_registar << ", [" << m_id << "]\n";

    // vracamo neku vrednost samo da bismo
    // se uskladili sa definicijom metoda
    return 0;
}

ASTCvor *Dodela::kloniraj() const {
    return new Dodela(*this);
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

Ispis::Ispis(ASTCvor *cvor) : UnarniCvor(cvor) {}

void Ispis::ispisi(std::ostream& os) const {
    os << "print(";
    m_cvor->ispisi(os);
    os << ");";
}

double Ispis::interpretiraj(TabelaSimbola &tabela_simbola) const {
    double vrednost = m_cvor->interpretiraj(tabela_simbola);
    std::cout << vrednost << std::endl;
    return vrednost;
}

int Ispis::prevedi(std::ofstream &fajl) const {
    int izraz_registar = m_cvor->prevedi(fajl);
    fajl << "mov r0, r" << izraz_registar << "\n";
    fajl << "call print\n";

    // vracamo neku vrednost samo da bismo
    // se uskladili sa definicijom metoda
    return 0;
}

ASTCvor *Ispis::kloniraj() const {
    return new Ispis(*this);
}

// --------------------------------------------

Sabiranje::Sabiranje(ASTCvor *levi, ASTCvor *desni)
    : BinarniCvor(levi, desni) {}

void Sabiranje::ispisi(std::ostream& os) const {
    os << "(";
    m_levi->ispisi(os);
    os << ") + (";
    m_desni->ispisi(os);
    os << ")";
}

double Sabiranje::interpretiraj(TabelaSimbola &tabela_simbola) const {
    return m_levi->interpretiraj(tabela_simbola) + m_desni->interpretiraj(tabela_simbola);
}

int Sabiranje::prevedi(std::ofstream &fajl) const {
    int levi_registar = m_levi->prevedi(fajl);
    int desni_registar = m_desni->prevedi(fajl);
    fajl << "add r" << levi_registar << ", r" << desni_registar << "\n";
    return levi_registar;
}

ASTCvor *Sabiranje::kloniraj() const {
    return new Sabiranje(*this);
}

// --------------------------------------------

Mnozenje::Mnozenje(ASTCvor *levi, ASTCvor *desni)
    : BinarniCvor(levi, desni) {}

void Mnozenje::ispisi(std::ostream& os) const {
    os << "(";
    m_levi->ispisi(os);
    os << ") * (";
    m_desni->ispisi(os);
    os << ")";
}

double Mnozenje::interpretiraj(TabelaSimbola &tabela_simbola) const {
    return m_levi->interpretiraj(tabela_simbola) * m_desni->interpretiraj(tabela_simbola);
}

int Mnozenje::prevedi(std::ofstream &fajl) const {
    int levi_registar = m_levi->prevedi(fajl);
    int desni_registar = m_desni->prevedi(fajl);
    fajl << "mul r" << levi_registar << ", r" << desni_registar << "\n";
    return levi_registar;
}

ASTCvor *Mnozenje::kloniraj() const {
    return new Mnozenje(*this);
}

// --------------------------------------------

Negacija::Negacija(ASTCvor *cvor) : UnarniCvor(cvor) {}

void Negacija::ispisi(std::ostream& os) const {
    os << "- (";
    m_cvor->ispisi(os);
    os << ")";
}

double Negacija::interpretiraj(TabelaSimbola &tabela_simbola) const {
    return - m_cvor->interpretiraj(tabela_simbola);
}

int Negacija::prevedi(std::ofstream &fajl) const {
    int izraz_registar = m_cvor->prevedi(fajl);
    fajl << "neg r" << izraz_registar << "\n";
    return izraz_registar;
}

ASTCvor *Negacija::kloniraj() const {
    return new Negacija(*this);
}

// --------------------------------------------

Konstanta::Konstanta(double vrednost) : m_vrednost(vrednost) {}

void Konstanta::ispisi(std::ostream& os) const {
    os << m_vrednost;
}

double Konstanta::interpretiraj(TabelaSimbola &tabela_simbola) const {
    return m_vrednost;
}

int Konstanta::prevedi(std::ofstream &fajl) const {
    int registar = indeks_slobodnog_registra;
    indeks_slobodnog_registra++;
    fajl << "mov r" << registar << ", " << m_vrednost << "\n";
    return registar;
}

ASTCvor *Konstanta::kloniraj() const {
    return new Konstanta(*this);
}

// --------------------------------------------

Promenljiva::Promenljiva(const std::string &id) : m_id(id) {}

void Promenljiva::ispisi(std::ostream& os) const {
    os << m_id;
}

double Promenljiva::interpretiraj(TabelaSimbola &tabela_simbola) const {
    return tabela_simbola.vrednost_promenljive(m_id);
}

int Promenljiva::prevedi(std::ofstream &fajl) const {
    int registar = indeks_slobodnog_registra;
    indeks_slobodnog_registra++;
    fajl << "load r" << registar << ", [" << m_id << "]\n";
    return registar;
}

ASTCvor *Promenljiva::kloniraj() const {
    return new Promenljiva(*this);
}

// --------------------------------------------

Poredjenje::Poredjenje(ASTCvor *levi, ASTCvor *desni)
    : BinarniCvor(levi, desni) {}

void Poredjenje::ispisi(std::ostream& os) const {
    os << "(";
    m_levi->ispisi(os);
    os << ") == (";
    m_desni->ispisi(os);
    os << ");";
}

double Poredjenje::interpretiraj(TabelaSimbola &tabela_simbola) const {
    bool uslov = (m_levi->interpretiraj(tabela_simbola) == m_desni->interpretiraj(tabela_simbola));
    std::cout << (uslov ? "True" : "False") << std::endl;
    return uslov;
}

int Poredjenje::prevedi(std::ofstream &fajl) const {
    int levi_registar = m_levi->prevedi(fajl);
    int desni_registar = m_desni->prevedi(fajl);

    fajl << "cmp r" << levi_registar << ", r" << desni_registar << "\n";

    int jednako_labela = indeks_slobodne_labele;
    indeks_slobodne_labele++;
    int kraj_labela = indeks_slobodne_labele;
    indeks_slobodne_labele++;

    fajl << "je label" << jednako_labela << "\n";
        fajl << "mov r0, 0\n";
        fajl << "jmp label" << kraj_labela << "\n";
    fajl << "label" << jednako_labela << ":\n";
        fajl << "mov r0, 1\n";
    fajl << "label" << kraj_labela << ":\n";
        fajl << "call print\n";

    // vracamo neku vrednost samo da bismo
    // se uskladili sa definicijom metoda
    return 0;
}

ASTCvor *Poredjenje::kloniraj() const {
    return new Poredjenje(*this);
}

// --------------------------------------------
