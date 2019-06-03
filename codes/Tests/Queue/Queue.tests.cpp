#include "../../Queue/Queue.cpp"
#include <gtest/gtest.h>
#include <vector>

const int N = (int)2e5 + 1;

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

class QueueValidation: public ::testing::TestWithParam<int>{};

TEST_P(QueueValidation, Validation) {
  Retroactivity::PartialQueue< int > rq;
  Brute::PartialQueue< int > bq;
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
    rq.Insert_Enqueue(t, x);
    bq.Insert_Enqueue(t, x);
    ASSERT_EQ(rq.front(), bq.front());
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
      rq.Insert_Enqueue(t, x);
      bq.Insert_Enqueue(t, x);
      ASSERT_EQ(rq.front(), bq.front());
      tr.update(t, N, 1);
    }
    else {
      int t;
      while(1) {
        t = genRand(0, N);
        if(!used[t] && tr.queryMn(t, N) >= 1) break;
      }
      used[t] = 1;
      rq.Insert_Dequeue(t);
      bq.Insert_Dequeue(t);
      ASSERT_EQ(rq.front(), bq.front());
      tr.update(t, N, -1);
    }
  }
}


class BruteQueueSpeed: public ::testing::TestWithParam<int>{};

TEST_P(BruteQueueSpeed, BruteSpeed) {
  Brute::PartialQueue< int > bq;
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
    bq.Insert_Enqueue(t, x);
    bq.front();
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
      bq.Insert_Enqueue(t, x);
      bq.front();
      tr.update(t, N, 1);
    }
    else {
      int t;
      while(1) {
        t = genRand(0, N);
        if(!used[t] && tr.queryMn(t, N) >= 1) break;
      }
      used[t] = 1;
      bq.Insert_Dequeue(t);
      bq.front();
      tr.update(t, N, -1);
    }
  }
}

class RetroactiveQueueSpeed: public ::testing::TestWithParam<int>{};

TEST_P(RetroactiveQueueSpeed, RetroactiveSpeed) {
  Retroactivity::PartialQueue< int > rq;
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
    rq.Insert_Enqueue(t, x);
    rq.front();
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
      rq.Insert_Enqueue(t, x);
      rq.front();
      tr.update(t, N, 1);
    }
    else {
      int t;
      while(1) {
        t = genRand(0, N);
        if(!used[t] && tr.queryMn(t, N) >= 1) break;
      }
      used[t] = 1;
      rq.Insert_Dequeue(t);
      rq.front();
      tr.update(t, N, -1);
    }
  }
}


INSTANTIATE_TEST_CASE_P(TestQueueValidation, QueueValidation, ::testing::Range(500, 5000, 50));
INSTANTIATE_TEST_CASE_P(BruteSpeedTest, BruteQueueSpeed, ::testing::Range(50, 5000, 50));
INSTANTIATE_TEST_CASE_P(RetroactiveSpeedTest, RetroactiveQueueSpeed, ::testing::Range(50, 5000, 50));

class FullQueueValidation: public ::testing::TestWithParam<int>{};

TEST_P(FullQueueValidation, Validation) {
  Retroactivity::FullQueue< int > rq;
  Brute::FullQueue< int > bq;
  int n = GetParam();
  map< int, int > used;
  Segtree tr;
  for(int i = 0; i < n; ++i) {
    int x = genRand(0, N);
    int t;
    while(1) {
      t = genRand(0, N);
      if(!used[t]) break;
    }
    used[t] = 1;
    rq.Insert_Enqueue(t, x);
    bq.Insert_Enqueue(t, x);
    tr.update(t, N, 1);
    while(1) {
    	t = genRand(0, N);
    	if(tr.querySm(t, t) >= 1) break;
    }
    ASSERT_EQ(rq.front(t), bq.front(t));
  }
}


class FullBruteQueueSpeed: public ::testing::TestWithParam<int>{};

TEST_P(FullBruteQueueSpeed, BruteSpeed) {
  Brute::FullQueue< int > bq;
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
    bq.Insert_Enqueue(t, x);
    bq.front(t);
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
      bq.Insert_Enqueue(t, x);
      tr.update(t, N, 1);
    }
    else {
      int t;
      while(1) {
        t = genRand(0, N);
        if(!used[t] && tr.queryMn(t, N) >= 1) break;
      }
      used[t] = 1;
      bq.Insert_Dequeue(t);
      tr.update(t, N, -1);
    }
	int t;
	while(1) {
		t = genRand(0, N);
		if(tr.querySm(t, t) >= 1) break;
	}
	bq.front(t);
  }
}

class FullRetroactiveQueueSpeed: public ::testing::TestWithParam<int>{};

TEST_P(FullRetroactiveQueueSpeed, RetroactiveSpeed) {
  Retroactivity::FullQueue< int > rq;
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
    rq.Insert_Enqueue(t, x);
    tr.update(t, N, 1);
    rq.front(t);
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
      rq.Insert_Enqueue(t, x);
      tr.update(t, N, 1);
    }
    else {
      int t;
      while(1) {
        t = genRand(0, N);
        if(!used[t] && tr.queryMn(t, N) >= 1) break;
      }
      used[t] = 1;
      rq.Insert_Dequeue(t);
      tr.update(t, N, -1);
    }
    int t = genRand(0, N);
    rq.front(t);
  }
}


INSTANTIATE_TEST_CASE_P(FullTestQueueValidation, FullQueueValidation, ::testing::Range(500, 5000, 50));
INSTANTIATE_TEST_CASE_P(FullBruteSpeedTest, FullBruteQueueSpeed, ::testing::Range(50, 5000, 50));
INSTANTIATE_TEST_CASE_P(FullRetroactiveSpeedTest, FullRetroactiveQueueSpeed, ::testing::Range(50, 5000, 50));


int main(int argc, char **argv) {
  srand(time(NULL));
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

  