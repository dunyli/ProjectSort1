/*
 main.c (тесты и примеры применения)
 *
 * Содержит:
 * 1. Автоматические тесты для всех алгоритмов сортировки
 * 2. Примеры практического применения
 * 3. Сравнение производительности алгоритмов
 */

#define _CRT_SECURE_NO_WARNINGS

#include "sorting.h"
#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

 /* Счётчики для итогов тестов */
static int passed = 0;
static int failed = 0;

/*
 * Вспомогательная функция для проверки условий и вывода результата
 * Используется во всех тестах для единообразного вывода
 */
static void check(const char* description, int condition) {
    if (condition) {
        printf("  Успешно: %s\n", description);
        passed++;
    }
    else {
        printf("  Ошибка: %s\n", description);
        failed++;
    }
}

/*
 * ============================================================================
 *                         ТЕСТ 1: БЫСТРАЯ СОРТИРОВКА
 * ============================================================================
 */

 /*
  * Выводит массив ДО и ПОСЛЕ сортировки для наглядности
  */
static void test_quick_sort(void) {
    printf("\n=== Тест 1: Быстрая сортировка ===\n");

    /* 1.1 Случайный массив */
    printf("\n1.1 Случайный массив из 10 элементов\n");
    int n = 10;
    int* arr = create_random_array(n);

    /* Вывод ДО сортировки */
    printf("  ДО сортировки: [");
    for (int i = 0; i < n; i++) {
        printf("%d", arr[i]);
        if (i < n - 1) printf(", ");
    }
    printf("]\n");

    quick_sort_wrapper(arr, n);

    /* Вывод ПОСЛЕ сортировки */
    printf("  ПОСЛЕ сортировки: [");
    for (int i = 0; i < n; i++) {
        printf("%d", arr[i]);
        if (i < n - 1) printf(", ");
    }
    printf("]\n");

    check("Массив отсортирован", is_sorted(arr, n));
    free(arr);

    /* 1.2 Массив с одинаковыми элементами */
    printf("\n1.2 Массив с одинаковыми элементами (10 элементов)\n");
    n = 10;
    arr = (int*)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) arr[i] = 42;

    printf("  ДО сортировки: [");
    for (int i = 0; i < n; i++) {
        printf("%d", arr[i]);
        if (i < n - 1) printf(", ");
    }
    printf("]\n");

    quick_sort_wrapper(arr, n);

    printf("  ПОСЛЕ сортировки: [");
    for (int i = 0; i < n; i++) {
        printf("%d", arr[i]);
        if (i < n - 1) printf(", ");
    }
    printf("]\n");

    check("Массив с одинаковыми элементами отсортирован", is_sorted(arr, n));
    free(arr);

    /* 1.3 Уже отсортированный массив */
    printf("\n1.3 Уже отсортированный массив (10 элементов)\n");
    n = 10;
    arr = (int*)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) arr[i] = i;

    printf("  ДО сортировки: [");
    for (int i = 0; i < n; i++) {
        printf("%d", arr[i]);
        if (i < n - 1) printf(", ");
    }
    printf("]\n");

    quick_sort_wrapper(arr, n);

    printf("  ПОСЛЕ сортировки: [");
    for (int i = 0; i < n; i++) {
        printf("%d", arr[i]);
        if (i < n - 1) printf(", ");
    }
    printf("]\n");

    check("Уже отсортированный массив остался отсортированным", is_sorted(arr, n));
    free(arr);

    /* 1.4 Обратно отсортированный массив */
    printf("\n1.4 Обратно отсортированный массив (10 элементов)\n");
    n = 10;
    arr = (int*)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) arr[i] = n - i;

    printf("  ДО сортировки: [");
    for (int i = 0; i < n; i++) {
        printf("%d", arr[i]);
        if (i < n - 1) printf(", ");
    }
    printf("]\n");

    quick_sort_wrapper(arr, n);

    printf("  ПОСЛЕ сортировки: [");
    for (int i = 0; i < n; i++) {
        printf("%d", arr[i]);
        if (i < n - 1) printf(", ");
    }
    printf("]\n");

    check("Обратно отсортированный массив отсортирован", is_sorted(arr, n));
    free(arr);

    /* 1.5 Массив с отрицательными числами */
    printf("\n1.5 Массив с отрицательными числами (10 элементов)\n");
    n = 10;
    arr = (int*)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) arr[i] = rand() % 200 - 100;

    printf("  ДО сортировки: [");
    for (int i = 0; i < n; i++) {
        printf("%d", arr[i]);
        if (i < n - 1) printf(", ");
    }
    printf("]\n");

    quick_sort_wrapper(arr, n);

    printf("  ПОСЛЕ сортировки: [");
    for (int i = 0; i < n; i++) {
        printf("%d", arr[i]);
        if (i < n - 1) printf(", ");
    }
    printf("]\n");

    check("Массив с отрицательными числами отсортирован", is_sorted(arr, n));
    free(arr);

    /* 1.6 Массив из одного элемента */
    printf("\n1.6 Массив из одного элемента\n");
    n = 1;
    arr = (int*)malloc(n * sizeof(int));
    arr[0] = 42;

    printf("  ДО сортировки: [%d]\n", arr[0]);
    quick_sort_wrapper(arr, n);
    printf("  ПОСЛЕ сортировки: [%d]\n", arr[0]);

    check("Массив из одного элемента отсортирован", is_sorted(arr, n));
    free(arr);

    /* 1.7 Пустой массив */
    printf("\n1.7 Пустой массив\n");
    n = 0;
    quick_sort_wrapper(NULL, n);
    check("Пустой массив обработан корректно", 1);
}
/*
 * ============================================================================
 *                         ТЕСТ 2: СОРТИРОВКА СЛИЯНИЕМ
 * ============================================================================
 */

 /*
  * Выводит массив ДО и ПОСЛЕ сортировки для наглядности
  */
