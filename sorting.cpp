#define _CRT_SECURE_NO_WARNINGS

#include "sorting.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#ifdef _WIN32
#include <windows.h>
#include <process.h>
#else
#include <pthread.h>
#endif

/*
 *                         ЧАСТЬ 1: БЫСТРАЯ СОРТИРОВКА (QUICKSORT)
 */

 /*
  * Разбиение массива для быстрой сортировки
  * Выбирает опорный элемент (последний), переставляет элементы
  * так, что все элементы меньше опорного оказываются слева,
  * а все элементы больше — справа.
  * Возвращает индекс опорного элемента.
  */
static int partition(int arr[], int low, int high) {
    int pivot = arr[high];     /* Опорный элемент — последний в массиве */
    int i = low - 1;           /* Индекс для элементов меньше опорного */
    int j;                     /* Счётчик для прохода по массиву */
    int temp;                  /* Временная переменная для обмена */

    /* Проходим по всем элементам от low до high-1 */
    for (j = low; j < high; j++) {
        /* Если текущий элемент меньше или равен опорному */
        if (arr[j] <= pivot) {
            i++;               /* Увеличиваем индекс меньших элементов */
            /* Меняем местами arr[i] и arr[j] */
            temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }

    /* Ставим опорный элемент на правильное место */
    temp = arr[i + 1];
    arr[i + 1] = arr[high];
    arr[high] = temp;

    return i + 1;              /* Возвращаем индекс опорного элемента */
}

/*
 * Быстрая сортировка (рекурсивная версия)
 * Рекурсивно сортирует подмассив arr[low..high]
 */
static void quick_sort(int arr[], int low, int high) {
    if (low < high) {          /* Базовый случай: если подмассив из 1 элемента */
        int pi = partition(arr, low, high);  /* Находим индекс опорного элемента */
        quick_sort(arr, low, pi - 1);        /* Сортируем левую часть */
        quick_sort(arr, pi + 1, high);       /* Сортируем правую часть */
    }
}

/*
 * Обёртка для быстрой сортировки
 * Принимает массив и его размер, вызывает рекурсивную функцию
 */
void quick_sort_wrapper(int arr[], int n) {
    if (n <= 1) return;
    quick_sort(arr, 0, n - 1); /* Вызываем сортировку всего массива */
}