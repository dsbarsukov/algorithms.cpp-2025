#ifndef SORTING_H
#define SORTING_H

#include <utility>

// Header-only

// Для swap
#include "collvalue.h"

// ----------------------------- BubbleSort --------------------------------------
template <typename Iterator>
void bubble_sort(Iterator begin, Iterator end)
{
    using std::swap;

    size_t n = end - begin;

    if (n <= 1)
    {
        return;
    }

    for (size_t i = 0; i < n - 1; i++)
    {
        bool swapped = false;

        for (size_t j = 0; j < n - i - 1; j++)
        {
            if (*(begin + j + 1) < *(begin + j))
            {
                swap(*(begin + j), *(begin + j + 1));
                swapped = true;
            }
        }

        if (!swapped)
        {
            break;
        }
    }
}

// --------------------------- HeapSort ---------------------------------------
template <typename Iterator>
// Подавление предупреждения clang-tidy:
// NOLINTNEXTLINE(bugprone-easily-swappable-parameters)
void heapify(Iterator begin, size_t heap_size, size_t root)
{
    using std::swap;

    size_t largest = root;
    size_t left = 2 * root + 1;
    size_t right = 2 * root + 2;

    if (left < heap_size && *(begin + largest) < *(begin + left))
    {
        largest = left;
    }

    if (right < heap_size && *(begin + largest) < *(begin + right))
    {
        largest = right;
    }

    if (largest != root)
    {
        swap(*(begin + root), *(begin + largest));
        heapify(begin, heap_size, largest);
    }
}

template <typename Iterator>
void heap_sort(Iterator begin, Iterator end)
{
    using std::swap;

    size_t n = end - begin;

    if (n <= 1)
    {
        return;
    }

    // Построение max-heap
    for (int i = static_cast<int>(n / 2) - 1; i >= 0; i--)
    {
        heapify(begin, n, i);
    }

    // Извлечение максимума
    for (int i = static_cast<int>(n) - 1; i > 0; i--)
    {
        swap(*begin, *(begin + i));
        heapify(begin, i, 0);
    }
}
#endif // SORTING_H
