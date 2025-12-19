#include "func.h"
#include <ctype.h>
#include <string.h>
int is_empty(Node* head) {
    return head == NULL;
}
Node* create_node(int value) {
    Node* node = (Node*)malloc(sizeof(Node));
    if (!node) {
        fprintf(stderr, "Ошибка памяти!\n");
        exit(EXIT_FAILURE);
    }
    node->data = value;
    node->next = NULL;
    return node;
}

void push(Node** head, int value) {
    Node* new_node = create_node(value);
    new_node->next = *head;
    *head = new_node;
}

int pop(Node** head) {
    if (is_empty(*head)) {
        fprintf(stderr, "Попытка извлечь из пустого стека!\n");
        exit(EXIT_FAILURE);
    }
    Node* temp = *head;
    int val = temp->data;
    *head = (*head)->next;
    free(temp);
    return val;
}

void print_stack(Node* head) {
    if (is_empty(head)) {
        printf("(стек пуст)\n");
        return;
    }
    Node* cur = head;
    printf("Стек: ");
    while (cur) {
        printf("%d ", cur->data);
        cur = cur->next;
    }
    printf("\n");
}

void free_stack(Node* head) {
    while (!is_empty(head)) {
        pop(&head);
    }
}

Node* generate_random_stack(int count) {
    if (count <= 0) return NULL;
    Node* stack = NULL;
    for (int i = 0; i < count; i++) {
        int num = rand() % 1000000;
        push(&stack, num);
    }
    return stack;
}

Node* copy_stack(Node* head) {
    if (is_empty(head)) return NULL;
    Node* temp = NULL;
    Node* cur = head;
    while (cur) {
        push(&temp, cur->data);
        cur = cur->next;
    }
    Node* result = NULL;
    while (!is_empty(temp)) {
        push(&result, pop(&temp));
    }
    free_stack(temp);
    return result;
}

int is_valid_integer(char* str) {
    if (!str) return 0;
    char* s = str;
    while (*s == ' ' || *s == '\t') s++;
    if (*s == '\0') return 0;
    if (*s == '-' || *s == '+') s++;
    if (*s == '\0') return 0;
    while (*s) {
        if (!isdigit((unsigned char)*s)) return 0;
        s++;
    }
    return 1;
}
void view_file_result(char* filename) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        printf("Ошибка: не удалось открыть файл '%s'\n", filename);
        return;
    }

    char line1[4096] = {0};
    char line2[4096] = {0};

    fgets(line1, sizeof(line1), file);
    fgets(line2, sizeof(line2), file);

    fclose(file);

    line1[strcspn(line1, "\n")] = '\0';
    line2[strcspn(line2, "\n")] = '\0';

    printf("Исходный ряд:\n%s\n", line1);
    printf("Отсортированный ряд:\n%s\n", line2);
}