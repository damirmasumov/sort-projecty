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
            printf("\n a — добавить, r — удалить, e — выйти: ");
            char op;
            scanf(" %c", &op);
            while (getchar() != '\n');

            if (op == 'a') {
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
            } else if (op == 'r') {
                if (!is_empty(stack)) {
                    printf("Удалено: %d\n", pop(&stack));
                    print_stack(stack);
                } else {
                    printf("Стек пуст!\n");
                }
            } else if (op == 'e') {
                break;
            }
        }

        int size = 0;
        Node* temp = stack;
        while (temp != NULL) {
            size++;
            temp = temp->next;
        }
       
        printf("\n--- Сортировка прямым включением ---\n");
        Node* copy1 = copy_stack(stack);
        clock_t start = clock();
        Node* sorted1 = insertion_sort_list(copy1);
        clock_t end = clock();
        double time1 = ((double)(end - start)) / CLOCKS_PER_SEC;
        print_stack(sorted1);
        printf("Время: %.6f сек\n", time1);
        free_stack(sorted1);

        printf("\n--- Сортировка слиянием ---\n");
        Node* copy2 = copy_stack(stack);
        start = clock();
        Node* sorted2 = merge_sort_list(copy2);
        end = clock();
        double time2 = ((double)(end - start)) / CLOCKS_PER_SEC;
        print_stack(sorted2);
        printf("Время: %.6f сек\n", time2);
        free_stack(sorted2);


        FILE* log_file = fopen("sorting_results.csv", "a");
        if (log_file != NULL) {
            fprintf(log_file, "InsertionSort,%d,%.6f\n", size, time1);
            fprintf(log_file, "MergeSort,%d,%.6f\n", size, time2);
            fclose(log_file);
        }
        
        
        free_stack(stack);

        printf("\nЗапустить снова? (y/n): ");
        scanf(" %c", &continue_program);
        while (getchar() != '\n');
    }
    return 0;
}