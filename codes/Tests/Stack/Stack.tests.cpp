#include "../../Stack/Stack.cpp"
#include <gtest/gtest.h>

class Segtree {
public:
  int n;
  vector< int > L, R;
  vector< int > sm, mn;
  vector< int > lz;
  int createNode() {
    int id = sm.size();
    sm.emplace_back(0);
    mn.emplace_back(0);
    lz.emplace_back(0);
    L.emplace_back(-1);
    R.emplace_back(-1);
    return id;  
  }
  Segtree(){
    n = N;
    createNode();
  };
  void propagate(int no, int l, int r) {
    if(l != r && L[no] == -1) {
      int id = createNode();
      L[no] = id;
    }
    if(l != r && R[no] == -1) {
      int id = createNode();
      R[no] = id;
    }
    sm[no] += (r - l + 1) * lz[no];
    mn[no] += lz[no];
    if(l != r) {
      lz[L[no]] += lz[no];
      lz[R[no]] += lz[no];
    }
    lz[no] = 0;
  }
  void join(int no, int nl, int nr) {
    sm[no] = sm[nl] + sm[nr];
    mn[no] = min(mn[nl], mn[nr]);
  }
  void update(int no, int l, int r, int i, int j, int v) {
    propagate(no, l, r);
    if(r < i || l > j) return;
    if(l >= i && r <= j) {
      lz[no] += v;
      propagate(no, l, r);
      return;
    }
    int mid = (l + r) >> 1;
    update(L[no], l, mid, i, j, v); update(R[no], mid + 1, r, i, j, v);
    join(no, L[no], R[no]);
  }
  int querySm(int no, int l, int r, int i, int j) {
    propagate(no, l, r);
    if(r < i || l > j) return 0;
    if(l >= i && r <= j) return sm[no];
    int mid = (l + r) >> 1;
    return querySm(L[no], l, mid, i, j) + querySm(R[no], mid + 1, r, i, j);
  }
  int queryMn(int no, int l, int r, int i, int j) {
    propagate(no, l, r);
    if(r < i || l > j) return INT_MAX;
    if(l >= i && r <= j) return mn[no];
    int mid = (l + r) >> 1;
    return min(queryMn(L[no], l, mid, i, j), queryMn(R[no], mid + 1, r, i, j));
  }
  void update(int l, int r, int v) {
    update(0, 0, n, l, r, v);
  }
  int querySm(int l, int r) {
    return querySm(0, 0, n, l, r);
  }
  int queryMn(int l, int r) {
    return queryMn(0, 0, n, l, r);
  }
};

int getRand() {
  int x = (rand() << 16) ^ (rand());
  x = abs(x);
  assert(x >= 0);
  return x;
}

int genRand(int l, int r) {
  int sz = (r - l + 1);
  int g = getRand() % sz;
  return l + g;
}

int GetSample(const std::set<int>& s) {
  double r = rand() % s.size();
  std::set<int>::iterator it = s.begin();
  for (; r != 0; r--) it++;
  return *it;
}

//Partial

class StackValidation: public ::testing::TestWithParam<int>{};

TEST_P(StackValidation, Validation) {
  map< int, int > used;
  Segtree tr;
  int n = GetParam();
  Retroactivity::PartialStack< int > rt;
  Brute::PartialStack< int > bt;

  set< int > ins, del;
  for(int i = 1; i <= n / 2; ++i) {
    int t, x;
    while(1) {
      t = genRand(1, N);
      if(used[t] == 0) break;
    }
    used[t] = 1;
    x = genRand(1, N);
    tr.update(t, N, 1);
    bt.Insert_Push(t, x);
    rt.Insert_Push(t, x);
    ins.insert(t);
    ASSERT_EQ(bt.peak(), rt.peak());
  }
  for(int i = 1; i <= n / 2; ++i) {
    int op = genRand(0, 3);
    if(op == 2 && ins.size() == 0) op = 1;
    if(op == 3 && del.size() == 0) op = 0;
    if(op == 0) {
      int t, x;
      while(1) {
        t = genRand(1, N);
        if(used[t] == 0) break;
      }
      used[t] = 1;
      x = genRand(1, N);
      bt.Insert_Push(t, x);
      rt.Insert_Push(t, x);
      ins.insert(t);
      tr.update(t, N, 1);
    }
    else if(op == 1) {
      int t; 
      while(1) {
        t = genRand(1, N);
        if(used[t] == 0 && tr.queryMn(t, N) >= 1) break;
      }
      used[t] = 1;
      bt.Insert_Pop(t);
      rt.Insert_Pop(t);
      del.insert(t);
      tr.update(t, N, -1);
    }
    else if(op == 2) {
      int t;
      while(1) {
        t = GetSample(ins);
        if(tr.querySm(t, t) >= 1 && tr.queryMn(t, N) >= 1) break;
      } 
      ins.erase(t);
      bt.Delete_Push(t);
      rt.Delete_Push(t);
      tr.update(t, N, -1);
    }
    else if(op == 3) {
      int t = GetSample(del);
      bt.Delete_Pop(t);
      rt.Delete_Pop(t);
      del.erase(t);
      tr.update(t, N, 1);
    }
    ASSERT_EQ(bt.peak(), rt.peak());
  }
}

