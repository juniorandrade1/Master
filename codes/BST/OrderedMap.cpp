#include "Treap.cpp"

namespace BST {
  template<typename K, typename V> 
  class OrderedMap {
    Treap< K, V > s;
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
  };
}
