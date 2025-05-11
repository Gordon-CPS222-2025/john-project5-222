#include "HighWayNetwork.h"
#include <iostream>
int main() {
    HighwayNetwork network(std::cin);
    std::cout << "The input data is:\n" << std::endl;
    network.printNetwork();

    std::cout << "\nThe shortest paths from NOWHERESVILLE are:\n" << std::endl;
    network.printShortestPaths();

    std::cout << "\nThe road upgrading goal can be achieved at minimal cost by upgrading:\n" << std::endl;
    network.printUpgrades();

    std::cout << "\nConnected components in event of a major storm are:\n";
    std::cout << "   If all bridges fail, the following towns would form an isolated group:\n";
    network.printComponents();

    network.printCriticalLinks();

    network.printCriticalTowns();




    std::cout << std::endl << std::endl << "------------------------------------------------------------------" << std::endl;
    return 0;
}
