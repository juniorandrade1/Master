#include <bits/stdc++.h>
#include "../BST/Treap.cpp"

using namespace std;

#define INF 0x3f3f3f3f

const int N = (int)2e5 + 1;

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
    n = N;
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
    map< int, int > type;
    PartialPriorityQueue(){
    };
    void insertPush(int t, T data) {
      int tl = bridges.getLastBridge(t);
      nqnow.insert(t, data);
      type[t] = 2;
      bridges.update(t, 1);
      pair<T, int> add = nqnow.getMaximumValueAfter(tl);
      nqnow.erase(add.second);
      qnow.insert(add.second, add.first);
      type[add.second] = 1;
      bridges.update(add.second, -1);
    }
    void insertPop(int t) {
      type[t] = 3;
      int tl = bridges.getNextBridge(t);
      bridges.update(t, -1);
      pair<T, int> rem = qnow.getMinimumValueBefore(tl);
      qnow.erase(rem.second);
      nqnow.insert(rem.second, rem.first);
      bridges.update(rem.second, 1);
      type[rem.second] = 2;
    }
    void removePush(int t) {
      assert(type[t] == 1 || type[t] == 2);
      if(type[t] == 1) {    
        qnow.erase(t);
        type.erase(t);
      }
      else {
        int tl = bridges.getNextBridge(t);
        pair<T, int> add = qnow.getMinimumValueBefore(tl);
        qnow.erase(add.second);
        nqnow.insert(add.second, add.first);
        type[add.second] = 2;
        bridges.update(add.second, 1);
        nqnow.erase(t);
        bridges.update(t, -1);
        type.erase(t);
      }
    }
    void removePop(int t) {
      assert(type[t] == 3);

      bridges.update(t, 1);
      int tl = bridges.getLastBridge(t);
      pair<T, int> add = nqnow.getMaximumValueAfter(tl);
      nqnow.erase(add.second);
      qnow.insert(add.second, add.first);
      type[add.second] = 1;
      bridges.update(add.second, -1);

      type.erase(t);
      return;
    }
    T getPeak() {
      return qnow.getMinimumValue().first;
    }
  };

  template <typename T> 
  class FullPriorityQueue {
    struct Operation {
      int t;
      int op;
      T data;
      Operation(){};
      Operation(int _t, int _op, T _data) {
        t = _t;
        op = _op;
        data = _data;
      }
      bool operator < (Operation o) {
        if(t != o.t) return t < o.t;
        if(op != o.op) return op < o.op;
        return data < o.data;
      }
    };
  public:
    int m;
    int b;
    vector< PartialPriorityQueue< T > > p;
    multiset< Operation > all;
    FullPriorityQueue(int _m) {
      m = _m;
      b = sqrt(m);
      p.resize((m + b - 1) / b);
    }
    void insertPush(int t, T data) {
      int st = t / b;
      for(int i = st + 1; i < p.size(); ++i) p[i].insertPush(t, data);
      all.insert(Operation(t, 0, data));
    }
    void insertPop(int t) {
      int st = t / b;
      for(int i = st + 1; i < p.size(); ++i) p[i].insertPop(t);
      all.insert(Operation(t, 0, -1));
    }
    void removePush(int t, T data) {
      int st = t / b;
      for(int i = st + 1; i < p.size(); ++i) p[i].removePush(t);
      all.erase(all.find(Operation(t, data, 0)));
    }
    void removePop(int t) {
      int st = t / b;
      for(int i = st + 1; i < p.size(); ++i) p[i].removePop(t);
      all.erase(all.find(Operation(t, 0, -1)));
    }
    T getPeak(int t) {
      int st = t / b;
      //Get operations between last bucket and t
      vector< Operation > op;
      typename multiset< Operation >::iterator it = lower_bound(all.begin(), all.end(), Operation(st * b, 0, 0));
      while(it != all.end() && it->t <= t) {
        op.emplace_back(*it);
        it++;
      }
      //Make operations between st * b and t
      for(int i = 0; i < (int)op.size(); ++i) {
        if(op[i].op == 0) p[st].insertPush(op[i].t);
        else if(op[i].op == 1) p[st].insertPop(op[i].t);
      }
      T peak = p[st].getPeak();
      //Rollback checkpoint 
      reverse(op.begin(), op.end());
      for(int i = 0; i < (int)op.size(); ++i) {
        if(op[i].op == 0) p[st].removePush(op[i].t);
        else if(op[i].op == 1) p[st].removePop(op[i].t);
      }
      return peak;
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
    void removePush(int t) {
      auto f = all.lower_bound(make_pair(t, make_pair(-1, -1)));
      assert(f->first == t);
      all.erase(f);
    }
    void removePop(int t) {
      auto f = all.lower_bound(make_pair(t, make_pair(-1, -1)));
      assert(f->first == t);
      all.erase(f);
    }
    T getPeak() {
      multiset< T > qnow;
      for(typename multiset< pair<int, pair<int, T> > > :: iterator it = all.begin(); it != all.end(); it++) {
        pair<int, pair<int, T> > foo = *it;
        if(foo.second.first == 1) qnow.insert(foo.second.second);
        else {
          qnow.erase(qnow.begin());
        }
      }
      return *qnow.begin();
    }
  };
  template < typename T >
  class FullPriorityQueue {
  public:
    multiset< pair<int, pair<int, T> > > all;
    void insertPush(int t, T data) {
      all.insert(make_pair(t, make_pair(1, data)));
    }
    void insertPop(int t) {
      all.insert(make_pair(t, make_pair(-1, T())));
    }
    void removePush(int t) {
      auto f = all.lower_bound(make_pair(t, make_pair(-1, -1)));
      assert(f->first == t);
      all.erase(f);
    }
    void removePop(int t) {
      auto f = all.lower_bound(make_pair(t, make_pair(-1, -1)));
      assert(f->first == t);
      all.erase(f);
    }
    T getPeak(int t) {
      multiset< T > qnow;
      for(typename multiset< pair<int, pair<int, T> > > :: iterator it = all.begin(); it != all.end(); it++) {
        pair<int, pair<int, T> > foo = *it;
        if(foo.first > t) continue;
        if(foo.second.first == 1) qnow.insert(foo.second.second);
        else {
          qnow.erase(qnow.begin());
        }
      }
      return *qnow.begin();
    }
  };
};
