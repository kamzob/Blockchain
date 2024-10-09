# Blockchain

## Reikalavimai hash'ui

1. Maišos funkcijos įėjimas(angl.input) gali būti bet kokio dydžio simbolių eilutė (angl. string). 
2. Maišos funkcijos išėjimas (angl.output) visuomet yra to paties, fiksuoto dydžio rezultatas (pageidautina 256 bit'ų ilgio, t.y., 64 simbolių hex'as). 
4. Maišos funkcija yra deterministinė,t.y.,tam pačiam įvedimui (input'ui) išvedimas (output'as) visuomet yra tas pats. 
lietuva:
``b5269fe5056dbf80dd03eba8dc8305089a113be6e495251c5736513782889e8e``
6. Maišos funkcijos reikšmė/kodas (hash‘as) bet kokiai input'o reikšmei yra apskaičiuojamas greitai - efektyviai.
7. Iš hash funkcijos rezultato (output'o) praktiškai neįmanoma atgaminti pradinio įvedimo (input'o).
8. Maišos funkcija yra atspari "kolizijai"(angl.collisionresistance),t.y.,praktiškai neįmanoma surasti tokių dviejų skirtingų argumentų m1 != m2, kad jiems gautume tą patį hash'ą: h(m1) = h(m2).
9. Bent minimaliai pakeitus įvedimą, pvz., vietoj "Lietuva" pateikus "lietuva", maišos funkcijos rezultatas-maišos kodas turi skirtis iš esmės, t.y., turi būti tenkinamas taip vadinamas lavinos efektas (angl. Avalanche effect).

| Įvedimas | Mano hash |
|----------|---------|
| "Lietuva" | 83fecc92b18d67221ff253c626b6456084210d069fa0da1aaaffa5e1498aa68d |
| "Lietuva!" | b6b87991e8a029b065444213fbe93af271b130cb60e0968a11a72d2d38fc6017 |
| "lietuva" | b5269fe5056dbf80dd03eba8dc8305089a113be6e495251c5736513782889e8e |

## Naudojimo instrukcija
Paleidus programą gausite meniu:

<img width="290" alt="Screenshot 2024-09-26 at 19 22 28" src="https://github.com/user-attachments/assets/ed36c9a2-3075-4d58-84e9-1d06741127d3">

1. Paspaudus 1 - galėsite įvesti savo norimą tekstą, kurį norite hash'uoti
2. Paspaudus 2 - Jus nukreips į skaitymo funkciją, kurioje galėsite pasirinkti, kurį failą skaityti, kad jo tekstą užhashuoti:
   
   <img width="482" alt="Screenshot 2024-09-26 at 19 31 54" src="https://github.com/user-attachments/assets/d14954d4-0eae-4d23-9075-422fb59c553d">
  2.1 simbolis1.txt, simbolis2.txt - failai, sudaryti iš vieno atsitiktinai sugeneruoto simbolio   
  
  2.2 random1000v.txt, random1000du.txt - failai, sudaryti iš 1000 atsitiktinai sugeneruotų simbolių
  
  2.3 tukstsimb1.txt, tukstsimb2.txt - failai sudaryti iš 1000 simbolių, tačiau skiriasi tik vienu simboliu
  
  2.4 tuscias.txt - tuščias failas
  
3. Paspaudus 3 - bus vykdomas failų "simbolis1.txt", "simbolis2.txt", "random1000v.txt", "random1000du.txt", "tukstsimb1.txt", "tukstsimb2.txt", "tuscias.txt" generavimas
4. Paspaudus 4 - bus atliekamas avalance (lavinos efekto) testavimas, kai bus tikrinamas hashų skirtumas hex ir bitų lygmenyje
5. Paspaudus 5 - bus tikrinamas atsparumas kolizijai, t.y. bus tikrinama, kiek hash'ų sutampa.
6. Paspaudus 6 - bus atliekamas laiko testavimas su failu konstitucija.txt
7. Paspaudus 7 - programa baigia darbą.
  
