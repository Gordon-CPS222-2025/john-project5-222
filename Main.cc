#include "HighWayNetwork.h"
#include <iostream>
int main() {
    HighwayNetwork network(std::cin);
    network.printNetwork();
    network.printShortestPaths();

    std::cout << std::endl << std::endl << "------------------------------------------------------------------" << std::endl;
    return 0;
}
