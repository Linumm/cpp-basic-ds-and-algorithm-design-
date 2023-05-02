#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <map>

using namespace std;

// Implement Disjoint-set structure
class SimpleDisjointSet
{
    private:
        struct Node
        {
            unsigned id;
            unsigned rank;
            unsigned parent;

            Node(unsigned _id) : id(_id), rank(0), parent(_id) {}

            bool operator != (const Node& n) const { return this->id != n.id;}
        };

        vector<Node> nodes;

    public:
        SimpleDisjointSet(unsigned N) { nodes.reserve(N); }
        
        void MakeSet(const unsigned& x) { nodes.emplace_back(x); }

        unsigned Find(unsigned x)
        {
            auto node_it = find_if(nodes.begin(), nodes.end(), [x](auto n) { return n.id == x; });
            unsigned node_id = (*node_it).id;

            // Move to root
            while (node_id != nodes[node_id].parent)
                node_id = nodes[node_id]. parent;
            
            return node_id;
        }

        void UnionSets(unsigned x, unsigned y)
        {
            // First, compare root of x and y
            auto root_x = Find(x);
            auto root_y = Find(y);

            if (root_x == root_y)
                return;
            
            // If two are different, link lower rank one to higher rank one.
            if (nodes[root_x].rank > nodes[root_y].rank)
                swap(root_x, root_y);
            
            nodes[root_x].parent = nodes[root_y].parent;
            nodes[root_y].rank++;
        }
};

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



// Kruskal MST Algorithm
template<typename T>
Graph<T> MSTAlgorithm(const Graph<T>& G)
{
    // Make a min heap with edge weight
    priority_queue<Edge<T>, vector<Edge<T>>, greater<Edge<T>>> edge_min_heap;

    for (auto& e: G.Edges())
        edge_min_heap.push(e);
    
    // Initialize Disjoint-set with the num of Vertex
    auto n = G.Vertices();
    SimpleDisjointSet dset(n);
    for (unsigned i=0; i<n; i++)
        dset.MakeSet(i);
    

    // Procedure
    Graph<T> mst(n);
    while (!edge_min_heap.empty()) {
        // Get minimum weighted edge from min heap
        auto e = edge_min_heap.top();
        edge_min_heap.pop();

        // If the edge from heap does not make "cycle", add it to mst
        if (dset.Find(e.src) != dset.Find(e.dst)) {
            mst.AddEdge(Edge<T> {e.src, e.dst, e.weight});
            dset.UnionSets(e.src, e.dst);
        }
    }

    return mst;
}


// test in main
int main()
{
    using T = unsigned;

    Graph<T> G(9);

    map<unsigned, vector<pair<unsigned, T>>> edge_map;
    edge_map[1] = {{2, 2}, {5, 3}};
    edge_map[2] = {{1, 2}, {5, 5}, {4, 1}};
	edge_map[3] = {{4, 2}, {7, 3}};
	edge_map[4] = {{2, 1}, {3, 2}, {5, 2}, {6, 4}, {8, 5}};
	edge_map[5] = {{1, 3}, {2, 5}, {4, 2}, {8, 3}};
	edge_map[6] = {{4, 4}, {7, 4}, {8, 1}};
	edge_map[7] = {{3, 3}, {6, 4}};
	edge_map[8] = {{4, 5}, {5, 3}, {6, 1}};

    for (auto& i: edge_map)
        for (auto& j: i.second)
            G.AddEdge(Edge<T> { i.first, j.first, j.second });
    
    cout << "[Input Graph]" << endl;
    cout << "[Start Point: {Destination: Weight}]" << endl;
    cout << G << endl;

    Graph<T> mst = MSTAlgorithm(G);
    cout << "[MST]" << endl;
    cout << mst;
}