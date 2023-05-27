#include <vector>
#include <stack>
#include <iostream>

using namespace std;

// DFS
void FillStack(int node, vector<bool>& visited, vector<vector<int>>& adj, stack<int>& stack)
{
    visited[node] = true;
    for (auto next: adj[node]) {
        if (!visited[next]) {
            FillStack(next, visited, adj, stack);
        }
    }
    stack.push(node);
}

// Return adj of transposed graph
vector<vector<int>> Transpose(int num_v, vector<vector<int>> adj)
{
    vector<vector<int>> transpose(num_v);

    for (int i=0; i<num_v; i++) {
        for (auto next: adj[i])
            transpose[next].push_back(i);
    }

    return transpose;
}

// Second DFS, 
void CollectConnectedComponents(int node, vector<bool>& visited, vector<vector<int>>& adj, vector<int>& component)
{
    visited[node] = true;
    component.push_back(node);

    for (auto next: adj[node]) {
        if (!visited[next])
            CollectConnectedComponents(next, visited, adj, component);
    }
}

vector<vector<int>> Kosaraju(int num_v, vector<vector<int>> adj)
{
    vector<bool> visited(num_v, false);
    stack<int> stack;

    // First DFS procedure
    for (int i=0; i<num_v; i++) {
        if (!visited[i])
            FillStack(i, visited, adj, stack);
    }

    vector<vector<int>> transpose = Transpose(num_v, adj);
    // Reset visited (false)
    fill(visited.begin(), visited.end(), false); 

    vector<vector<int>> connected_components;

    while (!stack.empty()) {
        int node = stack.top();
        stack.pop();

        if (!visited[node]) {
            vector<int> component;
            
            CollectConnectedComponents(node, visited, transpose, component);
            connected_components.push_back(component);
        }
    }
    /*
    <personal opinion>
    -The core part of Kosaraju is that there's no cycle between each SCCs (by its definition)
     : so when it comes to start 'second DFS procedure' from stack popping, only the vertices in one cycle is collected. -> This is SCC
    
    -Second point
     : Transposed graph -> This exchange in-edge, out-edge, so separate each SCCs, but remain the existing cycle.
    */

    return connected_components;
}

int main()
{
	int num_v = 9;

	vector<vector<int>> adj =
	{
		{ 1, 3 },
		{ 2, 4 },
		{ 3, 5 },
		{ 7 },
		{ 2 },
		{ 4, 6 },
		{ 7, 2 },
		{ 8 },
		{ 3 }
	};

	vector<vector<int>> connectedComponents = Kosaraju(num_v, adj);

	cout << "The num of SCCs: " << connectedComponents.size() << endl;

	for (int i = 0; i < connectedComponents.size(); i++)
	{
		cout << "[" << i + 1 << "] ";

		for (auto node : connectedComponents[i])
			cout << node << " ";

		cout << endl;
	}
}