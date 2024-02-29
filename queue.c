#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <math.h>
#include "queue.h"

/* Notice: sometimes, Cppcheck would find the potential NULL pointer bugs,
 * but some of them cannot occur. You can suppress them by adding the
 * following line.
 *   cppcheck-suppress nullPointer
 */


/* Create an empty queue */
struct list_head *q_new()
{
    struct list_head *head = malloc(sizeof(struct list_head));
    if (!head)
        return NULL;
    else {
        INIT_LIST_HEAD(head);
        return head;
    }
}

/* Free all storage used by queue */
void q_free(struct list_head *l)
{
    if (!l)
        return;
    element_t *entry, *safe;
    list_for_each_entry_safe (entry, safe, l, list)
        q_release_element(entry);
    free(l);
}

/* Insert an element at head of queue */
bool q_insert_head(struct list_head *head, char *s)
{
    if (!head || !s)
        return false;

    element_t *node = (element_t *) malloc(sizeof(element_t));
    if (!node)
        return false;
    INIT_LIST_HEAD(&node->list);
    node->value = (char *) malloc(strlen(s) + 1);
    if (!node->value) {
        free(node);
        return false;
    }

    strncpy(node->value, s, strlen(s));
    node->value[strlen(s)] = '\0';

    list_add(&node->list, head);

    return true;
}


/* Insert an element at tail of queue */
bool q_insert_tail(struct list_head *head, char *s)
{
    if (!head || !s)
        return false;

    element_t *node = (element_t *) malloc(sizeof(element_t));
    if (!node)
        return false;
    INIT_LIST_HEAD(&node->list);
    node->value = (char *) malloc(strlen(s) + 1);
    if (!node->value) {
        free(node);
        return false;
    }

    strncpy(node->value, s, strlen(s));
    node->value[strlen(s)] = '\0';

    list_add_tail(&node->list, head);

    return true;
}


/* Remove an element from head of queue */
element_t *q_remove_head(struct list_head *head, char *sp, size_t bufsize)
{
    if (!head || list_empty(head))
        return NULL;

    element_t *tmp = list_first_entry(head, element_t, list);

    if (sp) {
        size_t copy_size;
        if (strlen(tmp->value) < (bufsize)) {
            copy_size = strlen(tmp->value);
        } else {
            copy_size = bufsize - 1;
        }
        strncpy(sp, tmp->value, copy_size);
        sp[copy_size] = '\0';
    }

    list_del(&tmp->list);

    return tmp;
}

/* Remove an element from tail of queue */
element_t *q_remove_tail(struct list_head *head, char *sp, size_t bufsize)
{
    if (!head || list_empty(head))
        return NULL;

    element_t *tmp = list_last_entry(head, element_t, list);

    if (sp) {
        size_t copy_size;
        if (strlen(tmp->value) < (bufsize)) {
            copy_size = strlen(tmp->value);
        } else {
            copy_size = bufsize - 1;
        }
        strncpy(sp, tmp->value, copy_size);
        sp[copy_size] = '\0';
    }

    list_del(&tmp->list);

    return tmp;
}

/* Return number of elements in queue */
int q_size(struct list_head *head)
{
    if (!head)
        return 0;

    int len = 0;
    struct list_head *li;

    list_for_each (li, head)
        len++;
    return len;
}

/* Delete the middle node in queue */
bool q_delete_mid(struct list_head *head)
{
    // https://leetcode.com/problems/delete-the-middle-node-of-a-linked-list/
    if (list_empty(head))
        return false;

    int length = (double) q_size(head);
    int delindex = (int) floor(length / 2);
    struct list_head *tmp = head;
    for (int i = 0; i <= delindex; i++) {
        tmp = tmp->next;
    }
    element_t *node = list_entry(tmp, element_t, list);
    list_del(tmp);
    q_release_element(node);
    return true;
}

/* Delete all nodes that have duplicate string */
bool q_delete_dup(struct list_head *head)
{
    // https://leetcode.com/problems/remove-duplicates-from-sorted-list-ii/
    if (!head || list_empty(head))
        return NULL;
    bool dup = false;
    element_t *tmp, *safe;
    list_for_each_entry_safe (tmp, safe, head, list) {
        if (&safe->list != head && !strcmp(tmp->value, safe->value)) {
            list_del(&tmp->list);
            q_release_element(tmp);
            dup = true;
        } else if (dup) {
            list_del(&tmp->list);
            q_release_element(tmp);
            dup = false;
        }
    }

    return true;
}

/* Swap every two adjacent nodes */
void q_swap(struct list_head *head)
{
    // https://leetcode.com/problems/swap-nodes-in-pairs/
}

/* Reverse elements in queue */
void q_reverse(struct list_head *head)
{
    if (!head || list_empty(head))
        return;

    struct list_head *traverse = head;
    do {
        struct list_head *tmp = traverse->next;
        traverse->next = traverse->prev;
        traverse->prev = tmp;
        traverse = traverse->next;
    } while (traverse != head);
}

/* Reverse the nodes of the list k at a time */
void q_reverseK(struct list_head *head, int k)
{
    // https://leetcode.com/problems/reverse-nodes-in-k-group/
}

/* Sort elements of queue in ascending/descending order */
void q_sort(struct list_head *head, bool descend) {}

/* Remove every node which has a node with a strictly less value anywhere to
 * the right side of it */
int q_ascend(struct list_head *head)
{
    // https://leetcode.com/problems/remove-nodes-from-linked-list/
    return 0;
}

/* Remove every node which has a node with a strictly greater value anywhere to
 * the right side of it */
int q_descend(struct list_head *head)
{
    // https://leetcode.com/problems/remove-nodes-from-linked-list/
    return 0;
}

/* Merge all the queues into one sorted queue, which is in ascending/descending
 * order */
int q_merge(struct list_head *head, bool descend)
{
    // https://leetcode.com/problems/merge-k-sorted-lists/
    return 0;
}
