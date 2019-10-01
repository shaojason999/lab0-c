/*
 * Code for basic C skills diagnostic.
 * Developed for courses 15-213/18-213/15-513 by R. E. Bryant, 2017
 * Modified to store strings, 2018
 */

/*
 * This program implements a queue supporting both FIFO and LIFO
 * operations.
 *
 * It uses a singly-linked list to represent the set of queue elements
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "harness.h"
#include "queue.h"

/*
  Create empty queue.
  Return NULL if could not allocate space.
*/
queue_t *q_new()
{
    queue_t *q = malloc(sizeof(queue_t));
    /* What if malloc returned NULL? */
    if (!q)
        return NULL;
    q->head = NULL;
    q->tail = NULL;
    q->count = 0;
    return q;
}

/* Free all storage used by queue */
void q_free(queue_t *q)
{
    /* How about freeing the list elements and the strings? */
    /* Free queue structure */
    if (!q)
        return;
    list_ele_t *temp, *temp_next;
    temp = q->head;

    while (temp) {
        temp_next = temp->next;
        free(temp->value);
        free(temp);
        temp = temp_next;
    }

    free(q);
}

/*
  Attempt to insert element at head of queue.
  Return true if successful.
  Return false if q is NULL or could not allocate space.
  Argument s points to the string to be stored.
  The function must explicitly allocate space and copy the string into it.
 */
bool q_insert_head(queue_t *q, char *s)
{
    /* What should you do if the q is NULL? */
    if (!q)
        return false;
    list_ele_t *newh;
    newh = malloc(sizeof(list_ele_t));
    if (!newh)
        return false;
    /* Don't forget to allocate space for the string and copy it */
    /* What if either call to malloc returns NULL? */
    newh->value = malloc(sizeof(s));
    if (!(newh->value)) {
        free(newh);
        return false;
    }
    strcpy(newh->value, s);

    if (!(q->head)) {  // empty queue
        q->head = newh;
        q->tail = newh;
        newh->next = NULL;
    } else {
        newh->next = q->head;
        q->head = newh;
    }
    ++(q->count);
    return true;
}


/*
  Attempt to insert element at tail of queue.
  Return true if successful.
  Return false if q is NULL or could not allocate space.
  Argument s points to the string to be stored.
  The function must explicitly allocate space and copy the string into it.
 */
bool q_insert_tail(queue_t *q, char *s)
{
    /* You need to write the complete code for this function */
    /* Remember: It should operate in O(1) time */
    if (!q)
        return false;
    list_ele_t *newt;
    newt = malloc(sizeof(list_ele_t));
    if (!newt)
        return false;
    newt->value = malloc(sizeof(s));
    if (!(newt->value)) {
        free(newt);
        return false;
    }
    strcpy(newt->value, s);

    if (!(q->head)) {  // empty queue
        q->head = newt;
        q->tail = newt;
    } else {
        q->tail->next = newt;
        q->tail = newt;
    }
    newt->next = NULL;
    ++(q->count);

    return true;
}

/*
  Attempt to remove element from head of queue.
  Return true if successful.
  Return false if queue is NULL or empty.
  If sp is non-NULL and an element is removed, copy the removed string to *sp
  (up to a maximum of bufsize-1 characters, plus a null terminator.)
  The space used by the list element and the string should be freed.
*/
bool q_remove_head(queue_t *q, char *sp, size_t bufsize)
{
    /* You need to fix up this code. */
    if (!q || !(q->head))
        return false;

    list_ele_t *temp;
    if (sp)
        strncpy(sp, q->head->value, bufsize - 1);
    free(q->head->value);
    temp = q->head;
    q->head = q->head->next;
    free(temp);
    --(q->count);
    if (q->count == 0)
        q->tail = NULL;
    return true;
}

/*
  Return number of elements in queue.
  Return 0 if q is NULL or empty
 */
int q_size(queue_t *q)
{
    /* You need to write the code for this function */
    /* Remember: It should operate in O(1) time */
    if (!q || !(q->head))
        return 0;
    else
        return q->count;
}

/*
  Reverse elements in queue
  No effect if q is NULL or empty
  This function should not allocate or free any list elements
  (e.g., by calling q_insert_head, q_insert_tail, or q_remove_head).
  It should rearrange the existing ones.
 */
void q_reverse(queue_t *q)
{
    /* You need to write the code for this function */
    if (!q || !(q->head))
        return;

    list_ele_t *temp1, *temp2, *temp3;

    temp1 = q->head;
    temp2 = q->head->next;

    while (temp2) {
        temp3 = temp2->next;
        temp2->next = temp1;

        temp1 = temp2;
        temp2 = temp3;
    }

    q->tail = q->head;
    q->tail->next = NULL;
    q->head = temp1;
}
