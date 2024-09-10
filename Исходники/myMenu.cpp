bool MyMenu::ccTouchBegan(cocos2d::CCTouch *touch, cocos2d::CCEvent *event) {
    if (isActive) {
        cacheTouch  = map->transMapToTiled(map->convertToNodeSpace(touch->getLocation()));
        if (CCMenu::ccTouchBegan(touch, event)) {
//            if (m_pSelectedItem->getTag() == myTiledMenuItemTag) {
//                moveEnabled = true;
//                isMoved = false;
//                //TODO
////                ((MyMap*)map)->moveTemp = this;
//                MyMenu::reorderZandTouchPriority(1000000, -499);
//            } else {
////                ((MyMap*)map)->moveTemp = this;
//                moveEnabled = false;
//                isMoved = false;
//            }
            return true;
        }
        return false;
    }
    if (((MyMap*)map)->isBuild()) {
        return false;
    }
    CC_UNUSED_PARAM(event);
    if (m_eState != kCCMenuStateWaiting || ! m_bVisible || !isEnabled())
    {
        return false;
    }
    
    for (CCNode *c = this->m_pParent; c != NULL; c = c->getParent())
    {
        if (c->isVisible() == false)
        {
            return false;
        }
    }
    
    m_pSelectedItem = this->itemForTouch(touch);
    if (m_pSelectedItem)
    {
        m_eState = kCCMenuStateTrackingTouch;
        m_pSelectedItem->selected();
        return true;
    }
    return false;

}