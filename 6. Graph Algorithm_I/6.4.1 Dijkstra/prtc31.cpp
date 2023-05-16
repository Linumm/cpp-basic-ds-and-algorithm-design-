#include <string>
#include <vector>
#include <iostream>
#include <set>
#include <map>
#include <limits>
#include <queue>
#include <algorithm>

using namespace std;

// Copied from prtc28
template<typename T>
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

//Test-case graph
template <typename T>
auto createRefGraph()
{
    Graph<T> G(9);

    map<unsigned, vector<pair<unsigned, T>>> edge_map;

    edge_map[1] = { {2, 2}, {5, 3} };
	edge_map[2] = { {1, 2}, {5, 5}, {4, 2} };
	edge_map[3] = { {4, 2}, {7, 3} };
	edge_map[4] = { {2, 1}, {3, 2}, {5, 2}, {6, 4}, {8, 5} };
	edge_map[5] = { {1, 3}, {2, 5}, {4, 2}, {8, 3} };
	edge_map[6] = { {4, 4}, {7, 4}, {8, 1} };
	edge_map[7] = { {3, 3}, {6, 4} };
	edge_map[8] = { {4, 5}, {5, 3}, {6, 1} };

	for (auto& i : edge_map)
		for (auto& j : i.second)
			G.AddEdge(Edge<T>{ i.first, j.first, j.second });

	return G;
}

template <typename T>
struct Label // Tag of vertex with ID and distance value
{
    unsigned ID;
    T distance; // Difference with PRIM : this is the distance from "Start" vertex

    inline bool operator> (const Label<T>& _label) const
    {
        return this->distance > _label.distance;
    }
};

// Dijkstra Algorithm
template <typename T>
auto dijkstraShortPath(const Graph<T>& G, unsigned src, unsigned dst)
{
    priority_queue<Label<T>, vector<Label<T>>, greater<Label<T>>> heap;

    vector<T> distance(G.Vertices(), numeric_limits<T>::max());

    set<unsigned> visited; // visited vertices
    vector<unsigned> parent(G.Vertices()); // To remember path

    heap.emplace(Label<T>{src, 0}); // Enqueue start point (with distance 0)
    parent[src] = src;

    while (!heap.empty()) {
        auto current = heap.top();
        heap.pop();

        if (current.ID == dst) {
            cout << "Arrived at " << current.ID << endl;
            break;
        }

        // If never visited current vertex before 
        if (visited.find(current.ID) == visited.end()) {
            cout << "now in " << current.ID << endl;

            // About every edge from current vertex
            for (auto& edge: G.Edges(current.ID)) {
                auto neighbor = edge.dst;
                auto new_distance = current.distance + edge.weight; // This is the "main difference" with PRIM [+current.distance]

                if (new_distance < distance[neighbor]) {
                    heap.emplace(Label<T>{neighbor, new_distance});

                    parent[neighbor] = current.ID; // to backtrack later
                    distance[neighbor] = new_distance; // reset distance value of the vertex
                }
            }

            visited.insert(current.ID);
        }
    }

    // Make shortest_path by "Backtracking"
    vector<unsigned> shortest_path;
    auto current = dst;
    
    while (current != src) {
        shortest_path.push_back(current);
        current = parent[current];
    }

    shortest_path.push_back(src);
    reverse(shortest_path.begin(), shortest_path.end());

    return shortest_path;
}


int main()
{
    using T = unsigned;

    auto G = createRefGraph<T>();
    cout << "[First Graph]" << endl;
    cout << G << endl;

    auto shortest_path = dijkstraShortPath<T>(G, 1, 6);
    cout << endl << "[Shortest path from 1 to 6]" << endl;
    for (auto vertex: shortest_path)
        cout << vertex << " ";
    cout << endl;

    return 0;
}