#include "PersistentTreap.hpp"

template< typename K, typename V >
struct PersistentTreap< K, V> :: TreapNode {
  K key;
  V data;
  TreapNode *l, *r;
  //augmentation
  pair<V, K> mn, mx;
  int sz;
  int y;
  TreapNode() { }
  TreapNode (K _key, V _data) {
    key = _key;
    data = _data;
    mn = mx = make_pair(data, key);
    y = (rand() << 16) ^ (rand());
    sz = 1;
    l = r = NULL;
  }
};

template< typename K, typename V >
int PersistentTreap< K, V> :: getSize(pTreapNode p) {
  return p ? p->sz : 0;
}
template< typename K, typename V >
pair<V, K> PersistentTreap< K, V> :: getMinimumVK(pTreapNode p) {
  return p ? p->mn : make_pair(numeric_limits<V>::max(),numeric_limits<K>::max());
}

template< typename K, typename V >
pair<V, K> PersistentTreap< K, V> :: getMaximumVK(pTreapNode p) {
  return p ? p->mx : make_pair(numeric_limits<V>::min(),numeric_limits<K>::min());
}

template< typename K, typename V >
typename PersistentTreap< K, V> :: pTreapNode PersistentTreap< K, V> :: update(pTreapNode p) {
  if(p) {
    p->sz = 1 + getSize(p->l) + getSize(p->r);
    p->mn = min(make_pair(p->data, p->key), min(getMinimumVK(p->l), getMinimumVK(p->r)));
    p->mx = max(make_pair(p->data, p->key), max(getMaximumVK(p->l), getMaximumVK(p->r)));
  }
  return p;
}

template< typename K, typename V >
typename PersistentTreap< K, V> :: pTreapNode PersistentTreap< K, V> :: copy(pTreapNode p) {
  pTreapNode cpy = new TreapNode(p->key, p->data);
  cpy->l = p->l; 
  cpy->r = p->r;
  return update(cpy);
}

template< typename K, typename V >
void PersistentTreap< K, V> :: split(pTreapNode t, K key, pTreapNode &a, pTreapNode &b) {
  if (!t) {
    a = b = NULL;
    return;
  }
  pTreapNode aux;
  t = copy(t);
  if (key < t->key) {
    split(t->l, key, a, aux);
    t->l = aux;
    b = update(t);
  }
  else {
    split(t->r, key, aux, b);
    t->r = aux;
    a = update(t);
  }
}

template< typename K, typename V >
typename PersistentTreap< K, V> :: pTreapNode PersistentTreap< K, V> :: merge(pTreapNode l, pTreapNode r) {
  if (!l || !r) {
    return l ? l : r;
  }
  int m = getSize(l), n = getSize(r);
  if(rand() % (m + n) < m) {
    l = copy(l);
    l->r = merge(l->r, r);
    return update(l);
  }
  else {
    r = copy(r);
    r->l = merge(l, r->l);
    return update(r);
  }
}

template< typename K, typename V >
void PersistentTreap< K, V> :: preOrder(pTreapNode p) {
  if(p == NULL) return;
  preOrder(p->l);
  cout << p->key << " " << p->data << endl;
  preOrder(p->r);
}

template< typename K, typename V >
K PersistentTreap< K, V> :: getMinimumKey(pTreapNode t) {
  while(t->l) t = t->l;
  return t->key;
}

template< typename K, typename V >
K PersistentTreap< K, V> :: getMaximumKey(pTreapNode t) {
  while(t->r) t = t->r;
  return t->key;
}

template< typename K, typename V >
typename PersistentTreap< K, V> :: pTreapNode PersistentTreap< K, V> :: erase(pTreapNode t, K key) {
  if(t == NULL) return NULL;
  if (t->key == key) {
    t = merge(t->l, t->r);
  }
  else {
    if(key < t->key) t->l = erase(t->l, key);
    else t->r = erase(t->r, key);
  }
  return update(t);
}

template< typename K, typename V >
typename PersistentTreap< K, V> :: pTreapNode PersistentTreap< K, V> :: insert(pTreapNode t, pTreapNode it) {
  if(!t) {
    t = it;
  }
  else if(it->y < t->y) {
    split(t, it->key, it->l, it->r);
    t = it;
  }
  else {
    if(it->key < t->key) t->l = insert(t->l, it);
    else t->r = insert(t->r, it);
  }
  return update(t);
}

template< typename K, typename V >
int PersistentTreap< K, V> :: order_of_key(pTreapNode t, K k) {
  if(t == NULL) return 0;
  if(k >= t->key) return order_of_key(t->r, k) + getSize(t->l) + 1;
  else return order_of_key(t->l, k);
}

template< typename K, typename V >
int PersistentTreap< K, V> :: getQtdEG(pTreapNode t, K k) {
  if(t == NULL) return 0;
  if(t->key >= k) return getSize(t->r) + 1 + getQtdEG(t->l, k);
  else return getQtdEG(t->r, k);
}

template< typename K, typename V >
PersistentTreap< K, V> :: PersistentTreap(){
  root.clear();
  root.push_back(NULL);
}

template< typename K, typename V >
int PersistentTreap< K, V> :: insert(int ver, K key, V data) {
  root[ver] = insert(root[ver], new TreapNode(key, data));
  return ver;
}

template< typename K, typename V >
int PersistentTreap< K, V> :: erase(int ver, K key) {
  root[ver] = erase(root[ver], key);
  return ver;
}

template< typename K, typename V >
pair<int, int> PersistentTreap< K, V> :: split(int ver, K key) {
  pTreapNode a, b;
  split(root[ver], key, a, b);
  root.push_back(a);
  root.push_back(b);
  return make_pair(root.size() - 2, root.size() - 1);
}

template< typename K, typename V >
K PersistentTreap< K, V> :: getMinimumKey(int ver) {
  if(root[ver] == NULL) {
    return numeric_limits< K > :: max();
  }
  return getMinimumKey(root[ver]);
}

template< typename K, typename V >
void PersistentTreap< K, V> :: preOrder(int ver) {
  preOrder(root[ver]);
}

template< typename K, typename V >
int PersistentTreap< K, V> :: getSize(int ver) {
  return getSize(root[ver]);
}

template< typename K, typename V >
int PersistentTreap< K, V> :: order_of_key(int ver, K k) {
  return order_of_key(root[ver], k);
} 

template< typename K, typename V >
int PersistentTreap< K, V> :: getQtdEG(int ver, K k) {
  return getQtdEG(root[ver], k);
}