## Hash generatorius
### Paprastai pseudo-kodas
1. Funkcija priima input'ą bet kokio dydžio
2. Tada du tiesiog pirminiai dideli skaičiai paimami, užrašau juos šešioliktainiu formatu su priekyje 0x
3. Susikuriu masyvą 4 elementų (kiekvieno dydis 64 bitai), kurių pradinės reikšmės 0
4. Suku ciklą per inputo ilgį
5. Skaitomam simboliui priskiriu ASCII reikšmę
6. Suku dar vieną ciklą, kuris pereis per visus 4 masyvo elementus
7. Atlieku XOR operaciją elemento su skaitomo simbolio ASCII reikšme
8. Tada elementą padauginu su vienu iš pirminių skaičių
9. TAda vykdau bitų rotaciją į kairę per 13 elementų
10. Tada vykdau sekančio masyvo elemento bitų rotaciją dešinėn per 17 pozicijų ir atlieku XOR operaciją du dabartiniu masyvo elementu
11. Tuomet skaitomo simbolio reikšmę padauginu iš antrojo pirminio skaičiaus
12. Vidinis ciklas baigiasi
13. Pagrindinis ciklas baigiasi
14. Inicializuoju tuščią eilutę
15. SUku ciklą per kiekvieną masyvo elementą
16. Kiekvieną masyvo elementą pridedu į eilutę kaip 16 simbolių šešioliktainį sk
17. Grąžinu funkcijos rezultatą
18. Funkcija baigia darbą
### Detaliau
* sk1, sk2 - 64 bitų pirminių skaičių konstantos, paverstos i sesioliktaini:
```
  const unsigned long long sk1 = 0x100000001b3;// 1099511628211
  const unsigned long long sk1 = 0x100000001b3; // 12345300873145699937
```
* outputHash - 4 elementų po 64 bitus masyvas, kurio pradinės reikšmės 0:
```
  vector<unsigned long long> outputHash(4, 0);
```
* ```for(int i = 0; i < input.length(); i++)``` - einama per visa stringo ilgį
* dabSimb - skaitomas simbolis, reiksme = dabSimb ASCII reikšmė:
```
char dabSimb = input[i];
unsigned long long reiksme = static_cast<unsigned long long>(dabSimb);
```
* ``` for(int j = 0; j < 4; j++) ``` - einama per 4 blokus
* ``` outputHash[j] ^= reiksme;``` - XOR operacija, atliekama tarp 64 bitų vertės (outputHash[j]) ir kito 64 bitų kintamojo (reiksme), kurios metu bitai keičiasi taip:
0^0=0, 0^1=1, 1^0=1, 1^1=0.
* ``` outputHash[j]*= sk1; ``` - šios operarcijos metu, blokas yra dauginamas iš pirminio skaičiaus sk1
* ``` outputHash[j] = leftRotate(outputHash[j], 13);``` - kviečiame funkcija
```
unsigned long long int leftRotate (unsigned long long int reiksme, unsigned long long int d) {
    return (reiksme << d) | (reiksme >> (64 - d)); 
}
```
 ir vykdoma bitų rotacija kairėn per 13 pozicijų, pavyzdžiui:
```0000000000000000010011000000000000000000000000001000000100100100```
paverčiamas į:
```0000100110000000000000000000000000010000001001001000000000000000```
Taigi, pastumiamas per 13 pozicijų kairėn, o priekyje buvę 13 skaičių nukeliami į galą.
* ```outputHash[j]^=rightRotate(outputHash[(j+1)%4], 17)```
* * ```(j+1) % 4 ```yra indeksavimas, skirtas pasiekti kitą elementą outputHash masyve, bet jis naudoja operaciją (% 4), kad indeksas nesiektų daugiau nei 3, t.y. perslenka per vieną elemntą į priekį, o jei j+1 = 3, tai bus 0.
* * ```rightRotate(outputHash[(j+1)%4], 17)``` - kviečiama funkcija:
```
unsigned long long int rightRotate (unsigned long long int reiksme, unsigned long long int d) {
    return (reiksme >> d) | (reiksme << (64 - d));
}
```
Šios operacijos metu bitai pastumiami į dešinę per 17 pozicijų, o „išstumti“ bitai iš dešinės pusės sugrąžinami į kairę pusę.
* * Galiausiai vykdoma XOR operacija ^ (```outputHash[j]^=rightRotate(outputHash[(j+1)%4], 17)```), kurios metu bitai keičiasi taip:
0^0=0, 0^1=1, 1^0=1, 1^1=0.
* ```reiksme *= sk2;``` - simbolio ASCII reikšmė didėja sk2 kartų einant per outputHash[j] elementus.

*
```
  std::stringstream ss;
    for (const auto& val : outputHash) {
            ss << std::hex << std::setfill('0') << std::setw(16) << val;
        }
```
* * ``std::stringstream ss;`` - inicializuojama tuščia eilutė ss rezultatui išvesti
  * ```for (const auto& val : outputHash)```FOR kiekviena reikšmė val IN outputHash:
  * ```ss << std::hex << std::setfill('0') << std::setw(16) << val;``` - į ss pridedamas val kaip 16 simbolių šešioliktainis skaičius
