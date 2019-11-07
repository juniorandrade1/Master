#include <bits/stdc++.h>

using namespace std;

namespace BST {
  template< typename K, typename V >
  class Treap {
  public:
    class TreapNode;
    class iterator;
  private:
    
    typedef TreapNode * pTreapNode;
    int getSize(pTreapNode p) {
      return p ? p->sz : 0;
    }

    pair<V, K> nmin(pair<V, K> a, pair<V, K> b) {
      if(a.first != b.first) return (a < b) ? a : b;
      return (a.second < b.second) ? b : a;
    }
    pair<V, K> nmax(pair<V, K> a, pair<V, K> b) {
      if(a.first != b.first) return (a > b) ? a : b;
      return (a.second > b.second) ? b : a;
    }
    pair<V, K> getMinimumVK(pTreapNode p) {
      return p ? p->mn : make_pair(numeric_limits<V>::max(),numeric_limits<K>::max());
    }
    pair<V, K> getMaximumVK(pTreapNode p) {
      return p ? p->mx : make_pair(numeric_limits<V>::min(),numeric_limits<K>::min());
    }
    pair<V, K> getMinimumNVK(pTreapNode p) {
      return p ? p->nmn : make_pair(numeric_limits<V>::max(),numeric_limits<K>::min());
    }
    pair<V, K> getMaximumNVK(pTreapNode p) {
      return p ? p->nmx : make_pair(numeric_limits<V>::min(),numeric_limits<K>::max());
    }

