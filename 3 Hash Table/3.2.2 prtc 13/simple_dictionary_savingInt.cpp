#include <iostream>
#include <vector>
 // This exercise only cares unsigned int

class HashMap
{
    std::vector<int> data;
    
    public:
        HashMap(int n)
        {
            data = std::vector<int>(n, -1);
            // -1 means no data in that position
        }

        void Insert(int value)
        {
            int n = data.size();
            data[value % n] = value;
            std::cout << value << " is inserted" << std::endl;
        }

        bool Find(int value) // Lookup function
        {
            int n = data.size();
            return (data[value % n] == value);
        }

        void Erase(int value)
        {
            int n = data.size();
            if (data[value % n] == value) {
                data[value % n] = -1;
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
    hmap.Insert(100); // Collision with existing '2'
    print(100);
    print(2);

    hmap.Erase(25);

    return 0;
}