# P2-Rokovi

Rešeni zadaci iz jezika C sa rokova iz Programiranja 2 na ETF-u

## O skraćenicama

### Motivacija

U svim ispitnim zadacima gde se javlja upravljanje dinamičkom memorijom ili datotekama (a to su maltene svi zadaci) potrebno je pisati  delove koda za proveru uspešnosti alokacije ili otvaranja datoteke iznova i iznova. To izgleda npr. ovako:

```C
Elem *p = malloc(sizeof *p);
if (!p) {
    printf("Neuspesna alokacija\n");
    exit(1);
}
```

```C
FILE *fp = fopen("unos.txt", "r");
if (!fp) {
    printf("Neuspesno otvaranje fajla\n");
    exit(2);
}
```

Pošto su ovi kodovi uvek isti, može se značajno uštedeti na pisanju ako se ti delovi izvuku u makroe. Na taj način, umesto pisanja `if`-ova na svakom mestu gde se alocira memorija ili otvara datoteka (što može biti i do 5–6 puta po zadatku), dobija se ovako nešto:

```C
Elem *p = malloc(sizeof *p);
ALLOC_CHECK(p);
```

ili, ukoliko je `p` ranije definisano, još kraće: `ALLOC_CHECK(p = malloc(sizeof *p));`. Naravno, na kraju se memorija i dalje mora osloboditi s `free(p)`.

### Implementacija

Pomenuti makroi se mogu definisati na sledeći način:

```C
#define ALLOC_CHECK(p) if (!(p)) puts("Neuspesna alokacija"), exit(1)
#define FILE_CHECK(f)  if (!(f)) perror(NULL), exit(2)
```
 
