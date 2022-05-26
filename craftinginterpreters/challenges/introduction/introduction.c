#include "stdio.h"
#include "stdlib.h"

typedef struct Node {
  int value;
  struct Node* prev;
  struct Node* next;
} Node;

struct Node* make(int value) {
  struct Node* node;

  node = malloc(sizeof(struct Node));

  node -> value = value;
  node -> next = NULL;
  node -> prev = NULL;

  return node;
}

struct Node* find(Node* list, int value) {
  if (list == NULL) return NULL;

  if (list -> value == value) return list;
    
  return find(list -> next, value);
}


// [] -> [] -> [] -> []
// 0     1     2     3

struct Node* prepend(Node* list, Node* node, int index) {
  if (list == NULL) return node;

  if (index == 0) {
    node -> next = list;
    node -> prev = list -> prev;

    list -> prev = node;

    return node;
  }

  list -> next = prepend(list -> next, node, index - 1);

  return list;
}

struct Node* append(Node* list, Node* node, int index) {
  if (list == NULL) return node;

  if (index == 0) {
    node -> next = list -> next;
    node -> prev = list;

    list -> next = node;

    return list;
  }

  list -> next = append(list -> next, node, index - 1);

  return list;
}

struct Node* delete(Node* list, int index) {
  if (list == NULL) return NULL;

  if (index == 0) {
    if (list -> next == NULL) return NULL;
    
    list -> next -> prev = list -> prev;

    return list -> next;
  }

  list -> next = delete(list -> next, index - 1);

  return list;
}

void print(Node* list) {
  if (list == NULL) return;

  printf("%d -> ", list -> value);

  print(list -> next);
}

int main() {
  struct Node* list = make(-1);

  for (int i = 0; i < 3; i++) {
    list = append(list, make(i), i);
  }

  list = delete(list, 4);

  print(list);
}
