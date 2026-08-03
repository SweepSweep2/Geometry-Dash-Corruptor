#include <Geode/Geode.hpp>
#include <Geode/modify/GJListLayer.hpp>
#include "../util.hpp"

using namespace geode::prelude;

class $modify(MyGJListLayer, GJListLayer) {
    bool init(BoomListView* listView, char const* title, cocos2d::ccColor4B color, float width, float height, int type) {
        if (!GJListLayer::init(listView, title, color, width, height, type)) return false;
        
        corrupt(getChildByID("left-border"));
        corrupt(getChildByID("right-border"));
        corrupt(getChildByID("bottom-border"));
        corrupt(getChildByID("top-border"));

        return true;
    }
};
