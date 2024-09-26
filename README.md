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
<img width="266" alt="Screenshot 2024-09-26 at 14 26 50" src="https://github.com/user-attachments/assets/78a6d49e-0fc0-4cc6-8d02-65ebf6cb1513">

## Avalanche testavimmas (lavinos efekto)

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

