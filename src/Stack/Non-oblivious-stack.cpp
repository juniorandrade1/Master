#include <bits/stdc++.h>
#include "Stack.hpp"

int main() {
  Retroactivity::NonObliviousStack< int > st;
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
  st.showtpush();
  st.showtpop();

  time = st.InsertPop(60);
  printf("next inconsistent time = %d\n", time);
  st.fixPopOperation(time);
  st.showtpush();
  st.showtpop();

  time = st.InsertPop(50);
  printf("next inconsistent time = %d\n", time);
  st.fixPopOperation(time);
  st.showtpush();
  st.showtpop();

  time = st.InsertPop(15);
  printf("next inconsistent time = %d\n", time);
  st.fixPopOperation(time);
  st.showtpush();
  st.showtpop();

  time = st.InsertPop(25);
  printf("next inconsistent time = %d\n", time);
  st.fixPopOperation(time);
  st.showtpush();
  st.showtpop();

  return 0;
}