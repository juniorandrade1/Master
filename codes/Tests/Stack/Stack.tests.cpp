#include "../../Stack/Stack.cpp"
#include <gtest/gtest.h>

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

const int N = (int)100000;

int bit[N + 10];
int used[N + 10];

#define LSONE(x) (x & (-x))

void update(int x, int y) {
  while(x < N) {
    bit[x] += y;
    x += LSONE(x);
  } 
}

int gs(int x) {
  int s = 0;
  while(x) {
    s += bit[x];
    x -= LSONE(x);
  }
  return s;
}

TEST(PartialStackValidation, Int1000) {
  memset(bit, 0, sizeof bit);
  memset(used, 0, sizeof used);
  int n = 1000;
  Brute::PartialStack< int > bt;
  Retroactivity::PartialStack< int > st;
  for(int i = 1; i <= n / 10; ++i) {
    int t, x;
    while(1) {
      t = genRand(1, n);
      if(used[t] == 0) break;
    }
    used[t] = 1;
    x = genRand(1, (int)1e9);
    update(t, 1);
    bt.Insert_Push(t, x);
    st.Insert_Push(t, x);
    ASSERT_EQ(bt.peak(), st.peak());
  }
  for(int i = 1; i <= n / 10; ++i) {
    int op = genRand(0, 1);
    if(op) {
      int t, x;
      while(1) {
        t = genRand(1, n);
        if(used[t] == 0) break;
      }
      used[t] = 1;
      x = genRand(1, (int)1e9);
      bt.Insert_Push(t, x);
      st.Insert_Push(t, x);
      update(t, 1);
    }
    else {
      int t; 
      while(1) {
        t = genRand(1, n);
        if(used[t] == 0 && gs(t) >= 2) break;
      }
      used[t] = 1;
      bt.Insert_Pop(t);
      st.Insert_Pop(t);
      update(t, -1);
    }
    ASSERT_EQ(bt.peak(), st.peak());
  }
}

TEST(PartialStackValidation, Int10000) {
  memset(bit, 0, sizeof bit);
  memset(used, 0, sizeof used);
  int n = 10000;
  Brute::PartialStack< int > bt;
  Retroactivity::PartialStack< int > st;
  for(int i = 1; i <= n / 10; ++i) {
    int t, x;
    while(1) {
      t = genRand(1, n);
      if(used[t] == 0) break;
    }
    used[t] = 1;
    x = genRand(1, (int)1e9);
    update(t, 1);
    bt.Insert_Push(t, x);
    st.Insert_Push(t, x);
    ASSERT_EQ(bt.peak(), st.peak());
  }
  for(int i = 1; i <= n / 10; ++i) {
    int op = genRand(0, 1);
    if(op) {
      int t, x;
      while(1) {
        t = genRand(1, n);
        if(used[t] == 0) break;
      }
      used[t] = 1;
      x = genRand(1, (int)1e9);
      bt.Insert_Push(t, x);
      st.Insert_Push(t, x);
      update(t, 1);
    }
    else {
      int t; 
      while(1) {
        t = genRand(1, n);
        if(used[t] == 0 && gs(t) >= 2) break;
      }
      used[t] = 1;
      bt.Insert_Pop(t);
      st.Insert_Pop(t);
      update(t, -1);
    }
    ASSERT_EQ(bt.peak(), st.peak());
  }
}

TEST(PartialStackValidation, Int50000) {
  memset(bit, 0, sizeof bit);
  memset(used, 0, sizeof used);
  int n = 50000;
  Brute::PartialStack< int > bt;
  Retroactivity::PartialStack< int > st;
  for(int i = 1; i <= n / 10; ++i) {
    int t, x;
    while(1) {
      t = genRand(1, n);
      if(used[t] == 0) break;
    }
    used[t] = 1;
    x = genRand(1, (int)1e9);
    update(t, 1);
    bt.Insert_Push(t, x);
    st.Insert_Push(t, x);
    ASSERT_EQ(bt.peak(), st.peak());
  }
  for(int i = 1; i <= n / 10; ++i) {
    int op = genRand(0, 1);
    if(op) {
      int t, x;
      while(1) {
        t = genRand(1, n);
        if(used[t] == 0) break;
      }
      used[t] = 1;
      x = genRand(1, (int)1e9);
      bt.Insert_Push(t, x);
      st.Insert_Push(t, x);
      update(t, 1);
    }
    else {
      int t; 
      while(1) {
        t = genRand(1, n);
        if(used[t] == 0 && gs(t) >= 2) break;
      }
      used[t] = 1;
      bt.Insert_Pop(t);
      st.Insert_Pop(t);
      update(t, -1);
    }
    ASSERT_EQ(bt.peak(), st.peak());
  }
}

