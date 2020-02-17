// SegmentTree.h
#ifndef SEGMENT_TREE 
#define SEGMENT_TREE_H

#pragma once

#include <bits/stdc++.h>

namespace BST {
  class SegmentTree {
  public:
    int n;
    
    vector< multiset< pair<int, int> > > tr;
    
    map< int, pair<int, int> > Hseg; //guarda para dado um tempo de inserção inicial, qual o [tDel, x]
    
    map< int, int > Hins; //Hins[x] = t -> tempo de inserção da chave x

    SegmentTree();
    
    SegmentTree(int _n);
    
    void insertSegment(int no, int l, int r, int l0, int l1, int y, int idx);
    
    void eraseSegment(int no, int l, int r, int l0, int l1, int y, int idx);
    
    void insertSegment(int l0, int l1, int y, int idx = -1);
    
    void eraseSegment(int l0, int l1, int y, int idx = -1);
    
    int getMinY(int no, int l, int r, int t) ;
    
    int getMinY(int t);
    
    int getStartTimeFromKey(int x);
    
    int getFinishTimeFromKey(int x);
    
    int getKeyFromStartTime(int startTime);
    
    int getFinishTimeFromStartTime(int startTime);
  };
};

#include "SegmentTree.cpp"

#endif /* SEGMENT_TREE_H */