#include <bits/stdc++.h>

using namespace std;

#define INF 0x3f3f3f3f

namespace BST {
  template <typename T>
  class IntervalTree {
    struct Node {
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
      Node operator + (int x) const {
        return Node(ps + x, minIns + x, maxIns + x, data);
      }
      void showInfo() {
        printf("{%2d, %2d, %2d}\n", ps, minIns, maxIns);
      }
    };
  public:
    vector< Node > tr;
    vector< int > lz;
    vector< int > L, R;
    int n;
    void build(int no, int l, int r) {
      L[no] = l;
      R[no] = r;
      if(l == r) return;
      int nxt = (no << 1), mid = (l + r) >> 1;
      build(nxt, l, mid); build(nxt + 1, mid + 1, r);
    }
    IntervalTree(){
      n = (int)3e5;
      tr.resize(n * 4);
      lz.resize(n * 4);
      L.resize(n * 4);
      R.resize(n * 4);
      build(1, 1, n);
    };
    void propagate(int no, int l, int r) {
      if(!lz[no]) return;
      tr[no] = tr[no] + lz[no];
      if(l != r) {
        int nxt = (no << 1), mid = (l + r) >> 1;
        lz[nxt] += lz[no];
        lz[nxt + 1] += lz[no];
      }
      lz[no] = 0;
    }
    void updateInsert(int no, int l, int r, int t, T data) {
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
    void updateDelete(int no, int l, int r, int t) {
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
    T getPeak(int no, int l, int r, int i) {
      propagate(no, l, r);
      if(l == r) return tr[no].data;
      int nxt = (no << 1), mid = (l + r) >> 1;
      propagate(nxt, l, mid);
      propagate(nxt + 1, mid + 1, r);
      if(i >= tr[nxt + 1].minIns && i <= tr[nxt + 1].maxIns) return getPeak(nxt + 1, mid + 1, r, i);
      else return getPeak(nxt, l, mid, i);
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
      //printf("%2d [%2d %2d] = ", no, l, r); tr[no].showInfo();
      if(l == r) return;
      int nxt = (no << 1), mid = (l + r) >> 1;
      showTree(nxt, l, mid); showTree(nxt + 1, mid + 1, r);
    }
    int getPrefixSum(int no, int l, int r, int i) {
      propagate(no, l, r);
      if(l == r) {
        return tr[no].ps;
      } 
      int nxt = (no << 1), mid = (l + r) >> 1;
      if(i <= mid) return getPrefixSum(nxt, l, mid, i);
      else return getPrefixSum(nxt + 1, mid + 1, r, i);
    }
    void updateInsert(int t, T data) {
      updateInsert(1, 1, n, t, data);
    }
    void updateDelete(int i) {
      updateDelete(1, 1, n, i);
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
};