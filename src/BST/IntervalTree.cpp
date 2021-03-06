#include "IntervalTree.hpp"

namespace BST {
  template <typename T>
  struct IntervalTree< T > :: Node {
    int ps, maxIns, minIns;
    T data;
    Node(){
      ps = 0;
      maxIns = -INF;
      minIns = INF;
      data = T();
    };
    Node(int _ps, int _minIns, int _maxIns, T _data) {
      ps = _ps;
      minIns = _minIns;
      maxIns = _maxIns;
      data = _data;
    }
    Node operator + (Node other) const {
      return Node(ps + other.ps, 
        min(minIns, other.minIns),
        max(maxIns, other.maxIns),
        data);
    }
    void showInfo() {
      printf("{%2d, %2d, %2d}\n", ps, minIns, maxIns);
    }
  };

  template <typename T>
  void IntervalTree< T > :: build(int no, int l, int r) {
    L[no] = l;
    R[no] = r;
    if(l == r) return;
    int nxt = (no << 1), mid = (l + r) >> 1;
    build(nxt, l, mid); build(nxt + 1, mid + 1, r);
  }

  template <typename T>
  IntervalTree< T > :: IntervalTree() {
    n = (int)N;
    tr.resize(n * 4);
    lz.resize(n * 4);
    L.resize(n * 4);
    R.resize(n * 4);
    build(1, 0, n);
    updateInsert(1, 0, n, 0, T());
  };

