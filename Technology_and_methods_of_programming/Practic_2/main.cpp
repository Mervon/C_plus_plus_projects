#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <map>
#include <set>

using namespace std;

class Graph {
    vector<vector<int>> graph_1;
    map<int, vector<int>> graph_2;
    bool printable;
public:
    Graph(vector<vector<int>> graph) : graph_1(graph), printable(true) {}

    Graph(map<int, vector<int>> graph) : graph_2(graph), printable(false) {}

    void Print() {
        if (printable) {
            for (int i = 0; i < graph_1.size(); i++) {
                cout << i + 1 << ": ";
                for (int l = 0; l < graph_1[i].size(); l++) {
                    cout << graph_1[i][l] << " ";
                }
                cout << endl;
            }
        } else {
            cerr << "Bad Print call" << endl;
        }
    }

    int First(int v) {
        try {
            return graph_2.at(v).at(0);
        } catch (...) {
            return -666;
        }
    }

    int Next(int v, int i) {
        try {
            return graph_2.at(v).at(i + 1);
        } catch (...) {
            return -666;
        }
    }

    void Add_V(int v) {
        try {
            graph_2.at(v);
        } catch (...) {
            graph_2[v];
        }
    }

    void Add_E(int v, int w) {
        try {
            graph_2.at(v);
            graph_2.at(w);
            graph_2[v].push_back(v);
        } catch (...) {
            cerr << "Bad Add_E call" << endl;
        }
    }

    void Del_V(int v) {
        try {
            graph_2.at(v);
            for (int i = 0; i < 8; ++i) {
                for (int j : graph_2[i]) {
                    if (j == v) {
                        remove(graph_2[i].begin(), graph_2[i].end(), j);
                        break;
                    }
                }
            }
            graph_2.erase(v);
        } catch (...) {
            cerr << "Bad Del_V call" << endl;
        }
    }

    void Del_Е(int v, int w) {
        try {
            graph_2.at(v).at(w);
            std::remove(graph_2[v].begin(), graph_2[v].end(), w);
        } catch (...) {
            cerr << "Bad Del_Е call" << endl;
        }
    }

    void DFS(int v, set<int>& visited) {
        if (visited.find(v) != visited.end()) {
            return;
        }
        visited.insert(v);
        for (int i: graph_2[v]) {
            if (visited.find(i) == visited.end()) {
                DFS(i, visited);
            }
        }
    }

    void Solve() {
        vector<int> big_res;
        for (auto& item: graph_2) {
            set<int> result;
            DFS(item.first, result);
            if (result.size() == 8) {
                big_res.push_back(item.first);
            }
        }

        if (big_res.size() == 1) {
            cout << big_res[0] << endl;
        }
    }


};

int main() {
    vector<vector<int>> g1_1 = {
            {0, 1, 1, 0, 0, 0, 0, 0}, // 1
            {0, 0, 0, 1, 1, 0, 0, 1}, // 2
            {0, 0, 0, 0, 0, 0, 0, 0}, // 3
            {0, 0, 0, 1, 1, 0, 0, 0}, // 4
            {0, 0, 0, 0, 0, 1, 1, 0}, // 5
            {0, 0, 0, 0, 0, 0, 1, 0}, // 6
            {0, 0, 0, 0, 0, 0, 0, 1}, // 7
            {0, 0, 1, 0, 0, 0, 0, 0}, // 8
    };

    map<int, vector<int>> g1_2 = {
            {1, {2, 3}},
            {2, {4, 5}},
            {3, {}},
            {4, {5, 6}},
            {5, {2, 3}},
            {6, {7}},
            {7, {8}},
            {8, {3}},
    };

    Graph g1(g1_1);

    Graph g2(g1_2);

    g1.Print();
    g2.Solve();
}
