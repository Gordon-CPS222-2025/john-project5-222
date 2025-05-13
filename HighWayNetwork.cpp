// Include necessary headers
#include "HighWayNetwork.h"
#include "Road.h"
#include <queue>     
#include <set>        
#include <iostream>    
#include <iomanip>   
#include <unordered_set>  
#include "DisjointSet.h" 

/**
 * Constructor: Builds the highway network from input stream
 * 
 * @param in Input stream containing network data in the format:
 *        - First line: numTowns numRoads
 *        - Next numTowns lines: town names
 *        - Next numRoads lines: fromTown toTown bridgeFlag(B/R) distance
 */
HighwayNetwork::HighwayNetwork(std::istream& in) {
    // Read number of towns and roads from input
    int numTowns, numRoads;
    in >> numTowns >> numRoads;

    // Read and create all towns
    std::string townName;
    for (int i = 0; i < numTowns; ++i) {
        in >> townName;
        Town* town = new Town(townName);
        if (i == 0) capital = town; 
        towns.push_back(town);        
        nameToTown[townName] = town;  
    }

    // Read and create all road connections
    std::string from, to;
    char bridgeFlag;
    float distance;
    for (int i = 0; i < numRoads; ++i) {
        in >> from >> to >> bridgeFlag >> distance;
        addRoad(from, to, bridgeFlag == 'B', distance);  // 'B' indicates a bridge
    }
}

/**
 * Adds a bidirectional road between two towns
 * 
 * @param from Source town name
 * @param to Destination town name
 * @param isBridge Flag indicating if the road includes a bridge
 * @param distance Length of the road in miles
 * 
 * Creates two Road objects to represent the bidirectional connection
 */
void HighwayNetwork::addRoad(const std::string& from, const std::string& to, bool isBridge, float distance) {
    // Validate that both town names exist in our network
    if (nameToTown.find(from) == nameToTown.end() || nameToTown.find(to) == nameToTown.end()) {
        std::cerr << "Error: Town name not found in map: " << from << " or " << to << std::endl;
        return;  // or throw exception
    }

    // Get Town pointers from the name map
    Town* fromTown = nameToTown.at(from);
    Town* toTown = nameToTown.at(to);

    // Create bidirectional roads (two Road objects pointing in opposite directions)
    Road* road1 = new Road(toTown, distance, isBridge);
    Road* road2 = new Road(fromTown, distance, isBridge);

    // Add roads to their respective source towns
    fromTown->addRoad(road1);
    toTown->addRoad(road2);
}

/**
 * Prints the entire network using BFS traversal starting from the capital
 *
 */
void HighwayNetwork::printNetwork() const {
    // Use BFS to visit all towns starting from the capital
    std::queue<Town*> toVisit;
    std::set<std::string> visited;

    // Start BFS from the capital
    toVisit.push(capital);
    visited.insert(capital->getName());

    while (!toVisit.empty()) {
        Town* current = toVisit.front();
        toVisit.pop();

        // Print current town name
        std::cout << current->getName() << std::endl;

        // Print all roads from the current town
        for (Road* road : current->getRoads()) {
            Town* neighbor = road->getDestination();
            std::cout << "    " << neighbor->getName() << " ";
            std::cout << std::fixed << std::setprecision(1) << road->getDistance() << " mi";
            if (road->getIsBridge()) {
                std::cout << " via bridge";
            }
            std::cout << std::endl;

            // Enqueue unvisited neighbors to continue BFS
            if (visited.find(neighbor->getName()) == visited.end()) {
                visited.insert(neighbor->getName());
                toVisit.push(neighbor);
            }
        }
    }

    std::cout << std::endl;
}

/**
 * Prints all roads that need upgrades
 * Uses a set to track already processed roads 
 */
void HighwayNetwork::printUpgrades() const {
    // Track seen road pairs to avoid duplicates 
    std::set<std::pair<std::string, std::string>> seen;
    bool found = false;
    
    // Iterate through all towns and their roads
    for (Town* town : towns) {
        for (Road* road : town->getRoads()) {
            Town* dest = road->getDestination();
            
            // Create a canonical representation of the road pair (smaller name first)
            std::string nameA = town->getName();
            std::string nameB = dest->getName();
            if (nameA > nameB) std::swap(nameA, nameB);
            
            // If this road hasn't been seen before, print it as an upgrade candidate
            if (seen.insert({nameA, nameB}).second) {
                std::cout << "    " << nameB << " to " << nameA << std::endl;
                found = true;
            }
        }
    }
    
    if (!found) {
        std::cout << "    (None)" << std::endl;
    }
}

/**
 * Prints shortest paths from the capital to all other towns
 * Uses Dijkstra's algorithm to find the shortest paths
 */
