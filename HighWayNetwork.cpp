// Include necessary headers
#include "HighWayNetwork.h"
#include "Road.h"
#include <queue>      
#include <set>       
#include <iostream>    
#include <iomanip>     

// Constructor: Builds the highway network from input stream

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
        addRoad(from, to, bridgeFlag == 'B', distance);  
    }
}

// Adds a bidirectional road between two towns

void HighwayNetwork::addRoad(const std::string& from, const std::string& to, bool isBridge, float distance) {
    // Look up town pointers from names
    Town* fromTown = nameToTown[from];
    Town* toTown = nameToTown[to];

    // Create two road objects (one for each direction)
    Road* road1 = new Road(toTown, distance, isBridge);
    Road* road2 = new Road(fromTown, distance, isBridge);

    // Add roads to respective towns
    fromTown->addRoad(road1);
    toTown->addRoad(road2);
}

void HighwayNetwork::printNetwork() const {
    std::cout << "The input data is:\n" << std::endl;

    std::queue<Town*> toVisit;
    std::set<std::string> visited;

    toVisit.push(capital);
    visited.insert(capital->getName());

    while (!toVisit.empty()) {
        Town* current = toVisit.front();
        toVisit.pop();

        std::cout << current->getName() << std::endl;

        for (Road* road : current->getRoads()) {
            Town* neighbor = road->getDestination();
            std::cout << "    " << neighbor->getName() << " ";
            std::cout << std::fixed << std::setprecision(1) << road->getDistance() << " mi";
            if (road->getIsBridge()) {
                std::cout << " via bridge";
            }
            std::cout << std::endl;

            // Enqueue unvisited neighbors
            if (visited.find(neighbor->getName()) == visited.end()) {
                visited.insert(neighbor->getName());
                toVisit.push(neighbor);
            }
        }
    }

    

    std::cout << std::endl;
}

void HighwayNetwork::printUpgrades() const {
    std::cout << "The road upgrading goal can be achieved at minimal cost by upgrading:\n";
    for (Town* town : towns) {
        for (Road* road : town->getRoads()) {
            // Suggest upgrading bridges or roads longer than 5 miles
            if (road->getIsBridge() || road->getDistance() > 5.0f) {
                std::cout << "Upgrade road from " << town->getName() << " to "
                          << road->getDestination()->getName() << " ("
                          << road->getDistance() << " mi)"
                          << (road->getIsBridge() ? " [BRIDGE]" : "") << "\n";
            }
        }
    }
}

void HighwayNetwork::printShortestPaths() const {
    std::unordered_map<Town*, float> dist;
    std::unordered_map<Town*, Town*> prev;
    std::priority_queue<std::pair<float, Town*>, std::vector<std::pair<float, Town*>>, std::greater<>> pq;

    for (Town* town : towns) {
        dist[town] = std::numeric_limits<float>::max();
    }
    dist[capital] = 0.0f;
    pq.push({0.0f, capital});

    while (!pq.empty()) {
        auto [currentDist, current] = pq.top();
        pq.pop();

        for (Road* road : current->getRoads()) {
            Town* neighbor = road->getDestination();
            float newDist = currentDist + road->getDistance();
            if (newDist < dist[neighbor]) {
                dist[neighbor] = newDist;
                prev[neighbor] = current;
                pq.push({newDist, neighbor});
            }
        }
    }

    std::cout << "The shortest paths from " << capital->getName() << " are:\n";
    for (Town* town : towns) {
        if (town == capital) continue;

        if (dist[town] == std::numeric_limits<float>::max()) {
            std::cout << "No path from " << capital->getName() << " to "
                      << town->getName() << ".\n\n";
            continue;
        }

        std::vector<std::string> path;
        for (Town* at = town; at != nullptr; at = prev[at]) {
            path.push_back(at->getName());
        }
        std::reverse(path.begin(), path.end());

        std::cout << "The shortest path from " << capital->getName() << " to "
                  << town->getName() << " is " << std::fixed << std::setprecision(1)
                  << dist[town] << " mi:\n";
        for (const auto& name : path) {
            std::cout << name << "\n";
        }
        std::cout << "\n";
    }
}
 

HighwayNetwork::~HighwayNetwork() {
    for (Town* town : towns) {
        const std::vector<Road*>& roads = town->getRoads();
        for (Road* road : roads) {
            delete road;
        }
        delete town;
    }
}