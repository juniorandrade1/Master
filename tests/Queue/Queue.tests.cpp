#include "../../src/Queue/Queue.hpp"
#include <gtest/gtest.h>
#include <vector>

class QueueValidation: public ::testing::TestWithParam<int>{};

TEST_P(QueueValidation, Validation) {
  Retroactivity::PartialQueue< int > rq;
  Brute::PartialQueue< int > bq;
  int n = GetParam();
  string fileName = "../Datasets/Queue/partial/partialQueue" + to_string(n) + ".in";
  FILE *dataSet = fopen(fileName.c_str(), "r");
  if(dataSet == NULL) {
    printf("FILE NOT FOUND\n");
    FAIL();
  }
  fscanf(dataSet, "%d", &n);
  for(int i = 0; i < n; ++i) {
    char op, type; fscanf(dataSet, " %c %c", &op, &type);
    if(op == 'Q') {
      ASSERT_EQ(rq.front(), bq.front());
    }
    else if(op == 'I') {
      if(type == 'E') {
        int t, x; fscanf(dataSet, "%d %d", &t, &x);
        rq.InsertEnqueue(t, x);
        bq.InsertEnqueue(t, x);
      }
      else {
        int t; fscanf(dataSet, "%d", &t);
        rq.InsertDequeue(t);
        bq.InsertDequeue(t);
      }
    }
    else if(op == 'D') {
      if(type == 'E') {
        int t; fscanf(dataSet, "%d", &t);
        rq.DeleteEnqueue(t);
        bq.DeleteEnqueue(t);
      }
      else {
        int t; fscanf(dataSet, "%d", &t);
        rq.DeleteDequeue(t);
        bq.DeleteDequeue(t);
      }
    }
  }
  fclose(dataSet);
}

class BruteQueueSpeed: public ::testing::TestWithParam<int>{};

TEST_P(BruteQueueSpeed, BruteSpeed) {
  Brute::PartialQueue< int > bq;
  int n = GetParam();
  string fileName = "../Datasets/Queue/partial/partialQueue" + to_string(n) + ".in";
  FILE *dataSet = fopen(fileName.c_str(), "r");
  if(dataSet == NULL) {
    printf("FILE NOT FOUND\n");
    FAIL();
  }
  fscanf(dataSet, "%d", &n);
  for(int i = 0; i < n; ++i) {
    char op, type; fscanf(dataSet, " %c %c", &op, &type);
    if(op == 'Q') {
      bq.front();
    }
    else if(op == 'I') {
      if(type == 'E') {
        int t, x; fscanf(dataSet, "%d %d", &t, &x);
        bq.InsertEnqueue(t, x);
      }
      else {
        int t; fscanf(dataSet, "%d", &t);
        bq.InsertDequeue(t);
      }
    }
    else if(op == 'D') {
      if(type == 'E') {
        int t; fscanf(dataSet, "%d", &t);
        bq.DeleteEnqueue(t);
      }
      else {
        int t; fscanf(dataSet, "%d", &t);
        bq.DeleteDequeue(t);
      }
    }
  }
  fclose(dataSet);
}

class RetroactiveQueueSpeed: public ::testing::TestWithParam<int>{};

TEST_P(RetroactiveQueueSpeed, RetroactiveSpeed) {
  Retroactivity::PartialQueue< int > bq;
  int n = GetParam();
  string fileName = "../Datasets/Queue/partial/partialQueue" + to_string(n) + ".in";
  FILE *dataSet = fopen(fileName.c_str(), "r");
  if(dataSet == NULL) {
    printf("FILE NOT FOUND\n");
    FAIL();
  }
  fscanf(dataSet, "%d", &n);
  for(int i = 0; i < n; ++i) {
    char op, type; fscanf(dataSet, " %c %c", &op, &type);
    if(op == 'Q') {
      bq.front();
    }
    else if(op == 'I') {
      if(type == 'E') {
        int t, x; fscanf(dataSet, "%d %d", &t, &x);
        bq.InsertEnqueue(t, x);
      }
      else {
        int t; fscanf(dataSet, "%d", &t);
        bq.InsertDequeue(t);
      }
    }
    else if(op == 'D') {
      if(type == 'E') {
        int t; fscanf(dataSet, "%d", &t);
        bq.DeleteEnqueue(t);
      }
      else {
        int t; fscanf(dataSet, "%d", &t);
        bq.DeleteDequeue(t);
      }
    }
  }
  fclose(dataSet);
}

