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


// //PARTIAL STACK

// TEST(PartialStackValidation, Int1000) {
//   memset(bit, 0, sizeof bit);
//   memset(used, 0, sizeof used);
//   int n = 1000;
//   Brute::PartialStack< int > bt;
//   Retroactivity::PartialStack< int > st;
//   for(int i = 1; i <= n / 10; ++i) {
//     int t, x;
//     while(1) {
//       t = genRand(1, n);
//       if(used[t] == 0) break;
//     }
//     used[t] = 1;
//     x = genRand(1, (int)1e9);
//     update(t, 1);
//     bt.Insert_Push(t, x);
//     st.Insert_Push(t, x);
//     ASSERT_EQ(bt.peak(), st.peak());
//   }
//   for(int i = 1; i <= n / 10; ++i) {
//     int op = genRand(0, 1);
//     if(op) {
//       int t, x;
//       while(1) {
//         t = genRand(1, n);
//         if(used[t] == 0) break;
//       }
//       used[t] = 1;
//       x = genRand(1, (int)1e9);
//       bt.Insert_Push(t, x);
//       st.Insert_Push(t, x);
//       update(t, 1);
//     }
//     else {
//       int t; 
//       while(1) {
//         t = genRand(1, n);
//         if(used[t] == 0 && gs(t) >= 2) break;
//       }
//       used[t] = 1;
//       bt.Insert_Pop(t);
//       st.Insert_Pop(t);
//       update(t, -1);
//     }
//     ASSERT_EQ(bt.peak(), st.peak());
//   }
// }

// TEST(PartialStackValidation, Int10000) {
//   memset(bit, 0, sizeof bit);
//   memset(used, 0, sizeof used);
//   int n = 10000;
//   Brute::PartialStack< int > bt;
//   Retroactivity::PartialStack< int > st;
//   for(int i = 1; i <= n / 10; ++i) {
//     int t, x;
//     while(1) {
//       t = genRand(1, n);
//       if(used[t] == 0) break;
//     }
//     used[t] = 1;
//     x = genRand(1, (int)1e9);
//     update(t, 1);
//     bt.Insert_Push(t, x);
//     st.Insert_Push(t, x);
//     ASSERT_EQ(bt.peak(), st.peak());
//   }
//   for(int i = 1; i <= n / 10; ++i) {
//     int op = genRand(0, 1);
//     if(op) {
//       int t, x;
//       while(1) {
//         t = genRand(1, n);
//         if(used[t] == 0) break;
//       }
//       used[t] = 1;
//       x = genRand(1, (int)1e9);
//       bt.Insert_Push(t, x);
//       st.Insert_Push(t, x);
//       update(t, 1);
//     }
//     else {
//       int t; 
//       while(1) {
//         t = genRand(1, n);
//         if(used[t] == 0 && gs(t) >= 2) break;
//       }
//       used[t] = 1;
//       bt.Insert_Pop(t);
//       st.Insert_Pop(t);
//       update(t, -1);
//     }
//     ASSERT_EQ(bt.peak(), st.peak());
//   }
// }

// TEST(PartialStackValidation, Int50000) {
//   memset(bit, 0, sizeof bit);
//   memset(used, 0, sizeof used);
//   int n = 50000;
//   Brute::PartialStack< int > bt;
//   Retroactivity::PartialStack< int > st;
//   for(int i = 1; i <= n / 10; ++i) {
//     int t, x;
//     while(1) {
//       t = genRand(1, n);
//       if(used[t] == 0) break;
//     }
//     used[t] = 1;
//     x = genRand(1, (int)1e9);
//     update(t, 1);
//     bt.Insert_Push(t, x);
//     st.Insert_Push(t, x);
//     ASSERT_EQ(bt.peak(), st.peak());
//   }
//   for(int i = 1; i <= n / 10; ++i) {
//     int op = genRand(0, 1);
//     if(op) {
//       int t, x;
//       while(1) {
//         t = genRand(1, n);
//         if(used[t] == 0) break;
//       }
//       used[t] = 1;
//       x = genRand(1, (int)1e9);
//       bt.Insert_Push(t, x);
//       st.Insert_Push(t, x);
//       update(t, 1);
//     }
//     else {
//       int t; 
//       while(1) {
//         t = genRand(1, n);
//         if(used[t] == 0 && gs(t) >= 2) break;
//       }
//       used[t] = 1;
//       bt.Insert_Pop(t);
//       st.Insert_Pop(t);
//       update(t, -1);
//     }
//     ASSERT_EQ(bt.peak(), st.peak());
//   }
// }

