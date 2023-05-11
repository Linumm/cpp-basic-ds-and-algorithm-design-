#include <iostream>
#include <vector>
#include <iostream>
#include <set>
#include <map>
#include <queue>

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


//Test-case Graph
template <typename T>
auto createReferenceGraph()
{
    Graph<T> G(9);

    map<unsigned, vector<pair<unsigned, T>>> edge_map;
    // Every weight -> 0 since no need in BFS
	edge_map[1] = { {2, 0}, {5, 0} };
	edge_map[2] = { {1, 0}, {5, 0}, {4, 0} };
	edge_map[3] = { {4, 0}, {7, 0} };
	edge_map[4] = { {2, 0}, {3, 0}, {5, 0}, {6, 0}, {8, 0} };
	edge_map[5] = { {1, 0}, {2, 0}, {4, 0}, {8, 0} };
	edge_map[6] = { {4, 0}, {7, 0}, {8, 0} };
	edge_map[7] = { {3, 0}, {6, 0} };
	edge_map[8] = { {4, 0}, {5, 0}, {6, 0} };

	for (auto& i : edge_map)
		for (auto& j : i.second)
			G.AddEdge(Edge<T>{ i.first, j.first, j.second });

	return G;
}


// BFS
template <typename T>
auto BFS(const Graph<T>& G, unsigned start)
{
    queue<unsigned> q; // Feature: "QUEUE"
    set<unsigned> visited; // Visited vertices
    vector<unsigned> visit_order; // Output : order of visiting from "start"
    q.push(start);

    while (!q.empty()) {
        auto current_vertex = q.front();
        q.pop();

        if (visited.find(current_vertex) == visited.end()) { // If not visited before [to prevent duplicate visit]
            visited.insert(current_vertex); // Mark "visited"
            visit_order.push_back(current_vertex);

            for (auto& edge: G.Edges(current_vertex)) {
                // If there's none visited vertex in neighbor, enqueue
                if (visited.find(edge.dst) == visited.end())
                    q.push(edge.dst);
            }
        }
    }

    return visit_order;
}


int main()
{
	using T = unsigned;

	auto G = createReferenceGraph<T>();
	cout << "[Initialized Graph]" << endl;
	cout << G << endl;

	// BFS, start point: 1
	cout << "[BFS visit order]" << endl;
	auto bfs_visit_order = BFS(G, 1);
	for (auto v : bfs_visit_order)
		cout << v << " ";
    cout << endl;
}