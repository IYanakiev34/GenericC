#ifndef LINKED_LIST_INCLUDED_H
#define LINKED_LIST_INCLUDED_H

#include <stdbool.h>
#include <stdint.h>

typedef struct _node node;
typedef struct _list list;

/**
 * @brief Create a linked list that will store elements of a user defined
 * data size.
 * @param data_size the size in bytes of the data type that will be stored in
 * the linked list.
 * @return a pointer to the newly created linked list.
 */
list *list_create(uint32_t data_size);

/**
 * @brief Destroy an existing linked list. It will free all the memory of the
 * linked list along with the pointer to the linked list.
 * @param list The linked list to be destroyed.
 */
void list_destroy(list *list);

/** Convinience type for the print function of the value stored in the linked
 * list. TODO: very inefficient we should write to buffer
 */
typedef char const *(*node_value_pptr)(void const *);

/**
 * @brief Pretty print a linked list using a user supplied print function for
 * the type stored in the linked list.
 * @param list The list which will be printed to cout
 * @param print_func The function used for printing the values stored in the
 * list.
 */
void list_print(list *list, node_value_pptr print_func);

/**
 * @brief Add a value to the front of the linked list and update the head of it.
 * @param list The list to which the value will be inserted at the front.
 * @param value a pointer to the value to be added to the linked list. The value
 * will always be copied to the linked list.
 */
void list_add_front(list *list, void const *value);

/**
 * @brief Add a value to the back of the linked list and update the tail of it.
 * @param list The list to which the value will be inserted at the tail.
 * @param value a pointer to the value to be added to the linked list. The value
 * will always be copied to the linked list.
 */
void list_add_back(list *list, void const *value);

/**
 * @brief Add a value at a specified position in the linked list. If the index
 * is out of bounds nothing will happend, othewise the value will be copied and
 * added as a node to the list.
 * @param list The list to which the value will be added to.
 * @param value A pointer to the value which will be used to create a node.
 * @paam idx The position at which the value will be inserted if it is valid.
 */
void list_add_at(list *list, void const *value, uint32_t idx);

/**
 * @brief Remove the head of the list.
 * @param list The list on which the operation will be performed.
 */
void list_remove_front(list *list);

/**
 * @brief Remove the tail of the list.
 * @param list The list on which the operation will be performed.
 */
void list_remove_back(list *list);

/**
 * @brief Remove an element in the list at a specified position.
 * @param list The list in which the element will be removed.
 * @param idx The item at the position which should be removed.
 */
void list_remove_at(list *list, uint32_t idx);

/**
 * @brief Obtain a pointer to the head of the linked list if it exists.
 * @param list The list from which the head will be obtained.
 * @return The node of the linked list or NULL if the list is empty
 */
node *list_front(list *list);

/**
 * @brief Obtain a pointer to the tail of the linked list if it exists.
 * @param list The list from which the tail will be obtained.
 * @return The node of the linked list or NULL if the list is empty.
 */
node *list_back(list *list);

/**
 * @brief Get the number of elements stored in the list.
 * @param list The list on which we will obtain the count of.
 * @return The number of elements in the list.
 */
uint32_t list_count(list *list);

#endif
