#include <iostream>
#include <unordered_map>
#include <unordered_set>

void Print(const std::unordered_set<int>& kContainer)
{
    for (const auto& kElement : kContainer)
        std::cout << kElement << " ";
    std::cout << std::endl;
}

void Print(const std::unordered_map<int, int>& kContainer)
{
    for (const auto& kElement : kContainer)
        std::cout << kElement.first << ": " << kElement.second << ", ";
    std::cout << std::endl;
}

void Find(const std::unordered_set<int>& kContainer, const int kElement)
{
    if (kContainer.find(kElement) == kContainer.end())
        std::cout << kElement << " is not found" << std::endl;
    else
        std::cout << kElement << " is found" << std::endl;
}

void Find(const std::unordered_map<int, int>& kContainer, const int kElement)
{
    if (kContainer.find(kElement) == kContainer.end())
        std::cout << kElement << " is not found" << std::endl;
    else
        std::cout << kElement << " is found" << std:: endl;
}

int main()
{
    std::cout << "--std::unordered_set example--" << std::endl;
    std::unordered_set<int> set1 = {1, 2, 3, 4, 5};

    std::cout << "set1 initialized : ";
    Print(set1);

    set1.insert(2);
    std::cout << "2 inserted: ";
    Print(set1);

    set1.insert(10);
    set1.insert(300);
    std::cout << "10, 300 inserted: ";
    Print(set1);

    Find(set1, 4);
    Find(set1, 100);

    set1.erase(2);
    std::cout << "2 deleted: ";
    Print(set1);

    //Unordered_map example
    std::cout << "--std::unordered_map example--" << std::endl;
    std::unordered_map<int, int> square_map;

    square_map.insert({2, 4});
    square_map[3] = 9;
    std::cout << "square of 2, 3 inserted: ";
    Print(square_map);

    square_map[20] = 400;
    square_map[30] = 900;
    std::cout << "square of 20, 30 inserted: ";
    Print(square_map);

    Find(square_map, 10);
    Find(square_map, 20);

    std::cout << "square_map[3] = " << square_map[3] << std::endl;
    Print(square_map);
    std::cout << "Never inserted 100, but automatically standard value inserted: square_map[100]: " << square_map[100] << std::endl;
    
    return 0;
}