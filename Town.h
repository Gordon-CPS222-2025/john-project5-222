#ifndef TOWN_H
#define TOWN_H

#include <string>
#include <vector>

class Road;  // Forward declaration to avoid circular include

/**
 * Represents a town (node) in the highway network graph.
 */
class Town {
public:
    /**
     * Constructs a town with the given name.
     */
    explicit Town(const std::string& name);

    /**
     * Returns the name of the town.
     */
    const std::string& getName() const;

    /**
     * Adds a road connected to this town.
     */
    void addRoad(Road* road);

    /**
     * Returns the list of roads connected to this town.
     */
    const std::vector<Road*>& getRoads() const;

private:
    std::string name;
    std::vector<Road*> roads;
};

#endif  // TOWN_H
