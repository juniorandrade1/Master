#include "../../Priority_Queue/Priority_queue.hpp"
#include "../../Priority_Queue/Polylogarithm_Priority_Queue.cpp"
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


class PartialPriorityQueueValidation: public ::testing::TestWithParam<int>{};

TEST_P(PartialPriorityQueueValidation, Validation) {
  Retroactivity::PartialPriorityQueue< int > rq;
  Brute::PartialPriorityQueue< int > bq;
  int n = GetParam();
  map< int, int > used;
  Segtree tr;
  set< int > ins;
  set< int > del;
  for(int i = 0; i < n / 2; ++i) {
    int x = genRand(0, N);
    int t;
    while(1) {
      t = genRand(0, N);
      if(!used[t]) break;
    }
    used[t] = 1;
    rq.insertPush(t, x);
    bq.insertPush(t, x);
    tr.update(t, N, 1);
    ins.insert(t);

    if(!bq.empty()) ASSERT_EQ(rq.getPeak(), bq.getPeak());
    else ASSERT_EQ(rq.empty(), bq.empty());
  }
  for(int i = 0; i < n / 2; ++i) {
    int op = genRand(0, 3);
    if(op == 2 && ins.size() == 0) op = 1;
    if(op == 3 && del.size() == 0) op = 0;
    if(op == 0) {
      int x = genRand(0, N);
      int t;
      while(1) {
        t = genRand(0, N);
        if(!used[t]) break;
      }
      used[t] = 1;
      rq.insertPush(t, x);
      bq.insertPush(t, x);
      tr.update(t, N, 1);
    }
    else if(op == 1) {
      int t;
      while(1) {
        t = genRand(0, N);
        if(!used[t] && tr.queryMn(t, N) >= 1) break;
      }
      used[t] = 1;
      bq.insertPop(t);
      rq.insertPop(t);
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
      rq.removePush(t);
      bq.removePush(t);
      tr.update(t, N, -1);
    }
    else if(op == 3) {
      int t = GetSample(del);
      rq.removePop(t);
      bq.removePop(t);
      del.erase(t);
      tr.update(t, N, 1);
    }

    if(!bq.empty()) ASSERT_EQ(rq.getPeak(), bq.getPeak());
    else ASSERT_EQ(rq.empty(), bq.empty());
  }
}

class PartialBrutePriorityQueueSpeed: public ::testing::TestWithParam<int>{};

TEST_P(PartialBrutePriorityQueueSpeed, BruteSpeed) {
  Brute::PartialPriorityQueue< int > bq;
  int n = GetParam();
  map< int, int > used;
  Segtree tr;
  set< int > ins;
  set< int > del;
  for(int i = 0; i < n / 2; ++i) {
    int x = genRand(0, N);
    int t;
    while(1) {
      t = genRand(0, N);
      if(!used[t]) break;
    }
    used[t] = 1;
    bq.insertPush(t, x);
    tr.update(t, N, 1);
    ins.insert(t);

    if(!bq.empty()) bq.getPeak();
  }
  for(int i = 0; i < n / 2; ++i) {
    int op = genRand(0, 3);
    if(op == 2 && ins.size() == 0) op = 1;
    if(op == 3 && del.size() == 0) op = 0;
    if(op == 0) {
      int x = genRand(0, N);
      int t;
      while(1) {
        t = genRand(0, N);
        if(!used[t]) break;
      }
      used[t] = 1;
      bq.insertPush(t, x);
      tr.update(t, N, 1);
    }
    else if(op == 1) {
      int t;
      while(1) {
        t = genRand(0, N);
        if(!used[t] && tr.queryMn(t, N) >= 1) break;
      }
      used[t] = 1;
      bq.insertPop(t);
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
      bq.removePush(t);
      tr.update(t, N, -1);
    }
    else if(op == 3) {
      int t = GetSample(del);
      bq.removePop(t);
      del.erase(t);
      tr.update(t, N, 1);
    }

    if(!bq.empty()) bq.getPeak();
  }
}

class PartialRetroactivePriorityQueueSpeed: public ::testing::TestWithParam<int>{};

