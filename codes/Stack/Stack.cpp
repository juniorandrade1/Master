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
};