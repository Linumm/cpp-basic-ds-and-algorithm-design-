#include <iostream>
#include <vector>

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
    std::vector<std::vector<int>> data;  // 2d array. The element of data[m][n] indicates the weight of edge between m-n

    graph(int n) { //No edge right now.
        data.reserve(n);
        std::vector<int> row(n);
        std::fill(row.begin(), row.end(), -1); // Use entire space of N*N array. [Because of incorrect access error?]

        for (int i=0; i<n; i++)
            data.push_back(row);
    }

    void addEdge(const city c1, const city c2, int distance) { // Distance: weight of edge in here
        // Display edge info
        std::cout << "ADD EDGE: " << c1 << "-" << c2 << "=" << distance << std::endl;
        
        auto n1 = static_cast<int>(c1);
        auto n2 = static_cast<int>(c2);
        data[n1][n2] = distance;
        data[n2][n1] = distance;
    }

    void removeEdge(const city c1, const city c2) {
        std::cout << "REMOVE EDGE: " << c1 << "-" << c2 << std::endl;

        auto n1 = static_cast<int>(c1);
        auto n2 = static_cast<int>(c2);
        data[n1][n2] = -1;
        data[n2][n1] = -1;
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
    return 0;
}