TEST(PartialStackValidation, Int100000) {
  memset(bit, 0, sizeof bit);
  memset(used, 0, sizeof used);
  int n = 100000;
  Brute::PartialStack< int > bt;
  Retroactivity::PartialStack< int > st;
  for(int i = 1; i <= n / 10; ++i) {
    int t, x;
    while(1) {
      t = genRand(1, n);
      if(used[t] == 0) break;
    }
    used[t] = 1;
    x = genRand(1, (int)1e9);
    update(t, 1);
    bt.Insert_Push(t, x);
    st.Insert_Push(t, x);
    ASSERT_EQ(bt.peak(), st.peak());
  }
  for(int i = 1; i <= n / 10; ++i) {
    int op = genRand(0, 1);
    if(op) {
      int t, x;
      while(1) {
        t = genRand(1, n);
        if(used[t] == 0) break;
      }
      used[t] = 1;
      x = genRand(1, (int)1e9);
      bt.Insert_Push(t, x);
      st.Insert_Push(t, x);
      update(t, 1);
    }
    else {
      int t; 
      while(1) {
        t = genRand(1, n);
        if(used[t] == 0 && gs(t) >= 2) break;
      }
      used[t] = 1;
      bt.Insert_Pop(t);
      st.Insert_Pop(t);
      update(t, -1);
    }
    ASSERT_EQ(bt.peak(), st.peak());
  }
}

TEST(StackSpeed, PartialInt100000) {
  memset(bit, 0, sizeof bit);
  memset(used, 0, sizeof used);
  int n = 100000;
  Retroactivity::PartialStack< int > st;
  for(int i = 1; i <= n / 10; ++i) {
    int t, x;
    while(1) {
      t = genRand(1, n);
      if(used[t] == 0) break;
    }
    used[t] = 1;
    x = genRand(1, (int)1e9);
    update(t, 1);
    st.Insert_Push(t, x);
    st.peak();
  }
  for(int i = 1; i <= n / 10; ++i) {
    int op = genRand(0, 1);
    if(op) {
      int t, x;
      while(1) {
        t = genRand(1, n);
        if(used[t] == 0) break;
      }
      used[t] = 1;
      x = genRand(1, (int)1e9);
      st.Insert_Push(t, x);
      update(t, 1);
    }
    else {
      int t; 
      while(1) {
        t = genRand(1, n);
        if(used[t] == 0 && gs(t) >= 2) break;
      }
      used[t] = 1;
      st.Insert_Pop(t);
      update(t, -1);
    }
    st.peak();
  }
}

TEST(StackSpeed, BruteInt100000) {
  memset(bit, 0, sizeof bit);
  memset(used, 0, sizeof used);
  int n = 100000;
  Brute::PartialStack< int > st;
  for(int i = 1; i <= n / 10; ++i) {
    int t, x;
    while(1) {
      t = genRand(1, n);
      if(used[t] == 0) break;
    }
    used[t] = 1;
    x = genRand(1, (int)1e9);
    update(t, 1);
    st.Insert_Push(t, x);
    st.peak();
  }
  for(int i = 1; i <= n / 10; ++i) {
    int op = genRand(0, 1);
    if(op) {
      int t, x;
      while(1) {
        t = genRand(1, n);
        if(used[t] == 0) break;
      }
      used[t] = 1;
      x = genRand(1, (int)1e9);
      st.Insert_Push(t, x);
      update(t, 1);
    }
    else {
      int t; 
      while(1) {
        t = genRand(1, n);
        if(used[t] == 0 && gs(t) >= 2) break;
      }
      used[t] = 1;
      st.Insert_Pop(t);
      update(t, -1);
    }
    st.peak();
  }
}


int main(int argc, char **argv) {
  srand(time(NULL));
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}