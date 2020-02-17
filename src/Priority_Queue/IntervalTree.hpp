//IntervalTree.hpp

#ifndef INTERVALTREE 
#define INTERVALTREE_H

#pragma once

#include <bits/stdc++.h>

using namespace std;

const int N = (int)70000;

template <typename T>
class IntervalTreeSum {
  struct Node;

public:
  std::vector< Node > tr;

  std::vector< int > lz, L, R;

  int n;

  int createNode();

  IntervalTreeSum();

  void propagate(int no, int l, int r);

  void update(int no, int l, int r, int t, int inc);

  Node query(int no, int l, int r, int i, int j);

  void showTree(int no, int l, int r);

  Node query(int l, int r);

  void update(int t, T inc);

  void showTree();

  int getLastBridge(int t);

  int getNextBridge(int t);
};

#include "IntervalTree.cpp"

#endif /* INTERVALTREE_H */