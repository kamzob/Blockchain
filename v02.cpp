



//using namespace std;
#include "funkcijos.h"
#include "sha256.h"

int main()
{
    naudojimosiInstrukcija();

    
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
        cout << "7 - atlikti mano hash ir sha-256 palyginima\n";
        cout << "8 - baigti darbą\n";
        cin >> rinktis;
        while(!cin>>rinktis || rinktis < 1 || rinktis > 8)
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
                //getline(cin,tekstas);
                cin >> tekstas;
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
                 AvalancheTestavimas();
                break;
            }
            case 5:{
                kolizijosTestavimas();
                break;
            }
            case 6:{
                konstitucijosTestavimas();
                break;
            }
            case 7:
                manoHashVS256Hash();
        }
    }while(rinktis!=8);


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
//           cout << (std::bitset<64>) outputHash[j] << endl;
            outputHash[j]*= sk1;
           // cout << (std::bitset<64>) outputHash[j] << endl;
            outputHash[j] = leftRotate(outputHash[j], 13);
           // cout << (std::bitset<64>) outputHash[j] << endl;
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
string gautiString(int ilgis)
{
    static const char alphanum[] = "0123456789"
    "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
    "abcdefghijklmnopqrstuvwxyz";
    string atsitiktinis_string;
    atsitiktinis_string.reserve(ilgis);
    int dydis = 62;
    std::random_device rd;
    std::mt19937 generator(rd());
    std::uniform_int_distribution<int> distrib(0, dydis - 1);
    for(int i = 0; i < ilgis; i++)
    {
        atsitiktinis_string+=alphanum[distrib(generator)];
    }
    return atsitiktinis_string;
}
void generuotiAtsitiktinesPoras()
{
    ofstream fr("atsitiktinesporos.txt");
    vector<int> ilgiai = {10, 100, 500, 1000};
    for(int i = 0; i < 4; i++)
    {
        int ilgis = ilgiai.at(i);
        for(int j = 0; j < 25000; ++j)
        {
            string str1 = gautiString(ilgis);
            string str2 = gautiString(ilgis);
            while (str1 == str2) {
                str1 =  gautiString(ilgis);
                str2 =  gautiString(ilgis);
            }
            fr << str1 << " " << str2 << endl;
        }
    }
    fr.close();
}
void kolizijosTestavimas()
{
    int rinktis;
    cout << "Ar norite sugeneruoti faila su atsitiktinemis poromis, ar jau turite? Jei norite, spauskite 1, jei jau turite spauskite 2:" << endl;
    cin >> rinktis;
    if(rinktis == 1)
    {
        generuotiAtsitiktinesPoras();
    }
    ifstream fd("atsitiktinesporos.txt");
    if (!fd) {
        cerr << "Nepavyko atidaryti atsitiktinesporos.txt failo" << endl;
        return;
        }
    string str1, str2;
    int kolizijuSk = 0;
    int poruSk = 0;
    while(fd >> str1 >> str2)
    {
        poruSk++;
        string hash1 = hashFunkcija(str1);
        string hash2 = hashFunkcija(str2);
        if (hash1 == hash2) {
            kolizijuSk++;
            cout << "Kolizija aptikta! String 1: " << str1 << " | String 2: " << str2 << endl;
                }
    }
    fd.close();
    cout << "Viso patikrinta porų: " << poruSk << endl;
    cout << "Viso aptikta kolizijų: " << kolizijuSk << endl;
    
}