TEST_P(PartialRetroactivePriorityQueueSpeed, RetroactiveSpeed) {
  Retroactivity::PartialPriorityQueue< int > rq;
  int n = GetParam();
  map< int, int > used;
  Segtree tr;
  set< int > ins;
  set< int > del;
  for(int i = 0; i < n / 2; ++i) {
    int x = genRand(0, N);
    int t;
    while(1) {
      t = genRand(0, N);
      if(!used[t]) break;
    }
    used[t] = 1;
    rq.insertPush(t, x);
    tr.update(t, N, 1);
    ins.insert(t);
    if(!rq.empty()) rq.getPeak();
  }
  for(int i = 0; i < n / 2; ++i) {
    int op = genRand(0, 3);
    if(op == 2 && ins.size() == 0) op = 1;
    if(op == 3 && del.size() == 0) op = 0;
    if(op == 0) {
      int x = genRand(0, N);
      int t;
      while(1) {
        t = genRand(0, N);
        if(!used[t]) break;
      }
      used[t] = 1;
      rq.insertPush(t, x);
      tr.update(t, N, 1);
    }
    else if(op == 1) {
      int t;
      while(1) {
        t = genRand(0, N);
        if(!used[t] && tr.queryMn(t, N) >= 1) break;
      }
      used[t] = 1;
      rq.insertPop(t);
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
      rq.removePush(t);
      tr.update(t, N, -1);
    }
    else if(op == 3) {
      int t = GetSample(del);
      rq.removePop(t);
      del.erase(t);
      tr.update(t, N, 1);
    }
    if(!rq.empty()) rq.getPeak();
  }
}

// INSTANTIATE_TEST_CASE_P(TestPartialPriorityQueueValidation, PartialPriorityQueueValidation, ::testing::Range(1000, 5000, 1000));
// INSTANTIATE_TEST_CASE_P(RetroactiveSpeedTest, PartialRetroactivePriorityQueueSpeed, ::testing::Range(50, 5000, 50));
// INSTANTIATE_TEST_CASE_P(BruteSpeedTest, PartialBrutePriorityQueueSpeed, ::testing::Range(50, 5000, 50));



class FullPriorityQueueValidation: public ::testing::TestWithParam<int>{};

TEST_P(FullPriorityQueueValidation, Validation) {
  Retroactivity::FullPriorityQueue< int > rq;
  Brute::FullPriorityQueue< int > bq;
  int n = GetParam();
  map< int, int > used;
  Segtree tr;
  set< int > ins;
  set< int > del;
  for(int i = 0; i < (n + 1) / 2; ++i) {
    int x = genRand(1, N);
    int t;
    while(1) {
      t = genRand(1, N);
      if(!used[t]) break;
    }
    used[t] = 1;
    rq.insertPush(t, x);
    bq.insertPush(t, x);
    tr.update(t, N, 1);
    ins.insert(t);

    t = genRand(1, N);
    ASSERT_EQ(rq.empty(t), bq.empty(t));
    if(!rq.empty(t)) ASSERT_EQ(rq.getPeak(t), bq.getPeak(t));
  }

  for(int i = 0; i < n / 2; ++i) {
    int op = genRand(0, 1);
    if(op == 2 && ins.size() == 0) op = 1;
    if(op == 3 && del.size() == 0) op = 0;
    //printf("== %d\n", op);
    if(op == 0) {
      int x = genRand(0, N);
      int t;
      while(1) {
        t = genRand(0, N);
        if(!used[t]) break;
      }
      used[t] = 1;
      rq.insertPush(t, x);
      bq.insertPush(t, x);
      tr.update(t, N, 1);
    }
    else if(op == 1) {
      int t;
      while(1) {
        t = genRand(0, N);
        if(!used[t] && tr.queryMn(t, N) > 1) break;
      }
      used[t] = 1;
      bq.insertPop(t);
      rq.insertPop(t);
      del.insert(t);
      tr.update(t, N, -1);
    }
    else if(op == 2) {
      int t;
      while(1) {
        t = GetSample(ins);
        if(tr.queryMn(t, N) > 1) break;
      } 
      ins.erase(t);
      rq.removePush(t);
      bq.removePush(t);
      tr.update(t, N, -1);
    }
    else if(op == 3) {
      int t = GetSample(del);
      rq.removePop(t);
      bq.removePop(t);
      del.erase(t);
      tr.update(t, N, 1);
    }

    int t = genRand(0, N);
    ASSERT_EQ(rq.empty(t), bq.empty(t));
    if(!rq.empty(t)) ASSERT_EQ(rq.getPeak(t), bq.getPeak(t));
  }
}


class FullBrutePriorityQueueSpeed: public ::testing::TestWithParam<int>{};