class PartialStackSpeedBrute: public ::testing::TestWithParam<int>{};

TEST_P(PartialStackSpeedBrute, Brute) {
  map< int, int > used;
  Segtree tr;
  int n = GetParam();
  Brute::PartialStack< int > rt;
  for(int i = 1; i <= n / 2; ++i) {
    int t, x;
    while(1) {
      t = genRand(1, N);
      if(used[t] == 0) break;
    }
    used[t] = 1;
    x = genRand(1, N);
    tr.update(t, N, 1);
    rt.Insert_Push(t, x);
  }
  for(int i = 1; i <= n / 2; ++i) {
    int op = genRand(0, 1);
    if(op) {
      int t, x;
      while(1) {
        t = genRand(1, N);
        if(used[t] == 0) break;
      }
      used[t] = 1;
      x = genRand(1, N);
      rt.Insert_Push(t, x);
      tr.update(t, N, 1);
    }
    else {
      int t; 
      while(1) {
        t = genRand(1, N);
        if(used[t] == 0 && tr.queryMn(t, N) >= 1) break;
      }
      used[t] = 1;
      rt.Insert_Pop(t);
      tr.update(t, N, -1);
    }
    rt.peak();
  }
}

class PartialStackSpeed: public ::testing::TestWithParam<int>{};

TEST_P(PartialStackSpeed, Retroactive) {
  map< int, int > used;
  Segtree tr;
  int n = GetParam();
  Retroactivity::PartialStack< int > rt;
  for(int i = 1; i <= n / 2; ++i) {
    int t, x;
    while(1) {
      t = genRand(1, N);
      if(used[t] == 0) break;
    }
    used[t] = 1;
    x = genRand(1, N);
    tr.update(t, N, 1);
    rt.Insert_Push(t, x);
    //ASSERT_EQ(bt.peak(), rt.peak());
  }
  for(int i = 1; i <= n / 2; ++i) {
    int op = genRand(0, 1);
    if(op) {
      int t, x;
      while(1) {
        t = genRand(1, N);
        if(used[t] == 0) break;
      }
      used[t] = 1;
      x = genRand(1, N);
      rt.Insert_Push(t, x);
      tr.update(t, N, 1);
    }
    else {
      int t; 
      while(1) {
        t = genRand(1, N);
        if(used[t] == 0 && tr.queryMn(t, N) >= 1) break;
      }
      used[t] = 1;
      rt.Insert_Pop(t);
      tr.update(t, N, -1);
    }
    rt.peak();
  }
}

//Full

class StackFullValidation: public ::testing::TestWithParam<int>{};

