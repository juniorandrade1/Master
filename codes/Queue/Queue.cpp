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

  /* ------------------------------ BEGIN = Non-Oblivious Retroactive Queue --------------------------- */
  template <typename T> int NonObliviousQueue<T>::InsertEnqueue(int t, T x) {
    te.insert(t, std::make_pair(x, NULLVALUE));
    BST::Treap<int, int> :: iterator nextGEQThanT = td.lower_bound(t);
    if(nextGEQThanT == NULL) return NULLVALUE;
    else return (*nextGEQThanT).second;
  }

  template <typename T> int NonObliviousQueue<T>::InsertDequeue(int t) {
    // Find front element at time t
    typename BST::Treap<int, std::pair<T, int> > :: iterator frontIt = Front(t);
    std::pair<int, std::pair<T, int> > front = *frontIt;

    // Fix the element in Enqueue set pointed by Dequeue(t)
    if(front.second.second != NULLVALUE) {
      BST::Treap<int, int> :: iterator elementPointedByTIt = td.lower_bound(front.second.second);
      std::pair<int, int> elementPointedByT = *elementPointedByTIt;
      elementPointedByT.second = NULLVALUE;
      elementPointedByTIt.modify(elementPointedByT.first, elementPointedByT.second);
    }

    // Update dequeue operation from the enqueued element
    front.second.second = t;
    frontIt.modify(front.first, front.second);

    //Insert dequeue operation
    td.insert(t, front.first);

    //Find and return the next dequeue operation
    BST::Treap<int, int> :: iterator nextInconsistenceIt = ++td.lower_bound(t);
    if(nextInconsistenceIt == NULL) return NULLVALUE;
    return (*nextInconsistenceIt).first;
  }

  template <typename T> int NonObliviousQueue<T>::DeleteEnqueue(int t) {
    typename BST::Treap<int, std::pair<T, int> > :: iterator enqueueTIt = te.lower_bound(t);
    std::pair<int, std::pair<T, int> > enqueue = *enqueueTIt;
    te.erase(enqueue.first);
    return enqueue.second.second;
  }

  template <typename T> int NonObliviousQueue<T>::DeleteDequeue(int t) {
    //Find and delete operation at time t    
    BST::Treap<int, int> :: iterator deleteTIt = td.lower_bound(t);
    std::pair<int, int> deleteT = *deleteTIt;
    td.erase(deleteT.first);

    //Find and modify the enqueue operation pointed by dequeue(t)
    typename BST::Treap<int, std::pair<T, int> > :: iterator enqueueTIt = te.lower_bound(deleteT.second);
    std::pair< int, std::pair<T, int> > enqueueT = *enqueueTIt;
    enqueueT.second.second = NULLVALUE;
    enqueueTIt.modify(enqueueT.first, enqueueT.second);
    printf("%d %d %d\n", (*enqueueTIt).first, (*enqueueTIt).second.first, (*enqueueTIt).second.second);

    // Find the next inconsistent operation
    BST::Treap<int, int> :: iterator nextInconsistenceIt = td.lower_bound(t);
    if(nextInconsistenceIt == NULL) return NULLVALUE;
    else return (*nextInconsistenceIt).first;
  }

  template <typename T> void NonObliviousQueue<T>::fixDequeueOperation(int t) {
    if(t == -1) return; 

    {
      BST::Treap<int, int> :: iterator p = td.lower_bound(t);
      std::pair<int, int> foo = *p;

      if(foo.second != NULLVALUE) {
        typename BST::Treap<int, std::pair<T, int> > :: iterator it = te.lower_bound(foo.second);
        std::pair<int, std::pair<T, int> > front = *it;
        front.second.second = -1;
        it.modify(front.first, front.second);
      }
    }
   
    typename BST::Treap<int, std::pair<T, int> > :: iterator it = Front(t);
    std::pair<int, std::pair<T, int> > front = *it;

    front.second.second = t;
    it.modify(front.first, front.second);
   
    BST::Treap<int, int> :: iterator p = td.lower_bound(t);
    std::pair<int, int> foo = *p;

    foo.second = front.first;
    p.modify(foo.first, foo.second);

    ++p;
    if(p == NULL) {
      return;
    }
    else {
      fixDequeueOperation((*p).first);
    }
  }

  template <typename T> void NonObliviousQueue<T>::showTe() {
    printf("\n------------TE---------------\n");
    te.showTree();
    printf("\n\n");
  }

  template <typename T> void NonObliviousQueue<T>::showTd() {
    printf("\n------------TD---------------\n");
    td.showTree2();
    printf("\n\n");
  }

  template <typename T> typename BST::Treap<int, std::pair<T, int> > :: iterator NonObliviousQueue<T>::Front(int t) {
    int f = td.order_of_key(t);
    return te.find_by_order(f + 1);
  }
  /* ------------------------------ END = Non-Oblivious Retroactive Queue --------------------------- */  
};