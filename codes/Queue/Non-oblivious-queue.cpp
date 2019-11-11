#include <bits/stdc++.h>
#include "Queue.hpp"

int main() {
  Retroactivity::NonOblivious< int > q;
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