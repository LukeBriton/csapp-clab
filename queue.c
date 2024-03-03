/* 
 * Code for basic C skills diagnostic.
 * Developed for courses 15-213/18-213/15-513 by R. E. Bryant, 2017
 */

/*
 * This program implements a queue supporting both FIFO and LIFO
 * operations.
 *
 * It uses a singly-linked list to represent the set of queue elements
 */

#include <stdlib.h>
#include <stdio.h>

#include "harness.h"
#include "queue.h"

/*
  Create empty queue.
  Return NULL if could not allocate space.
*/
queue_t *q_new()
{
    queue_t *q = malloc(sizeof(queue_t)); 
    if(q != NULL)
    {
        q->head = NULL;
        q->tail = NULL;
        q->size = 0;
        return q;
    }
    /* Remember to handle the case if malloc returned NULL */
    return NULL;
}

/* Free all storage used by queue */
void q_free(queue_t *q)
{
    if(q == NULL)
        return;
    list_ele_t *present = q->head;
    list_ele_t *next;
    while(present)
    {
        next = present->next;
        free(present);
        present = next;
    }
    free(q);
    /* Remember to free the queue structue and list elements */
}

/*
  Attempt to insert element at head of queue.
  Return true if successful.
  Return false if q is NULL or could not allocate space.
 */
bool q_insert_head(queue_t *q, int v)
{
    if(q == NULL)
        return false;
    list_ele_t *inserted = malloc(sizeof(list_ele_t)); 
    if(inserted == NULL)
        return false;
    inserted->next = q->head;
    inserted->value = v;
    q->head = inserted; // Once misplaced
    if(q->size == 0)
        q->tail = q->head;
    q->size ++;
    /* What should you do if the q is NULL? */
    /* What if malloc returned NULL? */
    return true;
}


/*
  Attempt to insert element at tail of queue.
  Return true if successful.
  Return false if q is NULL or could not allocate space.
 */
bool q_insert_tail(queue_t *q, int v)
{
    if(q == NULL)
        return false;
    list_ele_t *inserted = malloc(sizeof(list_ele_t)); 
    if(inserted == NULL)
        return false;
    inserted->next = NULL;
    inserted->value = v;
    if(q->size == 0)
    {
        q->tail = inserted; // Once forgot
        q->head = q->tail;
    }
    else
    {
        q->tail->next = inserted; // Once misplaced
        q->tail = inserted;
    }
    q->size ++;
    /* Remember: It should operate in O(1) time */
    return true;
}

/*
  Attempt to remove element from head of queue.
  Return true if successful.
  Return false if queue is NULL or empty.
  If vp non-NULL and element removed, store removed value at *vp.
  Any unused storage should be freed
*/
bool q_remove_head(queue_t *q, int *vp)
{
    if(q == NULL || q->size == 0 || vp == NULL)
        return false;
    list_ele_t *removed = q->head;
    *vp = removed->value; // By pointer
    q->head = q->head->next;
    q->size --;
    free(removed);
    return true;
}

/*
  Return number of elements in queue.
  Return 0 if q is NULL or empty
 */
int q_size(queue_t *q)
{
    if(q != NULL)
        return q->size;
    /* Remember: It should operate in O(1) time */
    return 0;
}

/*
  Reverse elements in queue.

  Your implementation must not allocate or free any elements (e.g., by
  calling q_insert_head or q_remove_head).  Instead, it should modify
  the pointers in the existing data structure.
 */
// Inefficient one
// Time consuming O(n^2)
// 有點像先出隊再進隊,in-place。
/*
void q_reverse(queue_t *q)
{
    list_ele_t *new_head, *new_tail, *new_present, *temp;
    if(q == NULL || q->size == 0 || q->size == 1)
        return;
    new_head = q->tail;
    new_tail = q->head;
    new_present = new_head;
    for(int i = 1; i < q->size; ++i)
    {
        temp = q->head;
        for(int j = 1; j < q->size - i; ++j)
        {
            temp = temp->next;
        }
        new_present->next = temp;
        new_present = temp;
    }
    q->head = new_head;
    q->tail = new_tail;
    q->tail->next = NULL;
}
*/

// Efficient one O(n)
// 相當於改變了排隊時各人朝向
void q_reverse(queue_t *q)
{
    list_ele_t *current, *previous, *next, *tmp;
    list_ele_t *new_head, *new_tail;
    if(q == NULL || q->size == 0 || q->size == 1)
        return;
    new_head = q->tail;
    new_tail = q->head;
    tmp = q->head;
    next = q->head->next;
    for(int i = 1; i < q->size; ++i)
    {
        previous = tmp;
        tmp = next;
        current = tmp;
        next = tmp->next; //Once I used tmp = tmp->next
        current->next = previous;
    }
    q->head = new_head;
    q->tail = new_tail;
    q->tail->next = NULL;
}
