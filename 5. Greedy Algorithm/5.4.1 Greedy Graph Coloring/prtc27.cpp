#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <map>
#include <unordered_map>

using namespace std;

// Edge for Graph
template <typename T>
struct Edge
{
    unsigned src; // from src vertex
    unsigned dst; // to dst vertex
    T weight; 

    // In comparing, use "weight of edge"
    inline bool operator< (const Edge<T>& e) const
    {
        return this->weight < e.weight;
    }

    inline bool operator> (const Edge<T>& e) const
    {
        return this->weight > e.weight;
    }
};

// Graph
template <typename T>
class Graph
{
    public:
        Graph(unsigned N) : V(N) {}

        // Return the number of Vertex
        auto Vertices() const { return V; }

        // Return entire edge
        auto& Edges() const { return edge_list; }

        // Return every edge from 'v'
        auto Edges(unsigned v) const
        {
            vector<Edge<T>> edges_from_v;
            for (auto& e: edge_list) {
                if (e.src == v)
                    edges_from_v.emplace_back(e);
            }

            return edges_from_v;
        }

        void AddEdge(Edge<T>&& e)
        {
            // Check the validity of side vertext ID
            if (e.src >= 1 && e.src <= V && e.dst >= 1 && e.dst <= V)
                edge_list.emplace_back(e);
            else
                cerr << "Error: Vertex out of valid range" << endl;
        }

        template <typename U>
        friend ostream& operator<< (ostream& os, const Graph<U>& G);
    private:
        unsigned V; // the number of vertex
        vector<Edge<T>> edge_list;
};

template <typename U>
ostream& operator<< (ostream& os, const Graph<U>& G)
{
    for (unsigned i=1; i<G.Vertices(); i++) {
        os << i << ":\t";
        auto edges = G.Edges(i);
        for (auto& e: edges)
            os << "{" << e.dst << ": " << e.weight << "}, ";
        
        os << endl;
    }
    
    return os;
}


unordered_map<unsigned, string> color_map = {
    {1, "Red"},
    {2, "Blue"},
    {3, "Green"},
    {4, "Yellow"},
    {5, "Black"},
    {6, "White"}
};


template<typename T>
auto greedyColoring(const Graph<T>& G)
{
    auto size = G.Vertices(); // Get the num of vertex
    vector<unsigned> assigned_colors(size);

    for (unsigned i=1; i<size; i++) {
        auto outgoing_edges = G.Edges(i);

        // Current color of neighbour vertexes with i vertex
        set<unsigned> neighbours; 

        for (auto& e: outgoing_edges)
            neighbours.insert(assigned_colors[e.dst]); // put neighbour vertex into set
        
        // Choose the smallest color among unused colors of neighbour vertex
        auto smallest = 1;
        for (; smallest<=color_map.size(); smallest++) {
            // Find the smallest color that is not used in neighbour
            if (neighbours.find(smallest) == neighbours.end())
                break;
        }

        assigned_colors[i] = smallest;
    }

    return assigned_colors;

    /*
    1. Edge idx 따라 1번부터 오름차순으로, 가장 작은 value의 color 칠하기
    2. 색칠에서, 인접 vertex에 이미 color가 있으면 그건 제외 ->이걸 color 1번부터 쭉 조회 (for loop)
    3. 그렇게 해서 나온 minimum value coloring
    */
}


template <typename T>
void printColors(vector<T>& colors)
{
    for (auto i=1; i<colors.size(); i++)
        cout << i << ": " << color_map[colors[i]] << endl;
}


int main()
{
    using T = unsigned;
    Graph<T> G(9);

    map<unsigned, vector<pair<unsigned, T>>> edge_map;
    edge_map[1] = {{2, 0}, {5, 0}};
	edge_map[2] = {{1, 0}, {5, 0}, {4, 0}};
	edge_map[3] = {{4, 0}, {7, 0}};
	edge_map[4] = {{2, 0}, {3, 0}, {5, 0}, {6, 0}, {8, 0}};
	edge_map[5] = {{1, 0}, {2, 0}, {4, 0}, {8, 0}};
	edge_map[6] = {{4, 0}, {7, 0}, {8, 0}};
	edge_map[7] = {{3, 0}, {6, 0}};
	edge_map[8] = {{4, 0}, {5, 0}, {6, 0}};

    for (auto& i: edge_map)
        for (auto& j: i.second)
            G.AddEdge(Edge<T>{i.first, j.first, j.second});
    
    cout << "[Input Graph]" << endl;
    cout << G << endl;

    auto colors = greedyColoring<T>(G);
    cout << "[Graph Coloring]" << endl;
    printColors(colors);
}