Ako je ostatak koda na srpskom, mogu se nazvati i `PROV_MEM` i `PROV_DAT`, respektivno, ili bilo kako drugačije. Manje poznate funkcije koje se ovde koriste su objašnjene [ispod](#ostalo).
 
Na ovaj način, kada pretprocesor uradi tekstualnu zamenu, naredba `ALLOC_CHECK(p = malloc(sizeof *p));` postane `if (!(p = malloc(sizeof *p))) puts("Neuspesna alokacija"), exit(1);` što je ekvivalentno velikom `if` bloku odozgo; odnosno:

1. pokuša se alokacija bloka memorije date veličine;
2. rezultat se dodeli u pokazivačku promenljivu;
3. ako je rezultat nula, ispisuje se poruka i prekida se program.

Isto važi i za makro `FILE_CHECK`, samo je tu u pitanju otvaranje datoteke umesto alokacija. Primetiti da su u makroima zagrade <code>if (!**_(_**p**_)_**)</code> veoma bitne jer bi bez njih tekstualna zamena dala neispravan kod.

### `ASSIGN` makro

Otvaranje datoteka se još više može uprostiti ako se uvede makro:

```C
#define ASSIGN(p, f, m) if (!((p) = fopen(f, m))) perror(f), exit(1)
```

Ovaj makro u jednom potezu pozove `fopen` za dato ime i mod, sačuva rezultat u pokazivač i proveri da li je kojim slučajem došlo do greške pri otvaranju, a ako jeste prekine program. Koristi se na sledeći način (slično kao funkcija `Assign` u Paskalu):

```C
FILE *fp;
ASSIGN(fp, "moja_dat.bin", "rb+");
```

### Nedostaci

Mali nedostatak ovih makroa je da se zbog svog oblika ne smeju naći unutar kratke `if` naredbe neposredno pre `else` grane. Makro ekspanzija bi u tom slučaju neželjeno izmenila semantiku programa. Primer:

```C
if (uslov)
    ALLOC_CHECK(p = malloc(sizeof *p));
else  // Odnosi se na if u makrou, ne na `if (uslov)`
    puts("Nije uslov");
```

Mala je verovatnoća da se ovo desi, ali u tom slučaju samo treba pisati vitičaste zagrade oko grana `if`-a i neće biti problema.


## Ostalo

### [`puts`](http://www.cplusplus.com/reference/cstdio/puts/) / [`fputs`](http://www.cplusplus.com/reference/cstdio/fputs/)

Funkcija `puts` ispisuje string na standardni izlaz i prelazi u novi red. `puts("Neuspesna alokacija");` je, dakle, isto što i `printf("Neuspesna alokacija\n");`, samo što je malo brže za pisanje i ne može doći do slučajne greške ako se ispusuju znaci `%` (`puts` nema formatiranje).

`fputs` radi sličnu stvar, samo što umesto na izlaz ispisuje string u datoteku koja se zadaje kao drugi argument. Dakle, <code>fputs("Neuspesna alokacija", [stderr](http://www.cplusplus.com/reference/cstdio/stderr/))</code> umesto na standardni izlaz ispisuje poruku na izlaz za greške (mada to nije toliko bitno za zadatke), dok `fputs("neki string\n", fp)` upisuje string u otvorenu datoteku na koju pokazuje `fp`.

### <code>[perror](http://www.cplusplus.com/reference/cstdio/perror/)(NULL)</code>

Veoma korisna funkcija koja automatski ispisuje odgovarajuću poruku za grešku koja se desila prilikom otvaranja datoteke, npr. „No such file or directory” ili „File already in use”. Umesto `NULL` se može proslediti string koji će se ispisati zajedno sa porukom, npr. `perror("Greska")` → „Greska: File already in use”.

Sve gorenavedene funkcije su iz zaglavlja `<stdio.h>`.

### `sizeof *p` vs <code>sizeof(<em>tip</em>)</code>

Ove dve operacije rade isto (daju veličinu u bajtovima onoga na šta `p` pokazuje), ali je prvo [fleksibilnije](https://stackoverflow.com/q/373252/1523774) i to je preporučeni način pisanja. Primetiti da kada se stavlja `*p` umesto _`tip`_ zagrade nisu potrebne.

Alociranje niza od 10 brojeva onda izgleda ovako: `int *niz = malloc(10 * sizeof *niz);` ili `int *niz = calloc(10, sizeof *niz);`, dok se matrice formiraju na sledeći način:

```C
int **mat  = calloc(m, sizeof *mat);  // *mat daje tip int *
for (i = 0; i < m; i++) {
    mat[i] = calloc(n, sizeof **mat);  // **mat daje tip int
    for (j = 0; j < n; j++)
        scanf("%d", &mat[i][j]);
}
```

### Potpis funkcije `main`

Po standardu jezika C postoje dva ispravna potpisa za glavni program:

1. `int main(void)` – bez argumenata komandne linije;
2. `int main(int argc, char *argv[])` – sa argumentima komandne linije.

Pritom vredi naglasiti da imena parametara `argc` i `argv` nisu ni na koji način posebna i da se oni mogu zvati bilo kako, dokle god su im tipovi `int` i `char*[]` (odnosno `char**`), respektivno. Dakle, i `int main(int n, char **a)` je sasvim ispravan potpis glavnog programa.

Prema tome, varijante `void main()` ili ne daj bože samo `main()` **nisu ispravne** i ne treba tako pisati. Razlozi zašto prevodilac ovo dozvoljava su istorijski (davno, pre standardizacije C-a, se pisalo ovako i na još par načina), ali tome nije mesto u današnjem kodu. Mada ne iznađuje me da Katedra i dalje ovako piše.

Što se tiče potpisa `int main()` i on može proći kao prigodna zamena za 1. varijantu, ali postoji mala razlika: u C-u potpis `(void)` znači da funkcija _ne prima_ argumente, dok `()` znači da prima _proizvoljan broj_ argumenata. Prva varijanta je bolja jer je eksplicitnija.

Povratna vrednost glavnog programa je tipa `int` zato što preko nje programi javljaju okruženju da li su se uspešno izvršili (0 – uspešno; ≠0 – neuspešno, a vrednost predstavlja kod greške). Međutim, `return 0` na kraju `main`-a se ne mora pisati jer se po standardu podrazumeva.
