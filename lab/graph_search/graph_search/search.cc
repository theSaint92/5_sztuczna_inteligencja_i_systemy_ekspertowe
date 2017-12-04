#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <utility>
#include <algorithm>

using namespace std;


void bfs(vector< vector<int> > const &graph, char lStart, char lEnd) {
  int vStart = lStart - 'a';
  int vEnd = lEnd - 'a';
  
  vector<int> prev(graph.size(), -1);
  vector<int> dist(graph.size(), -1);
  
  queue<int> bfsQueue;
  bfsQueue.push(vStart);
  dist[vStart] = 0;
  prev[vStart] = vStart;
  
  while(!bfsQueue.empty()) {
    int v = bfsQueue.front();
    bfsQueue.pop();
    
    for(int i = 0; i < graph[v].size(); i++) {
      int u = graph[v][i];
      if(prev[u] == -1) {
        cerr << char('a' + v) << " -> " << char('a' + u) << '\n';
        bfsQueue.push(u);
        dist[u] = dist[v] + 1;
        prev[u] = v;
        /* if(u == vEnd) {
          return;
        } */
      }
    }
  }
  
  for(int i = 0; i < graph.size(); i++) {
    cerr << char('a' + i) << ": ";
    cerr << "dist=" << dist[i] << ", ";
    cerr << "prev=" << (prev[i] == -1 ? '-' : char('a' + prev[i])) << ", ";
    cerr << '\n';
  }
  
  // expample: generate and print path to the final state
  if(prev[vEnd] != -1) { // vEnd found
    vector<char> path;
    path.push_back('a' + vEnd);
    int v = vEnd;
    while(prev[v] != v) {
      v = prev[v];
      path.push_back('a' + v);
    }
    reverse(path.begin(), path.end());
    for(int i = 0; i < path.size(); i++) {
      if(i != 0) cout << " -> ";
      cout << path[i];
    }
    cout << '\n';
  }
  
}



struct VertexComparator {
  bool operator()(int const &u, int const &v) const {
    return u < v;
  }
};


void astar(vector< vector<int> > const &graph, char lStart, char lEnd) {
  int vStart = lStart - 'a';
  int vEnd = lEnd - 'a';
  
  vector<int> prev(graph.size(), -1);
  vector<int> dist(graph.size(), -1);
  
  priority_queue< int, vector<int>, VertexComparator > aQueue;
  aQueue.push(vStart);
  // dist[vStart] = 0;
  prev[vStart] = vStart;
  
  while(!aQueue.empty()) {
    int v = aQueue.top();
    aQueue.pop();
    
    for(int i = 0; i < graph[v].size(); i++) {
      int u = graph[v][i];
      if(prev[u] == -1) {
        cerr << char('a' + v) << " -> " << char('a' + u) << '\n';
        aQueue.push(u);
        // dist[u] = dist[v] + 1;
        prev[u] = v;
        /* if(u == vEnd) {
          return;
        } */
      }
    }
  }
  
  for(int i = 0; i < graph.size(); i++) {
    cerr << char('a' + i) << ": ";
    // cerr << "dist=" << dist[i] << ", ";
    cerr << "prev=" << (prev[i] == -1 ? '-' : char('a' + prev[i])) << ", ";
    cerr << '\n';
  }
  
}



void dfs(vector< vector<int> > const &graph, int v, int vEnd, vector<int> &prev) {
  
  if(v == vEnd) {
    cerr << "Vertex " << char('a' + vEnd) << " reached!\n";
    return;
  }
  
  for(int i = 0; i < graph[v].size(); i++) {
    int u = graph[v][i];
    if(prev[u] == -1) {
      cerr << char('a' + v) << " -> " << char('a' + u) << '\n';
      prev[u] = v;
      dfs(graph, u, vEnd, prev);
    }
  }
  
}


void dfs(vector< vector<int> > const &graph, char lStart, char lEnd) {
  int vStart = lStart - 'a';
  int vEnd = lEnd - 'a';
  
  vector<int> prev(graph.size(), -1);
  prev[vStart] = vStart;
  
  dfs(graph, vStart, vEnd, prev);
  
  for(int i = 0; i < graph.size(); i++) {
    cerr << char('a' + i) << ": ";
    cerr << "prev=" << (prev[i] == -1 ? '-' : char('a' + prev[i])) << ", ";
    cerr << '\n';
  }
}


void dfs_iter(vector< vector<int> > const &graph, char lStart, char lEnd) {
  int vStart = lStart - 'a';
  int vEnd = lEnd - 'a';
  
  stack< pair<int, int> > dfsStack; // stack of pairs (vertex, neigbour_id)
  
  vector<int> prev(graph.size(), -1);
  prev[vStart] = vStart;
  dfsStack.push(make_pair(vStart, 0));
  
  while(!dfsStack.empty()) {
    int v = dfsStack.top().first;
    int i = dfsStack.top().second;
    
    if(v == vEnd) {
      cerr << "Vertex " << char('a' + vEnd) << " reached!\n";
      break;
    }
    
    if(i < graph[v].size()) {
      int u = graph[v][i];
      dfsStack.top().second++;
      
      if(prev[u] == -1) {
        cerr << char('a' + v) << " -> " << char('a' + u) << '\n';
        prev[u] = v;
        dfsStack.push(make_pair(u, 0));
      }
    } else {
      dfsStack.pop();
    }
    
  }
  
  
  for(int i = 0; i < graph.size(); i++) {
    cerr << char('a' + i) << ": ";
    cerr << "prev=" << (prev[i] == -1 ? '-' : char('a' + prev[i])) << ", ";
    cerr << '\n';
  }
}



int main() {
  
  // tablica nxn z wartościami logicznymi - dla grafów gęstych
  // vector< vector<bool> > + ustalon rozmiar
  
  // tablica list sąsiadów - dla grafów rzadkich, które się nie zmieniają
  // vector< vector<int> >
  
  // tablica drzew przeszukiwań - grafy rzadkie, które się zmieniają
  // vector< set<int> >
  
  vector< vector<int> > graph;
  int vertices, edges;
  cin >> vertices >> edges;
  
  graph.resize(vertices);
  
  for(int i = 0; i < edges; i++) {
    char l1, l2;
    cin >> l1 >> l2;
    int v1 = l1 - 'a';
    int v2 = l2 - 'a';
    graph[v1].push_back(v2);
    graph[v2].push_back(v1);
  }
  
  // debug
  for(int i = 0; i < vertices; i++) {
    cerr << char('a' + i) << ": ";
    for(int j = 0; j < graph[i].size(); j++) {
      if(j != 0) cerr << ", ";
      cerr << char('a' + graph[i][j]);
    }
    cerr << '\n';
  }
  
  bfs(graph, 'a', 'i');
  
  return 0;
}









