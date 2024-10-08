//
//  funkcijos.h
//  v02
//
//  Created by Kamilė Zobėlaitė on 2024-10-02.
//

#ifndef funkcijos_h
#define funkcijos_h
#include "biblioteka.h"

string skaityti();
void naudojimosiInstrukcija();
string hashFunkcija(string input);
unsigned long long int rightRotate (unsigned long long int reiksme, unsigned long long int d);
unsigned long long int leftRotate (unsigned long long int reiksme, unsigned long long int d);
void failuGeneravimas();
void failasSuVienuSimboliu(const std::string& fileName, char c);
void randomFailas1000(const std::string& fileName, int ilgis);
void failas1000SuVienuSkirtingu(const std::string& fileName1, const std::string& fileName2, int ilgis);
void tusciasFailas(const std::string& fileName);
void konstitucijosTestavimas();
string gautiString(int ilgis);
void kolizijosTestavimas();
void AvalancheTestavimas();
void generuotiPorasSuVienuSkirtingu();
string hexToBin(string hex);
double bituLyginimas(string hashB1, string hashB2);
double hexLyginimas(string hash1, string hash2);
void manoHashVS256Hash();
string druskosGeneravimas(int ilgis);
string hashFunkcijaSuDruska(string input);
void generuotiVienodasPoras();
void hidingTyrimas();
void puzzleFriendliness();
#endif /* funkcijos_h */
