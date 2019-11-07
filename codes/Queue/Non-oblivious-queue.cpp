#include <bits/stdc++.h>
#include "../BST/Treap.cpp"

template <typename T>
class Queue {
public:
  BST::Treap<int, std::pair<T, int> > te;
  BST::Treap<int, int> td;
  const int NULLVALUE = -1;

  typename BST::Treap<int, std::pair<T, int> > :: iterator Front(int t) {
    int f = td.order_of_key(t);
    //printf("== HERE %d\n", f);
    return te.find_by_order(f + 1);
  }

  //Return the index of inconsistent operation from td
  int InsertEnqueue(int t, T x) {
    te.insert(t, std::make_pair(x, NULLVALUE));
    BST::Treap<int, int> :: iterator nextGEQThanT = td.lower_bound(t);
    if(nextGEQThanT == NULL) return NULLVALUE;
    else return (*nextGEQThanT).second;
  }

  //Return the index of inconsistent operation from td
  int InsertDequeue(int t) {
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

  //Return the index of inconsistent operation from td
  int DeleteEnqueue(int t) {
    typename BST::Treap<int, std::pair<T, int> > :: iterator enqueueTIt = te.lower_bound(t);
    std::pair<int, std::pair<T, int> > enqueue = *enqueueTIt;
    te.erase(enqueue.first);
    return enqueue.second.second;    
  }

  //Return the index of inconsistent operation from te
  int DeleteDequeue(int t) {
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
  void showTe() {
    printf("\n------------TE---------------\n");
    te.showTree();
    printf("\n\n");
  }
  void showTd() {
    printf("\n------------TD--------------\n");
    td.showTree2();
    printf("\n\n");
  }
  void fixDequeueOperation(int t) {

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
};

int main() {
  Queue< int > q;
  int time;

  time = q.InsertEnqueue(1, 10);
  printf("%d\n", time);
  time = q.InsertEnqueue(3, 20);
  printf("%d\n", time);
  time = q.InsertEnqueue(5, 30);
  printf("%d\n", time);
  time = q.InsertEnqueue(7, 40);
  printf("%d\n\n\n", time);

  time = q.InsertDequeue(6);
  printf("%d\n", time);
  q.fixDequeueOperation(time);
  q.showTe();
  q.showTd();

  time = q.InsertDequeue(4);
  printf("%d\n", time);
  q.fixDequeueOperation(time);
  q.showTe();
  q.showTd();

  time = q.DeleteEnqueue(1);
  printf("%d\n", time);
  q.fixDequeueOperation(time);
  q.showTe();
  q.showTd();

  time = q.DeleteDequeue(4);
  printf("%d\n", time);
  q.fixDequeueOperation(time);
  q.showTe();
  q.showTd();

  time = q.DeleteDequeue(6);
  printf("%d\n", time);
  q.fixDequeueOperation(time);
  q.showTe();
  q.showTd();

  time = q.InsertDequeue(100);
  printf("%d\n", time);
  q.fixDequeueOperation(time);
  q.showTe();
  q.showTd();

  time = q.InsertDequeue(300);
  printf("%d\n", time);
  q.fixDequeueOperation(time);
  q.showTe();
  q.showTd();

  time = q.InsertDequeue(200);
  printf("%d\n", time);
  q.fixDequeueOperation(time);
  q.showTe();
  q.showTd();

  time = q.DeleteDequeue(100);
  printf("%d\n", time);
  q.fixDequeueOperation(time);
  q.showTe();
  q.showTd();

  time = q.DeleteDequeue(200);
  printf("%d\n", time);
  q.fixDequeueOperation(time);
  q.showTe();
  q.showTd();

  time = q.DeleteDequeue(300);
  printf("%d\n", time);
  q.fixDequeueOperation(time);
  q.showTe();
  q.showTd();







  return 0;
}