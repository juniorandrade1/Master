#include <bits/stdc++.h>
#include "../BST/Treap.cpp"
#include "../BST/IntervalTree.cpp"

template <typename T>
class Stack {
public:
  BST::IntervalTree< T > prefixTree;

  BST::Treap< int, int > tpop;
  BST::Treap< int, std::pair<T, int> > tpush;
  const int NULLVALUE = -1;

  int InsertPush(int t, T x) {
    prefixTree.updateInsert(t, x);
    tpush.insert(t, std::make_pair(x, NULLVALUE));
    typename BST::Treap< int, int > :: iterator nextInconsistenceIt = tpop.lower_bound(t);
    if(nextInconsistenceIt == NULL) return NULLVALUE;
    else return (*nextInconsistenceIt).first;
  }
  int InsertPop(int t) {
    pair<int, T> peak = prefixTree.getPeakPair(prefixTree.getPrefixSum(t), t);
    typename BST::Treap< int, std::pair<T, int> > :: iterator peakIt = tpush.lower_bound(peak.first);
    pair< int, std::pair<T, int> > peakPair = *peakIt;
    peakPair.second.second = t;
    peakIt.modify(peakPair.first, peakPair.second);

    tpop.insert(t, peak.first);
    prefixTree.updateDelete(t);

    typename BST::Treap< int, int > :: iterator nextInconsistenceIt = ++tpop.lower_bound(t);
    if(nextInconsistenceIt == NULL) return NULLVALUE;
    else return (*nextInconsistenceIt).first;
  }
  int DeletePush(int t) {
    typename BST::Treap< int, std::pair<T, int> > :: iterator f = tpush.lower_bound(t);
    int nextInconsistenceTime = (*f).second.second;
    tpush.erase(t);
    prefixTree.erasePush(t);
    return nextInconsistenceTime;
  }
  int DeletePop(int t) {

    BST::Treap< int, int > :: iterator popIt = tpop.lower_bound(t);
    pair<int, int> popPair = *popIt;

    typename BST::Treap< int, std::pair<T, int> > :: iterator pushIt = tpush.lower_bound(popPair.first);
    pair< int, std::pair<T, int> > pushPair = *pushIt;
    pushPair.second.second = NULLVALUE;
    pushIt.modify(pushPair.first, pushPair.second);

    tpop.erase(t);
    prefixTree.erasePop(t);

    typename BST::Treap< int, int > :: iterator nextInconsistenceIt = tpop.lower_bound(t);
    if(nextInconsistenceIt == NULL) return NULLVALUE;
    else return (*nextInconsistenceIt).first;
  }

  void fixPopOperation(int t) {

    if(t == -1) return;

    auto popIt = tpop.lower_bound(t);
    auto popPair = *popIt;

    auto pushIt = tpush.lower_bound(popPair.second);
    auto pushPair = *pushIt;

    if(pushPair.second.second == t) {
      pushPair.second.second = NULLVALUE;
      pushIt.modify(pushPair.first, pushPair.second);
    }

    auto peak = prefixTree.getPeakPair(prefixTree.getPrefixSum(t - 1), t - 1);
    auto peakIt = tpush.lower_bound(peak.first);
    auto peakPair = *peakIt;
    peakPair.second.second = t;
    peakIt.modify(peakPair.first, peakPair.second);

    popPair.second = peak.first;
    popIt.modify(popPair.first, popPair.second);

    ++popIt;
    if(popIt == NULL) return;
    else return fixPopOperation((*popIt).first);
  }

  void showTe() {
    printf("\n------------tpush---------------\n");
    tpush.showTree();
    printf("\n\n");
  }
  void showtpop() {
    printf("\n------------tpop--------------\n");
    tpop.showTree2();
    printf("\n\n");
  }

};

int main() {
  Stack< int > st;
  int time;

  time = st.InsertPush(10, 10);
  printf("next inconsistent time = %d\n", time);
  st.fixPopOperation(time);

  time = st.InsertPush(20, 20);
  printf("next inconsistent time = %d\n", time);
  st.fixPopOperation(time);

  time = st.InsertPush(30, 30);
  printf("next inconsistent time = %d\n", time);
  st.fixPopOperation(time);

  time = st.InsertPush(40, 40);
  printf("next inconsistent time = %d\n", time);
  st.fixPopOperation(time);
  st.showTe();
  st.showtpop();

  time = st.InsertPop(60);
  printf("next inconsistent time = %d\n", time);
  st.fixPopOperation(time);
  st.showTe();
  st.showtpop();

  time = st.InsertPop(50);
  printf("next inconsistent time = %d\n", time);
  st.fixPopOperation(time);
  st.showTe();
  st.showtpop();

  time = st.InsertPop(15);
  printf("next inconsistent time = %d\n", time);
  st.fixPopOperation(time);
  st.showTe();
  st.showtpop();

  time = st.InsertPop(25);
  printf("next inconsistent time = %d\n", time);
  st.fixPopOperation(time);
  st.showTe();
  st.showtpop();




  return 0;
}