    void update(pTreapNode p) {
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
    void split (pTreapNode t, K key, pTreapNode & l, pTreapNode & r) {
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
    void insert (pTreapNode & t, pTreapNode it) {
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
    void merge (pTreapNode & t, pTreapNode l, pTreapNode r) {
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
    void erase (pTreapNode & t, K key) {
      if (t->key == key) {
        merge (t, t->l, t->r);
      }
      else {
        erase (key < t->key ? t->l : t->r, key);
      }
      update(t);
    }
    pTreapNode find_by_order(pTreapNode t, int k) {
      if(t == NULL) return NULL;
      if(getSize(t->l) + 1 < k) return find_by_order(t->r, k - (getSize(t->l) + 1));
      else if(getSize(t->l) + 1 == k) return t;
      else return find_by_order(t->l, k);
    }
    int order_of_key(pTreapNode t, K k) {
      if(t == NULL) return 0;
      if(k > t->key) return order_of_key(t->r, k) + getSize(t->l) + 1;
      else return order_of_key(t->l, k);
    }
    bool find(pTreapNode t, K k) {
      if(t == NULL) return false;
      if(t->key == k) return 1;
      if(t->key > k) return find(t->l, k);
      else return find(t->r, k);
      update(t);
    }
    K getMinimumKey(pTreapNode t) {
      while(t->l) t = t->l;
      return t->key;
    }
    K getMaximumKey(pTreapNode t) {
      while(t->r) t = t->r;
      return t->key;
    }
    pair<V, K> getMinimumValueAfter(pTreapNode t, int fkey) {
      update(t);
      if(!t) return getMinimumVK(t);
      pair<V, K> foo = fkey <= t->key ? make_pair(t->data, t->key) : getMinimumVK(NULL);
      if(t->key >= fkey) return min(foo, min(getMinimumVK(t->r), getMinimumValueAfter(t->l, fkey)));
      else return getMinimumValueAfter(t->r, fkey);
    }
    pair<V, K> getMaximumValueAfter(pTreapNode t, int fkey) {
      update(t);
      if(!t) return getMaximumNVK(t);
      pair<V, K> foo = fkey <= t->key ? make_pair(t->data, t->key) : getMaximumNVK(NULL);
      if(t->key >= fkey) return nmax(foo, nmax(getMaximumNVK(t->r), getMaximumValueAfter(t->l, fkey)));
      else return getMaximumValueAfter(t->r, fkey);
    }
    pair<V, K> getMinimumValueBefore(pTreapNode t, int fkey) {
      update(t);
      if(!t) return getMinimumNVK(t);
      pair<V, K> foo = fkey >= t->key ? make_pair(t->data, t->key) : getMinimumNVK(NULL);
      if(t->key <= fkey) return nmin(foo, nmin(getMinimumNVK(t->l), getMinimumValueBefore(t->r, fkey)));
      else return getMinimumValueBefore(t->l, fkey);
    }
    pair<V, K> getMaximumValueBefore(pTreapNode t, int fkey) {
      update(t);
      if(!t) return getMaximumVK(t);
      pair<V, K> foo = fkey >= t->key ? make_pair(t->data, t->key) : getMaximumVK(NULL);
      if(t->key <= fkey) return max(foo, max(getMaximumVK(t->l), getMaximumValueBefore(t->r, fkey)));
      else return getMaximumValueBefore(t->l, fkey);
    }
    void showTree(pTreapNode t) {
      if(!t) return;
      showTree(t->l);
      printf("NODE\n");
      printf("%d (%d, %d)\n", t->key, t->data.first, t->data.second);

      // printf("LEFT = ");
      // if(t->l == NULL) printf("NULL\n");
      // else printf("%d %d\n", t->l->key, t->l->data);

      // printf("RIGHT = ");
      // if(t->r == NULL) printf("NULL\n");
      // else printf("%d %d\n", t->r->key, t->r->data);

      // printf("parent = ");
      // if(t->parent == NULL) printf("NULL\n");
      // else printf("%d %d\n", t->parent->key, t->parent->data);

      showTree(t->r);
      update(t);
    }
    void showTree2(pTreapNode t) {
      if(!t) return;
      showTree2(t->l);
      printf("NODE\n");
      printf("%d (%d)\n", t->key, t->data);

      // printf("LEFT = ");
      // if(t->l == NULL) printf("NULL\n");
      // else printf("%d %d\n", t->l->key, t->l->data);

      // printf("RIGHT = ");
      // if(t->r == NULL) printf("NULL\n");
      // else printf("%d %d\n", t->r->key, t->r->data);

      // printf("parent = ");
      // if(t->parent == NULL) printf("NULL\n");
      // else printf("%d %d\n", t->parent->key, t->parent->data);

      showTree2(t->r);
      update(t);
    }
    void allTree(pTreapNode t, vector< V >&foo) {
      if(!t) return;
      allTree(t->l, foo);
      foo.push_back(t->data);
      allTree(t->r, foo);
    }
    pTreapNode getBegin(pTreapNode t) {
      while(t->l != NULL) t = t->l;
      return t;
    }
    pTreapNode lower_bound(pTreapNode t, K k) {
      if(t == NULL) return NULL;
      if(t->key == k) return t;
      if(t->key < k) return lower_bound(t->r, k);
      pTreapNode q = lower_bound(t->l, k);
      if(q == NULL) return t;
      else return q;
    }
  public:
    pTreapNode root;
    Treap() {
      root = NULL;
    }
    Treap(pTreapNode _root) {
      root = _root;
    }
    void insert(K key, V data) {
      pTreapNode it = new TreapNode(key, data);
      insert(root, it);
    }
    void erase(K key) {
      if(find(key)) {
        erase(root, key);
      }
    }
    // V find_by_order(int k) {
    //   pTreapNode p = find_by_order(root, k);
    //   if(p == NULL) return V();
    //   return p->data;
    // }
    // std::pair<K, V> find_by_order(int k) {
    //   pTreapNode p = find_by_order(root, k);
    //   if(p == NULL) return std::make_pair(K(), V());
    //   return std::make_pair(p->key, p->data);
    // }
    iterator find_by_order(int k) {
      return iterator(find_by_order(root, k));
    }
    int order_of_key(K k) {
      return order_of_key(root, k);
    } 
    bool find(K k) {
      return find(root, k);
    }
    K getMinimumKey() {
      return getMinimumKey(root);  
    }
    K getMaximumKey() {
      return getMaximumKey(root);
    }
    pair<V, K> getMinimumValueAfter(int w) {
      return getMinimumValueAfter(root, w);  
    }
    pair<V, K> getMaximumValueAfter(int w) {
      return getMaximumValueAfter(root, w);  
    }
    pair<V, K> getMinimumValueBefore(int w) {
      return getMinimumValueBefore(root, w);  
    }
    pair<V, K> getMaximumValueBefore(int w) {
      return getMaximumValueBefore(root, w);  
    }
    pair<V, K> getMinimumValue() {
      return getMinimumVK(root);
    }
    pair<V, K> getMaximumValue() {
      return getMaximumVK(root);
    }
    void showTree() {
      showTree(root);
    }
    void showTree2() {
      showTree2(root);
    }
    vector< V > getTree() {
      vector< V > foo;
      allTree(root, foo);
      return foo;
    }
    bool empty() {
      return (root == NULL);
    }
    int getSize() {
      return getSize(root);
    }
    pair< Treap<K, V>, Treap<K, V> > split(K key) {
      pTreapNode l, r;
      split(root, key, l, r);
      return make_pair(Treap<K, V>(l), Treap<K, V>(r));
    }
    iterator begin() {
      return iterator(getBegin(root));
    }
    iterator end() {
      return iterator(NULL);
    }
    iterator lower_bound(K k) {
      return iterator(lower_bound(root, k));
    }
  };

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

// int main() {
//   srand(time(NULL));
//   BST::Treap< int, int > td;
//   td.insert(4, -1);
//   BST::Treap< int, int > :: iterator it = td.lower_bound(4);
//   printf("%d\n", (*it).first);

//   // BST::Treap< int, int > td;
//   // BST::Treap< int, pair<int, BST::Treap< int, int > :: iterator> > te;


//   // BST::Treap< int, int > t;
//   // BST::Treap< int, int > :: iterator it;
//   // t.insert(1, 5);
//   // it = t.lower_bound(1);
//   // cout << (*it).first << endl; 
//   // t.insert(10, 2);
//   // it = t.lower_bound(1);
//   // cout << (*it).first << endl; 
//   // t.insert(15, 1);
//   // it = t.lower_bound(5);
//   // cout << (*it).first << endl; 
//   //t.insert(13, 2);
//   //t.insert(23, 231);
  
//   // t.insert(31, 23);
//   // BST::Treap< int, int > :: iterator it = t.begin();
//   // printf("%d %d\n", (*it).first, (*it).second);
//   // t.insert(50, 12);
//   // printf("%d %d\n", (*it).first, (*it).second);
//   // t.insert(34, 44);
//   // printf("%d %d\n", (*it).first, (*it).second);
//   // t.insert(28, 24);
//   // --it;
//   // printf("%d %d\n", (*it).first, (*it).second);
//   // t.insert(12, 19);
//   // --it;

//   // t.showTree();
//   // printf("%d %d\n", (*it).first, (*it).second);
//   return 0;
// }