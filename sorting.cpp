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
 * ============================================================================
 *                         ЧАСТЬ 1: БЫСТРАЯ СОРТИРОВКА (QUICKSORT)
 * ============================================================================
 */

 /*
  * Разбиение массива для быстрой сортировки
  * Использует стратегию с выбором среднего элемента в качестве опорного
  * и двухсторонним просмотром для улучшения производительности.
  *
  * Алгоритм:
  * 1. Выбираем опорный элемент как a[(l+r)/2]
  * 2. Двигаем указатель i слева направо, пока a[i] < опорный
  * 3. Двигаем указатель j справа налево, пока a[j] > опорный
  * 4. Если i >= j - останавливаемся
  * 5. Меняем местами a[i] и a[j], затем i++, j--
  * 6. Повторяем шаги 2-5 пока i <= j
  * 7. Возвращаем индекс j
  */
static int partition(int arr[], int low, int high) {
    int v = arr[(low + high) / 2];   /* Опорный элемент — средний */
    int i = low;                     /* Левый указатель */
    int j = high;                    /* Правый указатель */
    int temp;                        /* Временная переменная для обмена */

    while (i <= j) {
        /* Двигаем левый указатель вправо, пока элемент меньше опорного */
        while (arr[i] < v) {
            i++;
        }
        /* Двигаем правый указатель влево, пока элемент больше опорного */
        while (arr[j] > v) {
            j--;
        }
        /* Если указатели встретились, завершаем */
        if (i >= j) {
            break;
        }
        /* Меняем местами элементы и сдвигаем указатели */
        temp = arr[i];
        arr[i] = arr[j];
        arr[j] = temp;
        i++;
        j--;
    }

    return j;  /* Возвращаем индекс для разделения */
}

/*
 * Быстрая сортировка (рекурсивная версия)
 * Рекурсивно сортирует подмассив arr[low..high]
 * Использует улучшенное разбиение со средним элементом
 */
static void quick_sort(int arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);  /* Находим индекс разделения */
        quick_sort(arr, low, pi);            /* Сортируем левую часть */
        quick_sort(arr, pi + 1, high);       /* Сортируем правую часть */
    }
}

/*
 * Обёртка для быстрой сортировки
 * Принимает массив и его размер, вызывает рекурсивную функцию
 */
void quick_sort_wrapper(int arr[], int n) {
    if (n <= 1) return;
    quick_sort(arr, 0, n - 1);
}



/*
 * ============================================================================
 *                    ЧАСТЬ 2: СОРТИРОВКА СЛИЯНИЕМ (MERGE SORT)
 * ============================================================================
 */

 /*
  * Слияние двух отсортированных подмассивов
  * arr[l..m] и arr[m+1..r] сливаются в один отсортированный массив
  * Используется временный массив для хранения результата
  */
static void merge(int arr[], int left, int mid, int right) {
    int n1 = mid - left + 1;   /* Размер левой половины */
    int n2 = right - mid;      /* Размер правой половины */
    int* L;                    /* Временный массив для левой половины */
    int* R;                    /* Временный массив для правой половины */
    int i, j, k;               /* Счётчики для обхода массивов */

    /* Выделяем память для временных массивов */
    L = (int*)malloc(n1 * sizeof(int));
    R = (int*)malloc(n2 * sizeof(int));

    /* Копируем данные во временные массивы */
    for (i = 0; i < n1; i++) {
        L[i] = arr[left + i];  /* Копируем левую половину */
    }
    for (j = 0; j < n2; j++) {
        R[j] = arr[mid + 1 + j]; /* Копируем правую половину */
    }

    i = 0;                     /* Индекс для левого массива */
    j = 0;                     /* Индекс для правого массива */
    k = left;                  /* Индекс для результирующего массива */

    /* Слияние: сравниваем элементы и вставляем меньший */
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {    /* Если элемент из левой половины меньше */
            arr[k] = L[i];     /* Берём его */
            i++;               /* Переходим к следующему в левой */
        }
        else {               /* Иначе берём элемент из правой */
            arr[k] = R[j];
            j++;               /* Переходим к следующему в правой */
        }
        k++;                   /* Переходим к следующей позиции в результате */
    }

    /* Копируем оставшиеся элементы из левой половины (если есть) */
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    /* Копируем оставшиеся элементы из правой половины (если есть) */
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }

    /* Освобождаем временные массивы */
    free(L);
    free(R);
}

/*
 * Сортировка слиянием (рекурсивная версия)
 * Рекурсивно делит массив на две половины и сливает их
 */
static void merge_sort(int arr[], int left, int right) {
    if (left < right) {        /* Базовый случай: если подмассив из 1 элемента */
        int mid = left + (right - left) / 2; /* Находим середину */
        merge_sort(arr, left, mid);          /* Сортируем левую половину */
        merge_sort(arr, mid + 1, right);     /* Сортируем правую половину */
        merge(arr, left, mid, right);        /* Сливаем две половины */
    }
}

/*
 * Обёртка для сортировки слиянием
 * Принимает массив и его размер
 */
void merge_sort_wrapper(int arr[], int n) {
    if (n <= 1) return;
    merge_sort(arr, 0, n - 1);
}



/*
 * ============================================================================
 *               ЧАСТЬ 3: ВНЕШНЯЯ СОРТИРОВКА (EXTERNAL SORT)
 * ============================================================================
 */

 /*
  * Структура для хранения информации о сегменте (run) при внешней сортировке
  * Используется для k-путевого слияния
  *
  * Сегмент (run) — это отсортированная часть данных, сохранённая на диске
  * Каждый сегмент содержит:
  *   - data: указатель на массив данных сегмента в памяти
  *   - size: количество элементов в сегменте
  *   - current: текущий индекс для чтения (указывает, какой элемент следующий)
  */
