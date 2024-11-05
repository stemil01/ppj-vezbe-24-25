import sys
import os
import re

if len(sys.argv) != 2:
    sys.exit('pogresan broj argumanata komandne linije')

if not os.path.isdir(sys.argv[1]):
    sys.exit('nije unet direktorijum')

radovi_dir = sys.argv[1]

zadaci = ['c', 'cpp', 'java']
alas_patern = re.compile(r'^(m[imnvrla]|a[afi])(1[0-9]|2[0-4])(00[1-9]|0[1-9][0-9]|[1-5][0-9]{2})$')
fajl_patern = re.compile(r'^(?P<broj_zad>[1-9][0-9]*)\.(c(pp)?|java)$')
student_patern = re.compile(
    r'(?P<alas>(m[imnvrla]|a[afi])(1[0-9]|2[0-4])(00[1-9]|0[1-9][0-9]|[1-5][0-9]{2}))'
    + r',\s+(?P<ime>[a-zA-Z]+(\s+[a-zA-Z]+)*)'
)

nalozi = {}

for dir in os.listdir(radovi_dir):
    if alas_patern.search(dir) is not None:
        nalozi[dir] = set()
        for fajl in os.listdir(os.path.join(radovi_dir, dir)):
            fajl_match = fajl_patern.match(fajl)
            if fajl_match is not None:
                nalozi[dir].add(int(fajl_match.group('broj_zad')))

studenti = {}
try:
    with open('indeksi.txt', 'r') as f:
        for linija in f:
            student_match = student_patern.match(linija)
            if student_match is not None:
                studenti[student_match.group('ime')] = student_match.group('alas')
except IOError:
    sys.exit('ne postoji fajl indeksi.txt')

print('\t', end='')
for zad in range(1, 11):
    print('\t' + str(zad), end='')
print()
for student, nalog in studenti.items():
    print(student, end='')
    for zad in range(1, 11):
        if zad in nalozi[nalog]:
            print('\t+', end='')
        else:
            print('\t-', end='')
    print()
