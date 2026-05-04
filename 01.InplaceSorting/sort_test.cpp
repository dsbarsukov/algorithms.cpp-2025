#include <gtest/gtest.h>

#include <algorithm>
#include <vector>

#include "sorting.h"

template <typename SortFunc>
void check_sort(SortFunc sort_func)
{
    {
        std::vector<int> data = {};
        sort_func(data.begin(), data.end());
        EXPECT_TRUE(std::is_sorted(data.begin(), data.end()));
    }

    {
        std::vector<int> data = {1};
        sort_func(data.begin(), data.end());
        EXPECT_TRUE(std::is_sorted(data.begin(), data.end()));
    }

    {
        std::vector<int> data = {1, 2, 3, 4, 5};
        sort_func(data.begin(), data.end());
        EXPECT_TRUE(std::is_sorted(data.begin(), data.end()));
    }

    {
        std::vector<int> data = {5, 4, 3, 2, 1};
        sort_func(data.begin(), data.end());
        EXPECT_TRUE(std::is_sorted(data.begin(), data.end()));
    }

    {
        std::vector<int> data = {4, 1, 3, 2, 5};
        sort_func(data.begin(), data.end());
        EXPECT_TRUE(std::is_sorted(data.begin(), data.end()));
    }

    {
        std::vector<int> data = {3, 1, 2, 3, 1, 2};
        sort_func(data.begin(), data.end());
        EXPECT_TRUE(std::is_sorted(data.begin(), data.end()));
    }

    {
        std::vector<int> data = {-1, 5, 0, -10, 3};
        sort_func(data.begin(), data.end());
        EXPECT_TRUE(std::is_sorted(data.begin(), data.end()));
    }
}

TEST(BubbleSortTest, SortsDifferentArrays)
{
    check_sort(bubble_sort<std::vector<int>::iterator>);
}

TEST(HeapSortTest, SortsDifferentArrays)
{
    check_sort(heap_sort<std::vector<int>::iterator>);
}