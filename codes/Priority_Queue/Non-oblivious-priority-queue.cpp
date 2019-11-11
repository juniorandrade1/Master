#include <bits/stdc++.h>
#include "Priority_queue.hpp"





int main() {
  Retroactivity::NonObliviousPriorityQueue< int > q;
  int r;

  r = q.InsertPush(5, 10);
  printf("= %d\n", r);
  q.fixOperation(r, insertpush);
  printf("\n\n");

  r = q.InsertPush(10, 20);
  printf("= %d\n", r);
  q.fixOperation(r, insertpush);
  printf("\n\n");

  r = q.InsertPush(0, 5);
  printf("= %d\n", r);
  q.fixOperation(r, insertpush);
  printf("\n\n");

  r = q.InsertPop(4);
  printf("= %d\n", r);
  q.fixOperation(r, insertpop);
  printf("\n\n");

  r = q.InsertPush(1, 2);
  printf("= %d\n", r);
  q.fixOperation(r, insertpush);
  printf("\n\n");

  r = q.InsertPop(2);
  printf("= %d\n", r);
  q.fixOperation(r, insertpop);

  r = q.InsertPush(4, 50);
  printf("= %d\n", r);
  q.fixOperation(r, insertpush);


  r = q.DeletePush(0);
  printf("= %d\n", r);
  q.fixOperation(r, deletepush);

  r = q.DeletePop(2);
  printf("= %d\n", r);
  q.fixOperation(r, deletepop);


  return 0;
}