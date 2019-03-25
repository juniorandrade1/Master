#include <bits/stdc++.h>
template< typename K, typename V >
class Treap {
private:
  struct Node {
    K key;
    V data;
    int prior, sz;
    Node *l, *r;
    Node() { }
    Node (K _key, V _data) {
      key = _key;
      data = _data;
      prior = (rand() << 16) ^ (rand());
      sz = 1;
      l = r = NULL;
    }
  };
  typedef Node * pNode;
  int getSize(pNode p) {
    return p ? p->sz : 0;
  }
  void update(pNode p) {
    if(p) p->sz = 1 + getSize(p->l) + getSize(p->r);
  }
  void split (pNode t, K key, pNode & l, pNode & r) {
    if (!t) l = r = NULL;
    else if (key < t->key) split (t->l, key, l, t->l),  r = t;
    else split (t->r, key, t->r, r),  l = t;
    update(t);
  }
  void insert (pNode & t, pNode it) {
    if (!t) t = it;
    else if (it->prior > t->prior) split (t, it->key, it->l, it->r),  t = it;
    else insert (it->key < t->key ? t->l : t->r, it);
  }
  void merge (pNode & t, pNode l, pNode r) {
    if (!l || !r) t = l ? l : r;
    else if (l->prior > r->prior) merge (l->r, l->r, r),  t = l;
    else merge (r->l, l, r->l),  t = r;
    update(t);
  }
  void erase (pNode & t, K key) {
    if (t->key == key) merge (t, t->l, t->r);
    else erase (key < t->key ? t->l : t->r, key);
    update(t);
  }
  pNode unite (pNode l, pNode r) {
    if (!l || !r)  return l ? l : r;
    if (l->prior < r->prior)  swap (l, r);
    pNode lt, rt;
    split (r, l->key, lt, rt);
    l->l = unite (l->l, lt);
    l->r = unite (l->r, rt);
    return l;
  }
  pNode find_by_order(pNode t, int k) {
    if(t == NULL) return NULL;
    if(getSize(t->l) + 1 < k) return find_by_order(t->r, k - (getSize(t->l) + 1));
    else if(getSize(t->l) + 1 == k) return t;
    else return find_by_order(t->l, k);
  }
  int order_of_key(pNode t, K k) {
    if(t == NULL) return 0;
    if(k >= t->key) return order_of_key(t->r, k) + getSize(t->l) + 1;
    else return order_of_key(t->l, k);
  }
  bool find(pNode t, K k) {
    if(t == NULL) return false;
    if(t->key == k) return 1;
    if(t->key > k) return find(t->l, k);
    else return find(t->r, k);
  }
public:
  pNode root;
  Treap() {
    root = NULL;
  }
  void insert(K key, V data) {
    pNode it = new Node(key, data);
    insert(root, it);
  }
  void erase(K key) {
    if(find(key)) erase(root, key);
  }
  V find_by_order(int k) {
    pNode p = find_by_order(root, k);
    if(p == NULL) return V();
    return p->data;
  }
  int order_of_key(K k) {
    return order_of_key(root, k);
  } 
  bool find(K k) {
    return find(root, k);
  }
};