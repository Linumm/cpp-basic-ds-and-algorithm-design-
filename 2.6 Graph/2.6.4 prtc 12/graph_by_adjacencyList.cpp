#include <iostream>
#include <vector>
#include <algorithm>

enum class city : int {
    MOSCOW,
    LONDON,
    SEOUL,
    SEATTLE,
    DUBAI,
    SYDNEY
};

std::ostream& operator<<(std::ostream& os, const city c) { //overloading about "city enum"
    switch (c) {
        case city::LONDON:
            os << "LONDON";
            return os;
        case city::MOSCOW:
            os << "MOSCOW";
            return os;
        case city::SEOUL:
            os << "SEOUL";
            return os;
        case city::SEATTLE:
            os << "SEATTLE";
            return os;
        case city::DUBAI:
            os << "DUBAI";
            return os;
        case city::SYDNEY:
            os << "SYDNEY";
            return os;
        default:
            return os;
    }
}

struct graph {
    std::vector<std::vector<std::pair<int, int>>> data;

    graph(int n) {
        data = std::vector<std::vector<std::pair<int, int>>>(n,std::vector<std::pair<int,int>>());
    }

    void addEdge(const city c1, const city c2, int distance) {
        // Display edge info
        std::cout << "ADD EDGE: " << c1 << "-" << c2 << "=" << distance << std::endl;
        
        auto n1 = static_cast<int>(c1);
        auto n2 = static_cast<int>(c2);

        // Edge setting (It does not set entire nodes) 
        data[n1].push_back({n2, distance});
        data[n2].push_back({n1, distance});
    }

    void removeEdge(const city c1, const city c2) {
        std::cout << "REMOVE EDGE: " << c1 << "-" << c2 << std::endl;

        auto n1 = static_cast<int>(c1);
        auto n2 = static_cast<int>(c2);

        std::remove_if(data[n1].begin(), data[n1].end(), [n2](const auto& pair) {return pair.first == n2;});
        std::remove_if(data[n2].begin(), data[n2].end(), [n1](const auto& pair) {return pair.first == n1;});
    }
};

//main func
int main()
{
    graph g(6);
    g.addEdge(city::LONDON, city::MOSCOW, 2500);
    g.addEdge(city::LONDON, city::SEOUL, 9000);
    g.addEdge(city::LONDON, city::DUBAI, 5500);
    g.addEdge(city::SEOUL, city::MOSCOW, 6600);
    g.addEdge(city::SEOUL, city::SEATTLE, 8000);
    g.addEdge(city::SEOUL, city::DUBAI, 7000);
    g.addEdge(city::SEOUL, city::SYDNEY, 8000);
    g.addEdge(city::SEATTLE, city::MOSCOW, 8400);
    g.addEdge(city::SEATTLE, city::SYDNEY, 12000);
    g.addEdge(city::SEATTLE, city::LONDON, 8000);
    g.addEdge(city::DUBAI, city::SYDNEY, 1200);
    
    g.removeEdge(city::LONDON, city::MOSCOW);
    std::cout << "ADJ LIST" << std::endl;
    return 0;
}