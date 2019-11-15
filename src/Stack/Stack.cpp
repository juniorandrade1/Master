#include "Stack.hpp"

namespace Retroactivity {
  /* ------------------------------ BEGIN = Partial Retroactive Stack --------------------------- */
  template <typename T> void PartialStack<T>::InsertPush(int t, const T &x) {
    v.updateInsert(t, x);
  }
  template <typename T> void PartialStack<T>::InsertPop(int t) {
    v.updateDelete(t);
  }
  template <typename T> void PartialStack<T>::DeletePush(int t) {
    v.erasePush(t);
  }
  template <typename T> void PartialStack<T>::DeletePop(int t) {
    v.erasePop(t);
  }
  template <typename T> T PartialStack<T>::peak() {
    int n = v.getSize();
    return v.getPeak(v.getPrefixSum(n), n);
  }
  template <typename T> int PartialStack<T>::getSize() {
    int n = v.getSize();
    return v.getPrefixSum(n);
  }
  /* ------------------------------ END = Partial Retroactive Stack --------------------------- */
 

  /* ------------------------------ BEGIN = Full Retroactive Stack --------------------------- */
  template <typename T> void FullStack<T>::InsertPush(int t, const T &x) {
    v.updateInsert(t, x);
  }
  template <typename T> void FullStack<T>::InsertPop(int t) {
    v.updateDelete(t);
  }
  template <typename T> void FullStack<T>::DeletePush(int t) {
    v.erasePush(t);
  }
  template <typename T> void FullStack<T>::DeletePop(int t) {
    v.erasePop(t);
  }
  template <typename T> T FullStack<T>::peak(int t) {
    return v.getPeak(v.getPrefixSum(t), t);
  }
  template <typename T> int FullStack<T>::getSize(int t) {
    return v.getPrefixSum(t);
  }
  /* ------------------------------ END = Full Retroactive Stack --------------------------- */


  /* ------------------------------ BEGIN = Non-Oblivious Retroactive Stack --------------------------- */
  template <typename T> int NonObliviousStack<T>::InsertPush(int t, T x) {
    prefixTree.updateInsert(t, x);
    tpush.insert(t, std::make_pair(x, NULLVALUE));
    typename BST::Treap< int, int > :: iterator nextInconsistenceIt = tpop.lower_bound(t);
    if(nextInconsistenceIt == NULL) return NULLVALUE;
    else return (*nextInconsistenceIt).first;
  }
  template <typename T> int NonObliviousStack<T>::InsertPop(int t) {
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
  template <typename T> int NonObliviousStack<T>::DeletePush(int t) {
    typename BST::Treap< int, std::pair<T, int> > :: iterator f = tpush.lower_bound(t);
    int nextInconsistenceTime = (*f).second.second;
    tpush.erase(t);
    prefixTree.erasePush(t);
    return nextInconsistenceTime;
  }
  template <typename T> int NonObliviousStack<T>::DeletePop(int t) {

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
  template <typename T> void NonObliviousStack<T>::fixPopOperation(int t) {
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
  template <typename T> void NonObliviousStack<T>::showtpush() {
    printf("\n------------tpush---------------\n");
    tpush.showTree();
    printf("\n\n");
  }
  template <typename T> void NonObliviousStack<T>::showtpop() {
    printf("\n------------tpop--------------\n");
      tpop.showTree2();
      printf("\n\n");
  }
  /* ------------------------------ END = Non-Oblivious Retroactive Stack --------------------------- */
};