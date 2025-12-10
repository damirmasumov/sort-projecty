#include "func.h"

Node* insertion_sort_list(Node* head) {
    if (is_empty(head) || head->next == NULL) 
    return head;

    Node* sorted = NULL;
    Node* current = head;

    while (current != NULL) {
        Node* next = current->next;

        if (sorted == NULL || current->data <= sorted->data) {
            current->next = sorted;
            sorted = current;
        } else {
            Node* temp = sorted;
            while (temp->next != NULL && temp->next->data < current->data) {
                temp = temp->next;
            }
            current->next = temp->next;
            temp->next = current;
        }
        current = next;
    }
    return sorted;
}