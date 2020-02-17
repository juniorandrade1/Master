#include "PrioritySearchTree.hpp"

namespace BST {
  //private functions
  template <typename K, typename V>
  int DynamicPST< K, V > :: getQtd(pPSTNode p) {
    return p ? p->qtd : 0;
  }

  template <typename K, typename V>
  int DynamicPST< K, V > :: getLeftRange(pPSTNode p) {
    return p ? p->rangeLeft : numeric_limits< int > :: max();
  }

  template <typename K, typename V>
  int DynamicPST< K, V > :: getRightRange(pPSTNode p) {
    return p ? p->rangeRight : numeric_limits< int > :: min();
  }

  template <typename K, typename V>
  void DynamicPST< K, V > :: update(pPSTNode &p) {
    if(p) {
      p->rangeLeft = min(p->x, min(getLeftRange(p->l), getLeftRange(p->r)));
      p->rangeRight = max(p->x, max(getRightRange(p->r), getRightRange(p->r)));
      p->qtd = 1 + getQtd(p->l) + getQtd(p->r);
    }
  }

  template <typename K, typename V>
  typename DynamicPST< K, V > :: pPSTNode DynamicPST< K, V > :: insertPoint(K x, V y, pPSTNode p) {
    if(p == NULL) return new PSTNode(x, y);
    if(y > p->y) {
      swap(x, p->x);
      swap(y, p->y);
    }
    if(x < p->x) p->l = insertPoint(x, y, p->l);
    else p->r = insertPoint(x, y, p->r);
    update(p);
    return p;
  }


  template <typename K, typename V>
  typename DynamicPST< K, V > :: pPSTNode DynamicPST< K, V > :: tournament(pPSTNode l, pPSTNode r) {
    if(!l || !r) return (l ? l : r);
    if(l->y > r->y) {
      l->r = tournament(l->r, r);
      update(l);
      return l;
    }
    else {
      r->l = tournament(l, r->l);
      update(r);
      return r;
    }
  }

  template <typename K, typename V>
  typename DynamicPST< K, V > :: pPSTNode DynamicPST< K, V > ::erasePoint(K x, V y, pPSTNode p) {
    if(p == NULL) return NULL;
    if(p->x == x && p->y == y) p = tournament(p->l, p->r);
    else if(x < p->x) p->l = erasePoint(x, y, p->l);
    else p->r = erasePoint(x, y, p->r);
    update(p);
    return p;
  }

  template <typename K, typename V>
  void DynamicPST< K, V > ::queryPoints(K xl, K xr, V y, pPSTNode p) {
    if(p == NULL) return;
    if(p->y < y) return;
    if(p->rangeRight < xl || p->rangeLeft > xr) return;
    if(xl <= p->x && p->x <= xr && p->y >= y) {
      printf("(%d, %d)\n", p->x, p->y);
    }
    if(p->l) queryPoints(xl, xr, y, p->l);
    if(p->r) queryPoints(xl, xr, y, p->r);
  }

  template <typename K, typename V>
  V DynamicPST< K, V > ::getMinXGreaterThanOrEqualY(int xl, int xr, int y, pPSTNode p) {
    if(p == NULL) return numeric_limits< V > :: max(); 
    if(p->rangeRight < xl || p->rangeLeft > xr) return numeric_limits< V > :: max();
    if(p->y < y) return numeric_limits< V > :: max();
    V ans = numeric_limits< V > :: max();
    if(xl <= p->x && p->x <= xr && p->y >= y) {
      ans = min(ans, p->x);
    }
    if(p->l) ans = min(ans, getMinXGreaterThanOrEqualY(xl, xr, y, p->l));
    if(p->r) ans = min(ans, getMinXGreaterThanOrEqualY(xl, xr, y, p->r));
    return ans;
  }

  //public functions
  template <typename K, typename V>
  DynamicPST< K, V > :: DynamicPST() {
    root = NULL;
  }

  template <typename K, typename V>
  DynamicPST< K, V > :: DynamicPST(vector< pair<K, V> > v) {
    root = NULL;
    for(auto f : v) root = insertPoint(f.first, f.second, root);
  }

  template <typename K, typename V>
  void DynamicPST< K, V > :: insertPoint(K x, V y) {
    Vseg[x] = y;
    printf("inserting vertical segment (%d, %d)\n", x, y);
    root = insertPoint(x, y, root);
  }

  template <typename K, typename V>
  void DynamicPST< K, V > :: erasePoint(K x, V y) {
    Vseg.erase(x);
    printf("erasing vertical segment (%d, %d)\n", x, y);
    root = erasePoint(x, y, root);
  }

  template <typename K, typename V>
  void DynamicPST< K, V > :: queryPoints(K xl, K xr, V y) {
    printf("querying points\n");
    queryPoints(xl, xr, y, root);
  }

  template <typename K, typename V>
  V DynamicPST< K, V > :: getMinXGreaterThanOrEqualY(int xl, int xr, int y) {
    return getMinXGreaterThanOrEqualY(xl, xr, y, root);
  }

  template <typename K, typename V>
  V DynamicPST< K, V > :: getYFromX(K k) {
    return Vseg[k];
  }






  template <typename K, typename V>
  class DynamicPST< K, V > :: PSTNode {
  public:
    K x;
    V y;
    int rangeLeft, rangeRight;
    int qtd;
    PSTNode *l, *r;
    PSTNode () { 
      l = r = NULL;
      rangeLeft = numeric_limits< int > ::max();
      rangeRight = numeric_limits< int > ::min();
      qtd = 0;
    }
    PSTNode (K _x, V _y) {
      x = _x;
      y = _y;
      l = r = NULL;
      rangeLeft = x;
      rangeRight = x;
      qtd = 1;
    }
  };
}