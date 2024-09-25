# Blockchain
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
