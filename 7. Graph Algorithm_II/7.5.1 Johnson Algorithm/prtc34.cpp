#include <iostream>
#include <vector>
#include <climits>

using namespace std;
const int UNKNOWN = INT_MAX; // Infinity expression
struct Edge
{
    int src;
    int dst;
    int weight;
};


vector<int> BellmanFord(vector<Edge> edges, int num_v);
bool HasNegativeCycle(const vector<Edge>& edges, vector<int> distance);
int GetMinDistance(vector<int>& distance, vector<bool>& visited);
vector<int> Dijkstra(vector<Edge> edges, int num_v, int start);
void Johnson(vector<Edge> edges, int num_v);



// Bellman-Ford (difference: No start point input) -> return distance vector
vector<int> BellmanFord(vector<Edge> edges, int num_v)
{
    vector<int> distance(num_v+1, UNKNOWN); // to add 'dummy' -> +1
    int dummy = num_v;

    // Add edges to every vertices from dummy (with dist=0)
    for (int i=0; i<num_v; i++)
        edges.push_back(Edge {dummy,i,0});

    distance[dummy] = 0;

    // Now process Bellman-Ford from dummy
    for (int i=0; i<num_v; i++) {
        for (auto& edge: edges) {
            if (distance[edge.src] == UNKNOWN)
                continue;
            if (distance[edge.dst] > distance[edge.src] + edge.weight)
                distance[edge.dst] = distance[edge.src] + edge.weight;
        }
    }

    if (HasNegativeCycle(edges, distance)) {
        cout << "Negative Cycle is found" << endl;
        return {};
    }

    return distance;
}

// Test if there's any negative weighted cycle
bool HasNegativeCycle(const vector<Edge>& edges, vector<int> distance)
{
    for (auto& edge: edges) {
        if (distance[edge.src] == UNKNOWN)
            continue;
        
        if (distance[edge.src] + edge.weight < distance[edge.dst])
            return true;
    }
    return false;
}


// Dijkstra Algorithm
vector<int> Dijkstra(vector<Edge> edges, int num_v, int start)
{
    vector<int> distance(num_v, UNKNOWN);
    vector<bool> visited(num_v, false);
    
    distance[start] = 0;

    for (int i=0; i<num_v-1; i++) {
        // Find minimum dist vertex among not visited vertices
        int current = GetMinDistance(distance, visited);
        visited[current] = true;

        for (auto& edge: edges) {
            if (edge.src != current)
                continue;
            if (visited[edge.dst])
                continue;
            if (distance[current] != UNKNOWN && distance[edge.dst] > distance[current] + edge.weight)
                distance[edge.dst] = distance[current] + edge.weight;
        }
    }

    return distance;
}


// Minimum distance 'vertex' finder instead of using MinHeap
int GetMinDistance(vector<int>& distance, vector<bool>& visited)
{
    int min_distance = UNKNOWN;
    int target_idx = -1;

    for (int i=0; i<distance.size(); i++) {
        if (!visited[i] && distance[i] <= min_distance) {
            min_distance = distance[i];
            target_idx = i;
        }
    }

    return target_idx;
}


// Johnson's Algorithm
void Johnson(vector<Edge> edges, int num_v)
{
    // d[s,u]
    vector<int> dist_dummy = BellmanFord(edges, num_v);
    
    if (dist_dummy.empty())
        return;
    
    // Reweighting
    for (auto& edge: edges)
        edge.weight += (dist_dummy[edge.src] - dist_dummy[edge.dst]);

    vector<vector<int>> shortest(num_v);

    for (int i=0; i<num_v; i++)
        shortest[i] = Dijkstra(edges, num_v, i);

    // Now weight reversing
    for (int i=0; i<num_v; i++) {
        cout << i << ":\n";

        for (int j=0; j<num_v; j++) {
            if (shortest[i][j] != UNKNOWN) {
                // w(uv) = W(uv) + d(s,v) - d(s,u)
                shortest[i][j] += (dist_dummy[j] - dist_dummy[i]);
                cout << "\t" << j << ": " << shortest[i][j] << endl;
            }
        }
    }
}

int main()
{
    int num_v = 5;
    vector <Edge> edges;

    vector<vector<int>> edge_map {
        // {src, dst, weight}
        {0,1,-7},
        {1,2,-2},
        {2,0,10},
        {0,3,-5},
        {0,4,2},
        {3,4,4}
    };

    for (auto& edge: edge_map)
        edges.emplace_back(Edge {edge[0], edge[1], edge[2]});
    
    Johnson(edges, num_v);
}