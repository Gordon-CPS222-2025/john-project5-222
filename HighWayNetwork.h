#ifndef HIGHWAY_NETWORK_H
#define HIGHWAY_NETWORK_H

#include <iostream>
#include <vector>
#include <map>
#include <string>
#include "Town.h"

/**
 * Represents a province's road network (graph of towns and roads).
 * Responsible for reading input and performing analyses.
 */
class HighwayNetwork {
public:
    /**
     * Constructs the highway network from the given input stream.
     * Automatically reads towns and roads and builds the graph.
     */
    explicit HighwayNetwork(std::istream& in);

    /**
     * Destructor: cleans up all dynamically allocated memory.
     */
    ~HighwayNetwork();

    /**
     * Prints the road network in BFS order starting from the capital.
     * Each road is printed under both connected towns.
     */
    void printNetwork() const;
    void printShortestPaths() const;
    void printUpgrades() const;
    void printComponents() const;
    void printCriticalLinks() const;
    void printCriticalTowns() const;

private:
    std::vector<Town*> towns;
    Town* capital;
    std::map<std::string, Town*> nameToTown;

    /**
     * Adds a two-way road between two towns.
     */
    void addRoad(const std::string& from, const std::string& to, bool isBridge, float distance);
};

#endif  // HIGHWAY_NETWORK_H
