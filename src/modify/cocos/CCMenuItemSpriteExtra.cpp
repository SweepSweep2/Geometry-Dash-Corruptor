#include <Geode/Geode.hpp>
#include <Geode/modify/CCMenuItemSpriteExtra.hpp>
#include "../../util.hpp"

using namespace geode::prelude;

class $modify(MyCCMenuItemSpriteExtra, CCMenuItemSpriteExtra) {
    bool init(cocos2d::CCNode* sprite, cocos2d::CCNode* selectedSprite, cocos2d::CCObject* target, cocos2d::SEL_MenuHandler callback) {
        if (!CCMenuItemSpriteExtra::init(sprite, selectedSprite, target, callback)) return false;
        if (isInGeodeMenu()) return true;

        corrupt(this);

        return true;
    }
};