TEST_P(StackFullValidation, Validation) {
  map< int, int > used;
  Segtree tr;
  int n = GetParam();
  Retroactivity::FullStack< int > rt;
  Brute::FullStack< int > bt;
  set< int > ins, del;
  for(int i = 1; i <= n / 2; ++i) {
    int t, x;
    while(1) {
      t = genRand(1, N);
      if(used[t] == 0) break;
    }
    used[t] = 1;
    x = genRand(1, N);
    tr.update(t, N, 1);
    bt.Insert_Push(t, x);
    rt.Insert_Push(t, x);
    ins.insert(t);
    ASSERT_EQ(bt.peak(t), rt.peak(t));
  }
   for(int i = 1; i <= n / 2; ++i) {
    int op = genRand(0, 2);
    if(op == 2 && ins.size() == 0) op = 1;
    if(op == 3 && del.size() == 0) op = 0;
    if(op == 0) {
      int t, x;
      while(1) {
        t = genRand(1, N);
        if(used[t] == 0) break;
      }
      used[t] = 1;
      x = genRand(1, N);
      bt.Insert_Push(t, x);
      rt.Insert_Push(t, x);
      ins.insert(t);
      tr.update(t, N, 1);
    }
    else if(op == 1) {
      int t; 
      while(1) {
        t = genRand(1, N);
        if(used[t] == 0 && tr.queryMn(t, N) >= 1) break;
      }
      used[t] = 1;
      bt.Insert_Pop(t);
      rt.Insert_Pop(t);
      del.insert(t);
      tr.update(t, N, -1);
    }
    else if(op == 2) {
      int t;
      while(1) {
        t = GetSample(ins);
        if(tr.querySm(t, t) >= 1 && tr.queryMn(t, N) >= 1) break;
      } 
      ins.erase(t);
      bt.Delete_Push(t);
      rt.Delete_Push(t);
      tr.update(t, N, -1);
    }
    else if(op == 3) {
      int t = GetSample(del);
      bt.Delete_Pop(t);
      rt.Delete_Pop(t);
      del.erase(t);
      tr.update(t, N, 1);
    }
    int t;
    while(1) {
      t = genRand(1, N);
      if(tr.querySm(t, t) >= 1) break;
    }
    ASSERT_EQ(bt.peak(t), rt.peak(t));
  }
}

class StackFullSpeedBrute: public ::testing::TestWithParam<int>{};

TEST_P(StackFullSpeedBrute, Validation) {
  map< int, int > used;
  Segtree tr;
  int n = GetParam();
  Brute::FullStack< int > bt;
  for(int i = 1; i <= n / 2; ++i) {
    int t, x;
    while(1) {
      t = genRand(1, N);
      if(used[t] == 0) break;
    }
    used[t] = 1;
    x = genRand(1, N);
    tr.update(t, N, 1);
    bt.Insert_Push(t, x);
    bt.peak(t);
  }
  for(int i = 1; i <= n / 2; ++i) {
    int t;
    while(1) {
      t = genRand(1, N);
      if(tr.querySm(t, t) >= 1) break;
    }
    bt.peak(t);
  }
}

class StackFullSpeedRetroactive: public ::testing::TestWithParam<int>{};

TEST_P(StackFullSpeedRetroactive, Validation) {
  map< int, int > used;
  Segtree tr;
  int n = GetParam();
  Retroactivity::FullStack< int > rt;
  for(int i = 1; i <= n / 2; ++i) {
    int t, x;
    while(1) {
      t = genRand(1, N);
      if(used[t] == 0) break;
    }
    used[t] = 1;
    x = genRand(1, N);
    tr.update(t, N, 1);
    rt.Insert_Push(t, x);
    rt.peak(t);
  }
  for(int i = 1; i <= n / 2; ++i) {
    int t;
    while(1) {
      t = genRand(1, N);
      if(tr.querySm(t, t) >= 1) break;
    }
    rt.peak(t);
  }
}

INSTANTIATE_TEST_CASE_P(TestPartialStack, StackValidation, ::testing::Range(50, 5000, 50));
INSTANTIATE_TEST_CASE_P(TestPartialStackSpeedBrute, PartialStackSpeedBrute, ::testing::Range(500, 5000, 50));
INSTANTIATE_TEST_CASE_P(Partial, PartialStackSpeed, ::testing::Range(500, 5000, 50));

INSTANTIATE_TEST_CASE_P(TestFullStack, StackFullValidation, ::testing::Range(50, 5000, 50));
INSTANTIATE_TEST_CASE_P(FullStackSpeedBrute, StackFullSpeedBrute, ::testing::Range(500, 5000, 50));
INSTANTIATE_TEST_CASE_P(FullStackSpeedBrute, StackFullSpeedRetroactive, ::testing::Range(500, 5000, 50));


int main(int argc, char **argv) {
  srand(time(NULL));
  testing::InitGoogleTest(&argc, argv);  
  return RUN_ALL_TESTS();
}