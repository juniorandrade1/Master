#include "Priority_queue.hpp"

namespace Retroactivity {
  /* ------------------------------ BEGIN = Partial Retroactive Priority Queue --------------------------- */
  template <typename T> vector< pair<int, T> > PartialPriorityQueue<T>::insertPush(int t, T data) {
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
  template <typename T> vector< pair<int, T> > PartialPriorityQueue<T>::insertPop(int t) {
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
  template <typename T> void PartialPriorityQueue<T>::removePush(int t) {
    if(type[t] == 1) {    
      qnow.erase(t);
      type.erase(t);
    }
    else {
      int tl = bridges.getNextBridge(t);
      pair<T, int> add = qnow.getMinimumValueBefore(tl);
      qnow.erase(add.second);
      nqnow.insert(add.second, add.first);
      type[add.second] = 2;
      bridges.update(add.second, 1);
      nqnow.erase(t);
      bridges.update(t, -1);
      type.erase(t);
    }
  }
  template <typename T> void PartialPriorityQueue<T>::removePop(int t) {
    bridges.update(t, 1);
    int tl = bridges.getLastBridge(t);
    pair<T, int> add = nqnow.getMaximumValueAfter(tl);
    nqnow.erase(add.second);
    qnow.insert(add.second, add.first);
    type[add.second] = 1;
    bridges.update(add.second, -1);
    type.erase(t);
    return;
  }
  template <typename T> bool PartialPriorityQueue<T>::empty() {
    return qnow.empty();
  }
  template <typename T> T PartialPriorityQueue<T>::getPeak() {
    return qnow.getMinimumValue().first;
  }
  /* ------------------------------ END = Partial Retroactive Priority Queue -------------------------- */

  /* ------------------------------ BEGIN = Full Retroactive Priority Queue --------------------------- */

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
  template <typename T> void FullPriorityQueue<T>::insertPush(int t, T data) {
    int st = t / b;
    for(int i = st + 1; i < p.size(); ++i) p[i].insertPush(t, data);
    all.insert(Operation(t, 0, data));
  }
  template <typename T> void FullPriorityQueue<T>::insertPop(int t) {
    int st = t / b;
    for(int i = st + 1; i < p.size(); ++i) p[i].insertPop(t);
    all.insert(Operation(t, 1, 1));
  }
  template <typename T> void FullPriorityQueue<T>::removePush(int t) {
    int st = t / b;
    for(int i = st + 1; i < p.size(); ++i) p[i].removePush(t);
    auto f = all.lower_bound(Operation(t, -1, -1));
    all.erase(f);
  }
  template <typename T> void FullPriorityQueue<T>::removePop(int t) {
    int st = t / b;
    for(int i = st + 1; i < p.size(); ++i) p[i].removePop(t);
    auto f = all.lower_bound(Operation(t, -1, -1));
    all.erase(f);
  }
  template <typename T> T FullPriorityQueue<T>::getPeak(int t) {
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

  template <typename T> bool FullPriorityQueue<T>::empty(int t) {
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

};

// namespace NonOnblivious {
//   int INF = 0x3f3f3f3f;
//   struct BSTNode {
//     int key, data;
//     BSTNode *l, *r;
//     int y, sz;
//     BSTNode *link;
//     bool valid;
//     int mn, mx;
//     BSTNode(){
//       l = r = link = NULL;
//       y = (rand() << 16) ^ (rand());
//       sz = 0;
//       valid = false;
//       mn = INF;
//       mx = -INF;
//     }
//     BSTNode(int _key, int _data) {
//       key = _key;
//       data = _data;
//       l = r = link = NULL;
//       y = (rand() << 16) ^ (rand());
//       sz = 1;
//       valid = true;
//       mn = mx = data;
//     }
//   };
//   typedef BSTNode * pBSTNode;
//   class CartesianTree {
//   private:
//     int getSize(pBSTNode p) {
//       return !p ? 0 : p->sz;
//     }
//     int getMin(pBSTNode p) {
//       return !p ? INF : (p->valid) ? p->mn : INF;
//     }
//     int getMax(pBSTNode p) {
//       return !p ? -INF : (p->valid) ? p->mx : -INF; 
//     }
//     pBSTNode update(pBSTNode p) {
//       if(p) {
//         p->sz = 1 + getSize(p->l) + getSize(p->r);
//         p->mn = min((p == NULL || p->valid == false) ? INF : p->data, 
//           min(getMin(p->l), getMin(p->r)));
//         p->mx = max((p == NULL || p->valid == false) ? -INF : p->data, 
//           max(getMax(p->l), getMax(p->r)));
//       }
//       return p;
//     }
//     pBSTNode merge(pBSTNode a, pBSTNode b) {
//       if(!a || !b) return a ? a : b;
//       if(a->y > b->y) {
//         a->r = merge(a->r, b);
//         return update(a);
//       }
//       else {
//         b->l = merge(a, b->l);
//         return update(b);
//       }
//     }
//     void split(pBSTNode t, int key, pBSTNode &a, pBSTNode &b) {
//       if (!t) {
//         a = b = NULL;
//         return;
//       }
//       pBSTNode aux;
//       if (key < t->key) {
//         split(t->l, key, a, aux);
//         t->l = aux;
//         b = update(t);
//       }
//       else {
//         split(t->r, key, aux, b);
//         t->r = aux;
//         a = update(t);
//       }
//     }
//     pBSTNode erase(pBSTNode t, int key) {
//       if(t == NULL) return NULL;
//       if(t->key == key) {
//         return merge(t->l, t->r);
//       }
//       else {
//         if(key < t->key) {
//           t->l = erase(t->l, key);
//         }
//         else {
//           t->r = erase(t->r, key);
//         }
//         return update(t);
//       }
//     }

//     pBSTNode insert(pBSTNode t, pBSTNode it) {
//       if(!t) {
//         t = it;
//       }
//       else if(it->y < t->y) {
//         split(t, it->key, it->l, it->r);
//         t = it;
//       }
//       else {
//         if(it->key < t->key) t->l = insert(t->l, it);
//         else t->r = insert(t->r, it);
//       }
//       return update(t);
//     }

//     pBSTNode searchMinAfter(pBSTNode t, int key) {
//       if(!t) 
//     }


//   public:
//     pBSTNode root;
//     CartesianTree() {
//       root = NULL;
//     }
//     pBSTNode insert(int key, int data) {
//       return insert(root, new BSTNode(key, data));
//     }
//     pBSTNode erase(int key) {
//       return erase(root, key);
//     }
//     pBSTNode findPredecessor(int key) {
//       return NULL;
//     }
//     pBSTNode searchMinAfter(int key) {
//       return NULL;
//     }
//     pBSTNode searchMinBefore(int key) {
//       return NULL;
//     } 
//     pBSTNode findMin() {

//     }
//   };

//   class PriorityQueue {
//   public:
//     CartesianTree qins, qdel;
//     pBSTNode insertPush(int x, int t) {
//       qins.insert(x, t);
//       pBSTNode p = qdel.searchMinAfter(t);
//       return p;
//     }
//     pBSTNode insertPop(int t) {
      
//       pBSTNode iDel = qdel.insert(t, 0);
//       pBSTNode p = qdel.findPredecessor(t);

//       if(p == NULL) {
        
//         pBSTNode foo = qins.findMin();
        
//         iDel->link = foo;
//         foo->link = iDel;
        
//         return foo;
//       }
//       else {

//         int k = p->data;
//         pBSTNode t = qins.searchMinBefore(k);
//         t->valid = false;

//         t->link = iDel;
//         iDel->link = t;

//       }

//       return NULL;
//     }
//     // pBSTNode deletePush(int t) {
//     //   pBSTNode p = qdel.searchMinAfter(t);
//     //   if(p != NULL) {
//     //     return p;
//     //   }
//     //   else {
//     //     p = qins.search(t);
//     //     p->valid = false;
//     //   }
//     // }
//     // pBSTNode deletePop(int t) {
//     //   pBSTNode p = qdel.searchMinAfter(t);
//     //   if(p != NULL) {
//     //     return p;
//     //   }
//     //   else {

//     //   }
//     // }
//     int getPeak(int t) {

//     }
//   };
// };

// int main() {
//   NonOnblivious::PriorityQueue q;

//   return 0;
// }

// int main() {
//   Retroactivity::PartialPriorityQueue< int > q;
//   vector< pair<int, int> > f;
//   f = q.insertPop(10);
//   for(auto p : f) {
//     cout << p.first << " " << p.second << endl;
//   }
//   cout << endl;

//   f = q.insertPop(20);
//   for(auto p : f) {
//     cout << p.first << " " << p.second << endl;
//   }
//   cout << endl;

//   f = q.insertPush(5, 5);
//   for(auto p : f) {
//     cout << p.first << " " << p.second << endl;
//   }
//   cout << endl;
  
  
//   return 0;
// }