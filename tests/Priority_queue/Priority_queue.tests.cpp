#include "../../src/Priority_Queue/Priority_queue.hpp"
#include <gtest/gtest.h>

class PartialPriorityQueueValidation: public ::testing::TestWithParam<int>{};


TEST_P(PartialPriorityQueueValidation, Validation) {
  Retroactivity::PartialPriorityQueue< int > rq;
  Brute::PartialPriorityQueue< int > bq;
  int n = GetParam();
  string fileName = "../Datasets/Priority_Queue/partial/partialPriorityQueue" + to_string(n) + ".in";
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
//INSTANTIATE_TEST_CASE_P(PolylogarithmRetroactiveSpeedTest, PolylogarithmPriorityQueueSpeed, ::testing::Range(100, 2001, 100));

int main(int argc, char **argv) {
  //srand(42);
  srand(time(NULL));
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}



