#include <iostream>
#include <vector>
#include <list>
#include <algorithm>

using uint = unsigned int;

class HashMap
{
    std::vector<std::list<int>> data;

    public:
        HashMap(size_t n)
        {
            data.resize(n);
        }

        void Insert(uint value)
        {
            int n = data.size();
            data[value % n].push_back(value); // Add a key at last of node in list
            std::cout << value << " is inserted" << std::endl;
        }

        bool Find(uint value)
        {
            int n = data.size();
            auto& entries = data[value % n];
            return std::find(entries.begin(), entries.end(), value) != entries.end();
            // in c++ iterator, .end() means the last element idx + 1, so it means it already checked all elements
        }

        void Erase(uint value)
        {
            int n = data.size();
            auto& entries = data[value % n];
            auto iter = std::find(entries.begin(), entries.end(), value);

            if (iter != entries.end()) {
                entries.erase(iter);
                std::cout << value << " is deleted" << std::endl;
            }
        }
};

int main()
{
    HashMap hmap(7); // array size with N
    //Lambda func for lookup
    auto print = [&](int value) 
    {
        if (hmap.Find(value))
            std::cout << value << " is in hash map" << std::endl;
        else
            std::cout << value << " is not in hash map" << std::endl;
    };

    hmap.Insert(2);
    hmap.Insert(25);
    hmap.Insert(10);
    hmap.Insert(100); // Added after 2
    hmap.Insert(55);

    print(100);
    print(2);

    hmap.Erase(2);
    hmap.Erase(100);

    return 0;
}