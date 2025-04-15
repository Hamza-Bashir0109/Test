#include <iostream>
#include <string>
#include <limits>
#include <fstream>
#include <sstream>
#include <ctime>
#include <algorithm>
using namespace std;

class Airport {
public:
    int id;
    string name;
    string city;
    string country;
    Airport* next;

    Airport(int i, string n, string c, string cr) {
        id = i;
        name = n;
        city = c;
        country = cr;
        next = nullptr;
    }
};

class Route {
public:
    int sourceID;
    int destinationID;
    double distance;
    Route* next;

    Route(int s, int d, double dis) {
        sourceID = s;
        destinationID = d;
        distance = dis;
        next = nullptr;
    }
};

class FlightGraph {
private:
    struct AdjNode {
        int airportID;
        double distance;
        AdjNode* next;
        AdjNode(int id, double dist) : airportID(id), distance(dist), next(nullptr) {}
    };

    struct AdjList {
        AdjNode* head;
        AdjList() : head(nullptr) {}
    };

    AdjList* adjacencyList;
    int numAirports;
    Airport** airports;

public:
    FlightGraph(int maxAirports) {
        this->numAirports = maxAirports;
        adjacencyList = new AdjList[maxAirports];
        airports = new Airport*[maxAirports];
        for (int i = 0; i < maxAirports; ++i) {
            airports[i] = nullptr;
        }
    }
     void loadAirportsFromCSV(const string& fileName) {
    ifstream file(fileName);
    if (!file.is_open()) {
        cout << "Error: Could not open file " << fileName << endl;
        return;
    }

    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        string idStr, name, city, country;

        getline(ss, idStr, ',');
        getline(ss, name, ',');
        getline(ss, city, ',');
        getline(ss, country, ',');

        if (idStr.empty() || !all_of(idStr.begin(), idStr.end(), ::isdigit)) {
            cout << "Skipping invalid entry: " << line << endl;
            continue;
        }

        int id = stoi(idStr);
        addAirport(id, name, city, country);
    }

