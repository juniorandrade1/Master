#include "Treap.cpp"
#include <iterator>

namespace BST {
  template<typename K, typename V> 
  class OrderedMap {
  public:
    class iterator;
    class Node;
  private:
    BST::Treap< K, V > s;
  public:
    inline void insert(const K &k, V v) {
      s.insert(k, v);
    }
    inline void remove(const K &k) {
      s.erase(k);
    }
    inline V kth(int k) {
      return s.find_by_order(k);
    }
    inline int count(const K &k) {
      return s.order_of_key(k) + s.find(k);
    }

    iterator begin() {
      return iterator(s.begin());
    }
    iterator end() {
      return NULL;
    }

    int getSize() {
      return s.getSize();
    }
    
  };

  // template<typename K, typename V> 
  // class OrderedMap< K, V > :: iterator {
  // public:
  //   iterator() {
  //     cur = NULL;
  //   }
  //   iterator(typename BST::Treap< K, V > :: iterator foo) {
  //     cur = foo;
  //   }
  //   typename BST::Treap< K, V > :: iterator cur;
  //   iterator& operator++() {
  //     ++cur;
  //     return *this;
  //   }
  //   iterator& operator--() {
  //     --cur;
  //     return *this;
  //   }
  //   pair< K, V >& operator *() {
  //     return *cur;
  //   }
  // };
}