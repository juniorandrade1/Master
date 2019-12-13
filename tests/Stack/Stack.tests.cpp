#include "../../src/Stack/Stack.hpp"
#include <gtest/gtest.h>

class StackValidation: public ::testing::TestWithParam<int>{};

TEST_P(StackValidation, Validation) {
  Retroactivity::PartialStack< int > rq;
  Brute::PartialStack< int > bq;
  int n = GetParam();
  string fileName = "../Datasets/Stack/partial/partialStack" + to_string(n) + ".in";
  FILE *dataSet = fopen(fileName.c_str(), "r");
  if(dataSet == NULL) {
    printf("FILE NOT FOUND\n");
    FAIL();
  }
  fscanf(dataSet, "%d", &n);
  for(int i = 0; i < n; ++i) {
    char op, type; fscanf(dataSet, " %c %c", &op, &type);
    if(op == 'Q') {
      ASSERT_EQ(rq.peak(), bq.peak());
    }
    else if(op == 'I') {
      if(type == 'E') {
        int t, x; fscanf(dataSet, "%d %d", &t, &x);
        rq.InsertPush(t, x);
        bq.InsertPush(t, x);
      }
      else {
        int t; fscanf(dataSet, "%d", &t);
        rq.InsertPop(t);
        bq.InsertPop(t);
      }
    }
    else if(op == 'D') {
      if(type == 'E') {
        int t; fscanf(dataSet, "%d", &t);
        rq.DeletePush(t);
        bq.DeletePush(t);
      }
      else {
        int t; fscanf(dataSet, "%d", &t);
        rq.DeletePop(t);
        bq.DeletePop(t);
      }
    }
  }
  fclose(dataSet);
}

class PartialStackSpeedBrute: public ::testing::TestWithParam<int>{};

TEST_P(PartialStackSpeedBrute, SpeedTest) {
  Brute::PartialStack< int > bq;
  int n = GetParam();
  string fileName = "../Datasets/Stack/partial/partialStack" + to_string(n) + ".in";
  FILE *dataSet = fopen(fileName.c_str(), "r");
  if(dataSet == NULL) {
    printf("FILE NOT FOUND\n");
    FAIL();
  }
  fscanf(dataSet, "%d", &n);
  for(int i = 0; i < n; ++i) {
    char op, type; fscanf(dataSet, " %c %c", &op, &type);
    if(op == 'Q') {
      bq.peak();
    }
    else if(op == 'I') {
      if(type == 'E') {
        int t, x; fscanf(dataSet, "%d %d", &t, &x);
        bq.InsertPush(t, x);
      }
      else {
        int t; fscanf(dataSet, "%d", &t);
        bq.InsertPop(t);
      }
    }
    else if(op == 'D') {
      if(type == 'E') {
        int t; fscanf(dataSet, "%d", &t);
        bq.DeletePush(t);
      }
      else {
        int t; fscanf(dataSet, "%d", &t);
        bq.DeletePop(t);
      }
    }
  }
  fclose(dataSet);
}

class PartialStackSpeed: public ::testing::TestWithParam<int>{};

TEST_P(PartialStackSpeed, SpeedTest) {
  Retroactivity::PartialStack< int > rq;
  int n = GetParam();
  string fileName = "../Datasets/Stack/partial/partialStack" + to_string(n) + ".in";
  FILE *dataSet = fopen(fileName.c_str(), "r");
  if(dataSet == NULL) {
    printf("FILE NOT FOUND\n");
    FAIL();
  }
  fscanf(dataSet, "%d", &n);
  for(int i = 0; i < n; ++i) {
    char op, type; fscanf(dataSet, " %c %c", &op, &type);
    if(op == 'Q') {
      rq.peak();
    }
    else if(op == 'I') {
      if(type == 'E') {
        int t, x; fscanf(dataSet, "%d %d", &t, &x);
        rq.InsertPush(t, x);
      }
      else {
        int t; fscanf(dataSet, "%d", &t);
        rq.InsertPop(t);
      }
    }
    else if(op == 'D') {
      if(type == 'E') {
        int t; fscanf(dataSet, "%d", &t);
        rq.DeletePush(t);
      }
      else {
        int t; fscanf(dataSet, "%d", &t);
        rq.DeletePop(t);
      }
    }
  }
  fclose(dataSet);
}

