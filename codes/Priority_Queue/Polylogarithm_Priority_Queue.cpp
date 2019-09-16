#include <bits/stdc++.h>
#include "../BST/PersistentTreap.cpp"
// #include "Priority_queue.cpp"
using namespace std;

namespace Retroactivity {
  
  typedef pair<int, int> ii;

  template <typename T>
  class PolylogarithmPriorityQueue {
  private:
    struct Node {
      Retroactivity::PartialPriorityQueue< T > pq;
      PersistentTreap< T, int > qnow;
      PersistentTreap< T, int > qdel;
      int qnowV, qdelV;
      Node(){
        qnowV = qdelV = 0;
      };
    };

  public:
    int m; 
    vector< Node > tr;
    PolylogarithmPriorityQueue(int _m) {
      m = _m;
      tr.resize(4 * m);
    }

    struct QueryNode {
      vector< ii > t;
      QueryNode(){
      };
      void add(ii f) {
        t.emplace_back(f);
      }
      void add(QueryNode f) {
        for(auto p : f.t) add(p);
      }
    };

    int getQueryNodeSize(QueryNode q) {
      int sz = 0;
      for(auto p : q.t) {
        int no = p.first;
        if(no % 2 == 0) sz += tr[no / 2].qnow.getSize(p.second);
        else sz += tr[no / 2].qdel.getSize(p.second);
      }
      return sz;
    }

    int getQtdGE(QueryNode q, T key) {
      int sz = 0;
      for(auto p : q.t) {
        int no = p.first;
        if(no % 2 == 0) sz += tr[no / 2].qnow.getQtdEG(p.second, key);
        else sz += tr[no / 2].qdel.getQtdEG(p.second, key);
      }
      return sz;
    }

    T getMinimumKey(QueryNode f) {
      T s = numeric_limits< T > ::max();
      for(auto p : f.t) {
        s = min(s, tr[p.first].qnow.getMinimumKey(p.second));
      }
      return s;
    }

    void addPush(int no, int l, int r, int i, T data) {
      vector< pair<int, T > > operations = tr[no].pq.insertPush(i, data);
      for(auto p : operations) {
        if(p.first == 0) tr[no].qnowV = tr[no].qnow.insert(tr[no].qnowV, p.second, 1);
        if(p.first == 1) tr[no].qnowV = tr[no].qnow.erase(tr[no].qnowV, p.second);
        if(p.first == 2) tr[no].qdelV = tr[no].qdel.insert(tr[no].qdelV, p.second, 1);
        if(p.first == 3) tr[no].qdelV = tr[no].qdel.erase(tr[no].qdelV, p.second);
      }
      if(l == r) return;
      int nxt = (no << 1), mid = (l + r) >> 1;
      if(i <= mid) addPush(nxt, l, mid, i, data);
      else addPush(nxt + 1, mid + 1, r, i, data);
    }

    void addPop(int no, int l, int r, int i) {
      vector< pair< int, T > > operations = tr[no].pq.insertPop(i);
      
      for(auto p : operations) {
        if(p.first == 0) tr[no].qnowV = tr[no].qnow.insert(tr[no].qnowV, p.second, 1);
        if(p.first == 1) tr[no].qnowV = tr[no].qnow.erase(tr[no].qnowV, p.second);
        if(p.first == 2) tr[no].qdelV = tr[no].qdel.insert(tr[no].qdelV, p.second, 1);
        if(p.first == 3) tr[no].qdelV = tr[no].qdel.erase(tr[no].qdelV, p.second);
      }
      if(l == r) return;
      int nxt = (no << 1), mid = (l + r) >> 1;
      if(i <= mid) addPop(nxt, l, mid, i);
      else addPop(nxt + 1, mid + 1, r, i);
    }

    void getNodes(int no, int l, int r, int i, int j, vector< int > &s) {
      if(r < i || l > j) return;
      if(l >= i && r <= j) {
        s.push_back(no);
        return;
      }
      int nxt = (no << 1), mid = (l + r) >> 1;
      getNodes(nxt, l, mid, i, j, s);
      getNodes(nxt + 1, mid + 1, r, i, j, s);
    }

    T getSplitKey(T A, vector< ii > all) {
      int lo = 0, hi = numeric_limits< T >::max() / 2;
      while(lo < hi) {
        int md = (lo + hi) >> 1;
        int q = 0;
        for(auto p : all) {
          int no = p.first;
          if(no % 2 == 0) q += tr[p.first / 2].qnow.order_of_key(p.second, md);
          else q += tr[p.first / 2].qdel.order_of_key(p.second, md);
        }
        if(q < A) lo = md + 1;
        else hi = md;
      }
      return lo;
    }

