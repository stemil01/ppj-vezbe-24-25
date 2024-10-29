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
    r'(?=.*?<naslov>\s*(?P<naslov>[a-zA-Z]+(\s[a-zA-Z]+)*?)\s*<\/naslov>)'
    + r'(?=.*?<autor>\s*(?P<autor>[a-zA-Z]+(\s[a-zA-Z]+)*?)\s*<\/autor>)'
    + r'(?=.*?<god>\s*(?P<god>[1-9][0-9]*)\s*<\/god>)'
    + r'(?=.*?<izdavac>\s*(?P<izdavac>[a-zA-Z\'&]+(\s[a-zA-Z\'&]+)*?)\s*<\/izdavac>)'
    + r'(?=.*?<cena\s+valuta=\"(?P<valuta>[a-z]+)\">\s*(?P<cena>[1-9][0-9]*)\s*<\/cena>)'
    + r'.*?<\/knjiga>',
    re.DOTALL
)

try:
    with open('knjige.xml', 'r') as f:
        sadrzaj = f.read()
except IOError:
    sys.exit('greska pri otvaranju fajla knjige.xml')

knjige = {}
for match in knjiga_patern.finditer(sadrzaj):
    rbr = match.group('rbr')
    naslov = match.group('naslov')
    autor = match.group('autor')
    god = match.group('god')
    izdavac = match.group('izdavac')
    cena = match.group('cena')
    valuta = match.group('valuta')
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