void AvalancheTestavimas()
{
    int rinktis;
    cout << "Ar norite sugeneruoti faila su poromis, kuriu elementai skiriasi tik vienu simboliu, ar jau turite? Jei norite, spauskite 1, jei jau turite spauskite 2:" << endl;
    cin >> rinktis;
    if(rinktis == 1)
    {
        generuotiPorasSuVienuSkirtingu();
    }
    string str1, str2;
    ifstream fd("inputForAvalanche.txt");
    if (!fd) {
        cerr << "Nepavyko atidaryti inputForAvalanche.txt failo" << endl;
        return;
        }
    int poruSk = 0;
    double skirtingumasBitu = 0.0;
    double skirtingumasHex = 0.0;
    double minBitSkirtumas = 100.0;
    double maxBituSkirtumas = 0.0;
    double minxHexSkirtumas = 100.0;
    double maxHexSkirtumas = 0.0;
    
    while(fd >> str1 >> str2)
    {
       
        string hash1 = hashFunkcija(str1);
        string hash2 = hashFunkcija(str2);
        double skBitu = bituLyginimas(hexToBin(hash1), hexToBin(hash2));
        skirtingumasBitu+=skBitu;
        if(skBitu == 0)
        {
            cout << str1 << str2 << endl;
            cout << hash1 << endl;
            cout << hash2 << endl;
        }
        minBitSkirtumas = min(minBitSkirtumas, skBitu);
        maxBituSkirtumas=max(maxBituSkirtumas, skBitu);
        double skHex = hexLyginimas(hash1, hash2);
        skirtingumasHex+=skHex;
        minxHexSkirtumas= min(minxHexSkirtumas, skHex);
        maxHexSkirtumas = max(maxHexSkirtumas, skHex);
        poruSk++;
        
    }
    
    fd.close();
    cout << "Avalanche testas baigtas! Rezultatai: \n";
    cout << "Patikrinta poru: " << poruSk << endl;
    cout << "Vidutinis skirtumas bitų lygmenyje: " << ((skirtingumasBitu / poruSk)/256.0)*100.0 << "%" << endl;
    cout << "Minimalus skirtumas bitų lygmenyje: " << (minBitSkirtumas/256.0)*100.0 << "%" << endl;
    cout << "Maksimalus skirtumas bitų lygmenyje: " << (maxBituSkirtumas/256.0)*100.0 << "%" << endl;
    cout << "Vidutinis skirtumas hex lygmenyje: " << ((skirtingumasHex / poruSk)/64.0)*100.0 << "%" << endl;
    cout << "Minimalus skirtumas hex lygmenyje: " << (minxHexSkirtumas/64.0)*100.0 << "%" << endl;
    cout << "Maksimalus skirtumas hex lygmenyje: " << (maxHexSkirtumas/64.0)*100.0 << "%" << endl;
    
    
}
void generuotiPorasSuVienuSkirtingu()
{
    ofstream fr("inputForAvalanche.txt");
    vector<int> ilgiai = {10, 100, 500, 1000};
    for(int i = 0; i < 4; i++)
    {
        int ilgis = ilgiai.at(i);
        for(int j = 0; j < 25000; ++j)
        {
            string str1 = gautiString(ilgis);
            string str2 = str1;
            int keiciamoSimboloIndeksas = rand() % ilgis;
            char naujSimb;
            do{
                naujSimb = 'A' + (rand() % 26);
            }while(str1[keiciamoSimboloIndeksas]==naujSimb);
            str2[keiciamoSimboloIndeksas] = naujSimb;
            fr << str1 << " " << str2 << endl;
        }
    }
    fr.close();
}
string hexToBin(string hex)
{
    std::unordered_map<char, std::string> hex_to_bin {
            {'0', "0000"}, {'1', "0001"}, {'2', "0010"}, {'3', "0011"},
            {'4', "0100"}, {'5', "0101"}, {'6', "0110"}, {'7', "0111"},
            {'8', "1000"}, {'9', "1001"}, {'A', "1010"}, {'B', "1011"},
            {'C', "1100"}, {'D', "1101"}, {'E', "1110"}, {'F', "1111"}
        };
    string bin;
    for(char simb: hex)
    {
        bin += hex_to_bin[toupper(simb)];
    }
    return bin;
}
double bituLyginimas(string hashB1, string hashB2)
{
    double skirt = 0;
    for(int i = 0; i < hashB1.length(); i++)
    {
        if(hashB1[i]!=hashB2[i])
            skirt++;
    }
    return skirt;
}
double hexLyginimas(string hash1, string hash2)
{
    double skirt = 0;
    for(int i = 0; i < hash1.length(); i++)
    {
        if(hash1[i]!=hash2[i])
            skirt++;
    }
    return skirt;
}
void manoHashVS256Hash()
{
    cout << left << setw(12) << "Input dydis" << setw(10) <<  "Mano hash" << setw(10)  << "SHA-256" << endl;
    for(int i = 1; i <= 1048576; i*=2)
    {
        double manoLaikas = 0.0;
        double shaLaikas = 0.0;
        string input = gautiString(i);
        for(int j = 0; j < 5; j++)
        {
            auto start1 = std::chrono::high_resolution_clock::now();
            string mano = hashFunkcija(input);
//            cout << "Mano hash: " << mano << endl;
            auto end1 = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double> laikas1 = end1 - start1;
            manoLaikas+=laikas1.count();
            auto start2 = std::chrono::high_resolution_clock::now();
            string sha = sha256(input);
//            cout << "256 hash: " << sha << endl;
            auto end2 = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double> laikas2 = end2 - start2;
            shaLaikas+=laikas2.count();
        }
        
        cout << left <<setw(12) << i << setw(10) << manoLaikas*1000/5.0<< setw(10) << shaLaikas*1000/5.0 << endl;
    }
}
