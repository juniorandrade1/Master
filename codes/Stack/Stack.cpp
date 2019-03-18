#include <bits/stdc++.h>
#include "../BST/ABTree.cpp"

namespace Retroactivity {
  template<typename T>
  class PartialStack {
  public:
    BST::ABTree< T > v;
    void Insert_Push(int t, const T &x) {
      v.updateInsert(t, x);
    }
    void Insert_Pop(int t) {
      v.updateDelete(t);
    }
    void Delete_Push(int t) {
    }
    void Delete_Pop(int t) {
    }
    T peak() {
      int n = v.getSize();
      return v.getPeak(v.getPrefixSum(n));
    }
    int getSize() {
      int n = v.getSize();
      return v.getPrefixSum(n);
    }
  };
}

namespace Brute {
  template<typename T>
  class PartialStack {
  public:
    set< pair<int, T > > v;
    vector< T > aux;
    void Insert_Push(int t, const T &x) {
      v.insert(make_pair(t, x));
    }
    void Insert_Pop(int t) {
      v.insert(make_pair(t, -INF));
    }
    void Delete_Push(int t) {
    }
    void Delete_Pop(int t) {
    }
    T peak() {
      aux.clear();
      for(auto it : v) {
        if(it.second == -INF) aux.pop_back();
        else aux.push_back(it.second);
      }
      return aux[(int)aux.size() - 1];
    }
  };
};

int genRand(int l, int r) {
  int sz = (r - l + 1);
  int g = rand() % sz;
  return l + g;
}

const int N = (int)100000;

int bit[N + 10];
int used[N + 10];

#define LSONE(x) (x & (-x))

void update(int x, int y) {
  while(x < 123456) {
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


int main() {
  

  // Retroactivity::PartialStack< int > st;

  // printf("Retroactive STACK\n");

  // st.Insert_Push(1, 1);
  // printf("%d\n", st.peak()); 

  // st.Insert_Push(2, 2);
  // printf("%d\n", st.peak()); 

  // st.Insert_Push(3, 3);
  // printf("%d\n", st.peak()); 

  // st.Insert_Push(5, 4);
  // printf("%d\n", st.peak()); 

  // st.Insert_Push(6, 5);
  // printf("%d\n", st.peak()); 

  // st.Insert_Pop(4);
  // printf("%d\n", st.peak()); 

  // st.Insert_Pop(7);
  // printf("%d\n", st.peak()); 

  // st.Insert_Pop(8);
  // printf("%d\n", st.peak()); 

  // st.Insert_Pop(9);
  // printf("%d\n", st.peak());


  // printf("-------------------------------------------\n");
  // printf("BRUTE STACK\n");

  // Brute::PartialStack< int > bt;

  // bt.Insert_Push(1, 1);
  // printf("%d\n", bt.peak()); 

  // bt.Insert_Push(2, 2);
  // printf("%d\n", bt.peak()); 

  // bt.Insert_Push(3, 3);
  // printf("%d\n", bt.peak()); 

  // bt.Insert_Push(5, 4);
  // printf("%d\n", bt.peak()); 

  // bt.Insert_Push(6, 5);
  // printf("%d\n", bt.peak()); 

  // bt.Insert_Pop(4);
  // printf("%d\n", bt.peak()); 

  // bt.Insert_Pop(7);
  // printf("%d\n", bt.peak()); 

  // bt.Insert_Pop(8);
  // printf("%d\n", bt.peak()); 

  // bt.Insert_Pop(9);
  // printf("%d\n", bt.peak());


  srand(time(NULL));
  Brute::PartialStack< int > bt;
  Retroactivity::PartialStack< int > st;

  for(int i = 1; i <= N / 10; ++i) {
    if(i % 10 == 0) printf("%d\n", i);
    int t, x;
    while(1) {
      t = genRand(1, N);
      if(used[t] == 0) break;
    }
    used[t] = 1;
    x = genRand(1, (int)1e9);
    update(t, 1);
    bt.Insert_Push(t, x);
    st.Insert_Push(t, x);
    //printf("%d (%d %d) ===> %d %d\n", i, t, x, bt.peak(), st.peak());
    assert(st.peak() == st.peak());
  }


  printf("\n\n\n");

  for(int i = 1; i <= N / 10; ++i) {
    if(i % 10 == 0) printf("%d\n", i);
    int op = genRand(0, 1);
    if(op) {
      int t, x;
      while(1) {
        t = genRand(1, N);
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
        t = genRand(1, N);
        if(used[t] == 0 && gs(t) >= 2) break;
      }
      used[t] = 1;
      bt.Insert_Pop(t);
      st.Insert_Pop(t);
      update(t, -1);
    }
    assert(bt.peak() == st.peak());
  }

  return 0;
}