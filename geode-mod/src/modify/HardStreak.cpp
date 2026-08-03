#include <Geode/Geode.hpp>
#include <Geode/modify/HardStreak.hpp>
#include "../util.hpp"
#include <random>
#include <iostream>

using namespace geode::prelude;

class $modify(MyHardStreak, HardStreak) {
    bool init() {
        if (!HardStreak::init()) return false;
        
        corrupt(this);

        return true;
    }
};
