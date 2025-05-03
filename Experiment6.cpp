#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>
#include <limits>

using namespace std;

struct Edge {
    string destination;
    double cost;
    Edge(const string& dest, double c) : destination(dest), cost(c) {}
};

class GraphAdjList {
private:
    unordered_map<string, vector<Edge>> adjList;

public:
    void addCity(const string& city) {
        if (adjList.find(city) == adjList.end()) {
            adjList[city] = vector<Edge>();
        }
    }

    void addFlight(const string& cityA, const string& cityB, double cost) {
        addCity(cityA);
        addCity(cityB);
        adjList[cityA].push_back(Edge(cityB, cost));
    }

    void printGraph() const {
        cout << "Graph (Adjacency List Representation):" << endl;
        for (const auto& pair : adjList) {
            cout << pair.first << " -> ";
            for (const auto& edge : pair.second) {
                cout << "(" << edge.destination << ", cost: " << edge.cost << ") ";
            }
            cout << endl;
        }
    }
};

class GraphAdjMatrix {
private:
    vector<string> cities;
    vector<vector<double>> adjMatrix;
    unordered_map<string, int> cityIndex;
    const double INF = numeric_limits<double>::infinity();

public:
    void addCity(const string& city) {
        if (cityIndex.find(city) == cityIndex.end()) {
            cityIndex[city] = cities.size();
            cities.push_back(city);
            for (auto& row : adjMatrix) {
                row.push_back(INF);
            }
            adjMatrix.push_back(vector<double>(cities.size(), INF));
            adjMatrix.back()[cityIndex[city]] = 0;
        }
    }

    void addFlight(const string& cityA, const string& cityB, double cost) {
        addCity(cityA);
        addCity(cityB);
        int i = cityIndex[cityA];
        int j = cityIndex[cityB];
        adjMatrix[i][j] = cost;
    }

    void printGraph() const {
        cout << "Graph (Adjacency Matrix Representation):" << endl;
        cout << "    ";
        for (const auto& city : cities) {
            cout << city << "    ";
        }
        cout << endl;
        for (size_t i = 0; i < cities.size(); ++i) {
            cout << cities[i] << " ";
            for (size_t j = 0; j < cities.size(); ++j) {
                if (adjMatrix[i][j] == INF) {
                    cout << "INF    ";
                } else {
                    cout << adjMatrix[i][j] << "    ";
                }
            }
            cout << endl;
        }
    }
};

int main() {
    GraphAdjList graphList;
    graphList.addFlight("New York", "London", 7.5);
    graphList.addFlight("New York", "Paris", 8.0);
    graphList.addFlight("London", "Paris", 1.0);
    graphList.addFlight("Paris", "Berlin", 1.5);

    graphList.printGraph();

    cout << endl;

    GraphAdjMatrix graphMatrix;
    graphMatrix.addFlight("New York", "London", 7.5);
    graphMatrix.addFlight("New York", "Paris", 8.0);
    graphMatrix.addFlight("London", "Paris", 1.0);
    graphMatrix.addFlight("Paris", "Berlin", 1.5);

    graphMatrix.printGraph();

    cout << endl;

    cout << "Justification:" << endl;
    cout << "Adjacency List is preferred for sparse graphs like flight networks because it uses less memory and allows efficient iteration over connected flights." << endl;
    cout << "Adjacency Matrix uses more memory (O(V^2)) and is better for dense graphs where quick edge lookup is needed." << endl;

    return 0;
}
