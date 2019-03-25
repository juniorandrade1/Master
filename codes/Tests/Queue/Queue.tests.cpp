#include "../../Queue/Queue.cpp"
#include <gtest/gtest.h>
#include <vector>

TEST(FullQueue, int10) {
  int n = 10;
  std::vector<int> v;
  Retroactivity::FullQueue< int > p;
  for(int i = 0; i < n; i++) {
    v.push_back((rand() << 16) ^ rand());
    p.Insert_Enqueue(i, v[i]);
  }
  for(int i = 0; i < n; i++) {
    EXPECT_EQ(p.front(n + i), v[i]);
    EXPECT_EQ(p.getKth(n - 1, i + 1), v[i]);
    p.Insert_Dequeue(n + i);
  }
}

TEST(FullQueue, int100) {
  int n = 100;
  std::vector<int> v;
  Retroactivity::FullQueue< int > p;
  for(int i = 0; i < n; i++) {
    v.push_back((rand() << 16) ^ rand());
    p.Insert_Enqueue(i, v[i]);
  }
  for(int i = 0; i < n; i++) {
    EXPECT_EQ(p.front(n + i), v[i]);
    EXPECT_EQ(p.getKth(n - 1, i + 1), v[i]);
    p.Insert_Dequeue(n + i);
  }
}

TEST(FullQueue, int1000) {
  int n = 1000;
  std::vector<int> v;
  Retroactivity::FullQueue< int > p;
  for(int i = 0; i < n; i++) {
    v.push_back((rand() << 16) ^ rand());
    p.Insert_Enqueue(i, v[i]);
  }
  for(int i = 0; i < n; i++) {
    EXPECT_EQ(p.front(n + i), v[i]);
    EXPECT_EQ(p.getKth(n - 1, i + 1), v[i]);
    p.Insert_Dequeue(n + i);
  }
}

TEST(FullQueue, int10000) {
  int n = 10000;
  std::vector<int> v;
  Retroactivity::FullQueue< int > p;
  for(int i = 0; i < n; i++) {
    v.push_back((rand() << 16) ^ rand());
    p.Insert_Enqueue(i, v[i]);
  }
  for(int i = 0; i < n; i++) {
    EXPECT_EQ(p.front(n + i), v[i]);
    EXPECT_EQ(p.getKth(n - 1, i + 1), v[i]);
    p.Insert_Dequeue(n + i);
  }
}

TEST(FullQueue, int100000) {
  int n = 100000;
  std::vector<int> v;
  Retroactivity::FullQueue< int > p;
  for(int i = 0; i < n; i++) {
    v.push_back((rand() << 16) ^ rand());
    p.Insert_Enqueue(i, v[i]);
  }
  for(int i = 0; i < n; i++) {
    EXPECT_EQ(p.front(n + i), v[i]);
    EXPECT_EQ(p.getKth(n - 1, i + 1), v[i]);
    p.Insert_Dequeue(n + i);
  }
}

TEST(PartialQueue, int10) {
  int n = 10;
  std::vector<int> v;
  Retroactivity::PartialQueue< int > p;
  for(int i = 0; i < n; i++) {
    v.push_back((rand() << 16) ^ rand());
    p.Insert_Enqueue(i, v[i]);
  }
  for(int i = 0; i < n; i++) {
    EXPECT_EQ(p.front(), v[i]);
    EXPECT_EQ(p.getKth(n - 1, i + 1), v[i]);
    p.Insert_Dequeue(n + i);
  }
}

TEST(PartialQueue, int100) {
  int n = 100;
  std::vector<int> v;
  Retroactivity::PartialQueue< int > p;
  for(int i = 0; i < n; i++) {
    v.push_back((rand() << 16) ^ rand());
    p.Insert_Enqueue(i, v[i]);
  }
  for(int i = 0; i < n; i++) {
    EXPECT_EQ(p.front(), v[i]);
    EXPECT_EQ(p.getKth(n - 1, i + 1), v[i]);
    p.Insert_Dequeue(n + i);
  }
}

TEST(PartialQueue, int1000) {
  int n = 1000;
  std::vector<int> v;
  Retroactivity::PartialQueue< int > p;
  for(int i = 0; i < n; i++) {
    v.push_back((rand() << 16) ^ rand());
    p.Insert_Enqueue(i, v[i]);
  }
  for(int i = 0; i < n; i++) {
    EXPECT_EQ(p.front(), v[i]);
    EXPECT_EQ(p.getKth(n - 1, i + 1), v[i]);
    p.Insert_Dequeue(n + i);
  }
}


TEST(PartialQueue, int10000) {
  int n = 10000;
  std::vector<int> v;
  Retroactivity::PartialQueue< int > p;
  for(int i = 0; i < n; i++) {
    v.push_back((rand() << 16) ^ rand());
    p.Insert_Enqueue(i, v[i]);
  }
  for(int i = 0; i < n; i++) {
    EXPECT_EQ(p.front(), v[i]);
    EXPECT_EQ(p.getKth(n - 1, i + 1), v[i]);
    p.Insert_Dequeue(n + i);
  }
}

TEST(PartialQueue, int100000) {
  int n = 100000;
  std::vector<int> v;
  Retroactivity::PartialQueue< int > p;
  for(int i = 0; i < n; i++) {
    v.push_back((rand() << 16) ^ rand());
    p.Insert_Enqueue(i, v[i]);
  }
  for(int i = 0; i < n; i++) {
    EXPECT_EQ(p.front(), v[i]);
    EXPECT_EQ(p.getKth(n - 1, i + 1), v[i]);
    p.Insert_Dequeue(n + i);
  }
}

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}