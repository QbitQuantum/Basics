void DropSacrificeAnim::onPlayEnd()
{
    auto node = UIComponent::getInstance();
    CCPoint p;
    CCPoint p2;
    if (m_type == Wood) {
        p = node->m_woodIcon->getPosition();
        CCDirector::sharedDirector()->convertToGL(p);
         p2 = node->m_woodIcon->getParent()->convertToWorldSpace(p);
    }
    else if (m_type == Food) {
        p = node->m_foodIcon->getPosition();
        CCDirector::sharedDirector()->convertToGL(p);
        p2 = node->m_foodIcon->getParent()->convertToWorldSpace(p);
    }
    else if (m_type == Stone) {
        p = node->m_stoneIcon->getPosition();
        CCDirector::sharedDirector()->convertToGL(p);
        p2 = node->m_stoneIcon->getParent()->convertToWorldSpace(p);
    }
    else if (m_type == Iron) {
        p = node->m_ironIcon->getPosition();
        CCDirector::sharedDirector()->convertToGL(p);
        p2 = node->m_ironIcon->getParent()->convertToWorldSpace(p);
    }else{
        for (int i=0; i<m_dropSprs->count(); i++) {
            CCSprite* spr = dynamic_cast<CCSprite*>(m_dropSprs->objectAtIndex(i));
            if (spr) {
                CCDelayTime* delay = CCDelayTime::create(0.25);
                spr->runAction(CCSequence::create(delay, CCFadeOut::create(0.25),NULL));
            }
        }
        this->scheduleOnce(schedule_selector(DropSacrificeAnim::onDelete), 0.5);
        return;
    }

    CCCallFunc * funcall= CCCallFunc::create(this, callfunc_selector(DropSacrificeAnim::onPlayFlyEnd));
    int count =m_dropSprs->count();
    for (int i=0; i<m_dropSprs->count(); i++) {
        CCSprite* spr = dynamic_cast<CCSprite*>(m_dropSprs->objectAtIndex(i));
        if (spr) {
            CCPoint m_endpoint = spr->getParent()->convertToNodeSpace(p2);
            CCMoveTo* moveToAction = CCMoveTo::create(0.5f/count*(i+1), m_endpoint);
            CCDelayTime* delay = CCDelayTime::create(0.25);
////            spr->runAction(CCFadeOut::create(0.2));
//            CCSequence* action  =CCSequence::create(moveToAction,NULL);
            spr->runAction(CCSequence::create(delay,moveToAction,  CCFadeOut::create(0.2),funcall,NULL));
        }
    }
    this->scheduleOnce(schedule_selector(DropSacrificeAnim::onDelete), 1);
}