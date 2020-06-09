#include "IntervalTree.hpp"

/** 
* Estrutura que mantem um nó da árvore de intervalos
*/
template <typename T>
struct IntervalTreeSum < T > :: Node {
  /**
  * Soma do prefixo até o nó atual
  */
  T ps;

  /**
  * Maximo das somas de prefixo até o nó atual
  */
  T mx;

  /**
  * Mínimo das somas de prefixo até o nó atual
  */
  T mn;


  T maxIndexMinimum;
  T minIndexMinimum;

  /**
  * Construtor padrão para o nó
  */
  Node(){
    ps = mx = mn = 0;
    maxIndexMinimum = 0;
    minIndexMinimum = N;
  };

  /**
  * Construtor especial para o nó
  * @param _ps -> soma de prefixo até o nó atual
  * @param _mn -> mínimo das somas de prefixo até o nó atual
  * @param _mx -> máximo das somas de prefixo até o nó atual 
  */
  Node(T _ps, T _mn, T _mx) {
    ps = _ps;
    mn = _mn;
    mx = _mx;
    maxIndexMinimum = 0;
    minIndexMinimum = N;
  }

  Node(T _ps, T _mn, T _mx, T _minIndexMinimum, T _maxIndexMinimum) {
    ps = _ps;
    mn = _mn;
    mx = _mx;
    minIndexMinimum = _minIndexMinimum;
    maxIndexMinimum = _maxIndexMinimum;
  }

  Node(T l, T r) {
    ps = 0;
    mn = 0;
    mx = 0;
    minIndexMinimum = r;
    maxIndexMinimum = l;
  }

  /**
  * Operador de união para dois nós subsequentes
  * @param other -> Nó a direita do nó atual a ser unido
  */
  Node operator + (Node other) const {
    T fooMin = (mn == other.mn) ? min(minIndexMinimum, other.minIndexMinimum) : (mn < other.mn ? minIndexMinimum : other.minIndexMinimum);
    T fooMax = (mn == other.mn) ? max(maxIndexMinimum, other.maxIndexMinimum) : (mn < other.mn ? maxIndexMinimum : other.maxIndexMinimum);
    return Node(ps + other.ps, 
      min(mn, other.mn),
      max(mx, other.mx), 
      fooMin,
      fooMax);
  }

  /**
  * Função para demonstração do nó atual para o usuário
  */
  void showInfo() {
    printf("{%2d, %2d, %2d}\n", ps, mn, mx);
  }
};


template <typename T>
int IntervalTreeSum < T > :: createNode(int l, int r) {
  int id = tr.size();
  tr.emplace_back(Node(l, r));
  lz.emplace_back(0);
  L.emplace_back(-1);
  R.emplace_back(-1);
  return id;  
}

template <typename T>
IntervalTreeSum < T > :: IntervalTreeSum () {
  n = N;
  createNode(0, n);
};

template <typename T>
void IntervalTreeSum < T > :: propagate(int no, int l, int r) {
  if(l != r && L[no] == -1) {
    int id = createNode(l, r);
    L[no] = id;
  }
  if(l != r && R[no] == -1) {
    int id = createNode(l, r);
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
  Node sol = query(0, 0, n, 0, t);
  return sol.mn ? 1 : sol.maxIndexMinimum;
}

template <typename T>
int IntervalTreeSum < T > :: getNextBridge(int t) {
  Node sol = query(0, 0, n, t, n);
  return sol.mn ? n : sol.minIndexMinimum;
}