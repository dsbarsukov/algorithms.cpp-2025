#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <iomanip>

#include "collvalue.h"
#include "sorting.h"

using CollInt = CollectingValue<int>;

// Random data
std::vector<CollInt> generate_data(size_t n)
{
    std::vector<CollInt> data(n);
    std::iota(data.begin(), data.end(), CollInt(0));
    return data;
}

void shuffle_data(std::vector<CollInt>& data)
{
    std::shuffle(data.begin(), data.end(), std::mt19937{std::random_device{}()});
}

// Подавление предупреждения clang-tidy:
// NOLINTNEXTLINE(bugprone-exception-escape)
int main()
{
    // Используем обычный массив размеров вместо std::vector,
    // чтобы избежать лишних предупреждений clang-tidy
    // о потенциальных исключениях при динамическом выделении памяти.
    const size_t sizes[] = {100, 500, 1000, 2000};

    std::cout << std::setw(7) << "N" << " | "
              << std::setw(12) << "Algo" << " | "
              << std::setw(12) << "Comps" << " | "
              << std::setw(12) << "Swaps" << " | "
              << std::setw(12) << "Moves" << "\n";
    std::cout << "-------------------------------------------------------------------\n";

    for (size_t n : sizes)
    {
        // Используем один общий перемешанный набор данных для всех сортировок,
        // чтобы сравнение алгоритмов было корректным на одинаковом входе.
        auto source_data = generate_data(n);
        shuffle_data(source_data);

        // Использую setw для ровного табличного вывода,
        // чтобы статистика не смещалась и результаты было удобно анализировать.

        // --- Std Sort ---
        auto number_data = source_data;
        CollInt::reset_stats();
        std::sort(number_data.begin(), number_data.end());
        std::cout << std::setw(7) << n << " | "
                  << std::setw(12) << "std::sort" << " | "
                  << std::setw(12) << CollInt::comps << " | "
                  << std::setw(12) << CollInt::swaps << " | "
                  << std::setw(12) << CollInt::moves << "\n";

        // --- Bubble Sort ---
        number_data = source_data;
        CollInt::reset_stats();
        bubble_sort(number_data.begin(), number_data.end());
        std::cout << std::setw(7) << n << " | "
                  << std::setw(12) << "Bubble" << " | "
                  << std::setw(12) << CollInt::comps << " | "
                  << std::setw(12) << CollInt::swaps << " | "
                  << std::setw(12) << CollInt::moves << "\n";

        // --- Heap Sort ---
        number_data = source_data;
        CollInt::reset_stats();
        heap_sort(number_data.begin(), number_data.end());
        std::cout << std::setw(7) << n << " | "
                  << std::setw(12) << "Heap" << " | "
                  << std::setw(12) << CollInt::comps << " | "
                  << std::setw(12) << CollInt::swaps << " | "
                  << std::setw(12) << CollInt::moves << "\n";

        std::cout << "-------------------------------------------------------------------\n";
    }

    return 0;
}
