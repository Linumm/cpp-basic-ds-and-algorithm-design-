#include <iostream>
#include <vector>

template <typename T>
std::vector<T> Merge(std::vector<T>& arr1, std::vector<T>& arr2)
{
    std::vector<T> merged;

    auto iter1 = arr1.begin();
    auto iter2 = arr2.begin();

    while (iter1 != arr1.end() && iter2 != arr2.end()) {
        // Compare which is prior and emplace it to new vector. [Combine process]
        if (*iter1 < *iter2) {
            merged.emplace_back(*iter1);
            iter1++;
        }
        else {
            merged.emplace_back(*iter2);
            iter2++;
        }
    }

    if (iter1 != arr1.end()) {
        for (; iter1 != arr1.end(); iter1++)
            merged.emplace_back(*iter1);
    }
    else {
        for (; iter2 != arr2.end(); iter2++)
            merged.emplace_back(*iter2);
    }

    return merged;
}


template <typename T>
std::vector<T> MergeSort(std::vector<T> arr)
{
    if (arr.size() > 1) {
        // Divide process
        auto mid = size_t(arr.size() / 2); // To get dividing point. = median
        // Now make left half vector and right half vector
        auto left_half = MergeSort<T>(std::vector<T>(arr.begin(), arr.begin() + mid));
        auto right_half = MergeSort<T>(std::vector<T>(arr.begin() + mid, arr.end()));

        // Send it to Merging process and get a sorted vector
        return Merge<T>(left_half, right_half);
    }

    return arr;
}

template <typename T>
void PrintVector(std::vector<T> arr)
{
    for (auto i : arr)
        std::cout << i << " ";
    std::cout << std::endl;
}


//Function to test algorithm
void RunMergeSortTest()
{
    std::vector<int> s1 {10,32,1,4,6,12,11,47,51,51};
    std::vector<char> s2 {'b','g','f','e','k','a'};

    std::cout << "Given vector: " << std::endl;
    PrintVector<int>(s1);
    PrintVector<char>(s2);

    auto sorted_s1 = MergeSort<int>(s1);
    auto sorted_s2 = MergeSort<char>(s2);

    std::cout << "Sorted vector: " << std::endl;
    PrintVector<int>(sorted_s1);
    PrintVector<char>(sorted_s2);
    std::cout << std::endl;
}


int main()
{
    RunMergeSortTest();
    return 0;
}