// TEST(PartialStackValidation, Int100000) {
//   memset(bit, 0, sizeof bit);
//   memset(used, 0, sizeof used);
//   int n = 100000;
//   Brute::PartialStack< int > bt;
//   Retroactivity::PartialStack< int > st;
//   for(int i = 1; i <= n / 10; ++i) {
//     int t, x;
//     while(1) {
//       t = genRand(1, n);
//       if(used[t] == 0) break;
//     }
//     used[t] = 1;
//     x = genRand(1, (int)1e9);
//     update(t, 1);
//     bt.Insert_Push(t, x);
//     st.Insert_Push(t, x);
//     ASSERT_EQ(bt.peak(), st.peak());
//   }
//   for(int i = 1; i <= n / 10; ++i) {
//     int op = genRand(0, 1);
//     if(op) {
//       int t, x;
//       while(1) {
//         t = genRand(1, n);
//         if(used[t] == 0) break;
//       }
//       used[t] = 1;
//       x = genRand(1, (int)1e9);
//       bt.Insert_Push(t, x);
//       st.Insert_Push(t, x);
//       update(t, 1);
//     }
//     else {
//       int t; 
//       while(1) {
//         t = genRand(1, n);
//         if(used[t] == 0 && gs(t) >= 2) break;
//       }
//       used[t] = 1;
//       bt.Insert_Pop(t);
//       st.Insert_Pop(t);
//       update(t, -1);
//     }
//     ASSERT_EQ(bt.peak(), st.peak());
//   }
// }

// TEST(StackSpeed, PartialInt100000) {
//   memset(bit, 0, sizeof bit);
//   memset(used, 0, sizeof used);
//   int n = 100000;
//   Retroactivity::PartialStack< int > st;
//   for(int i = 1; i <= n / 10; ++i) {
//     int t, x;
//     while(1) {
//       t = genRand(1, n);
//       if(used[t] == 0) break;
//     }
//     used[t] = 1;
//     x = genRand(1, (int)1e9);
//     update(t, 1);
//     st.Insert_Push(t, x);
//     st.peak();
//   }
//   for(int i = 1; i <= n / 10; ++i) {
//     int op = genRand(0, 1);
//     if(op) {
//       int t, x;
//       while(1) {
//         t = genRand(1, n);
//         if(used[t] == 0) break;
//       }
//       used[t] = 1;
//       x = genRand(1, (int)1e9);
//       st.Insert_Push(t, x);
//       update(t, 1);
//     }
//     else {
//       int t; 
//       while(1) {
//         t = genRand(1, n);
//         if(used[t] == 0 && gs(t) >= 2) break;
//       }
//       used[t] = 1;
//       st.Insert_Pop(t);
//       update(t, -1);
//     }
//     st.peak();
//   }
// }

// TEST(StackSpeed, BruteInt100000) {
//   memset(bit, 0, sizeof bit);
//   memset(used, 0, sizeof used);
//   int n = 100000;
//   Brute::PartialStack< int > st;
//   for(int i = 1; i <= n / 10; ++i) {
//     int t, x;
//     while(1) {
//       t = genRand(1, n);
//       if(used[t] == 0) break;
//     }
//     used[t] = 1;
//     x = genRand(1, (int)1e9);
//     update(t, 1);
//     st.Insert_Push(t, x);
//     st.peak();
//   }
//   for(int i = 1; i <= n / 10; ++i) {
//     int op = genRand(0, 1);
//     if(op) {
//       int t, x;
//       while(1) {
//         t = genRand(1, n);
//         if(used[t] == 0) break;
//       }
//       used[t] = 1;
//       x = genRand(1, (int)1e9);
//       st.Insert_Push(t, x);
//       update(t, 1);
//     }
//     else {
//       int t; 
//       while(1) {
//         t = genRand(1, n);
//         if(used[t] == 0 && gs(t) >= 2) break;
//       }
//       used[t] = 1;
//       st.Insert_Pop(t);
//       update(t, -1);
//     }
//     st.peak();
//   }
// }




// //FULL STACk