    file.close();
    cout << "Airports loaded successfully from " << fileName << endl;
}
void dijkstra(int startID, int destID) {
        const double INF = numeric_limits<double>::infinity();
        double* distances = new double[numAirports];       // Distance array
        int* previous = new int[numAirports];             // Previous node for path reconstruction
        bool* visited = new bool[numAirports];            // Visited array

        // Initialize arrays
        for (int i = 0; i < numAirports; ++i) {
            distances[i] = INF;
            previous[i] = -1;
            visited[i] = false;
        }
        distances[startID] = 0;

        // Priority queue replacement: manually managed array of unvisited nodes
        int* queue = new int[numAirports];
        int queueSize = 0;

        for (int i = 0; i < numAirports; ++i) {
            queue[queueSize++] = i;
        }

        while (queueSize > 0) {
            // Find the unvisited node with the smallest distance
            int current = -1;
            double minDistance = INF;
            for (int i = 0; i < queueSize; ++i) {
                int node = queue[i];
                if (!visited[node] && distances[node] < minDistance) {
                    minDistance = distances[node];
                    current = node;
                }
            }

            if (current == -1) break;  // No reachable node left
            visited[current] = true;

            // Remove the current node from the queue
            for (int i = 0; i < queueSize; ++i) {
                if (queue[i] == current) {
                    queue[i] = queue[--queueSize];
                    break;
                }
            }

            // Update distances for neighbors
            AdjNode* neighbor = adjacencyList[current].head;
            while (neighbor) {
                if (!visited[neighbor->airportID]) {
                    double newDist = distances[current] + neighbor->distance;
                    if (newDist < distances[neighbor->airportID]) {
                        distances[neighbor->airportID] = newDist;
                        previous[neighbor->airportID] = current;
                    }
                }
                neighbor = neighbor->next;
            }
        }

        // Display the shortest path and its distance
        if (distances[destID] == INF) {
            cout << "No path exists from Airport " << startID << " to Airport " << destID << "." << endl;
        } else {
            cout << "Shortest path distance: " << distances[destID] << " km" << endl;
            cout << "Path: ";
            printPath(previous, destID);
            cout << endl;
        }

        // Clean up memory
        delete[] distances;
        delete[] previous;
        delete[] visited;
        delete[] queue;
    }
    void addAirport(int id, string name, string city, string country) {
        if (id >= numAirports || id < 0) {
            cout << "Error: Invalid Airport ID!" << endl;
            return;
        }
        if (airports[id] != nullptr) {
            cout << "Error: Airport ID already exists!" << endl;
            return;
        }
        airports[id] = new Airport(id, name, city, country);
        cout << "Airport added successfully." << endl;
    }

    void addRoute(int sourceID, int destinationID, double distance) {
        if (sourceID >= numAirports || destinationID >= numAirports || sourceID < 0 || destinationID < 0) {
            cout << "Error: Invalid Airport IDs for the route!" << endl;
            return;
        }
        if (airports[sourceID] == nullptr || airports[destinationID] == nullptr) {
            cout << "Error: One or both airports do not exist!" << endl;
            return;
        }
        AdjNode* newNode = new AdjNode(destinationID, distance);
        newNode->next = adjacencyList[sourceID].head;
        adjacencyList[sourceID].head = newNode;
        cout << "Route added successfully." << endl;
    }

    

    void printPath(int* previous, int currentID) {
        if (currentID == -1) return;
        printPath(previous, previous[currentID]);
        if (airports[currentID]) {
            cout << airports[currentID]->name << " ";
        } else {
            cout << currentID << " ";
        }
    }

    ~FlightGraph() {
        for (int i = 0; i < numAirports; ++i) {
            AdjNode* current = adjacencyList[i].head;
            while (current) {
                AdjNode* temp = current;
                current = current->next;
                delete temp;
            }
            if (airports[i]) {
                delete airports[i];
            }
        }
        delete[] adjacencyList;
        delete[] airports;
    }
        void addRandomRoutes(int numRoutes) {
        srand(time(0));
        for (int i = 0; i < numRoutes; ++i) {
            int fromID = rand() % numRoutes;
            int toID = rand() % numRoutes;
            double distance=rand()%numRoutes;
            if (fromID != toID) { // Avoid self-loops
                addRoute(fromID, toID,distance);
                cout << "Added route from " << fromID << " to " << toID << endl;
            }
        }
    }
};

int main() {
    
    int maxAirports=1000;
   
  FlightGraph graph(maxAirports);
  graph.loadAirportsFromCSV("route.csv");
graph.addRandomRoutes(50);
    int choice;
    do {
        cout << "\nMenu:\n";
        cout << "1. Add Airport\n";
        cout << "2. Add Route\n";
        cout << "3. Find Shortest Path\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        if (choice == 1) {
            int id;
            string name, city, country;
            cout << "Enter Airport ID: ";
            cin >> id;
            cout << "Enter Airport Name: ";
            cin >> name;
            cout << "Enter City: ";
            cin >> city;
            cout << "Enter Country: ";
            cin >> country;
            graph.addAirport(id, name, city, country);
        } else if (choice == 2) {
            int source, destination;
            double distance;
            cout << "Enter Source Airport ID: ";
            cin >> source;
            cout << "Enter Destination Airport ID: ";
            cin >> destination;
            cout << "Enter Distance: ";
            cin >> distance;
            graph.addRoute(source, destination, distance);
        } else if (choice == 3) {
            int source, destination;
            cout << "Enter Source Airport ID: ";
            cin >> source;
            cout << "Enter Destination Airport ID: ";
            cin >> destination;
            graph.dijkstra(source, destination);
        }
    } while (choice != 4);

    cout << "Thank you for using the Flight Route Optimization System!" << endl;
    return 0;
}