typedef struct {
    int* data;                 /* Указатель на массив данных сегмента */
    int size;                  /* Количество элементов в сегменте */
    int current;               /* Текущий индекс для чтения */
} RunInfo;

/*
 * Создание временного файла для хранения сегмента
 * Каждый сегмент сохраняется в отдельный временный файл
 * Возвращает имя созданного файла
 */
static char* create_temp_filename(int run_num) {
    char* filename = (char*)malloc(32 * sizeof(char));
    sprintf(filename, "temp_run_%d.dat", run_num);
    return filename;
}

/*
 * Запись сегмента во временный файл
 * Сохраняет отсортированный массив на диск в бинарном формате
 *
 * Параметры:
 *   - arr: отсортированный массив (сегмент)
 *   - size: размер массива
 *   - filename: имя файла для сохранения
 */
static void write_run_to_file(int arr[], int size, const char* filename) {
    FILE* file = fopen(filename, "wb");  /* Открываем файл для записи в бинарном режиме */
    if (!file) {
        perror("Не удалось создать временный файл");
        return;
    }
    fwrite(arr, sizeof(int), size, file); /* Записываем массив в файл */
    fclose(file);                         /* Закрываем файл */
}

/*
 * Структура для чтения сегмента по частям (без загрузки всего сегмента в память)
 *
 * В реальной внешней сортировке сегменты могут быть огромными
 * и не помещаться в память целиком. Поэтому читаем их по частям
 * используя буфер фиксированного размера.
 */
typedef struct {
    FILE* file;                /* Указатель на открытый файл сегмента */
    int* buffer;               /* Буфер для хранения текущего блока данных */
    int buffer_size;           /* Размер буфера (сколько элементов помещается) */
    int buffer_count;          /* Сколько элементов реально загружено в буфер */
    int current_pos;           /* Текущая позиция в буфере */
    int segment_size;          /* Общий размер сегмента (для информации) */
    int elements_read;         /* Сколько элементов уже прочитано из сегмента */
    int is_empty;              /* Флаг: закончились ли данные в сегменте */
    int segment_index;         /* Индекс сегмента (для отладки) */
} RunReader;

/*
 * Создание читателя для сегмента
 * Открывает файл и инициализирует буфер
 *
 * Сегмент НЕ загружается в память целиком!
 * Вместо этого открываем файл и будем читать из него блоками
 */
static RunReader* create_run_reader(const char* filename, int buffer_size) {
    RunReader* reader = (RunReader*)malloc(sizeof(RunReader));
    if (!reader) return NULL;

    /* Открываем файл для чтения */
    reader->file = fopen(filename, "rb");
    if (!reader->file) {
        free(reader);
        perror("Не удалось открыть файл сегмента");
        return NULL;
    }

    /* Выделяем память под буфер */
    reader->buffer = (int*)malloc(buffer_size * sizeof(int));
    if (!reader->buffer) {
        fclose(reader->file);
        free(reader);
        return NULL;
    }

    /* Инициализируем все поля */
    reader->buffer_size = buffer_size;
    reader->buffer_count = 0;
    reader->current_pos = 0;
    reader->segment_size = 0;
    reader->elements_read = 0;
    reader->is_empty = 0;
    reader->segment_index = 0;

    /* Загружаем первую порцию данных в буфер */
    reader->buffer_count = fread(reader->buffer, sizeof(int), buffer_size, reader->file);
    reader->current_pos = 0;
    reader->elements_read = reader->buffer_count;

    /* Если ничего не прочитали - сегмент пуст */
    if (reader->buffer_count == 0) {
        reader->is_empty = 1;
    }

    return reader;
}

/*
 * Получение следующего элемента из сегмента
 * Если буфер закончился - загружаем следующую порцию из файла
 * Возвращает: 1 если элемент получен, 0 если данных больше нет
 * Значение элемента записывается в out_value
 */
static int get_next_from_reader(RunReader* reader, int* out_value) {
    /* Если сегмент пуст или данные закончились */
    if (reader->is_empty) {
        return 0;
    }

    /* Если достигли конца буфера - загружаем следующую порцию */
    if (reader->current_pos >= reader->buffer_count) {
        /* Читаем следующую порцию из файла */
        reader->buffer_count = fread(reader->buffer, sizeof(int), reader->buffer_size, reader->file);
        reader->current_pos = 0;

        /* Если ничего не прочитали - данные закончились */
        if (reader->buffer_count == 0) {
            reader->is_empty = 1;
            return 0;
        }

        /* Обновляем количество прочитанных элементов */
        reader->elements_read += reader->buffer_count;
    }

    /* Возвращаем текущий элемент и сдвигаем позицию */
    *out_value = reader->buffer[reader->current_pos];
    reader->current_pos++;
    return 1;
}

/*
 * Получение общего размера сегмента (без загрузки в память)
 * Определяем размер файла и вычисляем количество элементов
 */
static int get_segment_size_from_file(const char* filename) {
    FILE* file = fopen(filename, "rb");
    if (!file) return 0;

    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    fclose(file);

    return file_size / sizeof(int);
}

/*
 * Уничтожение читателя (закрытие файла и освобождение памяти)
 */
static void destroy_run_reader(RunReader* reader) {
    if (!reader) return;
    if (reader->file) fclose(reader->file);
    if (reader->buffer) free(reader->buffer);
    free(reader);
}
