#include "sintaksno_stablo.hpp"
#include "tabela_simbola.hpp"
#include <ostream>

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
        m_naredbe[i] = drugi.m_naredbe[i];
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

int NizNaredbiCvor::interpretiraj(TabelaSimbola &tabela_simbola) const {
    for (ASTCvor *cvor : m_naredbe) {
        cvor->interpretiraj(tabela_simbola);
    }

    // vracamo neku vrednost samo da bismo
    // se uskladili sa definicijom metoda
    return 0;
}

ASTCvor *NizNaredbiCvor::kloniraj() const {
    return new NizNaredbiCvor(*this);
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
    os << m_id << ":=" << *m_izraz << ";";
}

int DodelaCvor::interpretiraj(TabelaSimbola &tabela_simbola) const {
    tabela_simbola.dodeli_vrednost(m_id, m_izraz->interpretiraj(tabela_simbola));

    // vracamo neku vrednost samo da bismo
    // se uskladili sa definicijom metoda
    return 0;
}

ASTCvor *DodelaCvor::kloniraj() const {
    return new DodelaCvor(*this);
}

// --------------------------------------------

PromenljivaCvor::PromenljivaCvor(const std::string &id) : m_id(id) {}

void PromenljivaCvor::ispisi(std::ostream &os) const {
    os << m_id;
}

int PromenljivaCvor::interpretiraj(TabelaSimbola &tabela_simbola) const {
    return tabela_simbola.vrednost_promenljive(m_id);
}

ASTCvor *PromenljivaCvor::kloniraj() const {
    return new PromenljivaCvor(*this);
}

// --------------------------------------------

KonstantaCvor::KonstantaCvor(int vrednost) : m_vrednost(vrednost) {}

void KonstantaCvor::ispisi(std::ostream &os) const {
    os << m_vrednost;
}

int KonstantaCvor::interpretiraj(TabelaSimbola &tabela_simbola) const {
    return m_vrednost;
}

