#include "Priority_queue.hpp"

namespace Retroactivity {
  /* ------------------------------ BEGIN = Partial Retroactive Priority Queue --------------------------- */
  template <typename T> 
  vector< pair<int, T> > PartialPriorityQueue<T>::insertPush(int t, T data) {
    vector< pair<int, T> > ret;

      int tl = bridges.getLastBridge(t);
      nqnow.insert(t, data);
      type[t] = 2;
      bridges.update(t, 1);
      pair<T, int> add = nqnow.getMaximumValueAfter(tl);

      nqnow.erase(add.second);
      qnow.insert(add.second, add.first);
      type[add.second] = 1;
      bridges.update(add.second, -1);

      ret.push_back(make_pair(2, data)); //insert qdel data
      ret.push_back(make_pair(3, add.first)); //delete qdel data
      ret.push_back(make_pair(0, add.first)); //insert qnow data

      return ret;
  }
  template <typename T> 
  vector< pair<int, T> > PartialPriorityQueue<T>::insertPop(int t) {
    vector< pair<int, T> > ret;
      
    type[t] = 3;
    int tl = bridges.getNextBridge(t);
    pair<T, int> rem = qnow.getMinimumValueBefore(tl);

    if(rem.second != numeric_limits<int>::min() && tl < N) {
      
      qnow.erase(rem.second);
      nqnow.insert(rem.second, rem.first);
      
      bridges.update(t, -1);
      bridges.update(rem.second, 1);
      
      type[rem.second] = 2;

      ret.push_back(make_pair(1, rem.first)); //delete qnow data
      ret.push_back(make_pair(2, rem.first)); //insert qdel data

    }
    else {
      nqnow.insert(t, numeric_limits< T > ::max());
      ret.push_back(make_pair(2, numeric_limits< T > ::max())); //insert qdel data
    }

    return ret;
  }

  template <typename T> 
  vector< pair<int, T> > PartialPriorityQueue<T>::removePush(int t) {
    vector< pair<int, T> > ret;
    if(type[t] == 1) {    

      auto aux = *qnow.lower_bound(t);
      ret.push_back(make_pair(1, aux.second)); //delete qnow t

      qnow.erase(t);
      type.erase(t);

    }
    else {
      int tl = bridges.getNextBridge(t);
      pair<T, int> add = qnow.getMinimumValueBefore(tl);
      qnow.erase(add.second);
      nqnow.insert(add.second, add.first);

      ret.push_back(make_pair(1, add.first)); //delete qnow data
      ret.push_back(make_pair(2, add.first)); //insert qdel data

      type[add.second] = 2;
      bridges.update(add.second, 1);

      auto aux = *nqnow.lower_bound(t);
      ret.push_back(make_pair(3, aux.second)); //delete qnow t

      nqnow.erase(t);
      bridges.update(t, -1);
      type.erase(t);
    }
    return ret;
  }
  template <typename T> 
  vector< pair<int, T> > PartialPriorityQueue<T>::removePop(int t) {
    vector< pair<int, T> > ret;
    bridges.update(t, 1);
    int tl = bridges.getLastBridge(t);
    pair<T, int> add = nqnow.getMaximumValueAfter(tl);
    nqnow.erase(add.second);
    qnow.insert(add.second, add.first);

    ret.push_back(make_pair(3, add.first)); //delete qdel data
    ret.push_back(make_pair(0, add.first)); //insert qnow data

    type[add.second] = 1;
    bridges.update(add.second, -1);
    type.erase(t);
    return ret;
  }
  template <typename T> 
  bool PartialPriorityQueue<T>::empty() {
    return qnow.empty();
  }
  template <typename T> 
  T PartialPriorityQueue<T>::getPeak() {
    return qnow.getMinimumValue().first;
  }
  /* ------------------------------ END = Partial Retroactive Priority Queue -------------------------- */

  /* ------------------------------ BEGIN = Full Retroactive Priority Queue --------------------------- */
  
