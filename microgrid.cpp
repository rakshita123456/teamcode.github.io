#include <iostream>
#include <queue>
using namespace std;

#define MAX 100

// Global variables
int graph[MAX][MAX];
bool visited[MAX];
int vertices;

// Depth First Search (DFS)
void dfs(int node) {
    cout << node << " ";
    visited[node] = true;
    for (int i = 0; i < vertices; i++) {
        if (graph[node][i] == 1 && !visited[i]) {
            dfs(i);
        }
    }
}

// Breadth First Search (BFS)
void bfs(int start) {
    queue<int> q;
    bool visited[MAX] = {false};

    q.push(start);
    visited[start] = true;

    while (!q.empty()) {
        int node = q.front();
        q.pop();
        cout << node << " ";

        for (int i = 0; i < vertices; i++) {
            if (graph[node][i] == 1 && !visited[i]) {
                visited[i] = true;
                q.push(i);
            }
        }
    }
}

// Main Function
int main() {
    int edges, choice;

    cout << "Enter the number of farms and energy sources: ";
    cin >> vertices;

    cout << "Enter the number of connections/paths between them: ";
    cin >> edges;

    // Initialize adjacency matrix
    for (int i = 0; i < vertices; i++) {
        for (int j = 0; j < vertices; j++) {
            graph[i][j] = 0;
        }
    }

    cout << "Enter the connections/paths (u v):" << endl;
    for (int i = 0; i < edges; i++) {
        int u, v;
        cin >> u >> v;
        graph[u][v] = 1;
        graph[v][u] = 1; // For undirected graph
    }

    do {
        // Reset visited array for each new traversal
        for (int i = 0; i < vertices; i++) {
            visited[i] = false;
        }

        cout << "\nMENU:\n";
        cout << "1. Identifying isolated farms or substations (Perform DFS)\n";
        cout << "2. Identifying the shortest path (Perform BFS)\n";
        cout << "3. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                int startNode;
                cout << "Enter the point where you are standing: ";
                cin >> startNode;
                cout << "Your route: ";
                dfs(startNode);
                cout << endl;
                break;
            }
            case 2: {
                int startNode;
                cout << "Enter the point where you are standing: ";
                cin >> startNode;
                cout << "Your route: ";
                bfs(startNode);
                cout << endl;
                break;
            }
            case 3:
                cout << "Exiting program. Goodbye!" << endl;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice != 3);

    return 0;
}

