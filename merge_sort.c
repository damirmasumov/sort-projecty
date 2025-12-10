#include "func.h"

void split_list(Node* head, Node** left, Node** right) {
    if (head == NULL || head->next == NULL) {
        *left = head;
        *right = NULL;
        return;
    }

    Node* slow = head;
    Node* fast = head->next;

    while (fast != NULL) {
        fast = fast->next;
        if (fast != NULL) {
            slow = slow->next;
            fast = fast->next;
        }
    }

    *left = head;
    *right = slow->next;
    slow->next = NULL;
}

Node* merge_lists(Node* a, Node* b) {
    if (a == NULL) return b;
    if (b == NULL) return a;

    if (a->data <= b->data) {
        a->next = merge_lists(a->next, b);
        return a;
    } else {
        b->next = merge_lists(a, b->next);
        return b;
    }
}

Node* merge_sort_list(Node* head) {
    if (head == NULL || head->next == NULL) return head;

    Node *left = NULL, *right = NULL;
    split_list(head, &left, &right);

    left = merge_sort_list(left);
    right = merge_sort_list(right);

    return merge_lists(left, right);
}