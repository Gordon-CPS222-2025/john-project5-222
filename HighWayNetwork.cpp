// Include necessary headers
#include "HighWayNetwork.h"
#include "Road.h"
#include <queue>       // For BFS traversal
#include <set>         // For tracking visited towns
#include <iostream>    // For output
#include <iomanip>     // For formatting distance output

// Constructor: Builds the highway network from input stream
// @param in - Input stream containing network data
HighwayNetwork::HighwayNetwork(std::istream& in) {
    // Read number of towns and roads from input
    int numTowns, numRoads;
    in >> numTowns >> numRoads;

    // Read and create all towns
    std::string townName;
    for (int i = 0; i < numTowns; ++i) {
        in >> townName;
        Town* town = new Town(townName);
        if (i == 0) capital = town;  // First town is treated as capital
        towns.push_back(town);        // Add to towns collection
        nameToTown[townName] = town;  // Map name to town pointer
    }

    // Read and create all road connections
    std::string from, to;
    char bridgeFlag;
    float distance;
    for (int i = 0; i < numRoads; ++i) {
        in >> from >> to >> bridgeFlag >> distance;
        addRoad(from, to, bridgeFlag == 'B', distance);  // 'B' indicates bridge
    }
}

// Adds a bidirectional road between two towns
// @param from - Name of starting town
// @param to - Name of destination town
// @param isBridge - Whether the road is a bridge
// @param distance - Length of the road in miles
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