* ``return ss.str();`` - grąžina funkcijos rezultatą.

# Eksperimentinis tyrimas ir tyrimų analizė
## Eksperimentas su testiniais failais
### Failai sudaryti iš vieno, tačiau skirtingo simbolio
simbolis1.txt (jame yra simbolis Y) jo hash:
``0b20000012e7600035e2fb86c8eb75f526c77bb2f86f7caf1b849787317375b0``
simbolis2.txt (jame yra simbolis S), jo hash:
``0a60000011a1200082cb0d1625cd3e8b66527bfd32792d16f38ce17967a53b2e``

### Failai, sudaryti iš 1000 atsitiktinių simbolių
random1000v.txt, jo hash:
``41b42670bf159a5601c6bf00a2defe7658775e95f68c38d72aa7f9a578ca2e1e``
random1000du.txt, jo hash:
a325b4fab82721cf25be3842c1b6fec67ff4502f2b891f88b596afeed57e3c2e

### Failai, sudaryti iš 1000 simbolių, otarpusavyje skiriasi tik vienu simboliu viduryje:
tukstsimb1.txt, jo hash:
``33e3ab9a8fddc4d54a50528bc86967aaa66854ee99fd5ea44359d5941074d424``
tukstsimb2.txt, jo hash:
``97716e1b69488b7cf4fb018eb314048ca5bd7682c434c99d79eef62c391db677``


## Konstitucija testavimas
<img width="769" alt="Screenshot 2024-09-26 at 00 21 19" src="https://github.com/user-attachments/assets/04a2c4c5-3631-43a3-947e-446e6b815d46">

| Eilučių kiekis:  | Hashavimo vidutinis laikas: (sek.) |
|----------------|------------------------------|
| 1 | 0,00000785 |
| 2 | 0,0000078918 |
| 4 | 0,0000123334 |
| 8 | 0,000020625 |
| 16 | 0,0000674916 |
| 32 | 0,0000987918 |
| 64 | 0,0001997 |
| 128 | 0,000485842 |
| 256 | 0,0013013 |
| 512 | 0,00335817 | 

## Kolizijų testavimas
Iš pradžių susigeneravau failą pagal užduoties rekomendaciją:  25 000 porų, kurių ilgis 10 simbolių, kitas 25 000 porų, kurių ilgis - 100, dar kitas 25 000 poras - 500, ir galiausiai likusias 25 000 poras, kurių ilgis - 1000 simbolių. Tada vykdomas tikrinimas: skaitoma iš failo string'ų pora, jie hashuojami. Tada tikrinami hashai: jei jie yra vienodi, tai atsiranda pranešimas: Kolizija aptikta! Ir išvedami inputai. Galiausiai patikrinus visas poras, atsiranda pranešimas kiek porų buvo patikrinta ir kiek kolizijų atsirado. Kaip matome, mano hashFunkcija veikia gerai, nes kolizijų nebuvo rasta.
<img width="266" alt="Screenshot 2024-09-26 at 14 26 50" src="https://github.com/user-attachments/assets/78a6d49e-0fc0-4cc6-8d02-65ebf6cb1513">

## Avalanche testavimmas (lavinos efekto)
Iš pradžių susigeneruoju failą "inputForAvalanche.txt", kuriame yra string'ų poros, kurios skiriasi vienu simboliu atsitiktinai parinktoje vietoje. Tada skaitau iš failo porą, sugeneruoju kiekvienam stringui po hash'ą. Vyksta lyginimas - skaičiuojamas skirtumas hex ir bitų lygmenyje. Čia šio tyrimo rezultatai:
<img width="438" alt="Screenshot 2024-09-26 at 18 25 00" src="https://github.com/user-attachments/assets/c2c39b39-74d5-4936-8214-f27cbc9d046f">

## Trūkumai ir stiprybės
### Stiprybės
* Nepaisant kokio ilgio input, output'as yra vienodo ilgio (255 bitų, 64 simbolių)
* Tas pats input, visada duoda tą patį output'ą.
* Iš avalanche testavimo, galime teigti, kad hash tenkina lavinos efektą.
* Su konstitucija veikia greitai.
* Kolizijų neatsirado

### Trūkumai 
* Iš šių testų sunku nustatyti, kaip dažnai atsiranda kolizijos.
* Hash'inant didesnius failus, programa užtrunka ilgiau.

