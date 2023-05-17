#include <vector>
#include <iostream>
#include <climits>

using namespace std;

struct Edge
{
    int src;
    int dst;
    int weight;
};

// Graph will be expressed by Vector<Edge>

const int UNKNOWN = INT_MAX; // infinity

vector<int> BellmanFord(vector<Edge> edges, int V, int start)
{
    vector<int> distance(V, UNKNOWN); // Distance vector for minimum distance from start -> this is the output  
    distance[start] = 0;

    // Repeat for entire edge
    for (int i=0; i<V-1; i++) {
        for (auto& edge: edges) {
            if (distance[edge.src] == UNKNOWN) // If current vertex's distance : infinity
                continue;
            
            if (distance[edge.dst] > distance[edge.src] + edge.weight) // If new distance is smaller 
                distance[edge.dst] = distance[edge.src] + edge.weight;
        }
    }

    return distance;
}

int main()
{
    int V = 5;
    vector<Edge> edges; // Edge-pointer's vector
    vector<vector<int>> edge_map = { // {src, dst, weight}
        {0,1,3},
        {1,2,5},
        {1,3,10},
        {3,2,-7},
        {2,4,2}
    };

    for (auto& edge : edge_map) 
        edges.emplace_back(Edge {edge[0], edge[1], edge[2]});
    
    int start = 0;
    vector<int> distance = BellmanFord(edges, V, start);

    cout << "[Minimum distance from " << start << "]" << endl;

    for (int i=0; i<distance.size(); i++) {
        if (distance[i] == UNKNOWN)
            cout << "Node " << i << " : not visited" << endl;
        else
            cout << "Node " << i << " :" << distance[i] << endl;
    }

    return 0;
}