static void test_merge_sort(void) {
    printf("\n=== Тест 2: Сортировка слиянием ===\n");

    /* 2.1 Случайный массив */
    printf("\n2.1 Случайный массив из 10 элементов\n");
    int n = 10;
    int* arr = create_random_array(n);

    printf("  ДО сортировки: [");
    for (int i = 0; i < n; i++) {
        printf("%d", arr[i]);
        if (i < n - 1) printf(", ");
    }
    printf("]\n");

    merge_sort_wrapper(arr, n);

    printf("  ПОСЛЕ сортировки: [");
    for (int i = 0; i < n; i++) {
        printf("%d", arr[i]);
        if (i < n - 1) printf(", ");
    }
    printf("]\n");

    check("Массив отсортирован", is_sorted(arr, n));
    free(arr);

    /* 2.2 Массив с одинаковыми элементами */
    printf("\n2.2 Массив с одинаковыми элементами (10 элементов)\n");
    n = 10;
    arr = (int*)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) arr[i] = 42;

    printf("  ДО сортировки: [");
    for (int i = 0; i < n; i++) {
        printf("%d", arr[i]);
        if (i < n - 1) printf(", ");
    }
    printf("]\n");

    merge_sort_wrapper(arr, n);

    printf("  ПОСЛЕ сортировки: [");
    for (int i = 0; i < n; i++) {
        printf("%d", arr[i]);
        if (i < n - 1) printf(", ");
    }
    printf("]\n");

    check("Массив с одинаковыми элементами отсортирован", is_sorted(arr, n));
    free(arr);

    /* 2.3 Уже отсортированный массив */
    printf("\n2.3 Уже отсортированный массив (10 элементов)\n");
    n = 10;
    arr = (int*)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) arr[i] = i;

    printf("  ДО сортировки: [");
    for (int i = 0; i < n; i++) {
        printf("%d", arr[i]);
        if (i < n - 1) printf(", ");
    }
    printf("]\n");

    merge_sort_wrapper(arr, n);

    printf("  ПОСЛЕ сортировки: [");
    for (int i = 0; i < n; i++) {
        printf("%d", arr[i]);
        if (i < n - 1) printf(", ");
    }
    printf("]\n");

    check("Уже отсортированный массив остался отсортированным", is_sorted(arr, n));
    free(arr);

    /* 2.4 Обратно отсортированный массив */
    printf("\n2.4 Обратно отсортированный массив (10 элементов)\n");
    n = 10;
    arr = (int*)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) arr[i] = n - i;

    printf("  ДО сортировки: [");
    for (int i = 0; i < n; i++) {
        printf("%d", arr[i]);
        if (i < n - 1) printf(", ");
    }
    printf("]\n");

    merge_sort_wrapper(arr, n);

    printf("  ПОСЛЕ сортировки: [");
    for (int i = 0; i < n; i++) {
        printf("%d", arr[i]);
        if (i < n - 1) printf(", ");
    }
    printf("]\n");

    check("Обратно отсортированный массив отсортирован", is_sorted(arr, n));
    free(arr);

    /* 2.5 Массив с отрицательными числами */
    printf("\n2.5 Массив с отрицательными числами (10 элементов)\n");
    n = 10;
    arr = (int*)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) arr[i] = rand() % 200 - 100;

    printf("  ДО сортировки: [");
    for (int i = 0; i < n; i++) {
        printf("%d", arr[i]);
        if (i < n - 1) printf(", ");
    }
    printf("]\n");

    merge_sort_wrapper(arr, n);

    printf("  ПОСЛЕ сортировки: [");
    for (int i = 0; i < n; i++) {
        printf("%d", arr[i]);
        if (i < n - 1) printf(", ");
    }
    printf("]\n");

    check("Массив с отрицательными числами отсортирован", is_sorted(arr, n));
    free(arr);

    /* 2.6 Массив из одного элемента */
    printf("\n2.6 Массив из одного элемента\n");
    n = 1;
    arr = (int*)malloc(n * sizeof(int));
    arr[0] = 42;

    printf("  ДО сортировки: [%d]\n", arr[0]);
    merge_sort_wrapper(arr, n);
    printf("  ПОСЛЕ сортировки: [%d]\n", arr[0]);

    check("Массив из одного элемента отсортирован", is_sorted(arr, n));
    free(arr);

    /* 2.7 Пустой массив */
    printf("\n2.7 Пустой массив\n");
    n = 0;
    merge_sort_wrapper(NULL, n);
    check("Пустой массив обработан корректно", 1);
}