    pair< QueryNode, QueryNode > getSplitedTrees(int x, vector< ii > all) {
      pair< QueryNode, QueryNode > ret;
      for(auto p : all) {
        int no = p.first;
        ii splited;
        if(no % 2 == 0) splited = tr[no / 2].qnow.split(p.second, x);
        else splited = tr[no / 2].qdel.split(p.second, x);
        ret.first.add(ii(no, splited.first));
        ret.second.add(ii(no, splited.second));
      }
      return ret;
    }

    void showQueryNode(pair< QueryNode, QueryNode > q3) {
      printf("Q_NOW\n");
      for(auto p : q3.first.t) {
        if(p.first % 2 == 0) tr[p.first / 2].qnow.preOrder(p.second);
        else tr[p.first / 2].qdel.preOrder(p.second);
      }
      cout << endl;
      printf("Q_DEL\n");
      for(auto p : q3.second.t) {
        if(p.first % 2 == 0) tr[p.first / 2].qnow.preOrder(p.second);
        else tr[p.first / 2].qdel.preOrder(p.second);
      }
      cout << endl;
    }

    // pair< QueryNode, QueryNode > solveINF(QueryNode q1now, QueryNode q2del) {
    //   int szQ1 = getQueryNodeSize(q1now);
    //   int szInf = getQtdGE(q2del, numeric_limits< T > ::max());
    //   if(szInf == 0) return make_pair(q1now, q2del);
    //   // if(szQ1 >= szInf) {
    //   //   T x = getSplitKey(szInf, q1now.t);
    //   //   cout << x << endl;
    //   //   pair< QueryNode, QueryNode > newQ1 = getSplitedTrees(x, q1now.t);
    //   //   q1now = newQ1.second;
    //   //   pair< QueryNode, QueryNode > newQ2 = getSplitedTrees(numeric_limits< T > ::max() - 1, q2del.t);
    //   //   q2del = newQ2.first;
    //   // }
    //   return make_pair(q1now, q2del);
    // }

    /*
    pair< QueryNode, QueryNode > Fuse(pair< QueryNode, QueryNode > q1, pair< QueryNode, QueryNode > q2) {

      // pair< QueryNode, QueryNode > ret = solveINF(q1.first, q2.second);
      // q1.first = ret.first;
      // q2.second = ret.second;

      //printf("Starting fusion\n");

      // printf("------------------Q1-------------------\n");
      // showQueryNode(q1);
      // printf("------------------Q2-------------------\n");
      // showQueryNode(q2);

      pair< QueryNode, QueryNode > newDel = getSplitedTrees(numeric_limits< T > :: max() - 1, q2.second.t);
      int infSz = getQueryNodeSize(newDel.second);
      q2.second = newDel.first;

      pair< QueryNode, QueryNode > newNow = getSplitedTrees(getSplitKey(infSz, q1.first.t), q1.first.t);
      q1.first = newNow.second;
      q1.second.add(newNow.first);      

      // printf("------------------Q1-------------------\n");
      // showQueryNode(q1);
      // printf("------------------Q2-------------------\n");
      // showQueryNode(q2);

      
      // pair< QueryNode, QueryNode > foo = getSplitedTrees(numeric_limits< T > ::max() - 1, all);
      // int szInf = getQueryNodeSize(foo.second);
      // pair< QueryNode, QueryNode > noInf = getSplitedTrees(getSplitKey(szInf, foo.first.t), foo.first.t);
      // q1.first = noInf.second;
      // q2.second = getSplitedTrees(numeric_limits< T >::max() - 1, q2.second.t).first;
      // q2.second.add(noInf.first);

      vector< ii > all;
      int A = getQueryNodeSize(q1.first) - getQueryNodeSize(q2.second);
      for(auto p : q1.first.t) { 
        all.emplace_back(p);
      }
      for(auto p : q2.second.t) {
        all.emplace_back(p);
      }


      T x = getSplitKey(A, all);
      //printf("SPLIT KEY %d\n", x);
      pair< QueryNode, QueryNode > q3 = getSplitedTrees(x, all);
      q3.first.add(q2.first);
      q3.second.add(q1.second);

      
      // printf("------------------Q3-------------------\n");
      // showQueryNode(q3);
      // printf("\n\n");

      //printf("End fusion\n");
      return q3;
    }
  */

