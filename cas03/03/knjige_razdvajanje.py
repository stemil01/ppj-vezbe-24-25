import sys
import re

if len(sys.argv) < 2 or len(sys.argv) > 3:
    sys.exit('pogresan broj argumanata komandne linije')

print_autor = True
print_cena = True
print_izdavac = True
print_godina = True


if len(sys.argv) == 3:
    if re.match(r'^-[acig]+$', sys.argv[1]) is None:
        sys.exit('pogresni argumenti')

    uneti_naslov = sys.argv[2]

    if re.match(r'.*a.*', sys.argv[1]) is None:
        print_autor = False
    if re.match(r'.*c.*', sys.argv[1]) is None:
        print_cena = False
    if re.match(r'.*i.*', sys.argv[1]) is None:
        print_izdavac = False
    if re.match(r'.*g.*', sys.argv[1]) is None:
        print_godina = False
else:
    uneti_naslov = sys.argv[1]

knjiga_patern = re.compile(
    r'<knjiga\s+rbr=\"(?P<rbr>[1-9][0-9]*)\"\s*>'
    + r'(?P<detalji>.*?)'
    + r'\s*<\/knjiga>',
    re.DOTALL
)

autor_patern = re.compile(r'<autor>\s*(?P<autor>[a-zA-Z]+(\s[a-zA-Z]+)*)\s*<\/autor>')
naslov_patern = re.compile(r'<naslov>\s*(?P<naslov>[a-zA-Z]+(\s[a-zA-Z]+)*)\s*<\/naslov>')
god_patern = re.compile(r'<god>\s*(?P<god>[1-9][0-9]*)\s*<\/god>')
izdavac_patern = re.compile(r'<izdavac>\s*(?P<izdavac>[a-zA-Z\'&]+(\s[a-zA-Z\'&]+)*)\s*<\/izdavac>')
cena_pattern = re.compile(r'<cena\s+valuta=\"(?P<valuta>[a-z]+)\">(?P<cena>[1-9][0-9]*)<\/cena>')

try:
    with open('knjige.xml', 'r') as f:
        sadrzaj = f.read()
except IOError:
    sys.exit('greska pri otvaranju fajla knjige.xml')

knjige = {}
for match in knjiga_patern.finditer(sadrzaj):
    detalji = match.group('detalji')
    rbr = match.group('rbr')

    autor = autor_patern.search(detalji).group('autor')
    naslov = naslov_patern.search(detalji).group('naslov')
    god = god_patern.search(detalji).group('god')
    izdavac = izdavac_patern.search(detalji).group('izdavac')
    cena = cena_pattern.search(detalji).group('cena')
    valuta = cena_pattern.search(detalji).group('valuta')

    knjige[naslov] = (rbr, autor, god, izdavac, cena, valuta)



info = knjige[uneti_naslov]
if print_autor:
    print(info[1])
if print_godina:
    print(info[2])
if print_izdavac:
    print(info[3])
if print_cena:
    print(info[4], info[5])