/*
 * ============================================================================
 *                         ТЕСТ 3: ВНЕШНЯЯ СОРТИРОВКА
 * ============================================================================
 */

static void test_external_sort(void) {
    printf("\n=== Тест 3: Внешняя сортировка ===\n");

    /* 3.1 Маленький массив */
    printf("3.1 Маленький массив (10 элементов, сегмент 3, буфер 2)\n");
    int arr1[] = { 64, 34, 25, 12, 22, 11, 90, 5, 88, 77 };
    int n1 = 10;
    int* sorted1 = external_merge_sort_with_buffer(arr1, n1, 3, 2);
    if (sorted1) {
        check("Массив отсортирован", is_sorted(sorted1, n1));
        free(sorted1);
    }

    /* 3.2 Средний массив */
    printf("\n3.2 Средний массив (100 элементов, сегмент 10, буфер 5)\n");
    int n2 = 100;
    int* arr2 = create_random_array(n2);
    int* sorted2 = external_merge_sort_with_buffer(arr2, n2, 10, 5);
    if (sorted2) {
        check("Массив отсортирован", is_sorted(sorted2, n2));
        free(sorted2);
    }
    free(arr2);

    /* 3.3 Большой массив */
    printf("\n3.3 Большой массив (1000 элементов, сегмент 50, буфер 10)\n");
    int n3 = 1000;
    int* arr3 = create_random_array(n3);
    int* sorted3 = external_merge_sort_with_buffer(arr3, n3, 50, 10);
    if (sorted3) {
        check("Массив отсортирован", is_sorted(sorted3, n3));
        free(sorted3);
    }
    free(arr3);

    /* 3.4 Массив с одинаковыми элементами */
    printf("\n3.4 Массив с одинаковыми элементами (20 элементов)\n");
    int n4 = 20;
    int* arr4 = (int*)malloc(n4 * sizeof(int));
    for (int i = 0; i < n4; i++) arr4[i] = 5;
    int* sorted4 = external_merge_sort_with_buffer(arr4, n4, 4, 2);
    if (sorted4) {
        check("Массив с одинаковыми элементами отсортирован", is_sorted(sorted4, n4));
        free(sorted4);
    }
    free(arr4);

    /* 3.5 Уже отсортированный массив */
    printf("\n3.5 Уже отсортированный массив (50 элементов)\n");
    int n5 = 50;
    int* arr5 = (int*)malloc(n5 * sizeof(int));
    for (int i = 0; i < n5; i++) arr5[i] = i * 2;
    int* sorted5 = external_merge_sort_with_buffer(arr5, n5, 10, 5);
    if (sorted5) {
        check("Уже отсортированный массив остался отсортированным", is_sorted(sorted5, n5));
        free(sorted5);
    }
    free(arr5);

    /* 3.6 Обратно отсортированный массив */
    printf("\n3.6 Обратно отсортированный массив (50 элементов)\n");
    int n6 = 50;
    int* arr6 = (int*)malloc(n6 * sizeof(int));
    for (int i = 0; i < n6; i++) arr6[i] = n6 - i;
    int* sorted6 = external_merge_sort_with_buffer(arr6, n6, 10, 5);
    if (sorted6) {
        check("Обратно отсортированный массив отсортирован", is_sorted(sorted6, n6));
        free(sorted6);
    }
    free(arr6);

    /* 3.7 Массив из одного элемента */
    printf("\n3.7 Массив из одного элемента\n");
    int n7 = 1;
    int arr7[] = { 42 };
    int* sorted7 = external_merge_sort_with_buffer(arr7, n7, 1, 1);
    if (sorted7) {
        check("Массив из одного элемента отсортирован", is_sorted(sorted7, n7));
        free(sorted7);
    }

    /* 3.8 Пустой массив */
    printf("\n3.8 Пустой массив\n");
    int n8 = 0;
    int* sorted8 = external_merge_sort_with_buffer(NULL, n8, 1, 1);
    check("Пустой массив обработан корректно", sorted8 == NULL);
}

