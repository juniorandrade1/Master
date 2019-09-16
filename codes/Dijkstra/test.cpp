#include <bits/stdc++.h>
#include "Dijkstra.cpp"

using namespace std;

int main() {
  int n, m; scanf("%d %d", &n, &m);
  FastBruteForce::Dijkstra< long long > g(n, 0);
  for(int i = 0; i < m; ++i) {
    int x, y, w; scanf("%d %d %d", &x, &y, &w); 
    g.addEdgeDynamic(x - 1, y - 1, w);
  }
  for(int i = 0; i < n; ++i) {
    printf("%lld ", g.dis[i]);
  }
  printf("\n");
  return 0;
}