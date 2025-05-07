#include "Town.h"
#include "Road.h"


// Constructor: Initializes a Town with the given name
// @param name - The name of the town to be created
Town::Town(const std::string& name) : name(name) {}

// Getter method for the town's name
const std::string& Town::getName() const {
    return name;
}

// Adds a road connection to this town
void Town::addRoad(Road* road) {
    roads.push_back(road);
}

// Getter method for all roads connected to this town
const std::vector<Road*>& Town::getRoads() const {
    return roads;
}