ASTCvor *KonstantaCvor::kloniraj() const {
    return new KonstantaCvor(*this);
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

TernarniCvor::TernarniCvor(ASTCvor *prvi, ASTCvor *drugi, ASTCvor *treci)
    : m_prvi(prvi), m_drugi(drugi), m_treci(treci) {}

TernarniCvor::TernarniCvor(const TernarniCvor &drugi) {
    m_prvi = drugi.m_prvi->kloniraj();
    m_drugi = drugi.m_drugi->kloniraj();
    m_treci = drugi.m_drugi->kloniraj();
}

TernarniCvor::~TernarniCvor() {
    delete m_prvi;
    delete m_drugi;
    delete m_treci;
}

// --------------------------------------------

PotprogramCvor::PotprogramCvor(ASTCvor *cvor) : UnarniCvor(cvor) {}

void PotprogramCvor::ispisi(std::ostream &os) const {
    os << "begin\n" << *m_cvor << "end";
}

int PotprogramCvor::interpretiraj(TabelaSimbola &tabela_simbola) const {
    return m_cvor->interpretiraj(tabela_simbola);
}

ASTCvor *PotprogramCvor::kloniraj() const {
    return new PotprogramCvor(*this);
}

// --------------------------------------------

IspisCvor::IspisCvor(ASTCvor *cvor) : UnarniCvor(cvor) {}

void IspisCvor::ispisi(std::ostream &os) const {
    os << "print(" << *m_cvor << ");";
}

int IspisCvor::interpretiraj(TabelaSimbola &tabela_simbola) const {
    std::cout << m_cvor->interpretiraj(tabela_simbola) << std::endl;

    // vracamo neku vrednost samo da bismo
    // se uskladili sa definicijom metoda
    return 0;
}

ASTCvor *IspisCvor::kloniraj() const {
    return new IspisCvor(*this);
}

// --------------------------------------------

IfCvor::IfCvor(ASTCvor *izraz, ASTCvor *telo)
    : BinarniCvor(izraz, telo) {}

void IfCvor::ispisi(std::ostream &os) const {
    os << "if " << *m_levi << " then\n" << *m_desni << "\n";
}

int IfCvor::interpretiraj(TabelaSimbola &tabela_simbola) const {
    if (m_levi->interpretiraj(tabela_simbola)) {
        m_desni->interpretiraj(tabela_simbola);
    }

    // vracamo neku vrednost samo da bismo
    // se uskladili sa definicijom metoda
    return 0;
}

ASTCvor *IfCvor::kloniraj() const {
    return new IfCvor(*this);
}

// --------------------------------------------

IfElseCvor::IfElseCvor(ASTCvor *izraz, ASTCvor *then_telo, ASTCvor *else_cvor)
    : TernarniCvor(izraz, then_telo, else_cvor) {}

void IfElseCvor::ispisi(std::ostream &os) const {
    os << "if " << *m_prvi << " then\n";
    os << *m_drugi << "\nelse\n" << *m_treci;
}

int IfElseCvor::interpretiraj(TabelaSimbola &tabela_simbola) const {
    if (m_prvi->interpretiraj(tabela_simbola)) {
        m_drugi->interpretiraj(tabela_simbola);
    }
    else {
        m_treci->interpretiraj(tabela_simbola);
    }

    // vracamo neku vrednost samo da bismo
    // se uskladili sa definicijom metoda
    return 0;
}

ASTCvor *IfElseCvor::kloniraj() const {
    return new IfElseCvor(*this);
}

// --------------------------------------------

WhileCvor::WhileCvor(ASTCvor *izraz, ASTCvor *telo)
    : BinarniCvor(izraz, telo) {}

void WhileCvor::ispisi(std::ostream &os) const {
    os << "while " << *m_levi << " do\n" << *m_desni;
}

int WhileCvor::interpretiraj(TabelaSimbola &tabela_simbola) const {
    while (m_levi->interpretiraj(tabela_simbola)) {
        m_desni->interpretiraj(tabela_simbola);
    }

    // vracamo neku vrednost samo da bismo
    // se uskladili sa definicijom metoda
    return 0;
}

ASTCvor *WhileCvor::kloniraj() const {
    return new WhileCvor(*this);
}

// --------------------------------------------

SabiranjeCvor::SabiranjeCvor(ASTCvor *levi, ASTCvor *desni)
    : BinarniCvor(levi, desni) {}

void SabiranjeCvor::ispisi(std::ostream &os) const {
    os << "(" << *m_levi << ") + (" << *m_desni << ")";
}

int SabiranjeCvor::interpretiraj(TabelaSimbola &tabela_simbola) const {
    return m_levi->interpretiraj(tabela_simbola) + m_desni->interpretiraj(tabela_simbola);
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

int OduzimanjeCvor::interpretiraj(TabelaSimbola &tabela_simbola) const {
    return m_levi->interpretiraj(tabela_simbola) - m_desni->interpretiraj(tabela_simbola);
}

ASTCvor *OduzimanjeCvor::kloniraj() const {
    return new OduzimanjeCvor(*this);
}

// --------------------------------------------

JednakostCvor::JednakostCvor(ASTCvor *levi, ASTCvor *desni)
    : BinarniCvor(levi, desni) {}

void JednakostCvor::ispisi(std::ostream &os) const {
    os << "(" << *m_levi << ") = (" << *m_desni << ")";
}

int JednakostCvor::interpretiraj(TabelaSimbola &tabela_simbola) const {
    return m_levi->interpretiraj(tabela_simbola) == m_desni->interpretiraj(tabela_simbola);
}

ASTCvor *JednakostCvor::kloniraj() const {
    return new JednakostCvor(*this);
}

// --------------------------------------------

ManjeCvor::ManjeCvor(ASTCvor *levi, ASTCvor *desni)
    : BinarniCvor(levi, desni) {}

void ManjeCvor::ispisi(std::ostream &os) const {
    os << "(" << *m_levi << ") < (" << *m_desni << ")";
}

int ManjeCvor::interpretiraj(TabelaSimbola &tabela_simbola) const {
    return m_levi->interpretiraj(tabela_simbola) < m_desni->interpretiraj(tabela_simbola);
}

ASTCvor *ManjeCvor::kloniraj() const {
    return new ManjeCvor(*this);
}

// --------------------------------------------

VeceCvor::VeceCvor(ASTCvor *levi, ASTCvor *desni)
    : BinarniCvor(levi, desni) {}

void VeceCvor::ispisi(std::ostream &os) const {
    os << "(" << *m_levi << ") > (" << *m_desni << ")";
}

int VeceCvor::interpretiraj(TabelaSimbola &tabela_simbola) const {
    return m_levi->interpretiraj(tabela_simbola) > m_desni->interpretiraj(tabela_simbola);
}

ASTCvor *VeceCvor::kloniraj() const {
    return new VeceCvor(*this);
}

// --------------------------------------------
