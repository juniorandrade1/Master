#include "../../Priority_Queue/Priority_queue.cpp"
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

class PriorityQueueValidation: public ::testing::TestWithParam<int>{};

TEST_P(PriorityQueueValidation, Validation) {
  Retroactivity::PartialPriorityQueue< int > rq;
  Brute::PartialPriorityQueue< int > bq;
  int n = GetParam();
  map< int, int > used;
  Segtree tr;
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
    ASSERT_EQ(rq.getPeak(), bq.getPeak());
    tr.update(t, N, 1);
  }
  for(int i = 0; i < n / 2; ++i) {
    int op = genRand(0, 1);
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
      ASSERT_EQ(rq.getPeak(), bq.getPeak());
      tr.update(t, N, 1);
    }
    else {
      int t;
      while(1) {
        t = genRand(0, N);
        if(!used[t] && tr.queryMn(t, N) >= 1) break;
      }
      used[t] = 1;
      rq.insertPop(t);
      bq.insertPop(t);
      ASSERT_EQ(rq.getPeak(), bq.getPeak());
      tr.update(t, N, -1);
    }
  }
}


class BrutePriorityQueueSpeed: public ::testing::TestWithParam<int>{};

TEST_P(BrutePriorityQueueSpeed, BruteSpeed) {
  Brute::PartialPriorityQueue< int > bq;
  int n = GetParam();
  map< int, int > used;
  Segtree tr;
  for(int i = 0; i < n / 2; ++i) {
    int x = genRand(0, N);
    int t;
    while(1) {
      t = genRand(0, N);
      if(!used[t]) break;
    }
    used[t] = 1;
    bq.insertPush(t, x);
    bq.getPeak();
    tr.update(t, N, 1);
  }
  for(int i = 0; i < n / 2; ++i) {
    int op = genRand(0, 1);
    if(op == 0) {
      int x = genRand(0, N);
      int t;
      while(1) {
        t = genRand(0, N);
        if(!used[t]) break;
      }
      used[t] = 1;
      bq.insertPush(t, x);
      bq.getPeak();
      tr.update(t, N, 1);
    }
    else {
      int t;
      while(1) {
        t = genRand(0, N);
        if(!used[t] && tr.queryMn(t, N) >= 1) break;
      }
      used[t] = 1;
      bq.insertPop(t);
      bq.getPeak();
      tr.update(t, N, -1);
    }
  }
}

class RetroactivePriorityQueueSpeed: public ::testing::TestWithParam<int>{};

TEST_P(RetroactivePriorityQueueSpeed, RetroactiveSpeed) {
  Retroactivity::PartialPriorityQueue< int > rq;
  int n = GetParam();
  map< int, int > used;
  Segtree tr;
  for(int i = 0; i < n / 2; ++i) {
    int x = genRand(0, N);
    int t;
    while(1) {
      t = genRand(0, N);
      if(!used[t]) break;
    }
    used[t] = 1;
    rq.insertPush(t, x);
    rq.getPeak();
    tr.update(t, N, 1);
  }
  for(int i = 0; i < n / 2; ++i) {
    int op = genRand(0, 1);
    if(op == 0) {
      int x = genRand(0, N);
      int t;
      while(1) {
        t = genRand(0, N);
        if(!used[t]) break;
      }
      used[t] = 1;
      rq.insertPush(t, x);
      rq.getPeak();
      tr.update(t, N, 1);
    }
    else {
      int t;
      while(1) {
        t = genRand(0, N);
        if(!used[t] && tr.queryMn(t, N) >= 1) break;
      }
      used[t] = 1;
      rq.insertPop(t);
      rq.getPeak();
      tr.update(t, N, -1);
    }
  }
}


INSTANTIATE_TEST_CASE_P(TestPriorityQueueValidation, PriorityQueueValidation, ::testing::Range(500, 5000, 500));
INSTANTIATE_TEST_CASE_P(BruteSpeedTest, BrutePriorityQueueSpeed, ::testing::Range(50, 5000, 50));
INSTANTIATE_TEST_CASE_P(RetroactiveSpeedTest, RetroactivePriorityQueueSpeed, ::testing::Range(50, 5000, 50));

int main(int argc, char **argv) {
  srand(time(NULL));
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}



