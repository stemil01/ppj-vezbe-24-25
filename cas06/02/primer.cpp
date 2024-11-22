
union U {
    int ceo_broj;
    double realan_broj;
    int nesto_trece;
    std::string *niska;
}

int main() {
    union U unija;
    unija.ceo_broj = 4;

    return 0;
}