void HighwayNetwork::printShortestPaths() const {
    std::unordered_map<Town*, float> dist;
    std::unordered_map<Town*, Town*> prev;
    std::priority_queue<std::pair<int, Town*>, std::vector<std::pair<int, Town*>>, std::greater<>> pq;

    // Initialize distances to infinity
    for (Town* town : towns) {
        dist[town] = std::numeric_limits<int>::max();
    }
    
    // Start from capital with distance 0
    dist[capital] = 0.0f;
    pq.push({0.0f, capital});

    // Dijkstra's algorithm main loop
    while (!pq.empty()) {
        auto [currentDist, current] = pq.top();
        pq.pop();

        // Process all neighbors of the current town
        for (Road* road : current->getRoads()) {
            Town* neighbor = road->getDestination();
            float newDist = currentDist + road->getDistance();
            
            // If we found a shorter path to this neighbor
            if (newDist < dist[neighbor]) {
                dist[neighbor] = newDist;
                prev[neighbor] = current;
                pq.push({newDist, neighbor});
            }
        }
    }

    // Print paths from capital to all other towns
    for (Town* town : towns) {
        if (town == capital) continue;  // Skip the capital itself

        // If no path exists
        if (dist[town] == std::numeric_limits<int>::max()) {
            std::cout << "No path from " << capital->getName() << " to "
                      << town->getName() << ".\n\n";
            continue;
        }

        // Reconstruct the path from destination to source
        std::vector<std::string> path;
        for (Town* at = town; at != nullptr; at = prev[at]) {
            path.push_back(at->getName());
        }
        // Reverse to get source to destination order
        std::reverse(path.begin(), path.end());

        // Print the path details
        std::cout << "The shortest path from " << capital->getName() << " to "
                  << town->getName() << " is " << std::fixed << std::setprecision(1)
                  << dist[town] << " mi:\n";
        for (const auto& name : path) {
            std::cout << name << "\n";
        }
        std::cout << "\n";
    }
}

/**
 * Prints all critical links (bridges) whose removal would disconnect the network
 * 
 * In this implementation, critical links are simply the roads marked as bridges
 */
void HighwayNetwork::printCriticalLinks() const {
    std::cout << "\nDestruction of any of the following would result in the province becoming\ndisconnected:\n";
    
    // Iterate through all towns and their roads
    for (Town* town : towns) {
        for (Road* road : town->getRoads()) {
            // Only print bridges as critical links
            if (road->getIsBridge()) {
                std::cout << town->getName() << " -- " 
                          << road->getDestination()->getName() << "\n";
            }
        }
    }
}

/**
 * Prints connected components that would form if all bridges were removed
 * 
 */
void HighwayNetwork::printComponents() const {
    std::unordered_set<Town*> visited;
    int component = 1;

    // Iterate through all towns
    for (Town* town : towns) {
        // If this town hasn't been visited, it belongs to a new component
        if (visited.find(town) == visited.end()) {
            std::queue<Town*> q;
            q.push(town);
            visited.insert(town);

            std::cout << "If all bridges fail, the following towns would form an isolated group:\n";

            // BFS to find all towns in this component
            while (!q.empty()) {
                Town* current = q.front();
                q.pop();
                std::cout << current->getName() << "\n";

                // Only consider roads that are not bridges
                for (Road* road : current->getRoads()) {
                    if (!road->getIsBridge()) {  // Ignore roads with bridges
                        Town* neighbor = road->getDestination();
                        if (visited.find(neighbor) == visited.end()) {
                            visited.insert(neighbor);
                            q.push(neighbor);
                        }
                    }
                }
            }
            std::cout << "\n";
        }
    }
}

/**
 * Prints critical towns  whose removal would disconnect the network
 * 
 */
void HighwayNetwork::printCriticalTowns() const {
    std::cout << "\nDestruction of any of the following would result in the province becoming\ndisconnected:\n";
    
   
    std::unordered_map<Town*, int> discoveryTime;
    std::unordered_map<Town*, int> low;            
    std::unordered_map<Town*, Town*> parent;      
    std::unordered_set<Town*> articulationPoints;  
    int time = 0; 

    // Recursive DFS function to find articulation points
    std::function<void(Town*)> dfs = [&](Town* u) {
        // Initialize discovery time and low value
        discoveryTime[u] = low[u] = ++time;
        int children = 0;  // Count of children in DFS tree

        // Visit all neighbors
        for (Road* road : u->getRoads()) {
            Town* v = road->getDestination();
            
            // If v is not visited yet
            if (discoveryTime.find(v) == discoveryTime.end()) {
                parent[v] = u;
                ++children;
                dfs(v);  // Recursive DFS

                // Update low value of u based on its children
                low[u] = std::min(low[u], low[v]);

                // Check if u is an articulation point:
                if ((parent.find(u) == parent.end() && children > 1) ||
                    (parent.find(u) != parent.end() && low[v] >= discoveryTime[u])) {
                    articulationPoints.insert(u);
                }
            } else if (v != parent[u]) {
                // Update low value for back edges
                low[u] = std::min(low[u], discoveryTime[v]);
            }
        }
    };

    // Run DFS for each unvisited town
    for (Town* town : towns) {
        if (discoveryTime.find(town) == discoveryTime.end()) {
            dfs(town);
        }
    }

    // Print the articulation points
    std::cout << "Destruction of any of the following would result in the province becoming\n";
    std::cout << "disconnected:\n";

    if (articulationPoints.empty()) {
        std::cout << "    (None)\n";
    } else {
        for (Town* town : articulationPoints) {
            std::cout << "    " << town->getName() << "\n";
        }
    }
}

/**
 * Destructor: Clean up all dynamically allocated memory
 * Deletes all Town and Road objects
 */
HighwayNetwork::~HighwayNetwork() {
    // First delete all Road objects, then delete Town objects
    for (Town* town : towns) {
        const std::vector<Road*>& roads = town->getRoads();
        for (Road* road : roads) {
            delete road;
        }
        delete town;
    }
}