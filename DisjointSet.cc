#ifndef DISJOINT_SET_H
#define DISJOINT_SET_H

#include "Town.h"
#include <unordered_map>
#include <vector>

class DisjointSet {
private:
    std::unordered_map<Town*, Town*> parent;