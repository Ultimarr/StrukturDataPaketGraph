#include <iostream>
using namespace std;


int main()
{

    string buyerName;
    string sellerName;
    string itemBought;
    char buyerAddress;
    char sellerAddress;

    cout << R"(
              7            3          1
        a ------------ f ----- g ---------- m
        |\             |      / \           |
        |  \  9        |     /   \3         |5
      3 |    ----      |    /2    \     8   |
        |       |  2   |   /       j ------ k
        b ----- e ---- h----------/         |
        |       |      |      5             |
      4 |       |2     |7                   |9
        |  8    |   5  |   7      9      7  |
        c ----- d ---- i ---- l ----- o --- n
    )";

    cout << "\nInputkan nama pembeli\t: ";
    getline(cin, buyerName);
    cout << "Inputkan apa yang dibeli: ";
    getline(cin, itemBought);
    cout << "Inputkan alamat pembeli\t: ";
    cin >> buyerAddress;
    cin.ignore();
    cout << "Inputkan nama penjual\t: ";
    getline(cin, sellerName);
    cout << "Inputkan alamat penjual\t: ";
    cin >> sellerAddress;

    cout << "\nBerikut adalah pengisian data: \n";
    cout << "Nama Pembeli\t: " << buyerName << endl;
    cout << "Membeli\t\t: " << itemBought << endl;
    cout << "Alamat Pembeli\t: " << buyerAddress << endl;
    cout << "Nama Penjual\t: " << sellerName << endl;
    cout << "Alamat Penjual\t: " << sellerAddress << endl;

    return 0;
}
