#include <iostream>
#include <vector>
#include <unordered_map>
#include <queue>
#include <string>
#include <map>

using namespace std;

class GraphAdjMatrix {
private:
    vector<string> landmarks;
    vector<vector<int>> adjMatrix;
    unordered_map<string, int> landmarkIndex;

public:
    void addLandmark(const string& landmark) {
        if (landmarkIndex.find(landmark) == landmarkIndex.end()) {
            landmarkIndex[landmark] = landmarks.size();
            landmarks.push_back(landmark);
            for (auto& row : adjMatrix) {
                row.push_back(0);
            }
            adjMatrix.push_back(vector<int>(landmarks.size(), 0));
        }
    }

    void addEdge(const string& from, const string& to) {
        addLandmark(from);
        addLandmark(to);
        int i = landmarkIndex[from];
        int j = landmarkIndex[to];
        adjMatrix[i][j] = 1;
        adjMatrix[j][i] = 1;
    }

    void DFSUtil(int v, vector<bool>& visited) {
        visited[v] = true;
        cout << landmarks[v] << " ";
        for (int i = 0; i < (int)landmarks.size(); i++) {
            if (adjMatrix[v][i] == 1 && !visited[i]) {
                DFSUtil(i, visited);
            }
        }
    }

    void DFS(const string& start) {
        if (landmarkIndex.find(start) == landmarkIndex.end()) {
            cout << "Start landmark not found in graph." << endl;
            return;
        }
        vector<bool> visited(landmarks.size(), false);
        cout << "DFS traversal starting from " << start << ": ";
        DFSUtil(landmarkIndex[start], visited);
        cout << endl;
    }
};

class GraphAdjList {
private:
    unordered_map<string, vector<string>> adjList;

public:
    void addLandmark(const string& landmark) {
        if (adjList.find(landmark) == adjList.end()) {
            adjList[landmark] = vector<string>();
        }
    }

    void addEdge(const string& from, const string& to) {
        addLandmark(from);
        addLandmark(to);
        adjList[from].push_back(to);
        adjList[to].push_back(from);
    }

    void BFS(const string& start) {
        if (adjList.find(start) == adjList.end()) {
            cout << "Start landmark not found in graph." << endl;
            return;
        }
        unordered_map<string, bool> visited;
        queue<string> q;
        visited[start] = true;
        q.push(start);

        cout << "BFS traversal starting from " << start << ": ";
        while (!q.empty()) {
            string current = q.front();
            q.pop();
            cout << current << " ";
            for (const auto& neighbor : adjList[current]) {
                if (!visited[neighbor]) {
                    visited[neighbor] = true;
                    q.push(neighbor);
                }
            }
        }
        cout << endl;
    }
};

int main() {
    vector<string> landmarks = {
        "College Gate",
        "Library",
        "Cafeteria",
        "Auditorium",
        "Sports Complex",
        "Admin Block",
        "Parking Lot"
    };

    GraphAdjMatrix graphMatrix;
    GraphAdjList graphList;

    graphMatrix.addEdge("College Gate", "Library");
    graphMatrix.addEdge("College Gate", "Cafeteria");
    graphMatrix.addEdge("Library", "Auditorium");
    graphMatrix.addEdge("Cafeteria", "Sports Complex");
    graphMatrix.addEdge("Auditorium", "Admin Block");
    graphMatrix.addEdge("Sports Complex", "Parking Lot");
    graphMatrix.addEdge("Admin Block", "Parking Lot");

    graphList.addEdge("College Gate", "Library");
    graphList.addEdge("College Gate", "Cafeteria");
    graphList.addEdge("Library", "Auditorium");
    graphList.addEdge("Cafeteria", "Sports Complex");
    graphList.addEdge("Auditorium", "Admin Block");
    graphList.addEdge("Sports Complex", "Parking Lot");
    graphList.addEdge("Admin Block", "Parking Lot");

    graphMatrix.DFS("College Gate");
    graphList.BFS("College Gate");

    return 0;
}
