#include <iostream>
#include <fstream>
#include <vector>

using namespace std;


// Vertex: vector of neighbours (derivation) + guild
struct Vertex : vector<int> {
  Vertex(): guild('N') { }
  char guild;
};

typedef vector<Vertex> Graph;


int main(int argc, char **argv) {
  if(argc != 3) {
    cerr << "Usage: program TEST ANSWER\n";
    return 1;
  }
  
  // read test data
  ifstream test(argv[1]);
  int n, m;
  test >> n >> m;
  Graph G(n);
  for(int i = 0; i < m; i++) {
    int a, b;
    test >> a >> b;
    a--; b--; // 1-indexing -> 0-indexing
    G[a].push_back(b);
    G[b].push_back(a);
  }
  test.close();
  
  // check for isolated vertices
  bool nope = false;
  for(int v = 0; v < n; v++) {
    if(G[v].empty()) {
      nope = true;
      break;
    }
  }
  
  // read the answer
  ifstream answer(argv[2]);
  string w;
  answer >> w;
  
  // analyze yes/no
  if(nope and w == "NIE") {
    cout << "Correct.\n";
    return 0;
  } else if((nope and w != "NIE") or ((not nope) and w != "TAK")) {
    cout << "Wrong answer (incorrect first word).\n";
    return 1;
  }
  
  // read the guilds
  for(int v = 0; v < n; v++) {
    string t;
    answer >> t;
    G[v].guild = t[0];
  }
  
  // check the condition
  for(int v = 0; v < n; v++) {
    bool k = (G[v].guild == 'K');
    bool s = (G[v].guild == 'S');
    for(size_t i = 0; i < G[v].size(); i++) {
      int u = G[v][i];
      k = (k or (G[u].guild == 'K'));
      s = (s or (G[u].guild == 'S'));
    }
    if(not (s and k)) {
      cout << "Wrong answer (failed conditions for city #" << v+1 << ").\n";
      return 1;
    }
  }
  
  answer.close();
  
  cout << "Correct.\n";
  return 0;
}