// TEST(FullStackValidation, Int1000) {
//   memset(bit, 0, sizeof bit);
//   memset(used, 0, sizeof used);
//   int n = 1000;
//   Brute::FullStack< int > bt;
//   Retroactivity::FullStack< int > st;
//   for(int i = 1; i <= n / 10; ++i) {
//     int t, x;
//     while(1) {
//       t = genRand(1, n);
//       if(used[t] == 0) break;
//     }
//     used[t] = 1;
//     x = genRand(1, (int)1e9);
//     update(t, 1);
//     bt.Insert_Push(t, x);
//     st.Insert_Push(t, x);
//     while(1) {
//       t = genRand(1, n);
//       if(!bt.empty(t)) break;
//     }
//     ASSERT_EQ(bt.peak(t), st.peak(t));
//   }
//   for(int i = 1; i <= n / 10; ++i) {
//     int op = genRand(0, 1);
//     if(op) {
//       int t, x;
//       while(1) {
//         t = genRand(1, n);
//         if(used[t] == 0) break;
//       }
//       used[t] = 1;
//       x = genRand(1, (int)1e9);
//       bt.Insert_Push(t, x);
//       st.Insert_Push(t, x);
//       update(t, 1);
//     }
//     else {
//       int t; 
//       while(1) {
//         t = genRand(1, n);
//         if(used[t] == 0 && gs(t) >= 2) break;
//       }
//       used[t] = 1;
//       bt.Insert_Pop(t);
//       st.Insert_Pop(t);
//       update(t, -1);
//     }
//     int t;
//     while(1) {
//       t = genRand(1, n);
//       if(!bt.empty(t)) break;
//     }
//     ASSERT_EQ(bt.peak(t), st.peak(t));
//   }
// }

// TEST(FullStackValidation, Int10000) {
//   memset(bit, 0, sizeof bit);
//   memset(used, 0, sizeof used);
//   int n = 10000;
//   Brute::FullStack< int > bt;
//   Retroactivity::FullStack< int > st;
//   for(int i = 1; i <= n / 10; ++i) {
//     int t, x;
//     while(1) {
//       t = genRand(1, n);
//       if(used[t] == 0) break;
//     }
//     used[t] = 1;
//     x = genRand(1, (int)1e9);
//     update(t, 1);
//     bt.Insert_Push(t, x);
//     st.Insert_Push(t, x);
//     while(1) {
//       t = genRand(1, n);
//       if(!bt.empty(t)) break;
//     }
//     ASSERT_EQ(bt.peak(t), st.peak(t));
//   }
//   for(int i = 1; i <= n / 10; ++i) {
//     int op = genRand(0, 1);
//     if(op) {
//       int t, x;
//       while(1) {
//         t = genRand(1, n);
//         if(used[t] == 0) break;
//       }
//       used[t] = 1;
//       x = genRand(1, (int)1e9);
//       bt.Insert_Push(t, x);
//       st.Insert_Push(t, x);
//       update(t, 1);
//     }
//     else {
//       int t; 
//       while(1) {
//         t = genRand(1, n);
//         if(used[t] == 0 && gs(t) >= 2) break;
//       }
//       used[t] = 1;
//       bt.Insert_Pop(t);
//       st.Insert_Pop(t);
//       update(t, -1);
//     }
//     int t;
//     while(1) {
//       t = genRand(1, n);
//       if(!bt.empty(t)) break;
//     }
//     ASSERT_EQ(bt.peak(t), st.peak(t));
//   }
// }

