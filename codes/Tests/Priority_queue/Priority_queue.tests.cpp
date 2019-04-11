#include "../../Priority_queue/Priority_queue.cpp"
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

const int N = (int)1000000;

int bit[N + 10];
int used[N + 10];

#define LSONE(x) (x & (-x))

void up(int x, int y) {
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

TEST(PartialPriorityQueueValidation, Int100) {
  memset(bit, 0, sizeof bit);
  memset(used, 0, sizeof used);
  int n = 100;

  Retroactivity::PartialPriorityQueue< int > q1;
  Brute::PartialPriorityQueue< int > q2;
  
  int mnx = INF;
  set< int > f1;
  set< int > f2;
  while(f1.size() < n) f1.insert(genRand(1, 100000));
  while(f2.size() < n) f2.insert(genRand(1, 100000));
  vector< int > a1(f1.begin(), f1.end()), a2(f2.begin(), f2.end());

  random_shuffle(a1.begin(), a1.end());
  random_shuffle(a2.begin(), a2.end());

  vector< pair<int, int> > input;
  for(int i = 0; i < n; ++i) {
    used[a1[i]] = 1;
    mnx = min(mnx, a2[i]);
    q1.insertPush(a1[i], a2[i]);
    q2.insertPush(a1[i], a2[i]);
    up(a1[i], 1);
    input.push_back(make_pair(a1[i], a2[i]));
    ASSERT_EQ(q1.getPeak(), q2.getPeak());
  }
  for(int i = 0; i < n / 10; ++i) {
    int tp = genRand(0, 1);
    int t = genRand(1, 100000);
    if(!tp) {
      while(used[t] || gs(t) == 0) t = genRand(1, 100000);
      up(t, -1);
      q1.insertPop(t);
      q2.insertPop(t);
    }
    else {
      while(used[t]) t = genRand(1, 100000);
      up(t, 1);
      int x = genRand(1, 100000);
      q1.insertPush(t, x);
      q2.insertPush(t, x);
    }
    ASSERT_EQ(q1.getPeak(), q2.getPeak());
  }
}


TEST(PartialPriorityQueueValidation, Int1000) {
  memset(bit, 0, sizeof bit);
  memset(used, 0, sizeof used);
  int n = 1000;

  Retroactivity::PartialPriorityQueue< int > q1;
  Brute::PartialPriorityQueue< int > q2;
  
  int mnx = INF;
  set< int > f1;
  set< int > f2;
  while(f1.size() < n) f1.insert(genRand(1, 100000));
  while(f2.size() < n) f2.insert(genRand(1, 100000));
  vector< int > a1(f1.begin(), f1.end()), a2(f2.begin(), f2.end());

  random_shuffle(a1.begin(), a1.end());
  random_shuffle(a2.begin(), a2.end());

  vector< pair<int, int> > input;
  for(int i = 0; i < n; ++i) {
    used[a1[i]] = 1;
    mnx = min(mnx, a2[i]);
    q1.insertPush(a1[i], a2[i]);
    q2.insertPush(a1[i], a2[i]);
    up(a1[i], 1);
    input.push_back(make_pair(a1[i], a2[i]));
    ASSERT_EQ(q1.getPeak(), q2.getPeak());
  }
  for(int i = 0; i < n / 10; ++i) {
    int tp = genRand(0, 1);
    int t = genRand(1, 100000);
    if(!tp) {
      while(used[t] || gs(t) == 0) t = genRand(1, 100000);
      up(t, -1);
      q1.insertPop(t);
      q2.insertPop(t);
    }
    else {
      while(used[t]) t = genRand(1, 100000);
      up(t, 1);
      int x = genRand(1, 100000);
      q1.insertPush(t, x);
      q2.insertPush(t, x);
    }
    ASSERT_EQ(q1.getPeak(), q2.getPeak());
  }
}

TEST(PartialPriorityQueueValidation, Int5000) {
  memset(bit, 0, sizeof bit);
  memset(used, 0, sizeof used);
  int n = 5000;

  Retroactivity::PartialPriorityQueue< int > q1;
  Brute::PartialPriorityQueue< int > q2;
  
  int mnx = INF;
  set< int > f1;
  set< int > f2;
  while(f1.size() < n) f1.insert(genRand(1, 200000));
  while(f2.size() < n) f2.insert(genRand(1, 200000));
  vector< int > a1(f1.begin(), f1.end()), a2(f2.begin(), f2.end());

  random_shuffle(a1.begin(), a1.end());
  random_shuffle(a2.begin(), a2.end());

  vector< pair<int, int> > input;
  for(int i = 0; i < n; ++i) {
    used[a1[i]] = 1;
    mnx = min(mnx, a2[i]);
    q1.insertPush(a1[i], a2[i]);
    q2.insertPush(a1[i], a2[i]);
    up(a1[i], 1);
    input.push_back(make_pair(a1[i], a2[i]));
    ASSERT_EQ(q1.getPeak(), q2.getPeak());
  }
  for(int i = 0; i < n / 10; ++i) {
    int tp = genRand(0, 1);
    int t = genRand(1, 200000);
    if(!tp) {
      while(used[t] || gs(t) == 0) t = genRand(1, 200000);
      up(t, -1);
      q1.insertPop(t);
      q2.insertPop(t);
    }
    else {
      while(used[t]) t = genRand(1, 200000);
      up(t, 1);
      int x = genRand(1, 200000);
      q1.insertPush(t, x);
      q2.insertPush(t, x);
    }
    ASSERT_EQ(q1.getPeak(), q2.getPeak());
  }
}


TEST(PartialPriorityQueueSpeed, Int5000) {
  memset(bit, 0, sizeof bit);
  memset(used, 0, sizeof used);
  int n = 5000;

  Retroactivity::PartialPriorityQueue< int > q1;
  //Brute::PartialPriorityQueue< int > q2;
  
  int mnx = INF;
  set< int > f1;
  set< int > f2;
  while(f1.size() < n) f1.insert(genRand(1, 100000));
  while(f2.size() < n) f2.insert(genRand(1, 100000));
  vector< int > a1(f1.begin(), f1.end()), a2(f2.begin(), f2.end());

  random_shuffle(a1.begin(), a1.end());
  random_shuffle(a2.begin(), a2.end());

  vector< pair<int, int> > input;
  for(int i = 0; i < n; ++i) {
    used[a1[i]] = 1;
    mnx = min(mnx, a2[i]);
    q1.insertPush(a1[i], a2[i]);
    //q2.insertPush(a1[i], a2[i]);
    up(a1[i], 1);
    input.push_back(make_pair(a1[i], a2[i]));
    ASSERT_EQ(q1.getPeak(), q1.getPeak());
  }
  for(int i = 0; i < n / 10; ++i) {
    int tp = genRand(0, 1);
    int t = genRand(1, 100000);
    if(!tp) {
      while(used[t] || gs(t) == 0) t = genRand(1, 100000);
      up(t, -1);
      q1.insertPop(t);
      //q2.insertPop(t);
    }
    else {
      while(used[t]) t = genRand(1, 100000);
      up(t, 1);
      int x = genRand(1, 100000);
      q1.insertPush(t, x);
      //q2.insertPush(t, x);
    }
    ASSERT_EQ(q1.getPeak(), q1.getPeak());
  }
}

TEST(PartialBrutePriorityQueueSpeed, Int5000) {
  memset(bit, 0, sizeof bit);
  memset(used, 0, sizeof used);
  int n = 5000;

  Brute::PartialPriorityQueue< int > q1;
  
  int mnx = INF;
  set< int > f1;
  set< int > f2;
  while(f1.size() < n) f1.insert(genRand(1, 100000));
  while(f2.size() < n) f2.insert(genRand(1, 100000));
  vector< int > a1(f1.begin(), f1.end()), a2(f2.begin(), f2.end());

  random_shuffle(a1.begin(), a1.end());
  random_shuffle(a2.begin(), a2.end());

  vector< pair<int, int> > input;
  for(int i = 0; i < n; ++i) {
    used[a1[i]] = 1;
    mnx = min(mnx, a2[i]);
    q1.insertPush(a1[i], a2[i]);
    up(a1[i], 1);
    input.push_back(make_pair(a1[i], a2[i]));
    ASSERT_EQ(q1.getPeak(), q1.getPeak());
  }
  for(int i = 0; i < n / 10; ++i) {
    int tp = genRand(0, 1);
    int t = genRand(1, 100000);
    if(!tp) {
      while(used[t] || gs(t) == 0) t = genRand(1, 100000);
      up(t, -1);
      q1.insertPop(t);
    }
    else {
      while(used[t]) t = genRand(1, 100000);
      up(t, 1);
      int x = genRand(1, 100000);
      q1.insertPush(t, x);
    }
    ASSERT_EQ(q1.getPeak(), q1.getPeak());
  }
}

int main(int argc, char **argv) {
  //srand(time(NULL));
  srand(time(NULL));
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}