    pair< QueryNode, QueryNode > Fuse(pair< QueryNode, QueryNode > q1, pair< QueryNode, QueryNode > q2) {
      vector< ii > all;
      for(auto p : q1.first.t) { 
        all.emplace_back(p);
      }
      for(auto p : q2.second.t) {
        all.emplace_back(p);
      }
      int D = getQueryNodeSize(q2.second);
      T x = getSplitKey(D, all);
      pair< QueryNode, QueryNode > q3 = getSplitedTrees(x, all);
      swap(q3.first, q3.second);
      q3.first.add(q2.first);
      q3.second.add(q1.second);

      // printf("------------------Q1-------------------\n");
      // showQueryNode(q1);
      // printf("\n\n");
      // printf("------------------Q2-------------------\n");
      // showQueryNode(q2);
      // printf("\n\n");
      // printf("------------------Q3-------------------\n");
      // showQueryNode(q3);
      // printf("\n\n");

      return q3;
    }

    pair< QueryNode, QueryNode > query(int no, int l, int r, int  i, int j) {
      if(r < i || l > j) return pair< QueryNode, QueryNode > ();
      if(l >= i && r <= j) {
        pair< QueryNode, QueryNode > ret;
        ret.first.add(ii(no * 2, tr[no].qnowV));
        ret.second.add(ii(no * 2 + 1, tr[no].qdelV));
        return ret;
      }
      int nxt = (no << 1), mid = (l + r) >> 1;
      return Fuse(query(nxt, l, mid, i, j), query(nxt + 1, mid + 1, r, i, j));
    }

    void insertPush(int t, T data) {
      addPush(1, 1, m, t, data);
    }
    void insertPop(int t) {
      addPop(1, 1, m, t);
      //printf("\n\n\n");
    }

    void removePush(int t) {
    }
    void removePop(int t) {
    }

    pair< QueryNode, QueryNode > getView(int t) {
      vector < int > nodes;
      getNodes(1, 1, m, 1, t, nodes);
      sort(nodes.begin(), nodes.end());
      pair< QueryNode, QueryNode > foo;
      for(auto p : nodes) {
        pair< QueryNode, QueryNode > ret;
        ret.first.add(ii(p * 2, tr[p].qnowV));
        ret.second.add(ii(p * 2 + 1, tr[p].qdelV));
        foo = Fuse(foo, ret);
      } 
      return foo;
    }

    T getPeak(int t) {
      pair< QueryNode, QueryNode > view = getView(t);
      T mn = numeric_limits< T >:: max();
      for(auto p : view.first.t) {
        if(p.first % 2 == 0) mn = min(mn, tr[p.first / 2].qnow.getMinimumKey(p.second));
        else mn = min(mn, tr[p.first / 2].qdel.getMinimumKey(p.second));
      }
      return mn;
    }
  };
}


/*

int main() {
  int m = 16;

  Retroactivity::PolylogarithmPriorityQueue< int > q(m + 1); 

  // for(int i = 1; i <= m / 2; ++i) {
  //   q.insertPush(i, m - i);
  //   for(int j = 1; j <= m; ++j) {
  //     printf("%d ", q.getPeak(j));
  //   }
  //   printf("\n");
  // }
  // for(int i = m / 2 + 1; i < m; ++i) {
  //   q.insertPop(i);
  //   for(int j = 1; j <= m; ++j) {
  //     printf("%d ", q.getPeak(j));
  //   }
  //   printf("\n");
  // }

  q.insertPush(3, 5);
  q.insertPush(14, 11);
  q.insertPush(16, 12);
  q.insertPush(15, 16);
  q.insertPush(2, 15);
  q.insertPush(1, 17);
  q.insertPush(9, 14);
  q.insertPush(6, 2);
  q.insertPush(5, 7);
  q.insertPop(10);
  q.insertPush(7, 4);
  q.insertPush(12, 8);
  q.insertPush(4, 9);
  q.insertPop(11);
  q.insertPush(13, 1);

  printf("%d\n", q.getPeak(13));

  // Retroactivity::PartialPriorityQueue< int > q;
  // auto f = q.insertPop(10);
  // for(auto p : f) {
  //   printf("%d %d\n", p.first, p.second);
  // }
  // printf("\n");
  // f = q.insertPush(12, 8);
  // for(auto p : f) {
  //   printf("%d %d\n", p.first, p.second);
  // }
  // printf("\n");
  // f = q.insertPop(11);
  // for(auto p : f) {
  //   printf("%d %d\n", p.first, p.second);
  // }
  
  return 0;
}
*/