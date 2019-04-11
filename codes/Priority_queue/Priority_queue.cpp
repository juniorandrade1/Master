#include <bits/stdc++.h>
#include "../BST/Treap.cpp"

using namespace std;

#define INF 0x3f3f3f3f

template <typename T>
class IntervalTreeSum {
  struct Node {
    T ps, mx, mn;
    Node(){
      ps = mx = mn = 0;
    };
    Node(int _ps, int _mn, int _mx) {
      ps = _ps;
      mn = _mn;
      mx = _mx;
    }
    Node operator + (Node other) const {
      return Node(ps + other.ps, 
        min(mn, other.mn),
        max(mx, other.mx));
    }
    void showInfo() {
      printf("{%2d, %2d, %2d}\n", ps, mn, mx);
    }
  };
public:
  vector< Node > tr;
  vector< int > lz;
  int n;
  IntervalTreeSum(){
    n = (int)200000;
    tr.resize(n * 4);
    lz.resize(n * 4);
  };
  void propagate(int no, int l, int r) {
    if(!lz[no]) return;
    tr[no].ps += (r - l + 1) * lz[no];
    tr[no].mn += lz[no];
    tr[no].mx += lz[no];
    if(l != r) {
      int nxt = (no << 1), mid = (l + r) >> 1;
      lz[nxt] += lz[no];
      lz[nxt + 1] += lz[no];
    }
    lz[no] = 0;
  }
  void update(int no, int l, int r, int t, int inc) {
    propagate(no, l, r);
    if(l == r) {
      lz[no] += inc;
      propagate(no, l, r);
      return;
    }
    int nxt = (no << 1), mid = (l + r) >> 1;
    if(t <= mid) {
      update(nxt, l, mid, t, inc); 
      lz[nxt + 1] += inc;
    }
    else update(nxt + 1, mid + 1, r, t, inc);
    propagate(nxt, l, mid);
    propagate(nxt + 1, mid + 1, r);
    tr[no] = tr[nxt] + tr[nxt + 1];
  }
  Node query(int no, int l, int r, int i, int j) {
    propagate(no, l, r);
    if(r < i || l > j) return Node(0, numeric_limits< T >::max(), numeric_limits< T >::min());
    if(l >= i && r <= j) return tr[no];
    int nxt = (no << 1), mid = (l + r) >> 1;
    return query(nxt, l, mid, i, j) + query(nxt + 1, mid + 1, r, i, j);
  }
  void showTree(int no, int l, int r) {
    propagate(no, l, r);
    if(l == r) {
      printf("%d, ", tr[no].ps);
      return;
    }
    int nxt = (no << 1), mid = (l + r) >> 1;
    showTree(nxt, l, mid); showTree(nxt + 1, mid + 1, r);
  }
  void update(int t, T inc) {
    update(1, 1, n, t, inc);
  }
  Node query(int l, int r) {
    return query(1, 1, n, l, r);
  }
  void showTree() {
    showTree(1, 1, n);
    printf("\n");
  }
  int getLastBridge(int t) {
    int lo = 1, hi = t;
    while(lo < hi) {
      int md = (lo + hi + 1) >> 1;
      if(query(md, t).mn) hi = md - 1;
      else lo = md;
    }
    return lo;
  }
  int getNextBridge(int t) {
    int lo = t, hi = n;
    while(lo < hi) {
      int md = (lo + hi) >> 1;
      if(query(t, md).mn) lo = md + 1;
      else hi = md;
    }
    return lo;
  }
};

namespace Retroactivity {
  template <typename T>
  class PartialPriorityQueue {
  public:
    Treap< int, T > qnow;
    Treap< int, T > nqnow;
    IntervalTreeSum< int > bridges;
    void insertPush(int t, T data) {
      
      int tl = bridges.getLastBridge(t);
      nqnow.insert(t, data);
      bridges.update(t, 1);

      pair<T, int> add = nqnow.getMaximumValueAfter(tl);
      nqnow.erase(add.second);
      
      qnow.insert(add.second, add.first);
      bridges.update(add.second, -1);

    }
    void insertPop(int t) {

      int tl = bridges.getNextBridge(t);
      bridges.update(t, -1);
      // printf("IMP\n");
      // printf("TL %d %d\n", t, tl);
      
      pair<T, int> rem = qnow.getMinimumValueBefore(tl);
      qnow.erase(rem.second);

      
      // printf("--> %d %d\n", rem.second, rem.first);
      // printf("IMP\n");
      
      nqnow.insert(rem.second, rem.first);
      bridges.update(rem.second, 1);
      //printf("L shape = %d %d\n", rem.second, t);
    }
    T getPeak() {
      //printf("Retroactivity\n");
      // vector< int > allIn = qnow.getTree();

      // //sort(allIn.begin(), allIn.end());
      // for(int i = 0; i < allIn.size(); ++i) printf("%d ", allIn[i]);
      // printf("\n\n");

      // vector< int > allRem = nqnow.getTree();
      // sort(allRem.begin(), allRem.end());
      // for(int i = 0; i < allRem.size(); ++i) printf("%d ", allRem[i]);
      // printf("\n----------------------\n\n");
      return qnow.getMinimumValue().first;
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
      // printf("BRUTE\n");
      // vector< int > oi;
      for(typename multiset< pair<int, pair<int, T> > > :: iterator it = all.begin(); it != all.end(); it++) {
        pair<int, pair<int, T> > foo = *it;
        if(foo.second.first == 1) qnow.insert(foo.second.second);
        else {
          //oi.push_back(*qnow.begin());
          qnow.erase(qnow.begin());
        }
      }
      // sort(oi.begin(), oi.end());
      // for(int i = 0; i < oi.size(); ++i) printf("%d ", oi[i]);
      // printf("\n________________________\n\n\n");
      return *qnow.begin();
    }
  };
};