class FullQueueValidation: public ::testing::TestWithParam<int>{};

TEST_P(FullQueueValidation, Validation) {
  Retroactivity::FullQueue< int > rq;
  Brute::FullQueue< int > bq;
  int n = GetParam();
  string fileName = "../Datasets/Queue/full/FullQueue" + to_string(n) + ".in";
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
      ASSERT_EQ(rq.front(t), bq.front(t));
    }
    else if(op == 'I') {
      if(type == 'E') {
        int t, x; fscanf(dataSet, "%d %d", &t, &x);
        rq.InsertEnqueue(t, x);
        bq.InsertEnqueue(t, x);
      }
      else {
        int t; fscanf(dataSet, "%d", &t);
        //rq.InsertDequeue(t);
        //bq.InsertDequeue(t);
      }
    }
    else if(op == 'D') {
      if(type == 'E') {
        int t; fscanf(dataSet, "%d", &t);
        //rq.DeleteEnqueue(t);
        //bq.DeleteEnqueue(t);
      }
      else {
        int t; fscanf(dataSet, "%d", &t);
        //rq.DeleteDequeue(t);
        //bq.DeleteDequeue(t);
      }
    }
  }
  fclose(dataSet);
}


class FullBruteQueueSpeed: public ::testing::TestWithParam<int>{};

TEST_P(FullBruteQueueSpeed, BruteSpeed) {
  Brute::FullQueue< int > bq;
  int n = GetParam();
  string fileName = "../Datasets/Queue/full/FullQueue" + to_string(n) + ".in";
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
      bq.front(t);
    }
    else if(op == 'I') {
      if(type == 'E') {
        int t, x; fscanf(dataSet, "%d %d", &t, &x);
        bq.InsertEnqueue(t, x);
      }
      else {
        int t; fscanf(dataSet, "%d", &t);
        bq.InsertDequeue(t);
      }
    }
    else if(op == 'D') {
      if(type == 'E') {
        int t; fscanf(dataSet, "%d", &t);
        bq.DeleteEnqueue(t);
      }
      else {
        int t; fscanf(dataSet, "%d", &t);
        bq.DeleteDequeue(t);
      }
    }
  }
  fclose(dataSet);
}

class FullRetroactiveQueueSpeed: public ::testing::TestWithParam<int>{};

TEST_P(FullRetroactiveQueueSpeed, RetroactiveSpeed) {
  Retroactivity::FullQueue< int > rq;
  int n = GetParam();
  string fileName = "../Datasets/Queue/full/FullQueue" + to_string(n) + ".in";
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
      rq.front(t);
    }
    else if(op == 'I') {
      if(type == 'E') {
        int t, x; fscanf(dataSet, "%d %d", &t, &x);
        rq.InsertEnqueue(t, x);
      }
      else {
        int t; fscanf(dataSet, "%d", &t);
        rq.InsertDequeue(t);
      }
    }
    else if(op == 'D') {
      if(type == 'E') {
        int t; fscanf(dataSet, "%d", &t);
        rq.DeleteEnqueue(t);
      }
      else {
        int t; fscanf(dataSet, "%d", &t);
        rq.DeleteDequeue(t);
      }
    }
  }
  fclose(dataSet);
}

INSTANTIATE_TEST_CASE_P(TestQueueValidation, QueueValidation, ::testing::Range(100, 5000, 100));
// INSTANTIATE_TEST_CASE_P(BruteSpeedTest, BruteQueueSpeed, ::testing::Range(100, 5000, 100));
// INSTANTIATE_TEST_CASE_P(RetroactiveSpeedTest, RetroactiveQueueSpeed, ::testing::Range(100, 5000, 100));



INSTANTIATE_TEST_CASE_P(FullTestQueueValidation, FullQueueValidation, ::testing::Range(100, 5000, 100));
// INSTANTIATE_TEST_CASE_P(FullBruteSpeedTest, FullBruteQueueSpeed, ::testing::Range(100, 5000, 100));
// INSTANTIATE_TEST_CASE_P(FullRetroactiveSpeedTest, FullRetroactiveQueueSpeed, ::testing::Range(100, 5000, 100));


int main(int argc, char **argv) {
  srand(1);
  //srand(time(NULL));
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

  