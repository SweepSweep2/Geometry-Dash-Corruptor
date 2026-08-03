#include "util.hpp"

using namespace geode::prelude;

void corrupt(CCNode* node) {
    float corruptionLevel = Mod::get()->getSettingValue<float>("corruption-level");
    if (corruptionLevel == 0.0) return;

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> distrib(0.0 - corruptionLevel, corruptionLevel);

    if (node) {
        node->setSkewX(distrib(gen) + node->getSkewX());
        node->setSkewY(distrib(gen) + node->getSkewY());

        node->setPositionX(distrib(gen) * 1.5 + node->getPositionX());
        node->setPositionY(distrib(gen) * 1.5 + node->getPositionY());

        node->setRotationX(distrib(gen) * 2.0 + node->getRotationX());
        node->setRotationY(distrib(gen) * 2.0 + node->getRotationY());
        
        node->setScaleX(distrib(gen) / 20.0 + node->getScaleX());
        node->setScaleY(distrib(gen) / 20.0 + node->getScaleY());
    }
}

bool isInGeodeMenu() {
    auto sharedDirector = CCDirector::sharedDirector();

    if (sharedDirector) {
        auto runningScene = sharedDirector->getRunningScene();

        if (runningScene) {
            auto child = runningScene->getChildByIndex(0);

            if (child) {
                if (child->getID() == "ModsLayer" || child->getID() == "") return true;
            }
        }
    }

    return false;
}