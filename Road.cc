#include "Road.h"


// Constructor: Initializes a Road with destination town, distance, and bridge status
// @param destination - Pointer to the Town this road leads to
// @param distance   - Length/weight of the road (in arbitrary units)
// @param isBridge   - Boolean flag indicating if this road is a bridge
Road::Road(Town* destination, int distance, bool isBridge)
    : destination(destination), distance(distance), isBridge(isBridge) {}

// Getter method for the destination town
Town* Road::getDestination() const {
    return destination;
}

// Getter method for the road's distance/length
int Road::getDistance() const {
    return distance;
}

// Getter method for bridge status
bool Road::getIsBridge() const {
    return isBridge;
}
