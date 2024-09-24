//
//  main.cpp
//  blockchainv1
//
//  Created by Kamilė Zobėlaitė on 2024-09-17.
//

#include <iostream>
#include <iomanip>
#include <vector>
#include <bitset>
#include <sstream>
#include <fstream>
using namespace std;
void skaityti();
void naudojimosiInstrukcija();
string hashFunkcija(string input);
unsigned long long int rightRotate (unsigned long long int reiksme, unsigned long long int d);
unsigned long long int leftRotate (unsigned long long int reiksme, unsigned long long int d);
void failuGeneravimas();
void failasSuVienuSimboliu(const std::string& fileName, char c);
void randomFailas1000(const std::string& fileName, int ilgis);
void failas1000SuVienuSkirtingu(const std::string& fileName1, const std::string& fileName2, int ilgis);
void tusciasFailas(const std::string& fileName);
int main()
{  
    srand( static_cast<unsigned int>(time(nullptr)));
    string output;
    failuGeneravimas();
//    cout << hashFunkcija("Lietuva");
//    cout << hashFunkcija("lietuva");
      //naudojimosiInstrukcija();
  
    //skaityti();
    return 0;
}
void naudojimosiInstrukcija()
{
    int rinktis;    // komandos parinkimas
    cout << "Pasirinkite:" << endl;
    cout << "1 - ivestis ranka\n";
    cout << "2 - ivestis is failo\n";
    cout << "3 - generuoti failus\n";
    cout << "4 - avalanche testavimas\n";
    cout << "5 - atsparumas kolizijai\n";
    cout << "6 - konstitucijos testavimas\n";
    cout << "7 - baigti darba\n";
    cin >> rinktis;
    while(!cin>>rinktis || rinktis < 1 || rinktis > 7)
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Klaida! Turite pasirinkti nuo 1 iki 7: \n";
            cin >> rinktis;
            
        }

    switch (rinktis)
    {
    case 1:{
        string tekstas;
        cout << "Irasykite norima teksta: \n";
        getline(cin,tekstas);
        cout << "Ivestas tekstas: \n" << tekstas << endl;
        break;}
    }

}

 void skaityti()
 {
     vector<string> galimiFailai = {"simbolis1.txt", "simbolis2.txt", "random1000v.txt", "random1000du.txt", "tukstsimb1.txt", "tukstsimb2.txt"};
     int rinktis;
     string failas;


     cout << "Pasirinkite faila, is kurio norite, kad butu skaitomi duomenys: \n";
     for (const auto& file : galimiFailai) {
         int i = 1;
         std::cout << i << " - " << file << std::endl;
         i++;
     }
     cin >> rinktis;
     failas = galimiFailai[rinktis - 1];
     ifstream fd(failas);
     
     
     fd.close();

 }