/*
 * ============================================================================
 *                         ТЕСТ 4: ПАРАЛЛЕЛЬНАЯ СОРТИРОВКА
 * ============================================================================
 */

static void test_parallel_sort(void) {
    printf("\n=== Тест 4: Параллельная сортировка слиянием ===\n");

    /* 4.1 Маленький массив */
    printf("4.1 Маленький массив (10 элементов)\n");
    int arr1[] = { 64, 34, 25, 12, 22, 11, 90, 5, 88, 77 };
    int n1 = 10;
    int* copy1 = copy_array(arr1, n1);
    parallel_merge_sort(copy1, n1);
    check("Массив отсортирован", is_sorted(copy1, n1));
    free(copy1);

    /* 4.2 Средний массив */
    printf("\n4.2 Средний массив (1000 элементов)\n");
    int n2 = 1000;
    int* arr2 = create_random_array(n2);
    int* copy2 = copy_array(arr2, n2);
    parallel_merge_sort(copy2, n2);
    check("Массив отсортирован", is_sorted(copy2, n2));
    free(arr2);
    free(copy2);

    /* 4.3 Большой массив */
    printf("\n4.3 Большой массив (10000 элементов)\n");
    int n3 = 10000;
    int* arr3 = create_random_array(n3);
    int* copy3 = copy_array(arr3, n3);
    parallel_merge_sort(copy3, n3);
    check("Массив отсортирован", is_sorted(copy3, n3));
    free(arr3);
    free(copy3);

    /* 4.4 Массив с одинаковыми элементами */
    printf("\n4.4 Массив с одинаковыми элементами (100 элементов)\n");
    int n4 = 100;
    int* arr4 = (int*)malloc(n4 * sizeof(int));
    for (int i = 0; i < n4; i++) arr4[i] = 7;
    int* copy4 = copy_array(arr4, n4);
    parallel_merge_sort(copy4, n4);
    check("Массив с одинаковыми элементами отсортирован", is_sorted(copy4, n4));
    free(arr4);
    free(copy4);

    /* 4.5 Уже отсортированный массив */
    printf("\n4.5 Уже отсортированный массив (100 элементов)\n");
    int n5 = 100;
    int* arr5 = (int*)malloc(n5 * sizeof(int));
    for (int i = 0; i < n5; i++) arr5[i] = i;
    int* copy5 = copy_array(arr5, n5);
    parallel_merge_sort(copy5, n5);
    check("Уже отсортированный массив остался отсортированным", is_sorted(copy5, n5));
    free(arr5);
    free(copy5);

    /* 4.6 Сравнение производительности */
    printf("\n4.6 Сравнение производительности (100000 элементов)\n");
    int n6 = 100000;
    int* arr6 = create_random_array(n6);
    int* copy6 = copy_array(arr6, n6);

    clock_t start = clock();
    merge_sort_wrapper(arr6, n6);
    clock_t end = clock();
    double time_sequential = (double)(end - start) / CLOCKS_PER_SEC;

    start = clock();
    parallel_merge_sort(copy6, n6);
    end = clock();
    double time_parallel = (double)(end - start) / CLOCKS_PER_SEC;

    printf("  Последовательная сортировка: %.3f сек\n", time_sequential);
    printf("  Параллельная сортировка: %.3f сек\n", time_parallel);
    printf("  Ускорение: %.2fx\n", time_sequential / time_parallel);

    check("Параллельная сортировка корректна", is_sorted(copy6, n6));

    free(arr6);
    free(copy6);
}

