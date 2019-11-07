#include "Queue.hpp"

namespace Retroactivity {
  /* ------------------------------ BEGIN = Partial Retroactive Queue --------------------------- */
  template <typename T> void PartialQueue<T>::InsertEnqueue(int t, const T &x) {
    E.insert(t, x);  
    if(E.getSize() == 1) {
      B = E.begin();
      F = E.begin();
    }
    else {
      if((*F).first > t) --F;
      B = E.end();
    }
  }
  template <typename T> void PartialQueue<T>:: InsertDequeue(int t) {
    ++F;
  }
  template <typename T> void PartialQueue<T>:: DeleteEnqueue(int t) {
    if((*F).first > t) ++F;
    if((*F).first == t) ++F;
    E.erase(t);
    B = E.end();
  }
  template <typename T> void PartialQueue<T>:: DeleteDequeue(int t) {
    --F;
  }
  template <typename T> T PartialQueue<T>:: front() {
    return (*F).second;
  }
  template <typename T> T PartialQueue<T>:: back() {
    return (*B).second;
  }
  /* ------------------------------ END = Partial Retroactive Queue -------------------------- */

  /* ------------------------------ BEGIN = Full Retroactive Queue --------------------------- */
  template <typename T> void FullQueue<T>::InsertEnqueue(int t, const T &x) {
    te.insert(t, x);
  }

  template <typename T> void FullQueue<T>::InsertDequeue(int t) {
    td.insert(t, 1);
  }

  template <typename T> void FullQueue<T>::DeleteEnqueue(int t) {
    te.erase(t);
  }

  template <typename T> void FullQueue<T>::DeleteDequeue(int t) {
    td.erase(t);
  }

  template <typename T> T FullQueue<T>::getKth(int t, int k) {
    int f = td.order_of_key(t) + td.find(t);
    return (*te.find_by_order(k + f)).second;
  }

  template <typename T> T FullQueue<T>::front(int t) {
    return getKth(t, 1);
  }
  /* ------------------------------ END = Full Retroactive Queue --------------------------- */

};