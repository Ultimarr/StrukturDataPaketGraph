#include <iostream>
#include <vector>
#include <string>
using namespace std;

/*
Dibuat oleh:
KELOMPOK 8
1. Hudayullah Ayasya Khoirizal
2. Muhammad Hanif Awliya
3. Aisya Citra Hapsari

main                 : Hudayullah
addressChecker       : Hudayullah
getCityName          : Hudayullah
Dijkstra             : Hanif
extractSmallest      : Hanif
getAdjacent          : Hanif
getDistance          : Hanif
findNode             : Hanif
contains             : Hanif
getDistance          : Hanif
printPath            : Hanif & Hudayullah
 kalo ada function lain jangan lupa di list disini
*/

#define INF 1000000

string getCityName(char code)
{
    string cityNames[15] = {
        "Bandung",     // a
        "Bekasi",      // b
        "Bogor",       // c
        "Cimahi",      // d
        "Cirebon",     // e
        "Depok",       // f
        "Garut",       // g
        "Indramayu",   // h
        "Karawang",    // i
        "Majalengka",  // j
        "Purwakarta",  // k
        "Tasikmalaya", // l
        "Banjar",      // m
        "Sukabumi",    // n
        "Subang"       // o
    };
    return cityNames[code - 'a'];
}

bool addressChecker(char Address)
{
    if (Address < 'a' || Address > 'o')
    {
        cout << "Alamat tidak valid" << endl;
        return false;
    }
    return true;
}

class Node;
class Edge;

vector<Node *> allNodes;
vector<Edge *> edges;

class Node
{
public:
    string name;
    Node *prev;
    int dist;

    Node(string name) : name(name), prev(NULL), dist(INF)
    {
        allNodes.push_back(this);
    }
};

class Edge
{
public:
    Node *a;
    Node *b;
    int weight;

    Edge(Node *a, Node *b, int w) : a(a), b(b), weight(w)
    {
        edges.push_back(this);
    }

    bool connects(Node *n1, Node *n2)
    {
        return (n1 == a && n2 == b) || (n1 == b && n2 == a);
    }
};

bool contains(vector<Node *> v, Node *n)
{
    for (Node *x : v)
        if (x == n)
            return true;
    return false;
}

vector<Node *> getAdjacent(Node *node)
{
    vector<Node *> result;
    for (Edge *e : edges)
    {
        if (e->a == node && !contains(result, e->b))
            result.push_back(e->b);
        else if (e->b == node && !contains(result, e->a))
            result.push_back(e->a);
    }
    return result;
}

int getDistance(Node *a, Node *b)
{
    for (Edge *e : edges)
        if (e->connects(a, b))
            return e->weight;
    return INF;
}

Node *extractSmallest(vector<Node *> &nodes)
{
    int smallest = 0;
    for (int i = 1; i < nodes.size(); ++i)
        if (nodes[i]->dist < nodes[smallest]->dist)
            smallest = i;
    Node *result = nodes[smallest];
    nodes.erase(nodes.begin() + smallest);
    return result;
}

Node *findNode(string name, Node *kota[], int size)
{
    for (int i = 0; i < size; ++i)
        if (kota[i]->name == name)
            return kota[i];
    return NULL;
}

void dijkstra()
{
    vector<Node *> q = allNodes;
    while (!q.empty())
    {
        Node *smallest = extractSmallest(q);
        vector<Node *> neighbors = getAdjacent(smallest);

        for (Node *neighbor : neighbors)
        {
            int alt = smallest->dist + getDistance(smallest, neighbor);
            if (alt < neighbor->dist)
            {
                neighbor->dist = alt;
                neighbor->prev = smallest;
            }
        }
    }
}

