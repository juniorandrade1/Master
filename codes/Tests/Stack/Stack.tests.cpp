#include "../../Stack/Stack.cpp"
#include <gtest/gtest.h>

const int N = (int)2e5 + 1;

class Segtree {
public:
  vector< int > sm, mn;
  vector< int > lz;
  Segtree(){
    sm.resize(4 * N);
    mn.resize(4 * N);
    lz.resize(4 * N);
  };
  void propagate(int no, int l, int r) {
    sm[no] += (r - l + 1) * lz[no];
    mn[no] += lz[no];
    if(l != r) {
      int nxt = (no << 1);
      lz[nxt] += lz[no];
      lz[nxt + 1] += lz[no];
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
    int nxt = (no << 1), mid = (l + r) >> 1;
    update(nxt, l, mid, i, j, v); update(nxt + 1, mid + 1, r, i, j, v);
    join(no, nxt, nxt + 1);
  }
  int querySm(int no, int l, int r, int i, int j) {
    propagate(no, l, r);
    if(r < i || l > j) return 0;
    if(l >= i && r <= j) return sm[no];
    int nxt = (no << 1), mid = (l + r) >> 1;
    return querySm(nxt, l, mid, i, j) + querySm(nxt + 1, mid + 1, r, i, j);
  }
  int queryMn(int no, int l, int r, int i, int j) {
    propagate(no, l, r);
    if(r < i || l > j) return INT_MAX;
    if(l >= i && r <= j) return mn[no];
    int nxt = (no << 1), mid = (l + r) >> 1;
    return min(queryMn(nxt, l, mid, i, j), queryMn(nxt + 1, mid + 1, r, i, j));
  }
  void update(int l, int r, int v) {
    update(1, 0, N, l, r, v);
  }
  int querySm(int l, int r) {
    return querySm(1, 0, N, l, r);
  }
  int queryMn(int l, int r) {
    return queryMn(1, 0, N, l, r);
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

//Partial

class StackValidation: public ::testing::TestWithParam<int>{};

TEST_P(StackValidation, Validation) {
  map< int, int > used;
  Segtree tr;
  int n = GetParam();
  Retroactivity::PartialStack< int > rt;
  Brute::PartialStack< int > bt;
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
    ASSERT_EQ(bt.peak(), rt.peak());
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
      bt.Insert_Push(t, x);
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
      bt.Insert_Pop(t);
      rt.Insert_Pop(t);
      tr.update(t, N, -1);
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
      //bt.Insert_Pop(t);
      rt.Insert_Pop(t);
      tr.update(t, N, -1);
    }
    //ASSERT_EQ(bt.peak(), rt.peak());
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
    ASSERT_EQ(bt.peak(t), rt.peak(t));
  }
  for(int i = 1; i <= n / 2; ++i) {
    int t;
    while(1) {
      t = genRand(1, N);
      if(tr.querySm(t, t) >= 1) break;
    }
    ASSERT_EQ(bt.peak(t), rt.peak(t));
    ASSERT_EQ(bt.peak(t), rt.peak(t));
  }
}

class StackFullSpeedBrute: public ::testing::TestWithParam<int>{};

TEST_P(StackFullSpeedBrute, Validation) {
  map< int, int > used;
  Segtree tr;
  int n = GetParam();
  //Retroactivity::FullStack< int > rt;
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
    //rt.Insert_Push(t, x);
    //ASSERT_EQ(bt.peak(t), rt.peak(t));
    bt.peak(t);
  }
  for(int i = 1; i <= n / 2; ++i) {
    int t;
    while(1) {
      t = genRand(1, N);
      if(tr.querySm(t, t) >= 1) break;
    }
    //ASSERT_EQ(bt.peak(t), rt.peak(t));
    bt.peak(t);
    bt.peak(t);
  }
}



class StackFullSpeedRetroactive: public ::testing::TestWithParam<int>{};

TEST_P(StackFullSpeedRetroactive, Validation) {
  map< int, int > used;
  Segtree tr;
  int n = GetParam();
  Retroactivity::FullStack< int > rt;
  //Brute::FullStack< int > bt;
  for(int i = 1; i <= n / 2; ++i) {
    int t, x;
    while(1) {
      t = genRand(1, N);
      if(used[t] == 0) break;
    }
    used[t] = 1;
    x = genRand(1, N);
    tr.update(t, N, 1);
    //bt.Insert_Push(t, x);
    rt.Insert_Push(t, x);
    //ASSERT_EQ(bt.peak(t), rt.peak(t));
    rt.peak(t);
  }
  for(int i = 1; i <= n / 2; ++i) {
    int t;
    while(1) {
      t = genRand(1, N);
      if(tr.querySm(t, t) >= 1) break;
    }
    //ASSERT_EQ(bt.peak(t), rt.peak(t));
    rt.peak(t);
    rt.peak(t);
  }
}

INSTANTIATE_TEST_CASE_P(TestPartialStack, StackValidation, ::testing::Range(500, 5000, 500));
INSTANTIATE_TEST_CASE_P(TestPartialStackSpeedBrute, PartialStackSpeedBrute, ::testing::Range(500, 5000, 50));
INSTANTIATE_TEST_CASE_P(Partial, PartialStackSpeed, ::testing::Range(500, 5000, 50));

INSTANTIATE_TEST_CASE_P(TestFullStack, StackFullValidation, ::testing::Range(500, 5000, 500));
INSTANTIATE_TEST_CASE_P(FullStackSpeedBrute, StackFullSpeedBrute, ::testing::Range(500, 5000, 50));
INSTANTIATE_TEST_CASE_P(FullStackSpeedBrute, StackFullSpeedRetroactive, ::testing::Range(500, 5000, 50));


int main(int argc, char **argv) {
  srand(time(NULL));
  testing::InitGoogleTest(&argc, argv);  
  return RUN_ALL_TESTS();
}