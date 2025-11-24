#include <iostream>
#include <list>
#include <string>
#include <unordered_map>
#include <queue>
#include <stack>
using namespace std;

// Edge
struct Edge {
    string to;
    int time;
    string line;
};

// Graph using linked list for adjacency
unordered_map<string, list<Edge>> graph;

// Undirected route
void addEdge(string from, string to, int time, string line) {
    graph[from].push_back({ to, time, line });
    graph[to].push_back({ from, time, line });
}

// List stations
void listStations() {
    cout << "\nAvailable stations in the system:\n";
    for (auto& pair : graph) {
        cout << "- " << pair.first << endl;
    }
    cout << endl;
}

// Station exists or not
bool stationExists(const string& station) {
    return graph.count(station) > 0;
}

// BFS
void findOptimizedRoute(string origin, string destination) {
    if (origin == destination) {
        cout << "\nOrigin and destination are the same.\n";
        return;
    }

    queue<string> q;
    unordered_map<string, string> parent; 
    unordered_map<string, bool> visited;

    q.push(origin);
    visited[origin] = true;

    bool found = false;

    while (!q.empty()) {
        string current = q.front();
        q.pop();

        if (current == destination) {
            found = true;
            break;
        }

        for (auto& edge : graph[current]) {
            if (!visited[edge.to]) {
                visited[edge.to] = true;
                parent[edge.to] = current;
                q.push(edge.to);
            }
        }
    }

    if (!found) {
        cout << "\nRoute not Found\n";
        return;
    }

    stack<string> path;
    string temp = destination;
    while (temp != origin) {
        path.push(temp);
        temp = parent[temp];
    }
    path.push(origin);

    cout << "\nRoute found: ";
    while (!path.empty()) {
        cout << path.top();
        path.pop();
        if (!path.empty()) cout << " -> ";
    }
    cout << endl;
}

int main() {
    addEdge("Perlis", "Kedah", 60, "ETS");
    addEdge("Kedah", "Penang", 40, "Intercity");
    addEdge("Penang", "Perak", 90, "ETS");
    addEdge("Perak", "Selangor", 120, "Intercity");
    addEdge("Selangor", "Kuala Lumpur", 30, "ETS");
    addEdge("Kuala Lumpur", "Negeri Sembilan", 60, "Intercity");
    addEdge("Negeri Sembilan", "Malacca", 90, "ETS");
    addEdge("Malacca", "Johor", 120, "Intercity");
    addEdge("Pahang", "Terengganu", 90, "Intercity");
    addEdge("Terengganu", "Kelantan", 80, "ETS");
    addEdge("Johor", "Pahang", 150, "Intercity");
    addEdge("Kelantan", "Perlis", 200, "ETS");
    addEdge("Sabah", "Sarawak", 300, "Intercity");

    bool continueProgram = true;

    while (continueProgram) {
        cout << "\n===== SMART KTMB ROUTE PLANNER (OPTIMIZED) =====\n";
        listStations();

        string origin, destination;

        cout << "Enter origin station: ";
        cin >> origin;
        if (!stationExists(origin)) {
            cout << "No such station exists in the system!\n";
            continue;
        }

        cout << "Enter destination station: ";
        cin >> destination;
        if (!stationExists(destination)) {
            cout << "No such station exists in the system!\n";
            continue;
        }

        findOptimizedRoute(origin, destination);

        // Ask user to continue or quit
        string choice;
        while (true) {
            cout << "\nDo you want to continue? (c = continue, q = quit): ";
            cin >> choice;
            if (choice == "q" || choice == "Q") {
                continueProgram = false;
                cout << "Exiting program...\n";
                break;
            }
            else if (choice == "c" || choice == "C") {
                break;
            }
            else {
                cout << "Invalid choice. Please enter 'c' or 'q'.\n";
            }
        }
    }

    return 0;
}