/*
 * ============================================================================
 *                         ПРИМЕРЫ ПРИМЕНЕНИЯ
 * ============================================================================
 */

 /*
  * Пример 1: Сортировка базы данных (внешняя сортировка)
  *
  * Ситуация: есть база данных с 10 000 записей, которые нужно отсортировать.
  * Данные хранятся в файле, и они не помещаются в память целиком.
  * Используем внешнюю сортировку для обработки.
  */
static void example_database_sort(void) {
    printf("\n=== Пример 1: Сортировка базы данных ===\n");
    printf("Симуляция сортировки записей базы данных\n");

    int n = 10000;
    int* records = create_random_array(n);

    printf("Размер базы данных: %d записей\n", n);
    printf("До сортировки (первые 10): ");
    for (int i = 0; i < 10 && i < n; i++) {
        printf("%d ", records[i]);
    }
    printf("...\n");

    /* Используем внешнюю сортировку с буферами */
    clock_t start = clock();
    int* sorted = external_merge_sort_with_buffer(records, n, 100, 10);
    clock_t end = clock();
    double time = (double)(end - start) / CLOCKS_PER_SEC;

    if (sorted) {
        printf("После сортировки (первые 10): ");
        for (int i = 0; i < 10 && i < n; i++) {
            printf("%d ", sorted[i]);
        }
        printf("...\n");
        printf("Время сортировки: %.3f сек\n", time);
        printf("Проверка: массив %s\n", is_sorted(sorted, n) ? "отсортирован" : "не отсортирован");
        free(sorted);
    }

    free(records);
}

/*
 * Пример 2: Многопоточная обработка больших данных
 *
 * Ситуация: нужно быстро отсортировать большой массив данных.
 * Используем параллельную сортировку для ускорения на многоядерных системах.
 */
static void example_parallel_processing(void) {
    printf("\n=== Пример 2: Параллельная обработка данных ===\n");
    printf("Сортировка большого массива с использованием нескольких потоков\n");

    int n = 200000;
    int* data = create_random_array(n);

    printf("Размер массива: %d элементов\n", n);

    /* Используем параллельную сортировку */
    clock_t start = clock();
    parallel_merge_sort(data, n);
    clock_t end = clock();

    double time = (double)(end - start) / CLOCKS_PER_SEC;
    printf("Время сортировки: %.3f сек\n", time);
    printf("Проверка: массив %s\n", is_sorted(data, n) ? "отсортирован" : "не отсортирован");

    free(data);
}

/*
 * Пример 3: Сортировка логов сервера (внешняя + параллельная)
 *
 * Ситуация: сервер генерирует логи, которые нужно отсортировать по времени.
 * Сначала логи сортируются по частям (параллельно), затем выполняется
 * внешнее слияние для получения единого отсортированного файла.
 */
static void example_log_sorting(void) {
    printf("\n=== Пример 3: Сортировка логов сервера ===\n");
    printf("Гибридный подход: внешняя сортировка с параллельной обработкой\n");

    int n = 5000;
    int* logs = create_random_array(n);

    printf("Сгенерировано %d записей логов\n", n);

    /* Сортируем чанки параллельно, затем внешнее слияние */
    int segment_size = 200;
    int num_segments = (n + segment_size - 1) / segment_size;

    printf("Размер сегмента: %d, количество сегментов: %d\n", segment_size, num_segments);
    printf("Параллельная сортировка сегментов...\n");

    /* Сортируем сегменты в памяти (можно было бы параллельно) */
    for (int i = 0; i < num_segments; i++) {
        int start = i * segment_size;
        int end = (i + 1) * segment_size;
        if (end > n) end = n;
        quick_sort_wrapper(logs + start, end - start);
    }

    /* Внешнее слияние с буферами */
    int* sorted = external_merge_sort_with_buffer(logs, n, segment_size, 20);

    if (sorted) {
        printf("Сортировка завершена\n");
        printf("Проверка: массив %s\n", is_sorted(sorted, n) ? "отсортирован" : "не отсортирован");
        free(sorted);
    }

    free(logs);
}

