#include "testlib.h"
#include <iostream>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    int n = rnd.next(1, 1000);
    int m = rnd.next(1, 2000);
    int s = rnd.next(1, n);
    cout << n << " " << m << " " << s << endl;
    for(int i = 0; i < m; ++i) {
      int x = rnd.next(1, n);
      int y = x;
      while(x == y) y = rnd.next(1, n);
      int w = rnd.next(1, 100000);
      cout << x << " " << y << " " << w << endl;
    }
    int q = rnd.next();
    cout << q << endl;
    for(int i = 0; i < q; ++i) {
      int x = rnd.next(1, n);
      int y = x;
      while(x == y) y = rnd.next(1, n);
      int w = rnd.next(1, 100000);
      int p = rnd.next(1, n);
      cout << x << " " << y << " " << w << " " << p << endl;
    }
}