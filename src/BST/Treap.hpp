//Treap.hpp

#ifndef TREAP 
#define TREAP_H

#pragma once

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

    int getSize(pTreapNode p);

    pair<V, K> nmin(pair<V, K> a, pair<V, K> b);

    pair<V, K> nmax(pair<V, K> a, pair<V, K> b);

    pair<V, K> getMinimumVK(pTreapNode p);

    pair<V, K> getMaximumVK(pTreapNode p);

    pair<V, K> getMinimumNVK(pTreapNode p);

    pair<V, K> getMaximumNVK(pTreapNode p);

    void update(pTreapNode p);

    void split (pTreapNode t, K key, pTreapNode & l, pTreapNode & r);

    void insert (pTreapNode & t, pTreapNode it);

    void merge (pTreapNode & t, pTreapNode l, pTreapNode r);

    void erase (pTreapNode & t, K key);

    pTreapNode find_by_order(pTreapNode t, int k);

    int order_of_key(pTreapNode t, K k);

    bool find(pTreapNode t, K k);

    K getMinimumKey(pTreapNode t);

    K getMaximumKey(pTreapNode t);

    pair<V, K> getMinimumValueAfter(pTreapNode t, int fkey);

    pair<V, K> getMaximumValueAfter(pTreapNode t, int fkey);

    pair<V, K> getMinimumValueBefore(pTreapNode t, int fkey);

    pair<V, K> getMaximumValueBefore(pTreapNode t, int fkey);

    /*
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
    */
    void allTree(pTreapNode t, vector< V >&foo);

    pTreapNode getBegin(pTreapNode t);

    pTreapNode lower_bound(pTreapNode t, K k);

  public:
    
    pTreapNode root;
    
    Treap();

    Treap(pTreapNode _root);

    void insert(K key, V data);

    void erase(K key);

    iterator find_by_order(int k);

    int order_of_key(K k);
    
    bool find(K k);

    K getMinimumKey();

    K getMaximumKey();

    pair<V, K> getMinimumValueAfter(int w);

    pair<V, K> getMaximumValueAfter(int w);

    pair<V, K> getMinimumValueBefore(int w);

    pair<V, K> getMaximumValueBefore(int w);

    pair<V, K> getMinimumValue();

    pair<V, K> getMaximumValue();

    void showTree();

    void showTree2();

    vector< V > getTree();

    bool empty();
    
    int getSize();

    pair< Treap<K, V>, Treap<K, V> > split(K key);

    iterator begin();

    iterator end();

    iterator lower_bound(K k);
  };

};

#include "Treap.cpp"

#endif /* TREAP_H */