string hashFunkcija(string input)
{
    
    int paskutinis = int(input.length())-1;
    vector<string> bituMasyvas;
    int sk1 = 1+pow(paskutinis*2, 2);
    int sk2 = 16+pow(paskutinis/2, 3);
    cout << sk1 << " " << sk2 << endl;
    vector<unsigned long long> outputHash = {333, 444, 555, 999};
    unsigned long long int suma = 0;        // hasho suma
    // visu pirma, sumaisom simbolius tarpusavyje
//    for (int i = 0; i + 3 < input.size(); ++i)
//    {
//        
//            swap(input[i], input[i+3]);
//        
//    }
    cout << input << endl;
    // 2 zingsnis - zaidziam su bitais
    
    for(int i = 0; i < input.length(); i++)
    {
        char dabSimb = input.at(i);
        cout << "nepakeistas" << endl << (std::bitset<64>) dabSimb << endl;
                std::bitset<64> desChar = rightRotate(dabSimb+i+1, 8);
        //cout << dabSimb* 73939 << endl;
        std::bitset<64> random1 = rightRotate(dabSimb*(sk1+i), 16);
//        cout << desChar << endl;
//        cout << random1 << endl;
        std::bitset<64> jungSimb = input.at(paskutinis);
        //cout  << "p " << jungSimb << endl;
        std::bitset<64> random2 = leftRotate(dabSimb*(sk2+i), 16);
//        cout << random2;
//        cout << endl;
        std::bitset<64> XORjungimas1 = desChar^jungSimb;
        //cout << XORjungimas1 << endl;
        std::bitset<64> XORjungimas2 = random1^random2;
//        cout << XORjungimas2 << endl;
//        cout << std::bitset<64>(XORjungimas1^XORjungimas2) << endl;
        std::bitset<64> kairChar = rightRotate(paskutinis, 8);
        std::bitset<64> finalinis = XORjungimas1^XORjungimas2^kairChar;
        std::bitset<64> diff = finalinis.to_ullong() - 256 * pow(876, i);
        outputHash[i%4] += leftRotate(diff.to_ullong(), 8191);
//        outputHash[i % 4] ^= desChar ^ random1 ^ random2;
//        outputHash[i % 4] += simbolioReiksme * (sk1 + sk2);
        if (i + 1 < input.length()/2) {
                    paskutinis--;
                }
                else if (i + 1 > input.length()/2) {
                    paskutinis++;
                }
                else {
                    paskutinis = 0;
                }
    }
    

    unsigned long long int hash = 5381;
    // pasiverciam inputa i bitus
//      for (std::size_t i = 0; i < input.size(); ++i)
//  {
//      
//      bitset<64> bitai(input.c_str()[i]);
//      bituMasyvas.push_back(bitai.to_string());
//  }
  for (const auto& bits : bituMasyvas) {
        std::cout << bits << " ";
    }
    cout << endl;
//  for (std::size_t i = 0; i +3 < input.size(); ++i)
//  {
//      
//          swap(bituMasyvas[i], bituMasyvas[i+3]);
//      
//  }
    
    
    for (const auto& bits : bituMasyvas) {
       std::cout << bits << " ";
   }
    cout << endl;


 for (std::size_t i = 0; i < input.size(); ++i) {
        hash = ((hash << 5) + hash) + input.c_str()[i];
    }
   
    cout << endl;
    std::stringstream ss;
    for (const auto& val : outputHash) {
            ss << std::hex << std::setfill('0') << std::setw(16) << val;
        }
    
        return ss.str();


   // return std::to_string(hash);

}
unsigned long long int rightRotate (unsigned long long int reiksme, unsigned long long int d) {
    return (reiksme >> d) | (reiksme << (64 - d));
}
unsigned long long int leftRotate (unsigned long long int reiksme, unsigned long long int d) {
    return (reiksme << d) | (reiksme >> (64 - d));
}


int binTodec(int sk)
{
    int temp = sk;
    int des_sk = 0;
    int baz = 1; // pradedam nuo 2^0=1
    while(temp)
    {
        int last_digit = temp % 10;
                temp = temp / 10;
                des_sk += last_digit * baz;
                baz = baz * 2;
    }
    return des_sk;
    
}
void failuGeneravimas()
{
    failasSuVienuSimboliu("simbolis1.txt", 'A'+rand()%26);
    failasSuVienuSimboliu("simbolis2.txt", 'A'+rand()%26);
    randomFailas1000("random1000v", 1000);
    randomFailas1000("random1000du", 1000);
    failas1000SuVienuSkirtingu("tukstsimb1.txt", "tukstsimb2.txt", 1000);
    tusciasFailas("tuscias.txt");
    
    
}
void failasSuVienuSimboliu(const std::string& fileName, char c) {
    std::ofstream fr(fileName);
    fr << c;
    fr.close();
}
void randomFailas1000(const std::string& fileName, int ilgis)
{
    ofstream fr(fileName);
    for(int i = 0;i < ilgis; i++)
    {
        char randomSimb = ' ' + rand() % 95;
        fr << randomSimb;
    }
    fr.close();
}
void failas1000SuVienuSkirtingu(const std::string& fileName1, const std::string& fileName2, int ilgis)
{
    ofstream f1("tukstsimb1.txt");
    ofstream f2("tukstsimb2.txt");
    for(int i = 0; i < ilgis; i++)
    {
        if(i==(ilgis/2))
        {
            f1<< 'Q';
            f2 << 'R';
        }
        char randomSimb = ' ' + rand()%95;
        f1<< randomSimb;
        f2 << randomSimb;
    }
    f1.close();
    f2.close();
}
void tusciasFailas(const std::string& fileName)
{
    ofstream fr(fileName);
    fr.close();
}
