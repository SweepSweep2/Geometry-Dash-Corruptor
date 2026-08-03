#include <Geode/Geode.hpp>
#include <Geode/modify/BoomListView.hpp>
#include "../util.hpp"

using namespace geode::prelude;

class $modify(MyBoomListView, BoomListView) {
    bool init(cocos2d::CCArray* entries, TableViewCellDelegate* delegate, float height, float width, int page, BoomListType type, float y) {
        if (!BoomListView::init(entries, delegate, height, width, page, type, y)) return false;

        for (auto obj : CCArrayExt(m_tableView->getChildByIndex(0)->getChildren())) {
            CCNode* childNode = static_cast<CCNode*>(obj);

            corrupt(childNode);
        }

        return true;
    }
};
