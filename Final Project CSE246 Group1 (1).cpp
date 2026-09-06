#include <iostream>
#include <unordered_map>
#include <vector>
#include <queue>
#include <limits>
#include <string>
#include <set>
#include <algorithm>
#include <iomanip>

using namespace std;

#include <iostream>
using namespace std;

void drawMap() {
    cout << "\n\n\t\t\t\tDhaka Map\n";
    cout << "\t\t\t\t---------\n\n";
    cout<<endl;
    cout << "                     Uttara  \n";
    cout << "                     /    \\\n";
    cout << "                    /      \\                  Bashundhara\n";
    cout << "                   /        \\                      |\n";
    cout << "                  /          \\                     |\n";
    cout << "                 |     .-----Banani----Gulshan----Badda\n";
    cout << "                 |    /       |                     |             \n";
    cout << "              Mirpur-'        |                     |             \n";
    cout << "                |          Mohakhali--------------Rampura\n";
    cout << "                |              \\       \n";
    cout << "                |               \\       \n";
    cout << "              Dhanmondi       Farmgate\n";
    cout << "                |                 \\\n";
    cout << "                |                  \\\n";
    cout << "              Shahbagh-----------Motijheel\n";
    cout<<endl;
    cout << "\n\n===========================================================================================================\n";
}


struct Edge {
    string to;
    double weight;
};

class Graph {
public:
    unordered_map<string, vector<Edge>> adj;
    void addEdge(const string& from, const string& to, double weight) {
        adj[from].push_back({to, weight});
        adj[to].push_back({from, weight});
    }

    vector<string> dijkstra(const string& source, const string& target) {
        unordered_map<string, double> dist;
        unordered_map<string, string> prev;
        set<pair<double, string>> pq;
        vector<string> path;
        if (adj.find(source) == adj.end()) {
            cout << "\t[Error] pickup location '" << source << "' not found in map.\n";
            return path;
        }

        if (adj.find(target) == adj.end()) {
            cout << "\t[Error] drop-off location '" << target << "' not found in map.\n";
            return path;
        }

        for (auto& node : adj) {
            dist[node.first] = numeric_limits<double>::infinity();
        }

        dist[source] = 0;
        pq.insert({0, source});

        while (!pq.empty()) {
            string u = pq.begin()->second;
            pq.erase(pq.begin());

            if (u == target) break;

            for (Edge e : adj[u]) {
                double alt = dist[u] + e.weight;
                if (alt < dist[e.to]) {
                    pq.erase({dist[e.to], e.to});
                    dist[e.to] = alt;
                    prev[e.to] = u;
                    pq.insert({alt, e.to});
                }
            }
        }

        if (dist[target] == numeric_limits<double>::infinity()) return path;

        for (string at = target; at != source; at = prev[at])
            path.push_back(at);
        path.push_back(source);
        reverse(path.begin(), path.end());
        return path;
    }

    void listLocations() {
        cout << "\nAvailable locations:\n";
        for (auto& pair : adj) {
            cout << " - " << pair.first << endl;
        }
    }
};

struct Passenger {
    string name;
    string pickup;
    string dropoff;
    vector<string> route;
};

double computeSimilarity(const vector<string>& r1, const vector<string>& r2) {
    set<string> set1(r1.begin(), r1.end());
    set<string> set2(r2.begin(), r2.end());

    vector<string> intersect;
    set_intersection(set1.begin(), set1.end(), set2.begin(), set2.end(),
                     back_inserter(intersect));

    vector<string> uni;
    set_union(set1.begin(), set1.end(), set2.begin(), set2.end(),
              back_inserter(uni));

    if (uni.empty()) return 0.0;
    return (double)intersect.size() / uni.size();
}

double getPathDistance(const vector<string>& path, const unordered_map<string, vector<Edge>>& adj) {
    double total = 0.0;
    for (size_t i = 0; i + 1 < path.size(); ++i) {
        string from = path[i], to = path[i + 1];
        for (const Edge& e : adj.at(from)) {
            if (e.to == to) {
                total += e.weight;
                break;
            }
        }
    }
    return total;
}


int main() {
    Graph city;

    // Build the city graph
    city.addEdge("Uttara", "Banani", 9.0);
    city.addEdge("Uttara", "Mirpur", 6.0);
    city.addEdge("Mirpur", "Banani", 5.0);
    city.addEdge("Banani", "Gulshan", 2.0);
    city.addEdge("Badda", "Bashundhara", 2.0);
    city.addEdge("Badda", "Rampura", 3.0);
    city.addEdge("Gulshan", "Banani", 3.0);

    city.addEdge("Banani", "Mohakhali", 1.5);
    city.addEdge("Mohakhali", "Farmgate", 2.5);
    city.addEdge("Rampura", "Mohakhali", 4.0);

    city.addEdge("Mirpur", "Dhanmondi", 6.5);
    city.addEdge("Dhanmondi", "Shahbagh", 2.0);
    city.addEdge("Shahbagh", "Motijheel", 3.0);
    city.addEdge("Farmgate", "Motijheel", 4.5);


    cout << "===========================================================================================================\n";
    cout << "\n";
    cout << "======      ======      ======     ======      Dhaka Ride       ======       ======      ======      ======\n";
    cout << "\n";
    cout << "===========================================================================================================\n";

    drawMap();

    int n;
    cout << "\n\tHow many passengers?\n\t= ";
    cin >> n;
    cin.ignore();

    vector<Passenger> passengers;
    //city.listLocations();

    for (int i = 0; i < n; ++i) {
        Passenger p;
        cout << "\n\tPassenger " << i + 1 << ": \n";
        cout << "\n\t\tName: ";
        getline(cin, p.name);

        cout << "\t\tPickup location: ";
        getline(cin, p.pickup);

        cout << "\t\tDrop-off location: ";
        getline(cin, p.dropoff);

        passengers.push_back(p);

    }

        cout << "\n===========================================================================================================\n";
    // Compute routes
    for (auto& p : passengers) {
        p.route = city.dijkstra(p.pickup, p.dropoff);

        if (p.route.empty()) {
            cout << "\tNo route found for " << p.name << "! Please check input.\n";
            continue;
        }

        cout << "\n\t" << p.name << ": ";
        for (auto node : p.route) {
            cout << node;
            if (node != p.route.back()) cout << " -> ";
        }
        double dist = getPathDistance(p.route, city.adj); // Calculate distance
        cout << "  (" << fixed << setprecision(2) << dist << " km)" << endl;


    }

    // Group passengers into ride pools
    vector<vector<string>> carPools;
    set<string> assigned;

    for (size_t i = 0; i < passengers.size(); ++i) {
        if (assigned.count(passengers[i].name)) continue;

        vector<string> group = {passengers[i].name};
        assigned.insert(passengers[i].name);

        for (size_t j = i + 1; j < passengers.size(); ++j) {
            if (assigned.count(passengers[j].name)) continue;
            double sim = computeSimilarity(passengers[i].route, passengers[j].route);
            if (sim >= 0.6) {
                group.push_back(passengers[j].name);
                assigned.insert(passengers[j].name);
            }
        }

        carPools.push_back(group);
    }

    // Output ride groups
    cout << "\n-------------------------------------------- Car Assignment --------------------------------------------\n";
    int carNum = 1;
    cout<<endl;
    for (auto& group : carPools) {
        cout << "\tCar " << carNum++ << ": ";
        for (auto& name : group) cout << name << " ";
        cout << endl;
    }

    return 0;
}

