#include "Treap.hpp"

namespace BST {
  template <typename K, typename V>
  pair<V, K> Treap< K, V > :: nmin(pair<V, K> a, pair<V, K> b) {
    if(a.first != b.first) return (a < b) ? a : b;
    return (a.second < b.second) ? b : a;
  }

  template <typename K, typename V>
  int Treap< K, V > :: getSize(pTreapNode p) {
    return p ? p->sz : 0;
  }

  template <typename K, typename V>
  pair<V, K> Treap< K, V > :: nmax(pair<V, K> a, pair<V, K> b) {
    if(a.first != b.first) return (a > b) ? a : b;
    return (a.second > b.second) ? b : a;
  }

  template <typename K, typename V>
  pair<V, K> Treap< K, V > :: getMinimumVK(pTreapNode p) {
    return p ? p->mn : make_pair(numeric_limits<V>::max(),numeric_limits<K>::max());
  }

  template <typename K, typename V>
  pair<V, K> Treap< K, V > :: getMaximumVK(pTreapNode p) {
    return p ? p->mx : make_pair(numeric_limits<V>::min(),numeric_limits<K>::min());
  }

  template <typename K, typename V>
  pair<V, K> Treap< K, V > :: getMinimumNVK(pTreapNode p) {
    return p ? p->nmn : make_pair(numeric_limits<V>::max(),numeric_limits<K>::min());
  }

  template <typename K, typename V>
  pair<V, K> Treap< K, V > :: getMaximumNVK(pTreapNode p) {
    return p ? p->nmx : make_pair(numeric_limits<V>::min(),numeric_limits<K>::max());
  }

  template <typename K, typename V>
  void Treap< K, V > :: update(pTreapNode p) {
    if(p) {

      p->parent = NULL;
      if(p->l) p->l->parent = p;
      if(p->r) p->r->parent = p;

      p->sz = 1 + getSize(p->l) + getSize(p->r);
      
      p->mn = min(make_pair(p->data, p->key), min(getMinimumVK(p->l), getMinimumVK(p->r)));
      p->mx = max(make_pair(p->data, p->key), max(getMaximumVK(p->l), getMaximumVK(p->r)));

      p->nmn = nmin(make_pair(p->data, p->key), nmin(getMinimumNVK(p->l), getMinimumNVK(p->r)));
      p->nmx = nmax(make_pair(p->data, p->key), nmax(getMaximumNVK(p->l), getMaximumNVK(p->r)));

    }
  }

  template <typename K, typename V>
  void Treap< K, V > :: split(pTreapNode t, K key, pTreapNode & l, pTreapNode & r) {
    if (!t) l = r = NULL;
    else if (key < t->key) {
      split (t->l, key, l, t->l);
      r = t;
    }
    else {
      split (t->r, key, t->r, r);
      l = t;
    }
    update(l);
    update(r);
    update(t);
  }

  template <typename K, typename V>
  void Treap< K, V > :: insert (pTreapNode & t, pTreapNode it) {
    if (!t) t = it;
    else {
      if (it->prior > t->prior) {
        split (t, it->key, it->l, it->r), t = it;
      }
      else {
        insert (it->key < t->key ? t->l : t->r, it);
      }
    }
    update(t);
  }

  template <typename K, typename V>
  void Treap< K, V > :: merge (pTreapNode & t, pTreapNode l, pTreapNode r) {
    if (!l || !r) {
      t = l ? l : r;
    }
    else {
      if (l->prior > r->prior) {
        merge (l->r, l->r, r),  t = l;
      }
      else {
        merge (r->l, l, r->l),  t = r;
      }
    }
    update(t);
  }

  template <typename K, typename V>
  void Treap< K, V > :: erase (pTreapNode & t, K key) {
    if (t->key == key) {
      merge (t, t->l, t->r);
    }
    else {
      erase (key < t->key ? t->l : t->r, key);
    }
    update(t);
  }

  template <typename K, typename V>
  typename Treap< K, V > :: pTreapNode Treap< K, V > :: find_by_order(pTreapNode t, int k) {
    if(t == NULL) return NULL;
    if(getSize(t->l) + 1 < k) return find_by_order(t->r, k - (getSize(t->l) + 1));
    else if(getSize(t->l) + 1 == k) return t;
    else return find_by_order(t->l, k);
  }


  template <typename K, typename V>
  int Treap< K, V > :: order_of_key(pTreapNode t, K k) {
    if(t == NULL) return 0;
    if(k > t->key) return order_of_key(t->r, k) + getSize(t->l) + 1;
    else return order_of_key(t->l, k);
  }

