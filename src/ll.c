#include "ll.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _node {
  void *value;
  struct _node *next;
} _node;

typedef struct _list {
  uint32_t count;
  uint32_t data_size;
  _node *head;
  _node *tail;
} _list;

static void node_delete(_node **node) {
  free((*node)->value);
  free(*node);
}

static _node *create_node(void const *value, uint32_t data_size) {
  _node *new_node = (_node *)malloc(sizeof(_node));
  new_node->value = malloc(data_size);
  memset(new_node->value, 0, data_size);
  memcpy(new_node->value, value, data_size);
  new_node->next = NULL;
  return new_node;
}

list *list_create(uint32_t data_size) {
  list *ll = (list *)malloc(sizeof(list));
  ll->count = 0;
  ll->data_size = data_size;
  ll->head = NULL;
  ll->tail = NULL;
  return ll;
}

void list_destroy(list *list) {
  _node *head = list->head;
  while (head) {
    _node *tmp = head;
    head = head->next;
    free(tmp->value);
    free(tmp);
  }

  free(list);
}

void list_print(list *list, node_value_pptr print_func) {
  assert(list != NULL);
  printf("Count: %d\tData Size: %d\n", list->count, list->data_size);
  _node *head = list->head;
  char buffer[2048];
  memset(&buffer[0], 0, sizeof(buffer));
  size_t written = 0;
  uint32_t count = 0;
  while (head) {
    if (count == list->count - 1) {
      written += snprintf(&buffer[written], 256, "%s", print_func(head->value));
    } else {
      written +=
          snprintf(&buffer[written], 256, "%s -> ", print_func(head->value));
    }
    head = head->next;
    ++count;
  }
  printf("%s\n", buffer);
}

void list_add_front(list *list, void const *value) {
  assert(list != NULL);
  _node *node_to_insert = create_node(value, list->data_size);
  node_to_insert->next = list->head;
  list->head = node_to_insert;
  if (list->count == 0) {
    list->tail = list->head;
  }
  ++list->count;
}

void list_add_back(list *list, void const *value) {
  assert(list != NULL);
  _node *node_to_insert = create_node(value, list->data_size);
  list->tail->next = node_to_insert;
  list->tail = node_to_insert;
  ++list->count;
}

void list_add_at(list *list, void const *value, uint32_t idx) {
  assert(list != NULL);
  if (idx == 0) {
    list_add_front(list, value);
    return;
  }

  _node *node_to_insert = create_node(value, list->data_size);
  _node *head = list->head;
  _node *prev = NULL;
  while (head && idx != 0) {
    prev = head;
    head = head->next;
    --idx;
  }

  assert(idx == 0);
  node_to_insert->next = prev->next;
  prev->next = node_to_insert;
  ++list->count;
}

void list_remove_front(list *list) {
  assert(list != NULL);
  assert(list->head != NULL);
  _node *head = list->head;
  list->head = list->head->next;
  node_delete(&head);
  --list->count;
  if (list->count == 0) {
    list->head = NULL;
    list->tail = NULL;
  }
}

void list_remove_back(list *list) {
  assert(list != NULL);
  assert(list->tail != NULL);
  _node *del = NULL;
  if (list->count == 1) {
    del = list->head;
    node_delete(&del);
    list->head = NULL;
    list->tail = NULL;
    return;
  }

  if (list->count == 2) {
    del = list->head;
    list->head = list->tail;
    node_delete(&del);
  }

  uint32_t second_to_last = list->count - 2;
  _node *it = list->head;
  while (it && second_to_last != 0) {
    it = it->next;
    second_to_last--;
  }

  it->next = NULL;
  del = list->tail;
  node_delete(&del);
  list->tail = it;
  --list->count;
}

void list_remove_at(list *list, uint32_t idx) {
  assert(list != NULL);
  assert(list->tail != NULL);
  if (idx == 0) {
    list_remove_front(list);
    return;
  }
  _node *it = list->head;
  _node *prev = NULL;
  while (it && idx != 0) {
    prev = it;
    it = it->next;
  }

  assert(idx == 0);
  prev->next = it->next;
  it->next = NULL;
  node_delete(&it);
  --list->count;
}

node *list_front(list *list) {
  assert(list != NULL);
  assert(list->head != NULL);
  return list->head;
}

node *list_back(list *list) {
  assert(list != NULL);
  assert(list->tail != NULL);
  return list->tail;
}

uint32_t list_count(list *list) {
  assert(list != NULL);
  return list->count;
}
