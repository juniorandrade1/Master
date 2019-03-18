#include <bits/stdc++.h>
#include "../BST/ABTree.cpp"

namespace Retroactivity {
  template<typename T>
  class PartialStack {
  public:
    BST::ABTree< T > v;
    void Insert_Push(int t, const T &x) {
      v.updateInsert(t, x);
    }
    void Insert_Pop(int t) {
      v.updateDelete(t);
    }
    void Delete_Push(int t) {
    }
    void Delete_Pop(int t) {
    }
    T peak() {
      int n = v.getSize();
      return v.getPeak(v.getPrefixSum(n));
    }
    int getSize() {
      int n = v.getSize();
      return v.getPrefixSum(n);
    }
  };
}

namespace Brute {
  template<typename T>
  class PartialStack {
  public:
    set< pair< int, T > > v;
    vector< T > aux;
    void Insert_Push(int t, const T &x) {
      v.insert(make_pair(t, x));
    }
    void Insert_Pop(int t) {
      v.insert(make_pair(t, -INF));
    }
    void Delete_Push(int t) {
    }
    void Delete_Pop(int t) {
    }
    T peak() {
      aux.clear();
      for(typename set< pair< int, T > > :: iterator it = v.begin(); it != v.end(); it++) {
        if(it->second == -INF) aux.pop_back();
        else aux.push_back(it->second);
      }
      return aux[(int)aux.size() - 1];
    }
  };
};