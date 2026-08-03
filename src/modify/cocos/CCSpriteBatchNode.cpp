#include <Geode/Geode.hpp>
#include <Geode/modify/CCSpriteBatchNode.hpp>
#include "../../util.hpp"
#include <random>
#include <iostream>

using namespace geode::prelude;

class $modify(MyCCSpriteBatchNode, CCSpriteBatchNode) {
    void addChild(cocos2d::CCNode* child, int zOrder, int tag) {
        CCSpriteBatchNode::addChild(child, zOrder, tag);

        if (isInGeodeMenu()) return;
        
        corrupt(child);
    }
};