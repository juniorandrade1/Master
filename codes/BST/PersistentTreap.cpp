#include <bits/stdc++.h>

using namespace std;


#include <bits/stdc++.h>

using namespace std;


template< typename K, typename V >
class PersistentTreap {
private:
  struct TreapNode {
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
  typedef TreapNode * pTreapNode;
  int getSize(pTreapNode p) {
    return p ? p->sz : 0;
  }
  pair<V, K> getMinimumVK(pTreapNode p) {
    return p ? p->mn : make_pair(numeric_limits<V>::max(),numeric_limits<K>::max());
  }
  pair<V, K> getMaximumVK(pTreapNode p) {
    return p ? p->mx : make_pair(numeric_limits<V>::min(),numeric_limits<K>::min());
  }
  pTreapNode update(pTreapNode p) {
    if(p) {
      p->sz = 1 + getSize(p->l) + getSize(p->r);
      p->mn = min(make_pair(p->data, p->key), min(getMinimumVK(p->l), getMinimumVK(p->r)));
      p->mx = max(make_pair(p->data, p->key), max(getMaximumVK(p->l), getMaximumVK(p->r)));
    }
    return p;
  }

  pTreapNode copy(pTreapNode p) {
    pTreapNode cpy = new TreapNode(p->key, p->data);
    cpy->l = p->l; 
    cpy->r = p->r;
    return update(cpy);
  }

  void split(pTreapNode t, K key, pTreapNode &a, pTreapNode &b) {
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

  pTreapNode merge(pTreapNode l, pTreapNode r) {
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

  void preOrder(pTreapNode p) {
    if(p == NULL) return;
    preOrder(p->l);
    cout << p->key << " " << p->data << endl;
    preOrder(p->r);
  }

  K getMinimumKey(pTreapNode t) {
    while(t->l) t = t->l;
    return t->key;
  }
  K getMaximumKey(pTreapNode t) {
    while(t->r) t = t->r;
    return t->key;
  }

  pTreapNode erase(pTreapNode t, K key) {
    if (t->key == key) {
      t = merge(t->l, t->r);
    }
    else {
      if(key < t->key) t->l = erase(t->l, key);
      else t->r = erase(t->r, key);
    }
    return update(t);
  }

  pTreapNode insert(pTreapNode t, pTreapNode it) {
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

  int order_of_key(pTreapNode t, K k) {
    if(t == NULL) return 0;
    if(k >= t->key) return order_of_key(t->r, k) + getSize(t->l) + 1;
    else return order_of_key(t->l, k);
  }

  int getQtdEG(pTreapNode t, K k) {
    if(t == NULL) return 0;
    if(t->key >= k) return getSize(t->r) + 1 + getQtdEG(t->l, k);
    else return getQtdEG(t->r, k);
  }




public:
  vector< pTreapNode > root;
  PersistentTreap(){
    root.clear();
    root.push_back(NULL);
  }
  int insert(int ver, K key, V data) {
    
    root[ver] = insert(root[ver], new TreapNode(key, data));
    return ver;

    // pTreapNode tree = insert(root[ver], new TreapNode(key, data));
    // root.push_back(tree);
    // return root.size() - 1;

    // pTreapNode a, b, tree;
    // split(root[ver], key, a, b);
    // tree = merge(merge(a, new TreapNode(key, data)), b);
    // root.push_back(tree);
    // return root.size() - 1;
  }
  int erase(int ver, K key) {
    root[ver] = erase(root[ver], key);
    return ver;

    // pTreapNode tree = erase(root[ver], key);
    // root.push_back(tree);
    // return root.size() - 1;

    // pTreapNode a, b, c, d;
    // split(root[ver], key - 1, a, b);
    // split(b, key, c, d);
    // root.push_back(merge(a, d));
    // return root.size() - 1;
  }
  pair<int, int> split(int ver, K key) {
    pTreapNode a, b;
    split(root[ver], key, a, b);
    root.push_back(a);
    root.push_back(b);
    return make_pair(root.size() - 2, root.size() - 1);
  }

  K getMinimumKey(int ver) {
    if(root[ver] == NULL) {
      //printf("EMPTY\n");
      return numeric_limits< K > :: max();
    }
    return getMinimumKey(root[ver]);
  }
  void preOrder(int ver) {
    preOrder(root[ver]);
  }
  int getSize(int ver) {
    return getSize(root[ver]);
  }

  int order_of_key(int ver, K k) {
    return order_of_key(root[ver], k);
  } 
  int getQtdEG(int ver, K k) {
    return getQtdEG(root[ver], k);
  }
};



// int main() {
//   PersistentTreap< int, int > t1;
//   int ver1 = t1.insert(0, 2, 1);
//   int ver2 = t1.insert(ver1, 5, 2);

//   int ver3 = t1.insert(ver1, 20, 10);
//   int ver4 = t1.insert(ver2, 666, 666);

//   t1.preOrder(ver1);

//   cout << endl;

//   t1.preOrder(ver2);

//   cout << endl;
//   t1.preOrder(ver3);

//   cout << endl;
//   t1.preOrder(ver4);

//   cout << endl;


//   cout << t1.getMinimumKey(ver4) << endl << endl;

//   int ver5 = t1.erase(ver4, 5);

//   t1.preOrder(ver5);
//   cout << endl;

//   t1.preOrder(ver4);
//   cout << endl;
//   return 0;
// }