  /** Classe para armazenamento das operações de um bloco
  *
  */
  template <typename T> 
  class FullPriorityQueue<T>::Operation {
  public:
    int t;
    int op;
    T data;
    Operation(){};
    Operation(int _t, int _op, T _data) {
      t = _t;
      op = _op;
      data = _data;
    }
    bool operator < (Operation o) const {
      if(t != o.t) return t < o.t;
      if(op != o.op) return op < o.op;
      return data < o.data;
    }
  };
  template <typename T>
  void FullPriorityQueue<T>::insertPush(int t, T data) {
    int st = t / b;
    for(int i = st + 1; i < p.size(); ++i) p[i].insertPush(t, data);
    all.insert(Operation(t, 0, data));
  }
  template <typename T>
  void FullPriorityQueue<T>::insertPop(int t) {
    int st = t / b;
    for(int i = st + 1; i < p.size(); ++i) p[i].insertPop(t);
    all.insert(Operation(t, 1, 1));
  }
  template <typename T>
  void FullPriorityQueue<T>::removePush(int t) {
    int st = t / b;
    for(int i = st + 1; i < p.size(); ++i) p[i].removePush(t);
    auto f = all.lower_bound(Operation(t, -1, -1));
    all.erase(f);
  }
  template <typename T>
  void FullPriorityQueue<T>::removePop(int t) {
    int st = t / b;
    for(int i = st + 1; i < p.size(); ++i) p[i].removePop(t);
    auto f = all.lower_bound(Operation(t, -1, -1));
    all.erase(f);
  }
  template <typename T>
  T FullPriorityQueue<T>::getPeak(int t) {
    int st = t / b;
    //Get operations between last bucket and t
    vector< Operation > op;
    typename multiset< Operation >::iterator it = lower_bound(all.begin(), all.end(), Operation(st * b, -1, -1));
    while(it != all.end() && it->t <= t) {
      op.emplace_back(*it);
      it++;
    }
    //Make operations between st * b and t
    for(int i = 0; i < (int)op.size(); ++i) {
      if(op[i].op == 0) p[st].insertPush(op[i].t, op[i].data);
      else if(op[i].op == 1) p[st].insertPop(op[i].t);
    }
    T peak = 0;
    if(p[st].empty()) peak = T();
    else peak = p[st].getPeak();
    //Rollback checkpoint 
    reverse(op.begin(), op.end());
    for(int i = 0; i < (int)op.size(); ++i) {
      if(op[i].op == 0) p[st].removePush(op[i].t);
      else if(op[i].op == 1) p[st].removePop(op[i].t);
    }
    return peak;
  }

  template <typename T>
  bool FullPriorityQueue<T>::empty(int t) {
    int st = t / b;
    //Get operations between last bucket and t
    vector< Operation > op;
    typename multiset< Operation >::iterator it = lower_bound(all.begin(), all.end(), Operation(st * b, -1, -1));
    while(it != all.end() && it->t <= t) {
      op.emplace_back(*it);
      it++;
    }
    //Make operations between st * b and t
    for(int i = 0; i < (int)op.size(); ++i) {
      if(op[i].op == 0) p[st].insertPush(op[i].t, op[i].data);
      else if(op[i].op == 1) p[st].insertPop(op[i].t);
    }
    bool emp = p[st].empty();
    //Rollback checkpoint 
    reverse(op.begin(), op.end());
    for(int i = 0; i < (int)op.size(); ++i) {
      if(op[i].op == 0) p[st].removePush(op[i].t);
      else if(op[i].op == 1) p[st].removePop(op[i].t);
    }
    return emp;
  }
  /* ------------------------------ END = Full Retroactive Priority Queue --------------------------- */