// TEST(FullStackValidation, Int100000) {
//   memset(bit, 0, sizeof bit);
//   memset(used, 0, sizeof used);
//   int n = 100000;
//   Brute::FullStack< int > bt;
//   Retroactivity::FullStack< int > st;
//   for(int i = 1; i <= n / 10; ++i) {
//     int t, x;
//     while(1) {
//       t = genRand(1, n);
//       if(used[t] == 0) break;
//     }
//     used[t] = 1;
//     x = genRand(1, (int)1e9);
//     update(t, 1);
//     bt.Insert_Push(t, x);
//     st.Insert_Push(t, x);
//     while(1) {
//       t = genRand(1, n);
//       if(!bt.empty(t)) break;
//     }
//     ASSERT_EQ(bt.peak(t), st.peak(t));
//   }
//   for(int i = 1; i <= n / 10; ++i) {
//     int op = genRand(0, 1);
//     if(op) {
//       int t, x;
//       while(1) {
//         t = genRand(1, n);
//         if(used[t] == 0) break;
//       }
//       used[t] = 1;
//       x = genRand(1, (int)1e9);
//       bt.Insert_Push(t, x);
//       st.Insert_Push(t, x);
//       update(t, 1);
//     }
//     else {
//       int t; 
//       while(1) {
//         t = genRand(1, n);
//         if(used[t] == 0 && gs(t) >= 2) break;
//       }
//       used[t] = 1;
//       bt.Insert_Pop(t);
//       st.Insert_Pop(t);
//       update(t, -1);
//     }
//     int t;
//     while(1) {
//       t = genRand(1, n);
//       if(!bt.empty(t)) break;
//     }
//     ASSERT_EQ(bt.peak(t), st.peak(t));
//   }
// }

//Partial


class StackValidation: public ::testing::TestWithParam<int>{};

