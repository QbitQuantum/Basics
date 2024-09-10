bool NewMenuDevice::ccTouchBegan(cocos2d::CCTouch *touch, cocos2d::CCEvent *event) {
    //    CCPoint pouchT = map->transScreenToMap(ccp(pTouch->locationInView().x,pTouch->locationInView().y));
    //    CCPoint posiT = map->transMapToTiled(this->getPosition());
    //        
    //    CCPoint tiled = map->transMapToTiled(pouchT);
    //    if(Mathlib::inBound(tiled.x, posiT.x+contentSizeByTiled.width/2, posiT.x-contentSizeByTiled.width/2) &&
    //           Mathlib::inBound(tiled.y, posiT.y+contentSizeByTiled.height/2, posiT.y-contentSizeByTiled.height/2)) {
    //        isMoved = true;
    //    }
    //    return CCMenu::ccTouchBegan(pTouch, pEvent);
    
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