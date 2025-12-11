#include <stdio.h>
#include <stdlib.h>


typedef struct Node {
    int data;
    struct Node* next;
} Node;

int is_empty(Node* head);
Node* create_node(int value);
void push(Node** head, int value);
int pop(Node** head);
void print_stack(Node* head);
void free_stack(Node* head);
Node* generate_random_stack(int count);
Node* copy_stack(Node* head);
Node* insertion_sort_list(Node* head);
void split_list(Node* head, Node** left, Node** right);
Node* merge_lists(Node* a, Node* b);
Node* merge_sort_list(Node* head);
int is_valid_integer(char* str);