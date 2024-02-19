#include "ll.h"
#include <stdio.h>
#include <stdlib.h>

char const *print_int(void const *value) {
  char *buffer = (char *)calloc(256, sizeof(char));
  sprintf(buffer, "%d", *(int const *)value);
  return buffer;
}

int main(int argc, char **argv) {
  list *l = list_create(sizeof(int));
  int value = 1;
  int second = 10;
  list_add_front(l, (void const *)&value);  // 1
  list_add_front(l, (void const *)&second); // 10->1
  int third = 25;
  list_add_back(l, (void const *)&third); // 10->1->25
  list_print(l, print_int);
  int four = 35;
  list_add_at(l, (void const *)&four, 2); // 10->1->35->25
  int five = 55;
  list_add_at(l, (void const *)&five, 1); // 10->55->1->35->25
  list_print(l, print_int);
  return 0;
}
