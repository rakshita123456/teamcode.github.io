#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <climits>
#include <algorithm>
#include <ctime>
using namespace std;

// Graph Representation using Adjacency List
class Graph {
    unordered_map<string, vector<pair<string, int>>> adj;

public:
    void addEdge(string src, string dest, int weight) {
        adj[src].push_back({dest, weight});
        adj[dest].push_back({src, weight}); // Assuming undirected graph
    }

    void dijkstra(string start, string end) {
        unordered_map<string, int> dist;
        unordered_map<string, string> parent;
        priority_queue<pair<int, string>, vector<pair<int, string>>, greater<>> pq;

        for (auto &node : adj)
            dist[node.first] = INT_MAX;

        dist[start] = 0;
        pq.push({0, start});

        while (!pq.empty()) {
            string node = pq.top().second;
            int nodeDist = pq.top().first;
            pq.pop();

            for (auto &neighbor : adj[node]) {
                string nextNode = neighbor.first;
                int edgeWeight = neighbor.second;

                if (nodeDist + edgeWeight < dist[nextNode]) {
                    dist[nextNode] = nodeDist + edgeWeight;
                    pq.push({dist[nextNode], nextNode});
                    parent[nextNode] = node;
                }
            }
        }

        // Output Shortest Path
        string current = end;
        vector<string> path;
        while (current != start) {
            path.push_back(current);
            current = parent[current];
        }
        path.push_back(start);
        reverse(path.begin(), path.end());

        cout << "Shortest Path: ";
        for (const auto &p : path) cout << p << " -> ";
        cout << "END\nTotal Cost: " << dist[end] << endl;
    }

    void dfs(string start, unordered_map<string, bool> &visited) {
        cout << "Visited: " << start << endl;
        visited[start] = true;

        for (auto &neighbor : adj[start]) {
            if (!visited[neighbor.first])
                dfs(neighbor.first, visited);
        }
    }

    void startDFS(string start) {
        unordered_map<string, bool> visited;
        for (auto &node : adj)
            visited[node.first] = false;

        dfs(start, visited);
    }
};

// Linked List for Dynamic Stages
struct Stage {
    string location;
    string timestamp;
    string condition;
    Stage *next;

    Stage(string loc, string time, string cond) : location(loc), timestamp(time), condition(cond), next(nullptr) {}
};

class LinkedList {
    Stage *head;

public:
    LinkedList() : head(nullptr) {}

    void addStage(string location, string timestamp, string condition) {
        Stage *newStage = new Stage(location, timestamp, condition);
        if (!head) {
            head = newStage;
        } else {
            Stage *temp = head;
            while (temp->next)
                temp = temp->next;
            temp->next = newStage;
        }
    }

    void displayStages() {
        Stage *temp = head;
        while (temp) {
            cout << "Location: " << temp->location
                 << ", Time: " << temp->timestamp
                 << ", Condition: " << temp->condition << endl;
            temp = temp->next;
        }
    }

    void bubbleSort() {
        if (!head) return;
        bool swapped;
        Stage *ptr1;
        Stage *lptr = nullptr;

        do {
            swapped = false;
            ptr1 = head;

            while (ptr1->next != lptr) {
                if (ptr1->timestamp > ptr1->next->timestamp) {
                    swap(*ptr1, *ptr1->next);
                    swapped = true;
                }
                ptr1 = ptr1->next;
            }
            lptr = ptr1;
        } while (swapped);
    }
};

// Queue for Crop Management
struct Crop {
    string cropName;
    int quantity;
    string farmLocation;
    string destination;

    Crop(string name, int qty, string farm, string dest)
        : cropName(name), quantity(qty), farmLocation(farm), destination(dest) {}
};

class CropQueue {
    queue<Crop> cropQueue;

public:
    void addCrop(string name, int qty, string farm, string dest) {
        cropQueue.push(Crop(name, qty, farm, dest));
        cout << "Crops Added{" << name << ", " << qty
             << ", " << farm << ", " << dest << "}\n";
    }

    void processCrop() {
        if (!cropQueue.empty()) {
            Crop processed = cropQueue.front();
            cropQueue.pop();
            cout << "Processed crop: {" << processed.cropName << ", "
                 << processed.quantity << ", " << processed.farmLocation
                 << ", " << processed.destination << "}\n";
        }
    }

    void displayQueue() {
    if (cropQueue.empty()) {
        cout << "Queue is empty.\n";
        return;
    }

    cout << "Current queue:\n";
    queue<Crop> tempQueue = cropQueue;

    while (!tempQueue.empty()) {
        Crop c = tempQueue.front();
        tempQueue.pop();
        cout << "{" << c.cropName << ", " << c.quantity << ", "
             << c.farmLocation << ", " << c.destination << "}\n";
    }
}

    };


int main() {
    Graph g;
    LinkedList ll;
    CropQueue cq;

    int graphEdges;
    cout << "Enter the number of locations ";
    cin >> graphEdges;

    cout << "Enter locations in this format (source destination weight):\n";
    for (int i = 0; i < graphEdges; ++i) {
        string src, dest;
        int weight;
        cin >> src >> dest >> weight;
        g.addEdge(src, dest, weight);
    }

    string start, end;
    cout << "Enter source and destination for finding route ";
    cin >> start >> end;
    g.dijkstra(start, end);

    cout << "\nDFS Traversal:\n";
    g.startDFS(start);

    int stages;
    cout << "\nEnter the number of stages  ";
    cin >> stages;

    cout << "Enter stages in this format (location timestamp condition):\n";
    for (int i = 0; i < stages; ++i) {
        string loc, time, cond;
        cin >> loc >> time >> cond;
        ll.addStage(loc, time, cond);
    }

    cout << "\nStages:\n";
    ll.displayStages();

    cout << "\nSorted by Timestamp:\n";
    ll.bubbleSort();
    ll.displayStages();

    int crops;
    cout << "\nEnter the number of crops ";
    cin >> crops;

    cout << "Enter crops in this format (name quantity farm destination):\n";
    for (int i = 0; i < crops; ++i) {
        string name, farm, dest;
        int qty;
        cin >> name >> qty >> farm >> dest;
        cq.addCrop(name, qty, farm, dest);
    }

    cout << "\nCrops\n";
    cq.displayQueue();

    cout << "\nProcessing crops:\n";
    for (int i = 0; i < crops; ++i) {
        cq.processCrop();
    }

    return 0;
}

