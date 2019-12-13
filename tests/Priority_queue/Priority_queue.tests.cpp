#include "../../src/Priority_Queue/Priority_queue.hpp"
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
  string fileName = "../Datasets/Priority_Queue/partial/partialPriorityQueue" + to_string(n) + ".in";
  printf("%s\n", fileName.c_str());
  FILE *dataSet = fopen(fileName.c_str(), "r");
  if(dataSet == NULL) {
    printf("FILE NOT FOUND\n");
    FAIL();
  }
  fscanf(dataSet, "%d", &n);
  int maxT = 0;
  for(int i = 0; i < n; ++i) {
    char op, type; fscanf(dataSet, " %c %c", &op, &type);
    if(op == 'Q') {
      ASSERT_EQ(rq.getPeak(), bq.getPeak());
    }
    else if(op == 'I') {
      if(type == 'E') {
        int t, x; fscanf(dataSet, "%d %d", &t, &x);
        rq.insertPush(t, x);
        bq.insertPush(t, x);
      }
      else {
        int t; fscanf(dataSet, "%d", &t);
        rq.insertPop(t);
        bq.insertPop(t);
      }
    }
    else if(op == 'D') {
      if(type == 'E') {
        int t; fscanf(dataSet, "%d", &t);
        rq.removePush(t);
        bq.removePush(t);
      }
      else {
        int t; fscanf(dataSet, "%d", &t);
        rq.removePop(t);
        bq.removePop(t);
      }
    }
  }
  fclose(dataSet);
}

class PartialBrutePriorityQueueSpeed: public ::testing::TestWithParam<int>{};

TEST_P(PartialBrutePriorityQueueSpeed, BruteSpeed) {
  Brute::PartialPriorityQueue< int > bq;
  int n = GetParam();
  string fileName = "../Datasets/Priority_Queue/partial/partialPriorityQueue" + to_string(n) + ".in";
  FILE *dataSet = fopen(fileName.c_str(), "r");
  if(dataSet == NULL) {
    printf("FILE NOT FOUND\n");
    FAIL();
  }
  fscanf(dataSet, "%d", &n);
  for(int i = 0; i < n; ++i) {
    char op, type; fscanf(dataSet, " %c %c", &op, &type);
    if(op == 'Q') {
      bq.getPeak();
    }
    else if(op == 'I') {
      if(type == 'E') {
        int t, x; fscanf(dataSet, "%d %d", &t, &x);
        bq.insertPush(t, x);
      }
      else {
        int t; fscanf(dataSet, "%d", &t);
        bq.insertPop(t);
      }
    }
    else if(op == 'D') {
      if(type == 'E') {
        int t; fscanf(dataSet, "%d", &t);
        bq.removePush(t);
      }
      else {
        int t; fscanf(dataSet, "%d", &t);
        bq.removePop(t);
      }
    }
  }
  fclose(dataSet);
}

class PartialRetroactivePriorityQueueSpeed: public ::testing::TestWithParam<int>{};

TEST_P(PartialRetroactivePriorityQueueSpeed, RetroactiveSpeed) {
  Retroactivity::PartialPriorityQueue< int > bq;
  int n = GetParam();
  string fileName = "../Datasets/Priority_Queue/partial/partialPriorityQueue" + to_string(n) + ".in";
  FILE *dataSet = fopen(fileName.c_str(), "r");
  if(dataSet == NULL) {
    printf("FILE NOT FOUND\n");
    FAIL();
  }
  fscanf(dataSet, "%d", &n);
  for(int i = 0; i < n; ++i) {
    char op, type; fscanf(dataSet, " %c %c", &op, &type);
    if(op == 'Q') {
      bq.getPeak();
    }
    else if(op == 'I') {
      if(type == 'E') {
        int t, x; fscanf(dataSet, "%d %d", &t, &x);
        bq.insertPush(t, x);
      }
      else {
        int t; fscanf(dataSet, "%d", &t);
        bq.insertPop(t);
      }
    }
    else if(op == 'D') {
      if(type == 'E') {
        int t; fscanf(dataSet, "%d", &t);
        bq.removePush(t);
      }
      else {
        int t; fscanf(dataSet, "%d", &t);
        bq.removePop(t);
      }
    }
  }
  fclose(dataSet);
}




class FullPriorityQueueValidation: public ::testing::TestWithParam<int>{};

