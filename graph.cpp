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
initGraph            : Hudayullah
Breadth First Search :
Dijkstra             : Hanif 
extractSmallest      : Hanif 
getAdjacent          : Hanif 
getDistance          : Hanif 
findNode             : Hanif 
contains             : Hanif 
getDistance          : Hanif 
printPath            : Hanif 
kalo ada function lain jangan lupa di list disini
*/

#define INF 1000000

class Node;
class Edge;

vector<Node*> allNodes;
vector<Edge*> edges;

class Node {
public:
  string name;
  Node* prev;
  int dist;

  Node(string name) : name(name), prev(NULL), dist(INF) {
    allNodes.push_back(this);
  }
};

class Edge {
public:
  Node* a;
  Node* b;
  int weight;

  Edge(Node* a, Node* b, int w) : a(a), b(b), weight(w) {
    edges.push_back(this);
  }

  bool connects(Node* n1, Node* n2) {
    return (n1 == a && n2 == b) || (n1 == b && n2 == a);
  }
};

//memeriksa apakah vektor kosong atau berisi
bool contains(vector<Node*> v, Node* n) {
  for (Node* x : v)
      if (x == n) return true;
  return false;
}

//mengembalikan daftar node yang terhubung (tetangga) dari node yang diberikan
vector<Node*> getAdjacent(Node* node) {
  vector<Node*> result;
  for (Edge* e : edges) {
    if (e->a == node && !contains(result, e->b)) result.push_back(e->b);
      else if (e->b == node && !contains(result, e->a)) result.push_back(e->a);
  }
  return result;
}

//menghitug jarak antara 2 node yang terhubung dengan edge
int getDistance(Node* a, Node* b) {
  for (Edge* e : edges)
      if (e->connects(a, b)) return e->weight;
  return INF;
}

//mengambil node dengan jarak terkecil
Node* extractSmallest(vector<Node*>& nodes) {
  int smallest = 0;
  for (int i = 1; i < nodes.size(); ++i)
    if (nodes[i]->dist < nodes[smallest]->dist) smallest = i;
  Node* result = nodes[smallest];
  nodes.erase(nodes.begin() + smallest);
  return result;
}

//mencari dan mengembalikan pointer ke node berdasarkan nama yang diberikan
Node* findNode(string name, Node* kota[], int size) {
  for (int i = 0; i < size; ++i)
    if (kota[i]->name == name) return kota[i];
  return NULL;
}

//menggunakan algoritma dijkstra untuk mencari jalur terpendek dari node awal ke node lain
void dijkstra() {
  vector<Node*> q = allNodes;
  while (!q.empty()) {
    Node* smallest = extractSmallest(q);
    vector<Node*> neighbors = getAdjacent(smallest);

    for (Node* neighbor : neighbors) {
      int alt = smallest->dist + getDistance(smallest, neighbor);
      if (alt < neighbor->dist) {
        neighbor->dist = alt;
        neighbor->prev = smallest;
      }
    }
  }
}

//buat nentuin jalur
void printPath(Node* dest) {
  if (dest == NULL) return;
  vector<string> path;
  for (Node* n = dest; n != NULL; n = n->prev)
  path.insert(path.begin(), n->name);
    
  cout << "Jalur tercepat: ";
  for (int i = 0; i < path.size(); ++i) {
    cout << path[i];
    if (i != path.size() - 1) cout << " -> ";
  }
  cout << endl;
  cout << "Total jarak: " << dest->dist << endl;
}

int **matrix;
bool **isSetMatrix;
int numOfNodes;
bool directed;
bool weighted;

void initGraph(int nodes, bool isDirected, bool isWeighted)
{
  numOfNodes = nodes;
  directed = isDirected;
  weighted = isWeighted;

  matrix = new int *[numOfNodes];
  isSetMatrix = new bool *[numOfNodes];

  for (int i = 0; i < numOfNodes; i++)
  {
    matrix[i] = new int[numOfNodes];
    isSetMatrix[i] = new bool[numOfNodes];
    for (int j = 0; j < numOfNodes; j++)
    {
      matrix[i][j] = 0;
      isSetMatrix[i][j] = false;
    }
  }
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

int main()
{
  const int jumlahKota = 15;
  Node* kota[jumlahKota];

  //membuat node dengan nama 'a' sampai 'o'
  for (int i = 0; i < jumlahKota; i++) {
    kota[i] = new Node(string(1, 'a' + i));
  }

  //inisialisasi edge
  // a - b (3), a - e (9), a - f (7)
  new Edge(kota[0], kota[1], 3);  // a - b
  new Edge(kota[0], kota[4], 9);  // a - e
  new Edge(kota[0], kota[5], 7);  // a - f

  // b - c (4), b - e (2)
  new Edge(kota[1], kota[2], 4);  // b - c
  new Edge(kota[1], kota[4], 2);  // b - e

  // c - d (8)
  new Edge(kota[2], kota[3], 8);  // c - d

  // d - i (5)
  new Edge(kota[3], kota[8], 5);  // d - i

  // e - h (7)
  new Edge(kota[4], kota[7], 7);  // e - h

  // f - g (3), f - h (2)
  new Edge(kota[5], kota[6], 3);  // f - g
  new Edge(kota[5], kota[7], 2);  // f - h

  // g - j (3)
  new Edge(kota[6], kota[9], 3);  // g - j

  // h - i (7)
  new Edge(kota[7], kota[8], 7);  // h - i

  // i - l (9)
  new Edge(kota[8], kota[11], 9); // i - l

  // j - k (8)
  new Edge(kota[9], kota[10], 8); // j - k

  // k - m (5)
  new Edge(kota[10], kota[12], 5); // k - m

  // l - o (7)
  new Edge(kota[11], kota[14], 7); // l - o

  // m - n (1)
  new Edge(kota[12], kota[13], 1); // m - n

  // o - n (7)
  new Edge(kota[14], kota[13], 7); // o - n

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

  // Input user
  string buyerName, sellerName, itemBought, alamat;
  char buyerAddress, sellerAddress;

  cout << "\nInputkan nama pembeli\t: ";
  getline(cin, buyerName);
  cout << "Inputkan apa yang dibeli: ";
  getline(cin, itemBought);
  cout << "Inputkan alamat pembeli\t: ";
  cin >> buyerAddress;
  if (!addressChecker(buyerAddress))
  {
    return 1;
  }
  cin.ignore();
  cout << "Inputkan nama penjual\t: ";
  getline(cin, sellerName);
  cout << "Inputkan alamat penjual\t: ";
  cin >> sellerAddress;
  if (!addressChecker(sellerAddress))
  {
    return 1;
  }

  Node* start = findNode(string(1, buyerAddress), kota, jumlahKota);
  Node* end = findNode(string(1, sellerAddress), kota, jumlahKota);

  if (start == NULL || end == NULL) {
    cout << "Kota tidak ditemukan.\n";
    return 1;
  }

  start->dist = 0;
  dijkstra();

  cout << "\n=== Informasi Pengiriman ===\n";
  cout << "Nama Pembeli\t: " << buyerName << endl;
  cout << "Membeli\t\t: " << itemBought << endl;
  cout << "Alamat Pembeli\t: " << buyerAddress << endl;
  cout << "Nama Penjual\t: " << sellerName << endl;
  cout << "Alamat Penjual\t: " << sellerAddress << endl;
  printPath(end);

  return 0;
}
