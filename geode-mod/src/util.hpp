#include <Geode/Geode.hpp>
#include <random>
#include <iostream>

using namespace geode::prelude;

void corrupt(CCNode* node);
bool isInGeodeMenu();

namespace storedData {
    inline float testingx = 0.0;
    inline float testingy = 0.0;
}