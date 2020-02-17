#include "IntervalTree.hpp"

template <typename T>
struct IntervalTreeSum < T > :: Node {
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


template <typename T>
int IntervalTreeSum < T > :: createNode() {
  int id = tr.size();
  tr.emplace_back(Node());
  lz.emplace_back(0);
  L.emplace_back(-1);
  R.emplace_back(-1);
  return id;  
}

template <typename T>
IntervalTreeSum < T > :: IntervalTreeSum () {
  n = N;
  createNode();
};

template <typename T>
void IntervalTreeSum < T > :: propagate(int no, int l, int r) {
  if(l != r && L[no] == -1) {
    int id = createNode();
    L[no] = id;
  }
  if(l != r && R[no] == -1) {
    int id = createNode();
    R[no] = id;
  }
  if(!lz[no]) return;
  tr[no].ps += (r - l + 1) * lz[no];
  tr[no].mn += lz[no];
  tr[no].mx += lz[no];
  if(l != r) {
    int mid = (l + r) >> 1;
    lz[L[no]] += lz[no];
    lz[R[no]] += lz[no];
  }
  lz[no] = 0;
}

template <typename T>
void IntervalTreeSum < T > :: update(int no, int l, int r, int t, int inc) {
  propagate(no, l, r);
  if(l == r) {
    lz[no] += inc;
    propagate(no, l, r);
    return;
  }
  int mid = (l + r) >> 1;
  if(t <= mid) {
    update(L[no], l, mid, t, inc); 
    lz[R[no]] += inc;
  }
  else update(R[no], mid + 1, r, t, inc);
  propagate(L[no], l, mid);
  propagate(R[no], mid + 1, r);
  tr[no] = tr[L[no]] + tr[R[no]];
}

template <typename T>
typename IntervalTreeSum < T > :: Node IntervalTreeSum < T > :: query(int no, int l, int r, int i, int j) {
  propagate(no, l, r);
  if(r < i || l > j) return Node(0, numeric_limits< T >::max(), numeric_limits< T >::min());
  if(l >= i && r <= j) return tr[no];
  int mid = (l + r) >> 1;
  return query(L[no], l, mid, i, j) + query(R[no], mid + 1, r, i, j);
}

template <typename T>
void IntervalTreeSum < T > :: showTree(int no, int l, int r) {
  propagate(no, l, r);
  if(l == r) {
    printf("%d, ", tr[no].ps);
    return;
  }
  int mid = (l + r) >> 1;
  showTree(L[no], l, mid); showTree(R[no], mid + 1, r);
}

template <typename T>
typename IntervalTreeSum < T > :: Node IntervalTreeSum < T > :: query(int l, int r) {
  return query(0, 0, n, l, r);
}

template <typename T>
void IntervalTreeSum < T > :: update(int t, T inc) {
  update(0, 0, n, t, inc);
}

template <typename T>
void IntervalTreeSum < T > :: showTree() {
  showTree(0, 0, n);
  printf("\n");
}

template <typename T>
int IntervalTreeSum < T > :: getLastBridge(int t) {
  int lo = 1, hi = t;
  while(lo < hi) {
    int md = (lo + hi + 1) >> 1;
    if(query(md, t).mn) hi = md - 1;
    else lo = md;
  }
  return lo;
}

template <typename T>
int IntervalTreeSum < T > :: getNextBridge(int t) {
  int lo = t, hi = n;
  while(lo < hi) {
    int md = (lo + hi) >> 1;
    if(query(t, md).mn) lo = md + 1;
    else hi = md;
  }
  return lo;
}