//IntervalTree.hpp

#ifndef INTERVALTREE 
#define INTERVALTREE_H

#pragma once

#include <bits/stdc++.h>

using namespace std;

const int N = (int)5e5 + 1;

#define INF 0x3f3f3f3f

namespace BST {
  template <typename T>
  class IntervalTree {
  public:

    struct Node;
    vector< Node > tr;
    vector< int > lz;
    vector< int > L, R;
    int n;

    void build(int no, int l, int r);

    IntervalTree();

    void propagate(int no, int l, int r);

    void updateInsert(int no, int l, int r, int t, T data);

    void updateDelete(int no, int l, int r, int t);

    void erasePush(int no, int l, int r, int t);

    void erasePop(int no, int l, int r, int t);

    int getNode(int no, int l, int r, int t);

    Node getRangeNode(int no, int l, int r, int i, int j);

    void showTree(int no, int l, int r);

    int getPrefixSum(int no, int l, int r, int i);

    void updateInsert(int t, T data);

    void updateDelete(int i);

    void erasePush(int t);

    void erasePop(int t);

    T getPeak(int i, int t);

    std::pair<int, T> getPeakPair(int i, int t);

    int getPrefixSum(int i);

    int getSize();

    void showTree();
    
  };
};

#include "IntervalTree.cpp"

#endif /* INTERVALTREE_H */