  template <typename K, typename V>
  bool Treap< K, V > :: find(pTreapNode t, K k) {
    if(t == NULL) return false;
    if(t->key == k) return 1;
    if(t->key > k) return find(t->l, k);
    else return find(t->r, k);
    update(t);
  }


  template <typename K, typename V>
  K Treap< K, V > :: getMinimumKey(pTreapNode t) {
    while(t->l) t = t->l;
    return t->key;
  }

  template <typename K, typename V>
  K Treap< K, V > :: getMaximumKey(pTreapNode t) {
    while(t->r) t = t->r;
    return t->key;
  }

  template <typename K, typename V>
  pair<V, K> Treap< K, V > :: getMinimumValueAfter(pTreapNode t, int fkey) {
    update(t);
    if(!t) return getMinimumVK(t);
    pair<V, K> foo = fkey <= t->key ? make_pair(t->data, t->key) : getMinimumVK(NULL);
    if(t->key >= fkey) return min(foo, min(getMinimumVK(t->r), getMinimumValueAfter(t->l, fkey)));
    else return getMinimumValueAfter(t->r, fkey);
  }

  template <typename K, typename V>
  pair<V, K> Treap< K, V > :: getMaximumValueAfter(pTreapNode t, int fkey) {
    update(t);
    if(!t) return getMaximumNVK(t);
    pair<V, K> foo = fkey <= t->key ? make_pair(t->data, t->key) : getMaximumNVK(NULL);
    if(t->key >= fkey) return nmax(foo, nmax(getMaximumNVK(t->r), getMaximumValueAfter(t->l, fkey)));
    else return getMaximumValueAfter(t->r, fkey);
  }

  template <typename K, typename V>
  pair<V, K> Treap< K, V > :: getMinimumValueBefore(pTreapNode t, int fkey) {
    update(t);
    if(!t) return getMinimumNVK(t);
    pair<V, K> foo = fkey >= t->key ? make_pair(t->data, t->key) : getMinimumNVK(NULL);
    if(t->key <= fkey) return nmin(foo, nmin(getMinimumNVK(t->l), getMinimumValueBefore(t->r, fkey)));
    else return getMinimumValueBefore(t->l, fkey);
  }

  template <typename K, typename V>
  pair<V, K> Treap< K, V > :: getMaximumValueBefore(pTreapNode t, int fkey) {
    update(t);
    if(!t) return getMaximumVK(t);
    pair<V, K> foo = fkey >= t->key ? make_pair(t->data, t->key) : getMaximumVK(NULL);
    if(t->key <= fkey) return max(foo, max(getMaximumVK(t->l), getMaximumValueBefore(t->r, fkey)));
    else return getMaximumValueBefore(t->l, fkey);
  }

  template <typename K, typename V>
  typename Treap< K, V > :: pTreapNode Treap< K, V > :: getBegin(pTreapNode t) {
    while(t->l != NULL) t = t->l;
    return t;
  }

  template <typename K, typename V>
  typename Treap< K, V > :: pTreapNode Treap< K, V > :: lower_bound(pTreapNode t, K k) {
    if(t == NULL) return NULL;
    if(t->key == k) return t;
    if(t->key < k) return lower_bound(t->r, k);
    pTreapNode q = lower_bound(t->l, k);
    if(q == NULL) return t;
    else return q;
  }

  template <typename K, typename V>
  void Treap< K, V > :: allTree(pTreapNode t, vector< V >&foo) {
    if(!t) return;
    allTree(t->l, foo);
    foo.push_back(t->data);
    allTree(t->r, foo);
  }

  //public functions
  template <typename K, typename V>
  Treap< K, V > :: Treap() {
    root = NULL;
  }

  template <typename K, typename V>
  Treap< K, V > :: Treap(pTreapNode _root) {
    root = _root;
  }

  template <typename K, typename V>
  void Treap< K, V > :: insert(K key, V data) {
    pTreapNode it = new TreapNode(key, data);
    insert(root, it);
  }

  template <typename K, typename V>
  void Treap< K, V > :: erase(K key) {
    if(find(key)) {
      erase(root, key);
    }
  }

  template <typename K, typename V>
  typename Treap< K, V > :: iterator Treap< K, V > :: find_by_order(int k) {
    return iterator(find_by_order(root, k));
  }

  template <typename K, typename V>
  int Treap< K, V > :: order_of_key(K k) {
    return order_of_key(root, k);
  } 