TEST_P(FullBrutePriorityQueueSpeed, BruteSpeed) {
  Brute::FullPriorityQueue< int > rq;
  int n = GetParam();
  map< int, int > used;
  Segtree tr;
  set< int > ins;
  set< int > del;

  vector< int > p(n + 1);
  for(int i = 0; i < n + 1; ++i) p[i] = i + 1;
  
  random_shuffle(p.begin(), p.end());


  for(int i = 0; i < (n + 1) / 2; ++i) {
    int x = p[i];
    int t;
    while(1) {
      t = genRand(0, N);
      if(!used[t]) break;
    }
    used[t] = 1;
    rq.insertPush(t, x);
    tr.update(t, N, 1);
    ins.insert(t);

    t = genRand(0, N);
    rq.getPeak(t);
  }
  for(int i = (n + 1) / 2; i < n; ++i) {
    int op = genRand(0, 3);
    if(op == 2 && ins.size() == 0) op = 1;
    if(op == 3 && del.size() == 0) op = 0;
    if(op == 0) {
      int x = p[i];
      int t;
      while(1) {
        t = genRand(0, N);
        if(!used[t]) break;
      }
      used[t] = 1;
      rq.insertPush(t, x);
      tr.update(t, N, 1);
    }
    else if(op == 1) {
      int t;
      while(1) {
        t = genRand(0, N);
        if(!used[t] && tr.queryMn(t, N) > 1) break;
      }
      used[t] = 1;
      rq.insertPop(t);
      del.insert(t);
      tr.update(t, N, -1);
    }
    else if(op == 2) {
      int t;
      while(1) {
        t = GetSample(ins);
        if(tr.queryMn(t, N) > 1) break;
      } 
      ins.erase(t);
      used[t] = 0;
      rq.removePush(t);
      tr.update(t, N, -1);
    }
    else if(op == 3) {
      int t = GetSample(del);
      rq.removePop(t);
      del.erase(t);
      used[t] = 0;
      tr.update(t, N, 1);
    }

    int t = genRand(0, N);
    rq.getPeak(t);
  }
}



class FullRetroactivePriorityQueueSpeed: public ::testing::TestWithParam<int>{};

TEST_P(FullRetroactivePriorityQueueSpeed, RetroactiveSpeed) {
  Retroactivity::FullPriorityQueue< int > rq;
  int n = GetParam();
  map< int, int > used;
  Segtree tr;
  set< int > ins;
  set< int > del;

  vector< int > p(n + 1);
  for(int i = 0; i < n + 1; ++i) p[i] = i + 1;
  
  random_shuffle(p.begin(), p.end());


  for(int i = 0; i < (n + 1) / 2; ++i) {
    int x = p[i];
    int t;
    while(1) {
      t = genRand(0, N);
      if(!used[t]) break;
    }
    used[t] = 1;
    rq.insertPush(t, x);
    tr.update(t, N, 1);
    ins.insert(t);

    t = genRand(0, N);
    rq.getPeak(t);
  }
  for(int i = (n + 1) / 2; i < n; ++i) {
    int op = genRand(0, 3);
    if(op == 2 && ins.size() == 0) op = 1;
    if(op == 3 && del.size() == 0) op = 0;
    if(op == 0) {
      int x = p[i];
      int t;
      while(1) {
        t = genRand(0, N);
        if(!used[t]) break;
      }
      used[t] = 1;
      rq.insertPush(t, x);
      tr.update(t, N, 1);
    }
    else if(op == 1) {
      int t;
      while(1) {
        t = genRand(0, N);
        if(!used[t] && tr.queryMn(t, N) > 1) break;
      }
      used[t] = 1;
      rq.insertPop(t);
      del.insert(t);
      tr.update(t, N, -1);
    }
    else if(op == 2) {
      int t;
      while(1) {
        t = GetSample(ins);
        if(tr.queryMn(t, N) > 1) break;
      } 
      ins.erase(t);
      used[t] = 0;
      rq.removePush(t);
      tr.update(t, N, -1);
    }
    else if(op == 3) {
      int t = GetSample(del);
      rq.removePop(t);
      del.erase(t);
      used[t] = 0;
      tr.update(t, N, 1);
    }

    int t = genRand(0, N);
    rq.getPeak(t);
  }
}

//INSTANTIATE_TEST_CASE_P(TestFullPriorityQueueValidation, FullPriorityQueueValidation, ::testing::Range(100, 200, 10));
INSTANTIATE_TEST_CASE_P(BruteSpeedTest, FullBrutePriorityQueueSpeed, ::testing::Range(3000, 30001, 3000));
INSTANTIATE_TEST_CASE_P(RetroactiveSpeedTest, FullRetroactivePriorityQueueSpeed, ::testing::Range(3000, 30001, 3000));


class FullPolylogarithmPriorityQueueValidation: public ::testing::TestWithParam<int>{};