TEST_P(FullPriorityQueueValidation, Validation) {
  Retroactivity::FullPriorityQueue< int > rq;
  Brute::FullPriorityQueue< int > bq;
  int n = GetParam();
  string fileName = "../Datasets/Priority_Queue/full/FullPriorityQueue" + to_string(n) + ".in";
  printf("%s\n", fileName.c_str());
  FILE *dataSet = fopen(fileName.c_str(), "r");
  if(dataSet == NULL) {
    printf("FILE NOT FOUND\n");
    FAIL();
  }
  fscanf(dataSet, "%d", &n);
  int maxT = 0;
  for(int i = 0; i < n; ++i) {
    char op, type; fscanf(dataSet, " %c %c", &op, &type);
    if(op == 'Q') {
      int t; fscanf(dataSet, "%d", &t);
      ASSERT_EQ(rq.getPeak(t), bq.getPeak(t));
    }
    else if(op == 'I') {
      if(type == 'E') {
        int t, x; fscanf(dataSet, "%d %d", &t, &x);
        rq.insertPush(t, x);
        bq.insertPush(t, x);
      }
      else {
        int t; fscanf(dataSet, "%d", &t);
        rq.insertPop(t);
        bq.insertPop(t);
      }
    }
    else if(op == 'D') {
      if(type == 'E') {
        int t; fscanf(dataSet, "%d", &t);
        rq.removePush(t);
        bq.removePush(t);
      }
      else {
        int t; fscanf(dataSet, "%d", &t);
        rq.removePop(t);
        bq.removePop(t);
      }
    }
  }
  fclose(dataSet);
}


class FullBrutePriorityQueueSpeed: public ::testing::TestWithParam<int>{};

TEST_P(FullBrutePriorityQueueSpeed, BruteSpeed) {
  Brute::FullPriorityQueue< int > bq;
  int n = GetParam();
  string fileName = "../Datasets/Priority_Queue/full/FullPriorityQueue" + to_string(n) + ".in";
  printf("%s\n", fileName.c_str());
  FILE *dataSet = fopen(fileName.c_str(), "r");
  if(dataSet == NULL) {
    printf("FILE NOT FOUND\n");
    FAIL();
  }
  fscanf(dataSet, "%d", &n);
  int maxT = 0;
  for(int i = 0; i < n; ++i) {
    char op, type; fscanf(dataSet, " %c %c", &op, &type);
    if(op == 'Q') {
      int t; fscanf(dataSet, "%d", &t);
      bq.getPeak(t);
    }
    else if(op == 'I') {
      if(type == 'E') {
        int t, x; fscanf(dataSet, "%d %d", &t, &x);
        bq.insertPush(t, x);
      }
      else {
        int t; fscanf(dataSet, "%d", &t);
        bq.insertPop(t);
      }
    }
    else if(op == 'D') {
      if(type == 'E') {
        int t; fscanf(dataSet, "%d", &t);
        bq.removePush(t);
      }
      else {
        int t; fscanf(dataSet, "%d", &t);
        bq.removePop(t);
      }
    }
  }
  fclose(dataSet);
}



class FullRetroactivePriorityQueueSpeed: public ::testing::TestWithParam<int>{};

TEST_P(FullRetroactivePriorityQueueSpeed, RetroactiveSpeed) {
  Retroactivity::FullPriorityQueue< int > bq;
  int n = GetParam();
  string fileName = "../Datasets/Priority_Queue/full/FullPriorityQueue" + to_string(n) + ".in";
  printf("%s\n", fileName.c_str());
  FILE *dataSet = fopen(fileName.c_str(), "r");
  if(dataSet == NULL) {
    printf("FILE NOT FOUND\n");
    FAIL();
  }
  fscanf(dataSet, "%d", &n);
  int maxT = 0;
  for(int i = 0; i < n; ++i) {
    char op, type; fscanf(dataSet, " %c %c", &op, &type);
    if(op == 'Q') {
      int t; fscanf(dataSet, "%d", &t);
      bq.getPeak(t);
    }
    else if(op == 'I') {
      if(type == 'E') {
        int t, x; fscanf(dataSet, "%d %d", &t, &x);
        bq.insertPush(t, x);
      }
      else {
        int t; fscanf(dataSet, "%d", &t);
        bq.insertPop(t);
      }
    }
    else if(op == 'D') {
      if(type == 'E') {
        int t; fscanf(dataSet, "%d", &t);
        bq.removePush(t);
      }
      else {
        int t; fscanf(dataSet, "%d", &t);
        bq.removePop(t);
      }
    }
  }
  fclose(dataSet);
}


class FullPolylogarithmPriorityQueueValidation: public ::testing::TestWithParam<int>{};