//Full

class StackFullValidation: public ::testing::TestWithParam<int>{};

TEST_P(StackFullValidation, Validation) {
  Retroactivity::FullStack< int > rq;
  Brute::FullStack< int > bq;
  int n = GetParam();
  string fileName = "../Datasets/Stack/full/FullStack" + to_string(n) + ".in";
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
      ASSERT_EQ(rq.peak(t), bq.peak(t));
    }
    else if(op == 'I') {
      if(type == 'E') {
        int t, x; fscanf(dataSet, "%d %d", &t, &x);
        rq.InsertPush(t, x);
        bq.InsertPush(t, x);
      }
      else {
        int t; fscanf(dataSet, "%d", &t);
        rq.InsertPop(t);
        bq.InsertPop(t);
      }
    }
    else if(op == 'D') {
      if(type == 'E') {
        int t; fscanf(dataSet, "%d", &t);
        rq.DeletePush(t);
        bq.DeletePush(t);
      }
      else {
        int t; fscanf(dataSet, "%d", &t);
        rq.DeletePop(t);
        bq.DeletePop(t);
      }
    }
  }
  fclose(dataSet);
}

class StackFullSpeedBrute: public ::testing::TestWithParam<int>{};

TEST_P(StackFullSpeedBrute, SpeedTest) {
  Brute::FullStack< int > bq;
  int n = GetParam();
  string fileName = "../Datasets/Stack/full/FullStack" + to_string(n) + ".in";
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
      bq.peak(t);
    }
    else if(op == 'I') {
      if(type == 'E') {
        int t, x; fscanf(dataSet, "%d %d", &t, &x);
        bq.InsertPush(t, x);
      }
      else {
        int t; fscanf(dataSet, "%d", &t);
        bq.InsertPop(t);
      }
    }
    else if(op == 'D') {
      if(type == 'E') {
        int t; fscanf(dataSet, "%d", &t);
        bq.DeletePush(t);
      }
      else {
        int t; fscanf(dataSet, "%d", &t);
        bq.DeletePop(t);
      }
    }
  }
  fclose(dataSet);
}

class StackFullSpeedRetroactive: public ::testing::TestWithParam<int>{};

TEST_P(StackFullSpeedRetroactive, SpeedTest) {
  Retroactivity::FullStack< int > rq;
  int n = GetParam();
  string fileName = "../Datasets/Stack/full/FullStack" + to_string(n) + ".in";
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
      rq.peak(t);
    }
    else if(op == 'I') {
      if(type == 'E') {
        int t, x; fscanf(dataSet, "%d %d", &t, &x);
        rq.InsertPush(t, x);
      }
      else {
        int t; fscanf(dataSet, "%d", &t);
        rq.InsertPop(t);
      }
    }
    else if(op == 'D') {
      if(type == 'E') {
        int t; fscanf(dataSet, "%d", &t);
        rq.DeletePush(t);
      }
      else {
        int t; fscanf(dataSet, "%d", &t);
        rq.DeletePop(t);
      }
    }
  }
  fclose(dataSet);
}

INSTANTIATE_TEST_CASE_P(TestPartialStack, StackValidation, ::testing::Range(100, 5001, 100));
//INSTANTIATE_TEST_CASE_P(TestPartialStackSpeedBrute, PartialStackSpeedBrute, ::testing::Range(100, 5001, 100));
//INSTANTIATE_TEST_CASE_P(Partial, PartialStackSpeed, ::testing::Range(100, 5001, 100));

INSTANTIATE_TEST_CASE_P(TestFullStack, StackFullValidation, ::testing::Range(100, 5001, 100));
//INSTANTIATE_TEST_CASE_P(FullStackSpeedBrute, StackFullSpeedBrute, ::testing::Range(100, 5001, 100));
//INSTANTIATE_TEST_CASE_P(FullStackSpeedBrute, StackFullSpeedRetroactive, ::testing::Range(100, 5001, 100));


int main(int argc, char **argv) {
  srand(time(NULL));
  testing::InitGoogleTest(&argc, argv);  
  return RUN_ALL_TESTS();
}