void printPath(Node *dest, string item, string seller, string buyer)
{
    if (dest == NULL)
        return;
    vector<Node *> path;
    for (Node *n = dest; n != NULL; n = n->prev)
        path.insert(path.begin(), n);

    cout << "\n=== Status Pengiriman ===\n";
    cout << "Paket berisi " << item << ", dikirim dari kota " << getCityName(path[0]->name[0]) << " oleh " << seller << endl;
    for (size_t i = 1; i < path.size(); ++i)
    {
        cout << "Paket berpindah dari kota " << getCityName(path[i - 1]->name[0]) << " ke kota " << getCityName(path[i]->name[0]) << endl;
    }
    cout << "Paket berhasil dikirim ke " << buyer << endl;
    cout << "Total jarak: " << dest->dist << endl;
}


int main()
{
    const int jumlahKota = 15;
    Node *kota[jumlahKota];

    for (int i = 0; i < jumlahKota; i++)
    {
        kota[i] = new Node(string(1, 'a' + i));
    }

    new Edge(kota[0], kota[1], 3);
    new Edge(kota[0], kota[4], 9);
    new Edge(kota[0], kota[5], 7);
    new Edge(kota[1], kota[2], 4);
    new Edge(kota[1], kota[4], 2);
    new Edge(kota[2], kota[3], 8);
    new Edge(kota[3], kota[8], 5);
    new Edge(kota[4], kota[7], 7);
    new Edge(kota[5], kota[6], 3);
    new Edge(kota[5], kota[7], 2);
    new Edge(kota[6], kota[9], 3);
    new Edge(kota[7], kota[8], 7);
    new Edge(kota[8], kota[11], 9);
    new Edge(kota[9], kota[10], 8);
    new Edge(kota[10], kota[12], 5);
    new Edge(kota[11], kota[14], 7);
    new Edge(kota[12], kota[13], 1);
    new Edge(kota[14], kota[13], 7);

    string buyerName, sellerName, itemBought;
    char buyerAddress, sellerAddress;
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

    cout << "\n\nDaftar Kota: \n";
    cout << "\na: Bandung";
    cout << "\nb: Bekasi";
    cout << "\nc: Bogor";
    cout << "\nd: Cimahi";
    cout << "\ne: Cirebon";
    cout << "\nf: Depok";
    cout << "\ng: Garut";
    cout << "\nh: Indramayu";
    cout << "\ni: Karawang";
    cout << "\nj: Majalengka";
    cout << "\nk: Purwakarta";
    cout << "\nl: Tasikmalaya";
    cout << "\nm: Banjar";
    cout << "\nn: Sukabumi";
    cout << "\no: Subang";

    cout << "\nInputkan nama pembeli\t: ";
    getline(cin, buyerName);
    cout << "Inputkan apa yang dibeli: ";
    getline(cin, itemBought);
    cout << "Inputkan alamat pembeli\t: ";
    cin >> buyerAddress;
    if (!addressChecker(buyerAddress))
        return 1;
    cin.ignore();
    cout << "Inputkan nama penjual\t: ";
    getline(cin, sellerName);
    cout << "Inputkan alamat penjual\t: ";
    cin >> sellerAddress;
    if (!addressChecker(sellerAddress))
        return 1;

    Node *start = findNode(string(1, sellerAddress), kota, jumlahKota);
    Node *end = findNode(string(1, buyerAddress), kota, jumlahKota);

    if (start == NULL || end == NULL)
    {
        cout << "Kota tidak ditemukan.\n";
        return 1;
    }

    start->dist = 0;
    dijkstra();

    cout << "\n=== Informasi Pengiriman ===\n";
    cout << "Nama Pembeli\t: " << buyerName << endl;
    cout << "Membeli\t\t: " << itemBought << endl;
    cout << "Alamat Pembeli\t: " << getCityName(buyerAddress) << endl;
    cout << "Nama Penjual\t: " << sellerName << endl;
    cout << "Alamat Penjual\t: " << getCityName(sellerAddress) << endl;
    printPath(end, itemBought, sellerName, buyerName);

    return 0;
}
