#include <iostream>
#include <vector>
#include <chrono>
#include <random>
#include <algorithm>

// To compare the speed
bool LinearSearch(int target, std::vector<int>& sequence)
{
    for (auto num : sequence)
    {
        if (num == target)
            return true;
    }
    return false;
}

bool BinarySearch(int target, std::vector<int>& sequence)
{
    //Iterator error occur, so replace to indexing 
    // In modern c++, basically, separate data type used in algorithm from algorithm logic for sustainability
    int first = 0;
    int last = sequence.size() - 1;

    while (true) {
        int range_length = last - first;
        int median_index = first + std::floor(range_length / 2);
        int median_element = sequence[median_index];

        if (median_element == target)
            return true;
        else if (median_element > target) // Search the left subpart
            last = median_index; // set median as a last of left subpart 
        else if (median_element < target) // Search the right subpart
            first = median_index; // set median as a first of right subpart
        
        if (range_length == 1) // element is not in.
            return false;
    }
}

// To test the speed of binary search in large size 
void RunLargeSearchTest(int size, int target)
{
    std::vector<int> sequence;
    std::random_device rnd;
    std::mt19937 rand(rnd()); // + Mersenne twister : to get better quality of random

    // get random int range 1~size
    std::uniform_int_distribution<std::mt19937::result_type> uniform_dist(1, size);

    for (auto i=0; i<size; i++) 
        sequence.push_back(uniform_dist(rand));
    
    std::sort(sequence.begin(), sequence.end());

    // Timer set <NOT WORKING IN VSCODE>
    std::chrono::system_clock::time_point begin = std::chrono::system_clock::now();
    bool search_result = BinarySearch(target, sequence);

    std::chrono::system_clock::time_point end = std::chrono::system_clock::now();

    auto diff = std::chrono::duration_cast<std::chrono::microseconds>(end - begin);
    std::cout << "Time recorded : " << diff.count() << std::endl;

    if (search_result)
        std::cout << "The target is found" << std::endl;
    else
        std::cout << "The target is not found" << std::endl;
}


int main()
{
    // Chr
    RunLargeSearchTest(10000, 36543);
    RunLargeSearchTest(100000, 36543);
    RunLargeSearchTest(1000000, 36543);

    return 0;
}