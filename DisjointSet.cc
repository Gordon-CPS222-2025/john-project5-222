#include "DisjointSet.h"

void DisjointSet::makeSet(const std::vector<Town*>& towns) {
    parent.clear();
    for (Town* town : towns) {
        parent[town] = town;
    }
}

Town* DisjointSet::find(Town* town) {
    if (parent[town] != town) {
        parent[town] = find(parent[town]);
    }
    return parent[town];
}

void DisjointSet::unite(Town* a, Town* b) {
    Town* rootA = find(a);
    Town* rootB = find(b);
    if (rootA != rootB) {
        parent[rootA] = rootB;
    }
}

bool DisjointSet::connected(Town* a, Town* b) {
    return find(a) == find(b);
}