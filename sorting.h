#pragma once
#ifndef SORTING_H
#define SORTING_H

#include <stdbool.h>

/*
 * ЧАСТЬ 1: БЫСТРАЯ СОРТИРОВКА (QUICKSORT)
 */
void quick_sort_wrapper(int arr[], int n);

/*
 * ЧАСТЬ 2: СОРТИРОВКА СЛИЯНИЕМ (MERGE SORT)
 */
void merge_sort_wrapper(int arr[], int n);

/*
 * ЧАСТЬ 3: ВНЕШНЯЯ СОРТИРОВКА (EXTERNAL SORT)
 */
int* external_merge_sort(int input[], int n, int chunk_size);

/*
 * ЧАСТЬ 4: ПАРАЛЛЕЛЬНАЯ СОРТИРОВКА СЛИЯНИЕМ
 */
void parallel_merge_sort(int arr[], int n);

/*
 * Вспомогательные функции для тестов
 */
int is_sorted(int arr[], int n);
int* create_random_array(int n);
int* copy_array(int arr[], int n);

#endif /* SORTING_H */