  /* ------------------------------ BEGIN = Non-Oblivious Retroactive Priority Queue --------------------------- */
  template <typename T>
  int NonObliviousPriorityQueue<T>::InsertPush(int t, T x) {
    H.insertSegment(t, MAX, x);
    return V.getMinXGreaterThanOrEqualY(t, MAX, x);
  }
  template <typename T> int NonObliviousPriorityQueue<T>::InsertPop(int t) {
    int x = H.getMinY(t);
    int tins = H.getStartTimeFromKey(x);
    int tdel = H.getFinishTimeFromKey(x);
    H.eraseSegment(tins, tdel, x);
    int newtdel = t;
    H.insertSegment(tins, newtdel, x);
    V.insertPoint(t, x);
    if(tdel < MAX) {
      V.erasePoint(tdel, x);
    }
    return tdel;
  }
  template <typename T>
  int NonObliviousPriorityQueue<T>::DeletePush(int t) {
    int tins = t;
    int tdel = H.getFinishTimeFromStartTime(tins);
    int x = H.getKeyFromStartTime(tins);
    H.eraseSegment(tins, tdel, x);
    if(tdel < MAX) {
      V.erasePoint(tdel, x);
    }
    return tdel;
  }
  template <typename T>
  int NonObliviousPriorityQueue<T>::DeletePop(int t)  {
    int x = V.getYFromX(t);
    int tins = H.getStartTimeFromKey(x);
    int tdel = H.getFinishTimeFromStartTime(tins);
    H.eraseSegment(tins, tdel, x);
    H.insertSegment(t, MAX, x);
    V.erasePoint(t, x);
    return V.getMinXGreaterThanOrEqualY(t, MAX, x);
  }
  template <typename T>
  T NonObliviousPriorityQueue<T>::Peak(int t) {
    return H.getMinY(t);
  }
  template <typename T>
  void NonObliviousPriorityQueue<T>::fixOperation(int t, Operation type) {
    if(t >= MAX) return;
    if(type == insertpush || type == deletepop) { 
       printf("FIX OPERATION RUNNING A\n");
       int px = V.Vseg[t];

      //remove from vertical set
      V.erasePoint(t, px);

      //remove from horizontal set
      int tinsPX = H.Hins[px];
      int tdelPX = H.Hseg[tinsPX].first;
      H.eraseSegment(tinsPX, tdelPX, px);
      H.insertSegment(tinsPX, MAX, px);


      //find new horizontal hit
      int x = H.getMinY(t);
      int tins = H.Hins[x];
      int tdel = H.Hseg[tins].first;
      H.eraseSegment(tins, tdel, x);


      int newtdel = t;
      H.insertSegment(tins, newtdel, x);
      V.insertPoint(t, x);

      fixOperation(tdel, type);
    }
    else {
      printf("FIX OPERATION RUNNING B\n");

      int x = H.getMinY(t);
      printf("-- %d\n", x);
      int tins = H.Hins[x];
      int tdel = H.Hseg[tins].first;

      H.eraseSegment(tins, tdel, x);
      int newtdel = t;

      H.insertSegment(tins, newtdel, x);
      V.insertPoint(t, x);

      if(tdel < MAX) {
        V.erasePoint(tdel, x);
      }
      fixOperation(tdel, type);
    }

    printf("END OPERATION RUNNING\n\n");
  }
  /* ------------------------------ END = Non-Oblivious Retroactive Priority Queue --------------------------- */

  /* ------------------------------ BEGIN = Polylogarithmic Retroactive Priority Queue --------------------------- */
  
  template <typename T>
  PolylogarithmPriorityQueue<T>::PolylogarithmPriorityQueue(int _m) {
    m = _m;
    tr.resize(4 * m);
  }
    
  template <typename T>
  class PolylogarithmPriorityQueue<T>::Node {
    public:
    Retroactivity::PartialPriorityQueue< T > pq;
    PersistentTreap< T, int > qnow;
    PersistentTreap< T, int > qdel;
    int qnowV, qdelV;
    Node(){
      qnowV = qdelV = 0;
    };
  };

  template <typename T>
  class PolylogarithmPriorityQueue<T>::QueryNode {
  public:
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


  template <typename T>
  int PolylogarithmPriorityQueue<T>::getQueryNodeSize(QueryNode q) {
    int sz = 0;
    for(auto p : q.t) {
      int no = p.first;
      if(no % 2 == 0) sz += tr[no / 2].qnow.getSize(p.second);
      else sz += tr[no / 2].qdel.getSize(p.second);
    }
    return sz;
  }

