import sys
import re

if len(sys.argv) != 2:
    sys.exit('pogresan broj argumenata komandne linije')

obradjenjeni_fajlovi = set()

def obradi_fajl(ime_fajla):
    if ime_fajla not in obradjenjeni_fajlovi:
        obradjenjeni_fajlovi.add(ime_fajla)
        print(ime_fajla)

        try:
            with open(ime_fajla, 'r') as f:
                sadrzaj = f.read()
        except IOError:
            sys.exit('greska pri otvaranju fajla')

        link_patern = re.compile(r'<a\s+href=\"(?P<link>[a-zA-Z0-9_:/.]+)\">.*?<\/a>', re.DOTALL)
        for match in link_patern.finditer(sadrzaj):
            obradi_fajl(match.group('link'))

obradi_fajl(sys.argv[1])