  template <typename K, typename V>
  bool Treap< K, V > :: find(K k) {
    return find(root, k);
  }

  template <typename K, typename V>
  K Treap< K, V > :: getMinimumKey() {
    return getMinimumKey(root);  
  }

  template <typename K, typename V>
  K Treap< K, V > :: getMaximumKey() {
    return getMaximumKey(root);
  }

  template <typename K, typename V>
  pair<V, K> Treap< K, V > :: getMinimumValueAfter(int w) {
    return getMinimumValueAfter(root, w);  
  }

  template <typename K, typename V>
  pair<V, K> Treap< K, V > :: getMaximumValueAfter(int w) {
    return getMaximumValueAfter(root, w);  
  }

  template <typename K, typename V>
  pair<V, K> Treap< K, V > :: getMinimumValueBefore(int w) {
    return getMinimumValueBefore(root, w);  
  }

  template <typename K, typename V>
  pair<V, K> Treap< K, V > :: getMaximumValueBefore(int w) {
    return getMaximumValueBefore(root, w);  
  }

  template <typename K, typename V>
  pair<V, K> Treap< K, V > :: getMinimumValue() {
    return getMinimumVK(root);
  }

  template <typename K, typename V>
  pair<V, K> Treap< K, V > :: getMaximumValue() {
    return getMaximumVK(root);
  }

  template <typename K, typename V>
  void Treap< K, V > :: showTree() {
    showTree(root);
  }

  template <typename K, typename V>
  void Treap< K, V > :: showTree2() {
    showTree2(root);
  }

  template <typename K, typename V>
  vector< V > Treap< K, V > :: getTree() {
    vector< V > foo;
    allTree(root, foo);
    return foo;
  }

  template <typename K, typename V>
  bool Treap< K, V > :: empty() {
      return (root == NULL);
    }
  template <typename K, typename V>
  pair< Treap<K, V>, Treap<K, V> > Treap< K, V > :: split(K key) {
    pTreapNode l, r;
    split(root, key, l, r);
    return make_pair(Treap<K, V>(l), Treap<K, V>(r));
  }
  template <typename K, typename V>
  int Treap< K, V > :: getSize() {
    return getSize(root);
  }

  template <typename K, typename V>
  class Treap< K, V > :: TreapNode {
  public:
    K key;
    V data;
    int prior, sz;
    TreapNode *l, *r;
    TreapNode *parent;
    //augmentation
    pair<V, K> mn, mx;
    pair<V, K> nmn, nmx;
    TreapNode() { }
    TreapNode (K _key, V _data) {
      key = _key;
      data = _data;
      mn = mx = make_pair(data, key);
      nmn = nmx = make_pair(data, key);
      prior = (rand() << 16) ^ (rand());
      sz = 1;
      l = r = parent = NULL;
    }
  };

  template <typename K, typename V>
  typename Treap< K, V > :: iterator Treap< K, V > :: begin() {
    return iterator(getBegin(root));
  }

  template <typename K, typename V>
  typename Treap< K, V > :: iterator Treap< K, V > :: end() {
    return iterator(NULL);
  }
  
  template <typename K, typename V>
  typename Treap< K, V > :: iterator Treap< K, V > :: lower_bound(K k) {
    return iterator(lower_bound(root, k));
  }

  template<typename K, typename V>
  class Treap< K, V > :: iterator {
  private:
    TreapNode *cur;
  public:
    iterator() {
      cur = NULL;
    }
    iterator(TreapNode *foo) {
      cur = foo;
    }
    bool operator == (const iterator &foo) const {
      return cur == foo.cur;
    }
    iterator& operator++() {
      K x = cur->key;
      if(cur->r) {
        cur = cur->r;
        while(cur->l) cur = cur->l;
        assert(cur->key > x);
        return *this;
      }

      while(cur != NULL) {
        if(cur->key > x) {
          return *this;
        }
        cur = cur->parent;
      }
      return *this;
    }
    iterator& operator--() {
      K x = cur->key;
      if(cur->l) {
        cur = cur->l;
        while(cur->r) cur = cur->r;
        assert(cur->key < x);
        return *this;
      }
      while(cur != NULL) {
        if(cur->key < x) {
          return *this;
        }
        cur = cur->parent;
      }
      return *this;
    }
    pair< K, V >& operator *() {
      pair< K, V > *foo = new pair<K, V>(cur->key, cur->data);
      return *foo;
    }
    void modify(K key, V data) {
      cur->key = key;
      cur->data = data;
    }
  };
};