#include <iostream>
#include <vector>

class BloomFilter
{
    std::vector<bool> data;
    int n_bits;

    int Hash(int num, int key)
    {
        switch (num) { // 'num' determines which hash function to use. this structure provides easy extension of hash func.
            case 0: return key % n_bits;
            case 1: return (key / 7) % n_bits;
            case 2: return (key / 11) % n_bits;
        }

        return 0;
    }

    public:
        BloomFilter(int n) : n_bits(n)
        {
            data = std::vector<bool>(n_bits, false); //initialize with "false"
        }

        void Lookup(int key) // Check whether every bit is 1
        {
            bool result = data[Hash(0, key)] & data[Hash(1, key)] & data[Hash(2, key)];

            if (result)
                std::cout << key << ": can exist (or not..?)" << std::endl;
            else
                std::cout << key << ": definitely does not exist" << std::endl;
        }

        void Insert(int key)
        {
            data[Hash(0, key)] = true;
            data[Hash(1, key)] = true;
            data[Hash(2, key)] = true;
            std::cout << key << ": inserted ->";

            for (auto a: data)
                std::cout << a << " ";
            std::cout << std::endl;
        }

};


int main()
{
    BloomFilter bloom_filter(7);
    bloom_filter.Insert(100);
    bloom_filter.Insert(54);
    bloom_filter.Insert(82);

    bloom_filter.Lookup(5);
    bloom_filter.Lookup(50);
    bloom_filter.Lookup(20);
    bloom_filter.Lookup(54);

    return 0;
}