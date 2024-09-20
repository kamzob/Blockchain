#include <iostream>
#include <iomanip>
#include <vector>

using namespace std;
void skaityti();
void naudojimosiInstrukcija();
int main()
{
      naudojimosiInstrukcija();
  
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

// void skaityti()
// {
//     vector<string> galimiFailai = {"pirmas.txt", "antras.txt", "trecias.txt"};
//     int rinktis;
//     string failas;


//     //cout << "Pasirinkite faila, is kurio norite, kad butu skaitomi duomenys: \n";
//     for (const auto& file : galimiFailai) {
//         int i = 1;
//         std::cout << i << " - " << file << std::endl;
//         i++;
//     }
//     cin >> rinktis;
//     failas = galimiFailai[rinktis - 1];

// }