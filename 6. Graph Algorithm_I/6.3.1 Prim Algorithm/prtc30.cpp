#include <string>
#include <vector>
#include <iostream>
#include <set>
#include <map>
#include <queue>
#include <limits>

using namespace std;

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

//------------------------------
// Sample graph for test
template <typename T>
auto createRefGraph()
{
    Graph<T> G(9);

    map<unsigned, vector<pair<unsigned, T>>> edge_map;

    edge_map[1] = { {2, 2}, {5, 3} };
	edge_map[2] = { {1, 2}, {5, 5}, {4, 1} };
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

// Distance between two vertices info label
template <typename T>
struct Label
{
    unsigned ID;
    T distance;

    inline bool operator> (const Label<T>& _label) const
    {
        return this->distance > _label.distance;
    }
};


//Prim Algorithm for MST
/*
1. Create a new min heap (and push start node)
2. Initially, every vertex's 'distance' is infinite 
3. Dequeue and push to MST for that vertex, rewrite all neighbor vertices' 'distance' with edge weight,
   but only if current edge weight <= neighbor vertex's 'distance' value
4. repeat (3) until heap is empty
*/
template <typename T>
auto primMST(const Graph<T>& G, unsigned src)
{
    // Min heap with label(distance) value
    priority_queue<Label<T>, vector<Label<T>>, greater<Label<T>>> heap;

    // Make every vertices' distance as infiity
    vector<T> distance(G.Vertices(), numeric_limits<T>::max());

    set<unsigned> visited;
    vector<unsigned> MST;

    heap.emplace(Label<T>{src, 0});

    while (!heap.empty()) {
        auto current = heap.top();
        heap.pop();

        if (visited.find(current.ID) == visited.end()) {
            MST.push_back(current.ID);

            for (auto& edge: G.Edges(current.ID)) {
                auto neighbor = edge.dst;
                auto new_distance = edge.weight;

                if (distance[neighbor] > new_distance) { // If new_distance is smaller, then enqueue with new_distance and rewrite
                    heap.emplace(Label<T>{neighbor, new_distance});
                    distance[neighbor] = new_distance;
                }
            }

            visited.insert(current.ID);
        }
    }

    return MST;
}

int main()
{
    using T = unsigned;

    auto G = createRefGraph<T>();
    cout << "[Initial Graph]" << endl;
    cout << G << endl;

    auto MST = primMST<T>(G, 1);

    cout << "[MST]" << endl;
    for (auto vertex: MST)
        cout << vertex << endl;
    cout << endl;
    
    return 0;
}