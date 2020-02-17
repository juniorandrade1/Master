//Treap.hpp

#ifndef PERSISTENT_TREAP 
#define PERSISTENT_TREAP_H

#pragma once

#include <bits/stdc++.h>

using namespace std;

template< typename K, typename V >
class PersistentTreap {
private:
  struct TreapNode;

  typedef TreapNode * pTreapNode;

  int getSize(pTreapNode p);

  pair<V, K> getMinimumVK(pTreapNode p);

  pair<V, K> getMaximumVK(pTreapNode p);

  pTreapNode update(pTreapNode p);

  pTreapNode copy(pTreapNode p);

  void split(pTreapNode t, K key, pTreapNode &a, pTreapNode &b);

  pTreapNode merge(pTreapNode l, pTreapNode r);

  void preOrder(pTreapNode p);

  K getMinimumKey(pTreapNode t);

  K getMaximumKey(pTreapNode t);

  pTreapNode erase(pTreapNode t, K key);

  pTreapNode insert(pTreapNode t, pTreapNode it);

  int order_of_key(pTreapNode t, K k);

  int getQtdEG(pTreapNode t, K k);




public:
  vector< pTreapNode > root;
  
  PersistentTreap();

  int insert(int ver, K key, V data);
  
  int erase(int ver, K key);
  
  pair<int, int> split(int ver, K key);

  K getMinimumKey(int ver) ;
  
  void preOrder(int ver) ;
  
  int getSize(int ver) ;

  int order_of_key(int ver, K k) ;
  
  int getQtdEG(int ver, K k);
};


#include "PersistentTreap.cpp"

#endif /* PERSISTENT_TREAP_H */