TEST_P(FullPolylogarithmPriorityQueueValidation, Validation) {
  int n = GetParam();
  int m = n * 2;
  Retroactivity::PolylogarithmPriorityQueue< int > rq(m + 1);
  Brute::FullPriorityQueue< int > bq;
  map< int, int > used;
  Segtree tr;
  set< int > ins;
  set< int > del;

  vector< int > p(n + 1);
  for(int i = 0; i < n + 1; ++i) p[i] = i + 1;
  
  random_shuffle(p.begin(), p.end());

  for(int i = 0; i < (n + 1) / 2; ++i) {
    int x = p[i];
    int t;
    while(1) {
      t = genRand(1, m);
      if(!used[t]) break;
    }
    used[t] = 1;
    rq.insertPush(t, x);
    bq.insertPush(t, x);
    tr.update(t, m, 1);
    ins.insert(t);

    t = genRand(1, m);
    rq.getPeak(t);
    if(!bq.empty(t)) ASSERT_EQ(rq.getPeak(t), bq.getPeak(t));
  }
  for(int i = (n + 1) / 2; i < n; ++i) {
    int op = genRand(0, 1);
    if(op == 0) {
      int x = p[i];
      int t;
      while(1) {
        t = genRand(1, m);
        if(!used[t]) break;
      }
      used[t] = 1;
      rq.insertPush(t, x);
      bq.insertPush(t, x);
      tr.update(t, m, 1);
      ins.insert(t);
    }
    else if(op == 1) {
      int t;
      while(1) {
        t = genRand(1, m);
        if(!used[t] && tr.queryMn(t, m) > 2) break;
      }
      used[t] = 1;
      bq.insertPop(t);
      rq.insertPop(t);
      del.insert(t);
      tr.update(t, m, -1);
    }
    // else if(op == 2) {
    //   int t;
    //   while(1) {
    //     t = GetSample(ins);
    //     if(tr.queryMn(t, m) > 1) break;
    //   } 
    //   ins.erase(t);
    //   rq.removePush(t);
    //   bq.removePush(t);
    //   tr.update(t, m, -1);
    // }
    // else if(op == 3) {
    //   int t = GetSample(del);
    //   rq.removePop(t);
    //   bq.removePop(t);
    //   del.erase(t);
    //   tr.update(t, m, 1);
    // }

    int t = genRand(1, m);
    if(!bq.empty(t)) {
      ASSERT_EQ(rq.getPeak(t), bq.getPeak(t));
    }
  }
}

//INSTANTIATE_TEST_CASE_P(PolylogarithmPriorityQueueTest, FullPolylogarithmPriorityQueueValidation, ::testing::Range(500, 1000, 100));




class PolylogarithmPriorityQueueSpeed: public ::testing::TestWithParam<int>{};

TEST_P(PolylogarithmPriorityQueueSpeed, PolylogarithmSpeed) {
  int n = GetParam();
  int m = n * 2;
  Retroactivity::PolylogarithmPriorityQueue< int > rq(m + 1);
  //Brute::FullPriorityQueue< int > bq;
  map< int, int > used;
  Segtree tr;
  set< int > ins;
  set< int > del;

  vector< int > p(n + 1);
  for(int i = 0; i < n + 1; ++i) p[i] = i + 1;
  
  random_shuffle(p.begin(), p.end());

  for(int i = 0; i < (n + 1) / 2; ++i) {
    int x = p[i];
    int t;
    while(1) {
      t = genRand(1, m);
      if(!used[t]) break;
    }
    used[t] = 1;
    rq.insertPush(t, x);
    //bq.insertPush(t, x);
    tr.update(t, m, 1);
    ins.insert(t);

    t = genRand(1, m);
    rq.getPeak(t);
    //if(!bq.empty(t)) ASSERT_EQ(rq.getPeak(t), bq.getPeak(t));
  }
  for(int i = (n + 1) / 2; i < n; ++i) {
    int op = genRand(0, 1);
    if(op == 0) {
      int x = p[i];
      int t;
      while(1) {
        t = genRand(1, m);
        if(!used[t]) break;
      }
      used[t] = 1;
      rq.insertPush(t, x);
     // bq.insertPush(t, x);
      tr.update(t, m, 1);
      ins.insert(t);
    }
    else if(op == 1) {
      int t;
      while(1) {
        t = genRand(1, m);
        if(!used[t] && tr.queryMn(t, m) > 2) break;
      }
      used[t] = 1;
      //bq.insertPop(t);
      rq.insertPop(t);
      del.insert(t);
      tr.update(t, m, -1);
    }
    // else if(op == 2) {
    //   int t;
    //   while(1) {
    //     t = GetSample(ins);
    //     if(tr.queryMn(t, m) > 1) break;
    //   } 
    //   ins.erase(t);
    //   rq.removePush(t);
    //   bq.removePush(t);
    //   tr.update(t, m, -1);
    // }
    // else if(op == 3) {
    //   int t = GetSample(del);
    //   rq.removePop(t);
    //   bq.removePop(t);
    //   del.erase(t);
    //   tr.update(t, m, 1);
    // }

    int t = genRand(1, m);
    rq.getPeak(t);
    //if(!bq.empty(t)) {
      //ASSERT_EQ(rq.getPeak(t), bq.getPeak(t));
    //}
  }
}

INSTANTIATE_TEST_CASE_P(PolylogarithmRetroactiveSpeedTest, PolylogarithmPriorityQueueSpeed, ::testing::Range(3000, 30001, 3000));

int main(int argc, char **argv) {
  srand(42);
  //srand(time(NULL));
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}