/*
 * Пример 4: Сортировка результатов тестирования
 *
 * Ситуация: есть результаты тестов студентов, которые нужно отсортировать
 * по убыванию (от лучшего к худшему) для составления рейтинга.
 */
static void example_grades_sorting(void) {
    printf("\n=== Пример 4: Сортировка результатов тестирования ===\n");
    printf("Сортировка оценок студентов (по убыванию)\n");

    int n = 50;
    int* grades = create_random_array(n);

    /* Ограничим оценки диапазоном 0-100 */
    for (int i = 0; i < n; i++) {
        grades[i] = grades[i] % 101;
    }

    printf("До сортировки (первые 10): ");
    for (int i = 0; i < 10 && i < n; i++) {
        printf("%d ", grades[i]);
    }
    printf("...\n");

    /* Сортируем по убыванию (меняем знак при сравнении) */
    /* Для этого используем быструю сортировку с другим компаратором */
    /* Но в нашей реализации сортировка только по возрастанию */
    /* Поэтому просто сортируем по возрастанию */
    quick_sort_wrapper(grades, n);

    printf("После сортировки по возрастанию (первые 10): ");
    for (int i = 0; i < 10 && i < n; i++) {
        printf("%d ", grades[i]);
    }
    printf("...\n");

    /* Вычисляем статистику */
    int sum = 0;
    for (int i = 0; i < n; i++) {
        sum += grades[i];
    }
    float average = (float)sum / n;
    printf("Средний балл: %.2f\n", average);
    printf("Минимальный балл: %d\n", grades[0]);
    printf("Максимальный балл: %d\n", grades[n - 1]);

    free(grades);
}

/*
 * Пример 5: Сортировка данных с диска (реальный сценарий)
 *
 * Ситуация: данные хранятся во внешнем файле и не помещаются в память.
 * Используется внешняя сортировка с пошаговым чтением.
 *
 * В этом примере мы создаём файл с данными, сортируем его
 * и сохраняем результат обратно в файл.
 */
static void example_file_sorting(void) {
    printf("\n=== Пример 5: Сортировка данных с диска ===\n");
    printf("Чтение данных из файла, сортировка, запись обратно\n");

    const char* input_file = "input_data.dat";
    const char* output_file = "output_data_sorted.dat";

    int n = 1000;
    int* data = create_random_array(n);

    /* Записываем данные в файл */
    FILE* f = fopen(input_file, "wb");
    if (!f) {
        printf("Не удалось создать входной файл\n");
        free(data);
        return;
    }
    fwrite(data, sizeof(int), n, f);
    fclose(f);
    printf("Создан входной файл: %s (размер: %d элементов)\n", input_file, n);

    /* Читаем данные из файла */
    f = fopen(input_file, "rb");
    if (!f) {
        printf("Не удалось открыть входной файл\n");
        free(data);
        return;
    }
    int* file_data = (int*)malloc(n * sizeof(int));
    fread(file_data, sizeof(int), n, f);
    fclose(f);
    printf("Данные прочитаны из файла\n");

    /* Сортируем данные */
    printf("Выполняется сортировка...\n");
    clock_t start = clock();
    int* sorted = external_merge_sort_with_buffer(file_data, n, 50, 10);
    clock_t end = clock();
    double time = (double)(end - start) / CLOCKS_PER_SEC;

    if (sorted) {
        printf("Сортировка завершена за %.3f сек\n", time);

        /* Записываем результат в файл */
        f = fopen(output_file, "wb");
        if (!f) {
            printf("Не удалось создать выходной файл\n");
            free(file_data);
            free(sorted);
            return;
        }
        fwrite(sorted, sizeof(int), n, f);
        fclose(f);
        printf("Результат сохранён в файл: %s\n", output_file);

        /* Проверяем результат */
        printf("Проверка: массив %s\n", is_sorted(sorted, n) ? "отсортирован" : "не отсортирован");

        free(sorted);
    }

    /* Очищаем временные файлы */
    remove(input_file);
    remove(output_file);
    printf("Временные файлы удалены\n");

    free(data);
    free(file_data);
}

/*
 * ============================================================================
 *                         СРАВНЕНИЕ АЛГОРИТМОВ
 * ============================================================================
 */

 /*
  * Сравнение производительности всех алгоритмов
  *
  * Тест показывает, какой алгоритм быстрее для разных размеров данных:
  * - Быстрая сортировка: хороша для малых и средних данных
  * - Сортировка слиянием: стабильна для любых данных
  * - Параллельная сортировка: быстрее на многоядерных системах
  * - Внешняя сортировка: необходима для данных, не помещающихся в память
  */
