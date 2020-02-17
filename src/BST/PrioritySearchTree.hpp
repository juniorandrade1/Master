// PrioritySearchTree.h
#ifndef PRIORITY_SEARCH_TREE 
#define PRIORITY_SEARCH_TREE_H

#pragma once

#include <bits/stdc++.h>

using namespace std;

namespace BST {
  template< typename K, typename V >
  class DynamicPST {
  public:
    class PSTNode;
    
    map< int, int > Vseg;

  private:
    typedef PSTNode * pPSTNode;

    int getQtd(pPSTNode p);

    int getLeftRange(pPSTNode p);

    int getRightRange(pPSTNode p);

    void update(pPSTNode &p);

    pPSTNode insertPoint(K x, V y, pPSTNode p);

    pPSTNode tournament(pPSTNode l, pPSTNode r);

    pPSTNode erasePoint(K x, V y, pPSTNode p);

    void queryPoints(K xl, K xr, V y, pPSTNode p);

    V getMinXGreaterThanOrEqualY(int xl, int xr, int y, pPSTNode p);

  public:
    pPSTNode root;

    DynamicPST();

    DynamicPST(vector< pair<K, V> > v);

    void insertPoint(K x, V y);

    void erasePoint(K x, V y);

    void queryPoints(K xl, K xr, V y);

    V getMinXGreaterThanOrEqualY(int xl, int xr, int y);

    V getYFromX(K k);
  };
}

#include "PrioritySearchTree.cpp"

#endif /* PRIORITY_SEARCH_TREE_H */