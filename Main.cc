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
    while (!eof(std::cin)) {
        HighwayNetwork network(std::cin);
        network.printNetwork();
    }
    return 0;
}
