#include "node.h"

Node * buildTree(uint64_t * counts) {
  //WRITE ME!
  priority_queue_t que;
  for (int i = 0; i < 257; i++) {
    if (counts[i] != 0) {
      que.push(new Node(i, counts[i]));
    }
  }
  int sz = que.size();
  if (sz == 0) {
    return NULL;
  }
  while (sz > 1) {
    Node * left = que.top();
    que.pop();
    Node * right = que.top();
    que.pop();
    que.push(new Node(left, right));
    sz = que.size();
  }
  return que.top();
}
