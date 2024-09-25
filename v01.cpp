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
int main()
{  
    srand( static_cast<unsigned int>(time(nullptr)));
    string output;
//    cout << hashFunkcija("lietuva") << endl;
//    cout << hashFunkcija("Lietuva") << endl;
//    cout << hashFunkcija("Lietuva!") << endl;
    //cout << static_cast<unsigned long long>('a') << endl;
    //hashinimas("Lietuva");
    //failuGeneravimas();
//   string input = skaityti();
//    cout << hashFunkcija(input);
    //cout << hashFunkcija("Lietuva");
   //cout << hashFunkcija("lietuva");
      naudojimosiInstrukcija();
  
    //skaityti();
    return 0;
}
void naudojimosiInstrukcija()
{
    
    int rinktis;    // komandos parinkimas
    do{
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
                cout << "Sio teksto hash:\n" << hashFunkcija(tekstas) << endl;
                break;}
            case 2:{
                string tekstas = skaityti();
                cout << hashFunkcija(tekstas) << endl;
                break;
            }
            case 3:{
                failuGeneravimas();
                break;
            }
            case 4:{
                break;
            }
            case 5:{
                break;
            }
            case 6:{
                konstitucijosTestavimas();
                break;
            }
        }
    }while(rinktis!=7);


}

string skaityti()
 {
    string input;
     vector<string> galimiFailai = {"simbolis1.txt", "simbolis2.txt", "random1000v.txt", "random1000du.txt", "tukstsimb1.txt", "tukstsimb2.txt", "tuscias.txt"};
     int rinktis;
     string failas;


     cout << "Pasirinkite faila, is kurio norite, kad butu skaitomi duomenys: \n";
    for (int i = 0; i < galimiFailai.size(); i++) {
         std::cout << i+1 << " - " << galimiFailai[i] << std::endl;
         
     }
     cin >> rinktis;
    while(!cin>>rinktis || rinktis < 1 || rinktis > 7)
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Klaida! Turite pasirinkti nuo 1 iki 7: \n";
        cin >> rinktis;
        
    }
    
     failas = galimiFailai[rinktis - 1];
     ifstream fd(failas);
    try {
         if (!fd)
             throw runtime_error("Failas neegzistuoja arba nepasiekiamas.");
     } catch(const std::exception& e) {
         cerr << "Klaida: " << failas << e.what() << endl;
         
     }
    if(fd.peek()==ifstream::traits_type::eof())
    {
        input ="da39a3ee5e6b4b0d3255bfef95601890afd80709";
    }
    else
    {
        std::stringstream buffer;
        buffer << fd.rdbuf();
        
        
        input = buffer.str();
    }
     fd.close();
    return input;

 }
string hashFunkcija(string input)
{
    const unsigned long long sk1 = 0x100000001b3; //1099511628211 pirminis
    const unsigned long long sk2 = 0xab5351bc652b4e61;
    //12345300873145699937 pirminis sk
    vector<unsigned long long> outputHash(4, 0);
    for(int i = 0; i < input.length(); i++)
    {
        char dabSimb = input[i];
        unsigned long long reiksme = static_cast<unsigned long long>(dabSimb);
        for(int j = 0; j < 4; j++)
        {
//            cout << (std::bitset<64>) outputHash[j] << endl;
            outputHash[j] ^= reiksme;
//            cout << (std::bitset<64>) outputHash[j] << endl;
            outputHash[j]*= sk1;
//            cout << (std::bitset<64>) outputHash[j] << endl;
            outputHash[j] = leftRotate(outputHash[j], 13);
//            cout << (std::bitset<64>) outputHash[j] << endl;
            outputHash[j]^=rightRotate(outputHash[(j+1)%4], 17);
//            cout << (std::bitset<64>) outputHash[j] << endl;
//            cout << endl;
            reiksme *= sk2;
        }
    }
    std::stringstream ss;
    for (const auto& val : outputHash) {
            ss << std::hex << std::setfill('0') << std::setw(16) << val;
        }
    
        return ss.str();
    
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
    randomFailas1000("random1000v.txt", 1000);
    randomFailas1000("random1000du.txt", 1000);
    failas1000SuVienuSkirtingu("tukstsimb1.txt","tukstsimb2.txt", 1000);
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
            f1<< 'A';
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
void konstitucijosTestavimas()
{
    vector<string> eilutes;
    string eilute;
    ifstream fd("konstitucija.txt");
    try {
         if (!fd)
             throw runtime_error("failas neegzistuoja arba nepasiekiamas.");
     } catch(const std::exception& e) {
         cerr << "Klaida: konsttitucija.txt " << e.what() << endl;
         return;
     }
    while(getline(fd, eilute))
    {
        eilutes.push_back(eilute);
    }
    fd.close();
    
    for(int i = 1; i <= eilutes.size(); i*=2)
    {
        int kartai = 5;
        auto start = std::chrono::high_resolution_clock::now();
        for(int j= 0; j < kartai; ++j)
        {
            string eil;
            for(int m = 0; m < i && m < eilutes.size(); ++m)
            {
                eil+=eilutes[m];
                
            }
            string hashas = hashFunkcija(eil);
        }
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> laikas = end - start;
        cout << "Eilučių kiekis: " << i << " | Hashavimo vidutinis laikas: " << laikas.count() / kartai << endl;
        
    }
    
}
//string gautiString(
