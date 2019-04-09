#include <bits/stdc++.h>
#include "../BST/Treap.cpp"

using namespace std;

#define INF 0x3f3f3f3f

template <typename T>
class IntervalTreeMax {
public:
  vector< T > tr;
  int n;
  IntervalTreeMax() {
    n = 200000;
    tr.resize(4 * n, numeric_limits< T >::min());
  }
  IntervalTreeMax(int _n) {
    n = _n;
    tr.resize(4 * n, numeric_limits< T >::min());
  }
  void update(int no, int l, int r, int i, T val) {
    if(l == r) {
      tr[no] = val;
      return;
    }
    int nxt = (no << 1), mid = (l + r) >> 1;
    if(i <= mid) update(nxt, l, mid, i, val);
    else update(nxt + 1, mid + 1, r, i, val);
    tr[no] = max(tr[nxt], tr[nxt + 1]);
  }
  T query(int no, int l, int r, int i, int j) {
    if(r < i || l > j) return numeric_limits< T >::min();
    if(l >= i && r <= j) return tr[no];
    int nxt = (no << 1), mid = (l + r) >> 1;
    return max(query(nxt, l, mid, i, j), query(nxt + 1, mid + 1, r, i, j));
  }
  T getAfter(int tl) {
    return query(1, 1, n, tl, n);
  }
  void update(int i, T data) {
    update(1, 1, n, i, data);
  }
};

template <typename T>
class IntervalTreeSum {
  struct Node {
    int ps, maxIns, minIns;
    Node(){
      ps = 0;
      maxIns = -INF;
      minIns = INF;
    };
    Node(int _ps, int _minIns, int _maxIns) {
      ps = _ps;
      minIns = _minIns;
      maxIns = _maxIns;
    }
    Node operator + (Node other) const {
      return Node(ps + other.ps, 
        min(minIns, other.minIns),
        max(maxIns, other.maxIns));
    }
    void showInfo() {
      printf("{%2d, %2d, %2d}\n", ps, minIns, maxIns);
    }
  };
public:
  vector< Node > tr;
  vector< T > lz;
  vector< int > L, R;
  vector< T > leaf;
  int n;
  void build(int no, int l, int r) {
    L[no] = l;
    R[no] = r;
    if(l == r) return;
    int nxt = (no << 1), mid = (l + r) >> 1;
    build(nxt, l, mid); build(nxt + 1, mid + 1, r);
  }
  IntervalTreeSum(){
    n = (int)200000;
    tr.resize(n * 4);
    lz.resize(n * 4);
    L.resize(n * 4);
    R.resize(n * 4);
    leaf.resize(n);
    build(1, 1, n);
  };
  void propagate(int no, int l, int r) {
    if(!lz[no]) return;
    tr[no].ps += (r - l + 1) * lz[no];
    tr[no].minIns += lz[no];
    tr[no].maxIns += lz[no];
    if(l != r) {
      int nxt = (no << 1), mid = (l + r) >> 1;
      lz[nxt] += lz[no];
      lz[nxt + 1] += lz[no];
    }
    lz[no] = 0;
  }
  void update(int no, int l, int r, int i, int j, T inc) {
    propagate(no, l, r);  
    if(r < i || l > j) return;
    if(l >= i && r <= j) {
      lz[no] += inc;
      propagate(no, l, r);
      return;
    }
    int nxt = (no << 1), mid = (l + r) >> 1;
    update(nxt, l, mid, i, j, inc); update(nxt + 1, mid + 1, r, i, j, inc);
    tr[no] = tr[nxt] + tr[nxt + 1];
  }
  int getNode(int no, int l, int r, int t) {
    propagate(no, l, r);
    if(l == r) return no;
    int nxt = (no << 1), mid = (l + r) >> 1;
    if(t <= mid) return getNode(nxt, l, mid, t);
    else return getNode(nxt + 1, mid + 1, r, t);
  }
  void showTree(int no, int l, int r) {
    propagate(no, l, r);
    if(l == r) return;
    int nxt = (no << 1), mid = (l + r) >> 1;
    showTree(nxt, l, mid); showTree(nxt + 1, mid + 1, r);
  }
  int getPrefixSum(int no, int l, int r, int i) {
    propagate(no, l, r);
    if(l == r) return tr[no].ps;
    int nxt = (no << 1), mid = (l + r) >> 1;
    if(i <= mid) return getPrefixSum(nxt, l, mid, i);
    else return getPrefixSum(nxt + 1, mid + 1, r, i);
  }
  void update(int t, T data) {
    T up = data - leaf[t];
    leaf[t] = data;
    update(1, 1, n, 1, t, up);
  }
  T getPeak(int i, int t) {
    t++;
    int no = getNode(1, 1, n, t);
    while(no != 1) {
      int d = (no & 1);
      no >>= 1;
      int nxt = (no << 1);
      propagate(nxt, L[nxt], R[nxt]);
      propagate(nxt + 1, L[nxt + 1], R[nxt + 1]);
      if(i >= tr[nxt].minIns && i <= tr[nxt].maxIns && d) {
        break;
      }
    }
    no <<= 1;
    propagate(no, L[no], R[no]);
    while(L[no] != R[no]) {
      int nxt = (no << 1);
      propagate(nxt, L[nxt], R[nxt]);
      propagate(nxt + 1, L[nxt + 1], R[nxt + 1]);
      if(i >= tr[nxt + 1].minIns && i <= tr[nxt + 1].maxIns) no = nxt + 1;
      else no = nxt;
    }
    return tr[no].data;
  }
  int getPrefixSum(int i) {
    return getPrefixSum(1, 1, n, i);
  }
  int getSize() {
    return n;
  }
  void showTree() {
    showTree(1, 1, n);
  }
};

namespace Retroactivity {
  template <typename T>
  class PartialPriorityQueue {
  public:
    Treap< T, bool > qnow;
    IntervalTreeMax< T > nqnow;
    IntervalTreeSum< int > bridges;
    void insertPush(int t, T data) {
      nqnow.insert(t, data);
      bridges.update(t, 1);
      int tl = bridges.getPeak(0, t);
      T add = nqnow.getAfter(tl);
      qnow.insert(add, 1);
    }
    void insertPop(int t) {

    }
    T getPeak() {
      return qnow.getMinimum();
    }
  };
};

namespace Brute {
  template <typename T>
  class PartialPriorityQueue {
  public:
    multiset< pair<int, pair<int, T> > > all;
    void insertPush(int t, T data) {
      all.insert(make_pair(t, make_pair(1, data)));
    }
    void insertPop(int t) {
      all.insert(make_pair(t, make_pair(-1, T())));
    }
    T getPeak() {
      multiset< T > qnow;
      for(typename multiset< pair<int, pair<int, T> > > :: iterator it = all.begin(); it != all.end(); it++) {
        pair<int, pair<int, T> > foo = *it;
        if(foo.second.first == 1) qnow.insert(foo.second.second);
        else qnow.erase(qnow.begin());
      }
      return *qnow.begin();
    }
  };
};

int main() {
  Brute::PartialPriorityQueue< int > q;
  q.insertPush(1, 5);
  q.insertPush(3, 7);
  q.insertPop(2);
  printf("%d\n", q.getPeak());
  return 0;
}