## Papildomos užduotys
1. Pabandykite kaip įmanoma objektyviau palyginti Jūsų Hash funkcijos spartą su MD5 , SHA-1 , SHA-256 ar kita gerai žinoma hash funkcija. Paliekame Jums sugalvoti, kaip
atlikti tokį palyginimą ir nuo jo objektyvumo priklausys ir bonus'o dydis.
Tai visų pirma, susiradau [SHA-256 generatorių](http://www.zedwood.com/article/cpp-sha256-function) - .cpp ir .h failus bei juos įsidėjau į savo darbą. Na o tada vyko tyrimas. Dariau ciklą, kurio metu i didėja du kartus, o i maks. - 1048576. Tada apsibrėžiau mano hash skaičiavimo laiką ir SHA-256, jiems priskyriau 0.0 reikšmes. Buvo generuojamas string'as i ilgio. Tada ciklo viduje sukau dar vieną ciklą, kuriame stringui sukuriami hash'ai su mano funkcija ir SHA-256 bei matuojamas laikas. Po 5 iteracijų išvedamas laikų vidurkis milisekundėmis. Apačioje galite matyti rezultatus, o išvada būtų tokia: SHA-256 generatorius laiko atžvilgiu yra žymiai efektyvesnis

|Input dydis    |   Mano hash     |   sha-256     |
|----------|----------|---------|
1	|	0.00485	|	0.0021584
2	|	0.0013086	|	0.0019748
4	|	0.0013416	|	0.0019752
8	|	0.0015334	|	0.0019916
16	|	0.0023752	|	0.0064834
32	|	0.0028664	|	0.0020498
64	|	0.0041	|	0.0026168
128	|	0.007075	|	0.0033086
256	|	0.0124748	|	0.0044498
512	|	0.0242668	|	0.0067832
1024	|	0.0474666	|	0.0115166
2048	|	0.091042	|	0.0208918
4096	|	0.178816	|	0.0393166
8192	|	0.35645	|	0.0767584
16384	|	0.713817	|	0.150933
32768	|	1.67725	|	0.3581
65536	|	2.63863	|	0.55005
131072	|	5.37869	|	1.12892
262144	|	10.9399	|	2.29623
524288	|	22.7407	|	4.77774
1048576	|	44.5441	|	9.28443

<img width="1096" alt="Screenshot 2024-10-02 at 19 11 25" src="https://github.com/user-attachments/assets/edaef8e3-c0b8-4ccf-90f4-13f8e7dba5f6">

### 2 papildoma
2. Parodykite,kad iš hash funkcijos rezultato (output'o) praktiškai neįmanoma atgaminti pradinio įvedimo (input'o), t. y., kaip Jūsų hash funkcijoje realizuota hiding ir puzzle-friendliness savybės. P.s. manau, kad šioje vietoje "druskos" tikrai nebus per daug :)
#### Hiding
Susikūriau 100000 porų failą taip: 25 000 porų, kurių ilgis 10 simbolių, kitas 25 000 porų, kurių ilgis - 100, dar kitas 25 000 poras - 500, ir galiausiai likusias 25 000 poras, kurių ilgis - 1000 simbolių. Poroje esantys string'ai vienodi. Atlikau testavimą tikrinant kolizijas, t.y tikrinau kolizijas savo paparastoje hash funkcijoje, kuri yra deterministinė ir naujoje hash funkcijoje, kur prie input'o pridedamas salt. Gavau štai tokius rezultatus:
<img width="579" alt="Screenshot 2024-10-08 at 23 04 44" src="https://github.com/user-attachments/assets/d39fa51a-638f-49c9-895b-6a7d8e350402">
Taigi, išvada būtų tokia: hiding su druska veikia kaip tikėtasi, nes kiekvienam input'ui, kad ir koks jis bebūtų, yra sugeneruojama unikali druska, kuri ir lemia hash skirtingumą ir kolizijų neatsiradimą. 

### puzzle-friendliness

<img width="572" alt="Screenshot 2024-10-09 at 00 07 19" src="https://github.com/user-attachments/assets/916d69ad-064e-4ed8-a8e8-d5869acb08cc">
Buvo paduodamas string "asmyliuLTU", gautas jo hash. Tada buvo 10 mln. bandymų generuojant atsitiktinę įvestį gauti tokį patį hash'ą. Deja, nepavyko, todėl reiškia, kad funkcija atitinka puzzle-friendliness savybę bent jau dalinai.

### 3 papildoma
Adriana Širokytė įtraukė mano hash funkciją į lenktynes ir apjungė kelių iš mūsų hash'us. Rezutltatus galite pamatyti čia: https://github.com/aran1ja/Blockchain/tree/v0.2 
