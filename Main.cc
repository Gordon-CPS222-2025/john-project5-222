#include "HighWayNetwork.h"
#include <iostream>

bool eof(std::istream& in) {
    char c;
    in >> std::ws;
    if (in.eof()) return true;
    in.unget();
    return false;
}

int main() {
        std::cout << "Reading network..." << std::endl;
        HighwayNetwork network(std::cin);
        std::cout << "Network read successfully." << std::endl;
        network.printNetwork();
    return 0;
}
