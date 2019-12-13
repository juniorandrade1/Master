#include <bits/stdc++.h>

namespace Random {
  std::mt19937_64 rng(std::chrono::steady_clock::now().time_since_epoch().count());
  int getInt(int l, int r) {
    return (rng() % (r - l + 1)) + l;
  }
};

namespace Tests {
  const int N = (int)3e4;
  class Segtree {
  public:
    int n;
    std::vector< int > L, R;
    std::vector< int > sm, mn;
    std::vector< int > lz;
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
      mn[no] = std::min(mn[nl], mn[nr]);
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
      return std::min(queryMn(L[no], l, mid, i, j), queryMn(R[no], mid + 1, r, i, j));
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

  int GetSample(const std::set<int>& s) {
    double r = rand() % s.size();
    std::set<int>::iterator it = s.begin();
    for (; r != 0; r--) it++;
    return *it;
  }

  class FullPriorityQueueTest {
  public:
    struct FullPriorityQueueTestOperation {
      char retroactiveOperation;
      char PriorityQueueOperation;
      int t;
      int x;
      FullPriorityQueueTestOperation(){};
      FullPriorityQueueTestOperation(char _retroactiveOperation, char _PriorityQueueOperation, int _t, int _x) {
        retroactiveOperation = _retroactiveOperation;
        PriorityQueueOperation = _PriorityQueueOperation;
        t = _t;
        x = _x;
      }
    };
    int q;
    std::vector< FullPriorityQueueTestOperation > allOperations;
    FullPriorityQueueTest(int _q) {
      q = _q;
      std::map< int, int > used;
      Segtree tr;
      std::set< int > ins, del;
      for(int i = 0; i < q / 2; ++i) {
        int x = Random::getInt(0, N);
        int t;
        while(1) {
          t = Random::getInt(0, N);
          if(!used[t]) break;
        }
        allOperations.push_back(FullPriorityQueueTestOperation('I', 'E', t, x));
        used[t] = 1;
        ins.insert(t);
        tr.update(t, N, 1);
      }
      for(int i = 0; i < q - q / 2; ++i) {
        int op = Random::getInt(0, 4);
        if(op == 2 && ins.size() == 0) op = 0;
        if(op == 3 && del.size() == 0) op = 1;
        if(op == 0) {
          int x = Random::getInt(0, N);
          int t;
          while(1) {
            t = Random::getInt(0, N);
            if(!used[t]) break;
          }
          used[t] = 1;
          allOperations.push_back(FullPriorityQueueTestOperation('I', 'E', t, x));
          ins.insert(t);
          tr.update(t, N, 1);
        }
        else if(op == 1) {
          int t;
          while(1) {
            t = Random::getInt(0, N);
            if(!used[t] && tr.queryMn(t, N) >= 4) break;
          }
          used[t] = 1;
          del.insert(t);
          allOperations.push_back(FullPriorityQueueTestOperation('I', 'D', t, INT_MIN));
          tr.update(t, N, -1);
        }
        else if(op == 2) {
          int x = GetSample(ins);
          ins.erase(ins.find(x));
          allOperations.push_back(FullPriorityQueueTestOperation('D', 'E', x, INT_MIN));
        }
        else if(op == 3) {
          int x = GetSample(del);
          del.erase(del.find(x));
          allOperations.push_back(FullPriorityQueueTestOperation('D', 'D', x, INT_MIN));
        }
        else {
          int t;
          while(1) {
            t = GetSample(ins);
            if(tr.querySm(t, t) >= 4 && tr.queryMn(t, N) >= 4) break;
          } 
          allOperations.push_back(FullPriorityQueueTestOperation('Q', 'T', t, INT_MIN));
        }
      }
    }
    void showAllOperations() {
      printf("%d\n", (int)allOperations.size());
      for(auto foo : allOperations) {
        printf("%c %c", foo.retroactiveOperation, foo.PriorityQueueOperation);
        if(foo.t != INT_MIN) printf(" %d", foo.t);
        if(foo.x != INT_MIN) printf(" %d", foo.x);
        printf("\n");
      }
    }
    void writeOperationsOnFile(FILE *f) {
      fprintf(f, "%d\n", (int)allOperations.size());
      for(auto foo : allOperations) {
        fprintf(f, "%c %c", foo.retroactiveOperation, foo.PriorityQueueOperation);
        if(foo.t != INT_MIN) fprintf(f, " %d", foo.t);
        if(foo.x != INT_MIN) fprintf(f, " %d", foo.x);
        fprintf(f, "\n");
      }
    }
  };
};
  
int main(int argc, char *argv[]) {
  if(argc != 4) {
    printf("Numero de argumentos errado!\n");
    printf("Os argumentos passados devem ser 'inicio fim passo'\n");
    return 0;
  }
  int start = std::stoi((std::string)argv[1]);
  int end = std::stoi((std::string)argv[2]);
  int passo = std::stoi((std::string)argv[3]);
  for(int i = start; i <= end; i += passo) {
    std::string str = "FullPriorityQueue" + std::to_string(i) + ".in";
    FILE *f = fopen(str.c_str(), "w");
    Tests::FullPriorityQueueTest v(i);
    v.writeOperationsOnFile(f);
    fclose(f);
  }
  return 0;
}