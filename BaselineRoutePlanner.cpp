
#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>

using namespace std;

struct Edge {
    string to;
    int time;
    string line;
};

unordered_map<string, vector<Edge>> graph;

// Add routes
void addEdge(const string& from, const string& to, int time, const string& line) {
    graph[from].push_back({ to, time, line });
    graph[to].push_back({ from, time, line });
}

// List all stations
void listStations() {
    cout << "\nAvailable stations in the system:\n";
    for (const auto& pair : graph) {
        cout << "- " << pair.first << endl;
    }
    cout << endl;
}

// Check if station exists
bool stationExists(const string& station) {
    return graph.count(station) > 0;
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
        cout << "\n===== SMART KTMB ROUTE PLANNER (BASELINE) =====\n";
        listStations();

        string origin, destination;

        // Get origin
        cout << "Enter origin station: ";
        cin >> origin;
        if (!stationExists(origin)) {
            cout << "No such station exists in the system!\n";
            continue;
        }

        // Get destination
        cout << "Enter destination station: ";
        cin >> destination;
        if (!stationExists(destination)) {
            cout << "No such station exists in the system!\n";
            continue;
        }

        bool found = false;

        // Baseline: direct routes only
        for (const auto& e : graph[origin]) {
            if (e.to == destination) {
                cout << "\nDirect route found\n";
                found = true;
                break;
            }
        }

        if (!found) {
            cout << "\nRoute not Found\n";
        }

        // Ask user whether to continue
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
                // continue the loop
                break;
            }
            else {
                cout << "Invalid choice. Please enter 'c' or 'q'.\n";
            }
        }
    }

    return 0;
}