TEST_P(FullPolylogarithmPriorityQueueValidation, Validation) {
  Retroactivity::PolylogarithmPriorityQueue< int > rq((int)6e4);
  Brute::FullPriorityQueue< int > bq;
  int n = GetParam();
  string fileName = "../Datasets/Priority_Queue/full/FullPriorityQueue" + to_string(n) + ".in";
  printf("%s\n", fileName.c_str());
  FILE *dataSet = fopen(fileName.c_str(), "r");
  if(dataSet == NULL) {
    printf("FILE NOT FOUND\n");
    FAIL();
  }
  fscanf(dataSet, "%d", &n);
  for(int i = 0; i < n; ++i) {
    char op, type; fscanf(dataSet, " %c %c", &op, &type);
    if(op == 'Q') {
      int t; fscanf(dataSet, "%d", &t);
      ASSERT_EQ(rq.getPeak(t), bq.getPeak(t));
    }
    else if(op == 'I') {
      if(type == 'E') {
        int t, x; fscanf(dataSet, "%d %d", &t, &x);
        rq.insertPush(t, x);
        bq.insertPush(t, x);
      }
      else {
        int t; fscanf(dataSet, "%d", &t);
        rq.insertPop(t);
        bq.insertPop(t);
      }
    }
    else if(op == 'D') {
      if(type == 'E') {
        int t; fscanf(dataSet, "%d", &t);
        rq.removePush(t);
        bq.removePush(t);
      }
      else {
        int t; fscanf(dataSet, "%d", &t);
        rq.removePop(t);
        bq.removePop(t);
      }
    }
  }
  fclose(dataSet);
}





class PolylogarithmPriorityQueueSpeed: public ::testing::TestWithParam<int>{};

TEST_P(PolylogarithmPriorityQueueSpeed, PolylogarithmSpeed) {
  Retroactivity::PolylogarithmPriorityQueue< int > rq((int)6e4);
  int n = GetParam();
  string fileName = "../Datasets/Priority_Queue/full/FullPriorityQueue" + to_string(n) + ".in";
  printf("%s\n", fileName.c_str());
  FILE *dataSet = fopen(fileName.c_str(), "r");
  if(dataSet == NULL) {
    printf("FILE NOT FOUND\n");
    FAIL();
  }
  fscanf(dataSet, "%d", &n);
  for(int i = 0; i < n; ++i) {
    char op, type; fscanf(dataSet, " %c %c", &op, &type);
    if(op == 'Q') {
      int t; fscanf(dataSet, "%d", &t);
      rq.getPeak(t);
    }
    else if(op == 'I') {
      if(type == 'E') {
        int t, x; fscanf(dataSet, "%d %d", &t, &x);
        rq.insertPush(t, x);
      }
      else {
        int t; fscanf(dataSet, "%d", &t);
        rq.insertPop(t);
      }
    }
    else if(op == 'D') {
      if(type == 'E') {
        int t; fscanf(dataSet, "%d", &t);
        rq.removePush(t);
      }
      else {
        int t; fscanf(dataSet, "%d", &t);
        rq.removePop(t);
      }
    }
  }
  fclose(dataSet);
}

INSTANTIATE_TEST_CASE_P(TestPartialPriorityQueueValidation, PartialPriorityQueueValidation, ::testing::Range(100, 1001, 100));
//INSTANTIATE_TEST_CASE_P(BruteSpeedTest, PartialBrutePriorityQueueSpeed, ::testing::Range(100, 2001, 100));
//INSTANTIATE_TEST_CASE_P(RetroactiveSpeedTest, PartialRetroactivePriorityQueueSpeed, ::testing::Range(100, 2001, 100));


INSTANTIATE_TEST_CASE_P(TestFullPriorityQueueValidation, FullPriorityQueueValidation, ::testing::Range(100, 1001, 100));
//INSTANTIATE_TEST_CASE_P(BruteSpeedTest, FullBrutePriorityQueueSpeed, ::testing::Range(100, 2001, 100));
//INSTANTIATE_TEST_CASE_P(RetroactiveSpeedTest, FullRetroactivePriorityQueueSpeed, ::testing::Range(100, 2001, 100));



INSTANTIATE_TEST_CASE_P(PolylogarithmPriorityQueueTest, FullPolylogarithmPriorityQueueValidation, ::testing::Range(100, 1001, 100));
//INSTANTIATE_TEST_CASE_P(PolylogarithmRetroactiveSpeedTest, PolylogarithmPriorityQueueSpeed, ::testing::Range(100, 1001, 100));

int main(int argc, char **argv) {
  //srand(42);
  srand(time(NULL));
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}



