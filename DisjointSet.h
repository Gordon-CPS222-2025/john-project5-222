#ifndef DISJOINT_SET_H
#define DISJOINT_SET_H

#include "Town.h"
#include <unordered_map>
#include <vector>

class DisjointSet {
private:
    std::unordered_map<Town*, Town*> parent;

public:
void makeSet(const std::vector<Town*>& towns);
Town *find(Town *town);
void unite(Town *a, Town *b);
bool connected(Town* a, Town* b);
};

#endif // DISJOINT_SET_H
