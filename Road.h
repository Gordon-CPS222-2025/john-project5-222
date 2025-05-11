#ifndef ROAD_H
#define ROAD_H

class Town;

/**
 * Represents a road (edge) between two towns in the highway network.
 * This is a directional connection used in both directions during graph setup.
 */
class Road {
public:
    /**
     * Constructs a road to the given destination town with distance and bridge flag.
     */
    Road(Town* destination, int distance, bool isBridge);

    /**
     * Returns the destination town this road leads to.
     */
    Town* getDestination() const;

    /**
     * Returns the distance of the road in miles.
     */
    int getDistance() const;

    /**
     * Returns true if the road is a bridge, false otherwise.
     */
    bool getIsBridge() const;

private:
    Town* destination;
    int distance;
    bool isBridge;
};

#endif  // ROAD_H
