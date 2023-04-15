#include <iostream>
#include <vector>

// Parition() to divide
template <typename T>
auto Partition(typename std::vector<T>::iterator begin, typename std::vector<T>::iterator end)
{
    // 3 Iterator : begin, pivot, end
    auto pivot_val = *begin; // Here, pivot is the begin point
    auto left_iter = begin + 1; 
    auto right_iter = end;

    while (1)
    {
        //Compare elements with pivot, from left
        while (*left_iter <= pivot_val && std::distance(left_iter, right_iter) > 0)
            left_iter++;
        
        while (*right_iter > pivot_val && std::distance(left_iter, right_iter) > 0)
            right_iter--;
        
        //If left_iter == right_iter, then there's no element to exchange
        // if not, exchange
        if (left_iter == right_iter)
            break;
        else
            std::iter_swap(left_iter, right_iter);
    }
    
    if (pivot_val > *right_iter)
            std::iter_swap(begin, right_iter);
        
        return right_iter;
}

template <typename T>
void QuickSort(typename std::vector<T>::iterator begin, typename std::vector<T>::iterator last)
{
    if (std::distance(begin, last) >= 1) { 
        // If the number of elements >= 1, partition and recursively sort the generated vector by partition
        auto partition_iter = Partition<T>(begin, last);
        QuickSort<T>(begin, partition_iter - 1);
        QuickSort<T>(partition_iter, last);
    }
}

template <typename T>
void PrintVector(std::vector<T> arr)
{
    for (auto i: arr)
        std::cout << i << " ";
    std::cout << std::endl;
}


// Test case function
void RunQuickSortTest()
{
    std::vector<int> s1 {10,32,1,4,6,12,11,47,51,51};
    std::vector<char> s2 {'b','g','f','e','k','a'};
    std::vector<double> s3 {7.8, 4.3, 10.1, 10.9, 2.4, 1.5};

    std::cout << "Given vector: " << std::endl;
    PrintVector<int>(s1);
    PrintVector<char>(s2);
    PrintVector<double>(s3);

    QuickSort<int>(s1.begin(), s1.end()-1);
    QuickSort<char>(s2.begin(), s2.end()-1);
    QuickSort<double>(s3.begin(), s3.end()-1);

    std::cout << "Sorted vector: " << std::endl;
    PrintVector<int>(s1);
    PrintVector<char>(s2);
    PrintVector<double>(s3);
    std::cout << std::endl;
}


int main()
{
    RunQuickSortTest();
    return 0;
}