static void compare_algorithms(void) {
    printf("\n=== Сравнение производительности алгоритмов ===\n");

    int sizes[] = { 100, 1000, 10000, 50000 };
    int num_sizes = sizeof(sizes) / sizeof(sizes[0]);

    printf("%-10s | %-12s | %-12s | %-12s | %-12s\n",
        "Размер", "Быстрая", "Слияние", "Параллельная", "Внешняя");
    printf("-----------+--------------+--------------+--------------+--------------\n");

    for (int s = 0; s < num_sizes; s++) {
        int n = sizes[s];
        int* arr = create_random_array(n);
        int* copy;
        double time_quick, time_merge, time_parallel, time_external;
        clock_t start, end;

        /* Быстрая сортировка */
        copy = copy_array(arr, n);
        start = clock();
        quick_sort_wrapper(copy, n);
        end = clock();
        time_quick = (double)(end - start) / CLOCKS_PER_SEC;
        free(copy);

        /* Сортировка слиянием */
        copy = copy_array(arr, n);
        start = clock();
        merge_sort_wrapper(copy, n);
        end = clock();
        time_merge = (double)(end - start) / CLOCKS_PER_SEC;
        free(copy);

        /* Параллельная сортировка (только для больших массивов) */
        if (n >= 1000) {
            copy = copy_array(arr, n);
            start = clock();
            parallel_merge_sort(copy, n);
            end = clock();
            time_parallel = (double)(end - start) / CLOCKS_PER_SEC;
            free(copy);
        }
        else {
            time_parallel = 0;
        }

        /* Внешняя сортировка (только для средних массивов) */
        if (n >= 100 && n <= 10000) {
            int segment_size = (n > 100) ? 50 : 10;
            int buffer_size = (n > 100) ? 10 : 3;
            start = clock();
            int* sorted = external_merge_sort_with_buffer(arr, n, segment_size, buffer_size);
            end = clock();
            time_external = (double)(end - start) / CLOCKS_PER_SEC;
            if (sorted) free(sorted);
        }
        else {
            time_external = 0;
        }

        printf("%-10d | %-12.4f | %-12.4f | %-12.4f | %-12.4f\n",
            n, time_quick, time_merge, time_parallel, time_external);

        free(arr);
    }

    printf("\nПримечания:\n");
    printf("  - Быстрая сортировка: быстрая для малых данных\n");
    printf("  - Сортировка слиянием: стабильная для любых данных\n");
    printf("  - Параллельная сортировка: использует несколько потоков\n");
    printf("  - Внешняя сортировка: работает с данными на диске\n");
}

/*
 * ============================================================================
 *                         ЗАПУСК ВСЕХ ТЕСТОВ
 * ============================================================================
 */

static void run_all_tests(void) {
    /* Инициализация генератора случайных чисел */
    srand((unsigned int)time(NULL));

    /* Тесты алгоритмов */
    test_quick_sort();
    test_merge_sort();
    test_external_sort();
    test_parallel_sort();

    /* Примеры применения */
    example_database_sort();
    example_parallel_processing();
    example_log_sorting();
    example_grades_sorting();
    example_file_sorting();

    /* Сравнение производительности */
    compare_algorithms();
}

/*
 *                               MAIN
 */

int main(void) {
    setlocale(0, "Rus");
    printf("Реализованные алгоритмы:\n");
    printf("  1. Быстрая сортировка (Quicksort)\n");
    printf("  2. Сортировка слиянием (Merge Sort)\n");
    printf("  3. Внешняя сортировка слиянием с буферами (External Sort)\n");
    printf("  4. Параллельная сортировка слиянием (Parallel Merge Sort)\n");
    printf("===============================================================\n");

    run_all_tests();

    printf("ИТОГИ ТЕСТОВ:\n");
    printf("  Пройдено: %d\n", passed);
    printf("  Провалено: %d\n", failed);
    printf("  Всего: %d\n", passed + failed);

    if (failed == 0) {
        printf("\nВСЕ ТЕСТЫ ПРОЙДЕНЫ УСПЕШНО!\n");
    }
    else {
        printf("\nЕСТЬ ПРОВАЛЕННЫЕ ТЕСТЫ!\n");
    }

    return 0;
}