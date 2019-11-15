#include "testlib.h"
#include <iostream>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    int n = 100000;
    int m = 100000 - 1;
    int s = 1;
    cout << n << " " << m << " " << s << endl;
    for(int i = 0; i < m; ++i) {
      int x = i + 1;
      int y = i + 2;
      int w = 100000;
      cout << x << " " << y << " " << w << endl;
    }
    int q = 100000;
    cout << q << endl;
    for(int i = 0; i < q; ++i) {
      int x = 1;
      int y = 2;
      int w = q - i - 1;
      int p = rnd.next(1, n);
      cout << x << " " << y << " " << w << " " << p << endl;
    }
}