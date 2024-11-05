import sys
import re

if len(sys.argv) != 2:
    sys.exit('pogresan broj argumanata komandne linije')

if re.match(r'\w*\.html$', sys.argv[1]) is None:
    sys.exit('fajl nema html ekstenziju')

try:
    with open(sys.argv[1], 'r') as f:
        sadrzaj = f.read()
except IOError:
    sys.exit('greska pri otvaranju fajla')

re_patern = re.compile(
    r'<tr>\s*<td>\s*(?P<ime>[a-zA-Z]+(\s+[a-zA-Z]+)*)\s*<\/td>\s*'
    + r'<td>\s*(?P<pismeni>[0-9]+)\s*<\/td>\s*'
    + r'<td>\s*(?P<usmeni>[0-9]+)\s*<\/td>\s*'
    + r'<\/tr>')

studenti = []

for poklapanje in re_patern.finditer(sadrzaj):
    ime = poklapanje.group('ime')
    pismeni = int(poklapanje.group('pismeni'))
    usmeni = int(poklapanje.group('usmeni'))
    studenti.append((ime, pismeni + usmeni))

studenti.sort(key=lambda x: x[1], reverse=True)
for student in studenti:
    print(student[0] + ', ' + str(student[1]))