  template <typename T>
  int PolylogarithmPriorityQueue<T>::getQtdGE(QueryNode q, T key) {
    int sz = 0;
    for(auto p : q.t) {
      int no = p.first;
      if(no % 2 == 0) sz += tr[no / 2].qnow.getQtdEG(p.second, key);
      else sz += tr[no / 2].qdel.getQtdEG(p.second, key);
    }
    return sz;
  }
  template <typename T>
  T PolylogarithmPriorityQueue<T>::getMinimumKey(QueryNode f) {
    T s = numeric_limits< T > ::max();
    for(auto p : f.t) {
      s = min(s, tr[p.first].qnow.getMinimumKey(p.second));
    }
    return s;
  }
  template <typename T>
  void PolylogarithmPriorityQueue<T>::addPush(int no, int l, int r, int i, T data) {
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

  template <typename T>
  void PolylogarithmPriorityQueue<T>::addPop(int no, int l, int r, int i) {
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

  template <typename T>
  void PolylogarithmPriorityQueue<T>::delPush(int no, int l, int r, int i) {
    vector< pair< int, T > > operations = tr[no].pq.removePush(i);
    for(auto p : operations) {
      if(p.first == 0) tr[no].qnowV = tr[no].qnow.insert(tr[no].qnowV, p.second, 1);
      if(p.first == 1) tr[no].qnowV = tr[no].qnow.erase(tr[no].qnowV, p.second);
      if(p.first == 2) tr[no].qdelV = tr[no].qdel.insert(tr[no].qdelV, p.second, 1);
      if(p.first == 3) tr[no].qdelV = tr[no].qdel.erase(tr[no].qdelV, p.second);
    }
    if(l == r) return;
    int nxt = (no << 1), mid = (l + r) >> 1;
    if(i <= mid) delPush(nxt, l, mid, i);
    else delPush(nxt + 1, mid + 1, r, i);
  }


  template <typename T>
  void PolylogarithmPriorityQueue<T>::delPop(int no, int l, int r, int i) {
    vector< pair< int, T > > operations = tr[no].pq.removePop(i);
    for(auto p : operations) {
      if(p.first == 0) tr[no].qnowV = tr[no].qnow.insert(tr[no].qnowV, p.second, 1);
      if(p.first == 1) tr[no].qnowV = tr[no].qnow.erase(tr[no].qnowV, p.second);
      if(p.first == 2) tr[no].qdelV = tr[no].qdel.insert(tr[no].qdelV, p.second, 1);
      if(p.first == 3) tr[no].qdelV = tr[no].qdel.erase(tr[no].qdelV, p.second);
    }
    if(l == r) return;
    int nxt = (no << 1), mid = (l + r) >> 1;
    if(i <= mid) delPop(nxt, l, mid, i);
    else delPop(nxt + 1, mid + 1, r, i);
  }

  template <typename T>
  void PolylogarithmPriorityQueue<T>::insertPush(int t, T data) {
    addPush(1, 0, m, t, data);
  }

  template <typename T>
  void PolylogarithmPriorityQueue<T>::insertPop(int t) {
    addPop(1, 0, m, t);
  }

  template <typename T>
  void PolylogarithmPriorityQueue<T>::removePush(int t) {
    delPush(1, 0, m, t);
  }

  template <typename T>
  void PolylogarithmPriorityQueue<T>::removePop(int t) {
    delPop(1, 0, m, t);
  }

  template <typename T>
  void PolylogarithmPriorityQueue<T>::getNodes(int no, int l, int r, int i, int j, vector< int > &s) {
    if(r < i || l > j) return;
    if(l >= i && r <= j) {
      s.push_back(no);
      return;
    }
    int nxt = (no << 1), mid = (l + r) >> 1;
    getNodes(nxt, l, mid, i, j, s);
    getNodes(nxt + 1, mid + 1, r, i, j, s);
  }

  template <typename T>
  T PolylogarithmPriorityQueue<T>::getSplitKey(T A, vector< ii > all) {
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

  // template <typename T>
  // void PolylogarithmPriorityQueue<T>::showQueryNode(pair< QueryNode, QueryNode > q3) {
  //   printf("Q_NOW\n");
  //   for(auto p : q3.first.t) {
  //     if(p.first % 2 == 0) tr[p.first / 2].qnow.preOrder(p.second);
  //     else tr[p.first / 2].qdel.preOrder(p.second);
  //   }
  //   cout << endl;
  //   printf("Q_DEL\n");
  //   for(auto p : q3.second.t) {
  //     if(p.first % 2 == 0) tr[p.first / 2].qnow.preOrder(p.second);
  //     else tr[p.first / 2].qdel.preOrder(p.second);
  //   }
  //   cout << endl;
  // }


  template <typename T>
  T PolylogarithmPriorityQueue<T>::getPeak(int t) {
    pair< QueryNode, QueryNode > view = getView(t);
    T mn = numeric_limits< T >:: max();
    for(auto p : view.first.t) {
      if(p.first % 2 == 0) mn = min(mn, tr[p.first / 2].qnow.getMinimumKey(p.second));
      else mn = min(mn, tr[p.first / 2].qdel.getMinimumKey(p.second));
    }
    return mn;
  }

  template <typename T>
  pair< typename PolylogarithmPriorityQueue<T>::QueryNode, typename PolylogarithmPriorityQueue<T>::QueryNode > PolylogarithmPriorityQueue<T>::getSplitedTrees(int x, vector< ii > all) {
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

  template <typename T>
  pair< typename PolylogarithmPriorityQueue<T>::QueryNode, typename PolylogarithmPriorityQueue<T>::QueryNode > PolylogarithmPriorityQueue<T>::Fuse(pair< QueryNode, QueryNode > q1, pair< QueryNode, QueryNode > q2) {
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

  template <typename T>
  pair< typename PolylogarithmPriorityQueue<T>::QueryNode, typename PolylogarithmPriorityQueue<T>::QueryNode > PolylogarithmPriorityQueue<T>::query(int no, int l, int r, int  i, int j) {
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

  template <typename T>
  pair< typename PolylogarithmPriorityQueue<T>::QueryNode, typename PolylogarithmPriorityQueue<T>::QueryNode > PolylogarithmPriorityQueue<T>::getView(int t) {
    vector < int > nodes;
    getNodes(1, 0, m, 0, t, nodes);
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


  /* ------------------------------ END = Polylogarithmic Retroactive Priority Queue --------------------------- */
};
