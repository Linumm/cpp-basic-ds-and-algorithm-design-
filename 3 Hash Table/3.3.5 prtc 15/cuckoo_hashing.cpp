#include <iostream>
#include <vector>

class Hashmap
{
    std::vector<int> hash_table1;
    std::vector<int> hash_table2;
    int size;
    //Constructor

    //Hash function [here, use module]
    int Hash1(int key) const //Hash table 1's hashing func
    {
        return key % size;
    }

    int Hash2(int key) const //Hash table 2's hashing func. !! There must be diference between two hash func.
    {
        return (key / size) % size; 
    }

    public:
        Hashmap(int n) : size(n)
        {
            hash_table1 = std::vector<int>(size, -1);
            hash_table2 = std::vector<int>(size, -1);
        }

        std::vector<int>::iterator Lookup(int key)
        {
            auto hash_value1 = Hash1(key);
            if (hash_table1[hash_value1] == key) {
                std::cout << "key " << key << " is found in Hash table 1" << std::endl;
                return hash_table1.begin() + hash_value1;
            }
            // If it is not in table1
            auto hash_value2 = Hash2(key);
            if (hash_table2[hash_value2] == key) {
                std::cout << "key " << key << " is found in Hash table 2" << std::endl;
                return hash_table2.begin() + hash_value2;
            }
            //If none
            return hash_table2.end();
            
        }

        void Erase(int key)
        {
            auto position = Lookup(key);
            if (position != hash_table2.end()) {
                *position = -1;
                std::cout << "key " << key << " is deleted" << std::endl;
            }
            else
                std::cout << "key " << key << " is not in table" << std::endl;
        }

        void Insert(int key)
        {
            Insert_impl(key, 0, 1);
        }

        void Insert_impl(int key, int num_recursive_called, int table_num)
        {
            if (num_recursive_called >= size) {
                std::cout << "Cycle happened : Rehashing is required" << std::endl;
                return;
            }

            if (table_num == 1) { // First step into table1
                int hash = Hash1(key);
                if (hash_table1[hash] == -1) {
                    hash_table1[hash] = key;
                    std::cout << "key " << key << " is Inserted" << std::endl;
                }
                else { // Now move existing key to hash table2 
                    int existing_key = hash_table1[hash];
                    hash_table1[hash] = key;
                    std::cout << key << " is Inserted in table" << table_num << " : Existing " << existing_key << " is now on move" << std::endl;
                    Insert_impl(existing_key, num_recursive_called + 1, 2);
                }
            }
            else { // table_num == 2
                int hash = Hash2(key);
                if (hash_table2[hash] == -1) {
                    hash_table2[hash] = key;
                    std::cout << "key " << key << " is Inserted" << std::endl;
                }
                else {
                    int existing_key = hash_table2[hash];
                    hash_table2[hash] = key;
                    std::cout << key << " is Inserted in table" << table_num << " : Existing " << existing_key << " is now on move" << std::endl;
                    Insert_impl(existing_key, num_recursive_called + 1, 1);
                }
            }
        }

        void Print()
        {
            std::cout << "Index: ";
            for (int i=0; i<size; i++)
                std::cout << i << '\t';
            std::cout << std::endl;

            std::cout << "Table1: ";
            for (auto i : hash_table1)
                std::cout << i << '\t';
            std::cout << std::endl;

            std::cout << "Table2: ";
            for (auto i : hash_table2)
                std::cout << i << '\t';
            std::cout << std::endl;
        }
};


int main()
{
    Hashmap hm(7);
    hm.Print();
    std::cout << std::endl;

    hm.Insert(10);
    hm.Insert(20);
    hm.Insert(30);
    std::cout << std::endl;


    hm.Insert(104);
    hm.Insert(2);
    hm.Insert(70);
    hm.Insert(9);
    hm.Insert(90);
    hm.Insert(2);
    hm.Insert(7);
    std::cout << std::endl;

    hm.Print();
    std::cout << std::endl;

    hm.Insert(14);

    return 0;
}