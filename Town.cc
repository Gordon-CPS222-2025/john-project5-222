#include "Town.h"
#include "Road.h"

Town::Town(const std::string& name) : name(name) {}

const std::string& Town::getName() const {
    return name;
}

void Town::addRoad(Road* road) {
    roads.push_back(road);
}

const std::vector<Road*>& Town::getRoads() const {
    return roads;
}
