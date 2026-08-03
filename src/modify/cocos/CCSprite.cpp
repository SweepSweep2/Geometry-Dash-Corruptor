#include <Geode/Geode.hpp>
#include <Geode/modify/CCSprite.hpp>
#include "../../util.hpp"
#include <random>
#include <iostream>

using namespace geode::prelude;

class $modify(MyCCSprite, CCSprite) {
    struct Fields {
        bool m_corrupted = false;
    };

    void draw() {
        CCSprite::draw();

        // if you are approving this mod or just checking it out, please tell me a better way to do this
        // this is the only way that actually worked for me, as if i use init then it wont work for sprites being directly used in CCMenuItemSpriteExtra

        if (!m_fields->m_corrupted) {
            if (isInGeodeMenu()) return;

            corrupt(this);

            m_fields->m_corrupted = true;
        }
    }
};