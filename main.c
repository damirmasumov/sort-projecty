#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include "func.h"
int main() {
    srand((unsigned int)time(NULL));
    char continue_program = 'y';

    while (continue_program == 'y' || continue_program == 'Y') {
        Node* stack = NULL;

        printf("\n=== Создание стека ===\n");
        printf("1. Ввести числа вручную\n");
        printf("2. Сгенерировать случайные числа\n");
        printf("Выберите (1 или 2): ");

        int choice;
        if (scanf("%d", &choice) != 1) {
            printf("Ошибка ввода!\n");
            while (getchar() != '\n');
            continue;
        }
        while (getchar() != '\n');

        if (choice == 1) {
            printf("Введите числа через пробел: ");
            char input[4096];
            if (!fgets(input, sizeof(input), stdin)) {
                printf("Ошибка ввода!\n");
                continue;
            }
            input[strcspn(input, "\n")] = '\0';
            if (strlen(input) == 0) {
                printf("Ошибка ввода!\n");
                continue;
            }

            char* token = strtok(input, " \t");
            while (token != NULL) {
                if (!is_valid_integer(token)) {
                    printf("Ошибка ввода!\n");
                    free_stack(stack);
                    stack = NULL;
                    break;
                }
                push(&stack, atoi(token));
                token = strtok(NULL, " \t");
            }
            if (!stack) continue;

        } else if (choice == 2) {
            printf("Сколько чисел? ");
            int count;
            if (scanf("%d", &count) != 1 || count <= 0) {
                printf("Ошибка ввода!\n");
                while (getchar() != '\n');
                continue;
            }
            while (getchar() != '\n');
            stack = generate_random_stack(count);

        } else {
            printf("Ошибка ввода!\n");
            continue;
        }

        if (is_empty(stack)) {
            printf("Ошибка: стек пуст!\n");
            continue;
        }

        printf("\n--- Ваш стек ---\n");
        print_stack(stack);

        char edit;
        printf("\nХотите изменить стек? (y/n): ");
        scanf(" %c", &edit);
        while (getchar() != '\n');

        while (edit == 'y' || edit == 'Y') {
            printf("\n add — добавить, remove — удалить, exit — выйти: ");
            char op;
            scanf(" %c", &op);
            while (getchar() != '\n');

            if (op == 'add') {
                printf("Число: ");
                int num;
                if (scanf("%d", &num) != 1) {
                    printf("Ошибка ввода!\n");
                    while (getchar() != '\n');
                    continue;
                }
                while (getchar() != '\n');
                push(&stack, num);
                print_stack(stack);
            } else if (op == 'remove') {
                if (!is_empty(stack)) {
                    printf("Удалено: %d\n", pop(&stack));
                    print_stack(stack);
                } else {
                    printf("Стек пуст!\n");
                }
            } else if (op == 'exit') {
                break;
            }
        }

        printf("\n--- Сортировка прямым включением ---\n");
        Node* copy1 = copy_stack(stack);
        clock_t start = clock();
        Node* sorted1 = insertion_sort_list(copy1);
        clock_t end = clock();
        printf("Время: %.6f сек\n", ((double)(end - start)) / CLOCKS_PER_SEC);
        free_stack(sorted1);

        printf("\n--- Сортировка слиянием ---\n");
        Node* copy2 = copy_stack(stack);
        start = clock();
        Node* sorted2 = merge_sort_list(copy2);
        end = clock();
        printf("Время: %.6f сек\n", ((double)(end - start)) / CLOCKS_PER_SEC);
        free_stack(sorted2);

        free_stack(stack);

        printf("\nЗапустить снова? (y/n): ");
        scanf(" %c", &continue_program);
        while (getchar() != '\n');
    }
    return 0;
}