  template <typename T>
  void IntervalTree< T > :: propagate(int no, int l, int r) {
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

  template <typename T>
  void IntervalTree< T > :: updateInsert(int no, int l, int r, int t, T data) {
    propagate(no, l, r);
    if(l == r) {
      lz[no]++;
      propagate(no, l, r);
      tr[no].data = data;
      tr[no].minIns = tr[no].ps;
      tr[no].maxIns = tr[no].ps;
      return;
    }
    int nxt = (no << 1), mid = (l + r) >> 1;
    if(t <= mid) {
      updateInsert(nxt, l, mid, t, data); 
      lz[nxt + 1]++;
    }
    else updateInsert(nxt + 1, mid + 1, r, t, data);
    propagate(nxt, l, mid);
    propagate(nxt + 1, mid + 1, r);
    tr[no] = tr[nxt] + tr[nxt + 1];
  }

  template <typename T>
  void IntervalTree< T > :: updateDelete(int no, int l, int r, int t) {
    propagate(no, l, r);
    if(l == r) {
      lz[no]--;
      propagate(no, l, r);
      tr[no].maxIns = -INF;
      tr[no].minIns = INF;
      return;
    }
    int nxt = (no << 1), mid = (l + r) >> 1;
    if(t <= mid) {
      updateDelete(nxt, l, mid, t);
      lz[nxt + 1]--;
    }
    else updateDelete(nxt + 1, mid + 1, r, t);
    propagate(nxt, l, mid);
    propagate(nxt + 1, mid + 1, r);
    tr[no] = tr[nxt] + tr[nxt + 1];
  }

  template <typename T>
  void IntervalTree< T > :: erasePush(int no, int l, int r, int t) {
    propagate(no, l, r);
    if(l == r) {
      lz[no]--;
      propagate(no, l, r);
      tr[no].maxIns = -INF;
      tr[no].minIns = INF;
      return;
    }
    int nxt = (no << 1), mid = (l + r) >> 1;
    if(t <= mid) {
      erasePush(nxt, l, mid, t); 
      lz[nxt + 1]--;
    }
    else erasePush(nxt + 1, mid + 1, r, t);
    propagate(nxt, l, mid);
    propagate(nxt + 1, mid + 1, r);
    tr[no] = tr[nxt] + tr[nxt + 1];
  }

  template <typename T>
  void IntervalTree< T > :: erasePop(int no, int l, int r, int t) {
    propagate(no, l, r);
    if(l == r) {
      lz[no]++;
      propagate(no, l, r);
      tr[no].maxIns = -INF;
      tr[no].minIns = INF;
      return;
    }
    int nxt = (no << 1), mid = (l + r) >> 1;
    if(t <= mid) {
      erasePop(nxt, l, mid, t);
      lz[nxt + 1]++;
    }
    else erasePop(nxt + 1, mid + 1, r, t);
    propagate(nxt, l, mid);
    propagate(nxt + 1, mid + 1, r);
    tr[no] = tr[nxt] + tr[nxt + 1];
  }

  template <typename T>
  int IntervalTree< T > :: getNode(int no, int l, int r, int t) {
    propagate(no, l, r);
    if(l == r) return no;
    int nxt = (no << 1), mid = (l + r) >> 1;
    if(t <= mid) return getNode(nxt, l, mid, t);
    else return getNode(nxt + 1, mid + 1, r, t);
  }

  template <typename T>
  typename IntervalTree < T > :: Node IntervalTree< T > :: getRangeNode(int no, int l, int r, int i, int j) {
    if(r < i || l > j) return Node();
    if(l >= i && r <= j) return tr[no];
    int nxt = (no << 1), mid = (l + r) >> 1;
    return getRangeNode(nxt, l, mid, i, j) + getRangeNode(nxt + 1, mid + 1, r, i, j);
  }

  template <typename T>
  void IntervalTree< T > :: showTree(int no, int l, int r) {
    propagate(no, l, r);
    //printf("%2d [%2d %2d] = ", no, l, r); tr[no].showInfo();
    if(l == r) return;
    int nxt = (no << 1), mid = (l + r) >> 1;
    showTree(nxt, l, mid); showTree(nxt + 1, mid + 1, r);
  }

  template <typename T>
  int IntervalTree< T > :: getPrefixSum(int no, int l, int r, int i) {
    propagate(no, l, r);
    if(l == r) {
      return tr[no].ps;
    } 
    int nxt = (no << 1), mid = (l + r) >> 1;
    if(i <= mid) return getPrefixSum(nxt, l, mid, i);
    else return getPrefixSum(nxt + 1, mid + 1, r, i);
  }

  template <typename T>
  void IntervalTree< T > :: updateInsert(int t, T data) {
    updateInsert(1, 0, n, t, data);
  }

  template <typename T>
  void IntervalTree< T > :: updateDelete(int i) {
    updateDelete(1, 0, n, i);
  }

  template <typename T>
  void IntervalTree< T > :: erasePush(int t) {
    erasePush(1, 0, n, t);
  }

  template <typename T>
  void IntervalTree< T > :: erasePop(int t) {
    erasePop(1, 0, n, t);
  }

  template <typename T>
  T IntervalTree< T > :: getPeak(int i, int t) { 
    t++;
    int no = getNode(1, 0, n, t);
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
    if(i < tr[no].minIns || i > tr[no].maxIns) no++;
    propagate(no, L[no], R[no]);
    while(L[no] != R[no]) {
      int nxt = (no << 1);
      propagate(nxt, L[nxt], R[nxt]);
      propagate(nxt + 1, L[nxt + 1], R[nxt + 1]);
      if(i >= tr[nxt + 1].minIns && i <= tr[nxt + 1].maxIns && L[nxt + 1] < t) no = nxt + 1;
      else if(i >= tr[nxt].minIns && i <= tr[nxt].maxIns) no = nxt;
      else assert(false);
    }
    return tr[no].data;
  }

  template <typename T>
  std::pair<int, T> IntervalTree< T > :: getPeakPair(int i, int t) { 
    t++;
    int no = getNode(1, 0, n, t);
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
    if(i < tr[no].minIns || i > tr[no].maxIns) no++;
    propagate(no, L[no], R[no]);
    while(L[no] != R[no]) {
      int nxt = (no << 1);
      propagate(nxt, L[nxt], R[nxt]);
      propagate(nxt + 1, L[nxt + 1], R[nxt + 1]);
      if(i >= tr[nxt + 1].minIns && i <= tr[nxt + 1].maxIns && L[nxt + 1] < t) no = nxt + 1;
      else if(i >= tr[nxt].minIns && i <= tr[nxt].maxIns) no = nxt;
      else assert(false);
    }
    return std::make_pair(L[no], tr[no].data);
  }

  template <typename T>
  int IntervalTree< T > :: getPrefixSum(int i) {
    return getPrefixSum(1, 0, n, i);
  }

  template <typename T>
  int IntervalTree< T > :: getSize() {
    return n;
  }

  template <typename T>
  void IntervalTree< T > :: showTree() {
    showTree(1, 1, n);
  }

};