TEST_P(StackValidation, Validation) {
  map< int, int > used;
  Segtree tr;
  int n = GetParam();
  Retroactivity::PartialStack< int > rt;
  Brute::PartialStack< int > bt;
  for(int i = 1; i <= n; ++i) {
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
  for(int i = 1; i <= n; ++i) {
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

INSTANTIATE_TEST_CASE_P(TestPartialStack, StackValidation, ::testing::Range(500, 5000, 500));


class StackSpeedBrute: public ::testing::TestWithParam<int>{};

TEST_P(StackSpeedBrute, Validation) {
  map< int, int > used;
  Segtree tr;
  int n = GetParam();
  Brute::PartialStack< int > rt;
  for(int i = 1; i <= n; ++i) {
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
  for(int i = 1; i <= n; ++i) {
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

INSTANTIATE_TEST_CASE_P(TestStackSpeedBrute, StackSpeedBrute, ::testing::Range(500, 5000, 50));



class StackSpeedRetroactive: public ::testing::TestWithParam<int>{};

TEST_P(StackSpeedRetroactive, Retroactive) {
  map< int, int > used;
  Segtree tr;
  int n = GetParam();
  Retroactivity::PartialStack< int > rt;
  for(int i = 1; i <= n; ++i) {
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
  for(int i = 1; i <= n; ++i) {
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

INSTANTIATE_TEST_CASE_P(Partial, StackSpeedRetroactive, ::testing::Range(500, 5000, 50));

//Full

// class StackFullValidation: public ::testing::TestWithParam<int>{};

// TEST_P(StackFullValidation, Validation) {
//   memset(bit, 0, sizeof bit);
//   memset(used, 0, sizeof used);
//   int n = GetParam();
//   Brute::FullStack< int > bt;
//   Retroactivity::FullStack< int > st;
//   for(int i = 1; i <= n / 10; ++i) {
//     int t, x;
//     while(1) {
//       t = genRand(1, n);
//       if(used[t] == 0) break;
//     }
//     used[t] = 1;
//     x = genRand(1, (int)1e9);
//     update(t, 1);
//     bt.Insert_Push(t, x);
//     st.Insert_Push(t, x);
//     while(1) {
//       t = genRand(1, n);
//       if(!bt.empty(t)) break;
//     }
//     ASSERT_EQ(bt.peak(t), st.peak(t));
//   }
//   for(int i = 1; i <= n / 10; ++i) {
//     int op = genRand(0, 1);
//     if(op) {
//       int t, x;
//       while(1) {
//         t = genRand(1, n);
//         if(used[t] == 0) break;
//       }
//       used[t] = 1;
//       x = genRand(1, (int)1e9);
//       bt.Insert_Push(t, x);
//       st.Insert_Push(t, x);
//       update(t, 1);
//     }
//     else {
//       int t; 
//       while(1) {
//         t = genRand(1, n);
//         if(used[t] == 0 && gs(t) >= 2) break;
//       }
//       used[t] = 1;
//       bt.Insert_Pop(t);
//       st.Insert_Pop(t);
//       update(t, -1);
//     }
//     int t;
//     while(1) {
//       t = genRand(1, n);
//       if(!bt.empty(t)) break;
//     }
//     ASSERT_EQ(bt.peak(t), st.peak(t));
//   }
// }


// class FullStackSpeed: public ::testing::TestWithParam<int>{};

// TEST_P(FullStackSpeed, Speed) {
//   memset(bit, 0, sizeof bit);
//   memset(used, 0, sizeof used);
//   int n = GetParam();
//   Brute::FullStack< int > bt;
//   Retroactivity::FullStack< int > st;
//   for(int i = 1; i <= n / 10; ++i) {
//     int t, x;
//     while(1) {
//       t = genRand(1, n);
//       if(used[t] == 0) break;
//     }
//     used[t] = 1;
//     x = genRand(1, (int)1e9);
//     update(t, 1);
//     bt.Insert_Push(t, x);
//     st.Insert_Push(t, x);
//     while(1) {
//       t = genRand(1, n);
//       if(!bt.empty(t)) break;
//     }
//     ASSERT_EQ(bt.peak(t), st.peak(t));
//   }
//   for(int i = 1; i <= n / 10; ++i) {
//     int op = genRand(0, 1);
//     if(op) {
//       int t, x;
//       while(1) {
//         t = genRand(1, n);
//         if(used[t] == 0) break;
//       }
//       used[t] = 1;
//       x = genRand(1, (int)1e9);
//       bt.Insert_Push(t, x);
//       st.Insert_Push(t, x);
//       update(t, 1);
//     }
//     else {
//       int t; 
//       while(1) {
//         t = genRand(1, n);
//         if(used[t] == 0 && gs(t) >= 2) break;
//       }
//       used[t] = 1;
//       bt.Insert_Pop(t);
//       st.Insert_Pop(t);
//       update(t, -1);
//     }
//     int t;
//     while(1) {
//       t = genRand(1, n);
//       if(!bt.empty(t)) break;
//     }
//     ASSERT_EQ(bt.peak(t), st.peak(t));
//   }
// }


// class FullStackSpeedBrute: public ::testing::TestWithParam<int>{};

// TEST_P(FullStackSpeedBrute, Speed) {
//   memset(bit, 0, sizeof bit);
//   memset(used, 0, sizeof used);
//   int n = GetParam();
//   Brute::FullStack< int > bt;
//   //Retroactivity::FullStack< int > st;
//   for(int i = 1; i <= n / 10; ++i) {
//     int t, x;
//     while(1) {
//       t = genRand(1, n);
//       if(used[t] == 0) break;
//     }
//     used[t] = 1;
//     x = genRand(1, (int)1e9);
//     update(t, 1);
//     bt.Insert_Push(t, x);
//     //st.Insert_Push(t, x);
//     while(1) {
//       t = genRand(1, n);
//       if(!bt.empty(t)) break;
//     }
//     //ASSERT_EQ(bt.peak(t), st.peak(t));
//   }
//   for(int i = 1; i <= n / 10; ++i) {
//     int op = genRand(0, 1);
//     if(op) {
//       int t, x;
//       while(1) {
//         t = genRand(1, n);
//         if(used[t] == 0) break;
//       }
//       used[t] = 1;
//       x = genRand(1, (int)1e9);
//       bt.Insert_Push(t, x);
//       //st.Insert_Push(t, x);
//       update(t, 1);
//     }
//     else {
//       int t; 
//       while(1) {
//         t = genRand(1, n);
//         if(used[t] == 0 && gs(t) >= 2) break;
//       }
//       used[t] = 1;
//       bt.Insert_Pop(t);
//       //st.Insert_Pop(t);
//       update(t, -1);
//     }
//     int t;
//     while(1) {
//       t = genRand(1, n);
//       if(!bt.empty(t)) break;
//     }
//     //ASSERT_EQ(bt.peak(t), st.peak(t));
//   }
// }

// INSTANTIATE_TEST_CASE_P(TestFullStack, StackFullValidation, ::testing::Range(50, 5000, 50));
// INSTANTIATE_TEST_CASE_P(TestPartialFullStackSpeed, FullStackSpeed, ::testing::Range(50, 5000, 50));
// INSTANTIATE_TEST_CASE_P(TestPartialFullStackSpeedBrute, FullStackSpeedBrute, ::testing::Range(50, 5000, 50));


int main(int argc, char **argv) {
  srand(time(NULL));
  testing::InitGoogleTest(&argc, argv);  
  return RUN_ALL_TESTS();
}