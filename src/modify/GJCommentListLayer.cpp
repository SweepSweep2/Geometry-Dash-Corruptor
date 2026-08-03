#include <Geode/Geode.hpp>
#include <Geode/modify/GJCommentListLayer.hpp>
#include "../util.hpp"
#include <random>
#include <iostream>

using namespace geode::prelude;

class $modify(MyGJCommentListLayer, GJCommentListLayer) {
    bool init(BoomListView* listView, char const* title, cocos2d::ccColor4B color, float width, float height, bool blueBorder) {
        if (!GJCommentListLayer::init(listView, title, color, width, height, blueBorder)) return false;
        
        corrupt(this);

        return true;
    }
};
