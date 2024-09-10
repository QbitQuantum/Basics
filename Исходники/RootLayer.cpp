CCObject *HTouchEnabledLayerColor::dismissNodeEx(int command, HEndDismissNode *notify) {
    CCNode *node = notify->getNode();
    do {
        if (node->getParent() != this) break;
        HBakNodeInfo *info = NULL;
        for (int i = m_pBakNodeList->count() - 1; i >= 0; --i) {
            info = (HBakNodeInfo *)m_pBakNodeList->objectAtIndex(i);
            if (node == info->m_pNode) {
                break;
            }
            info = NULL;
        }
        if (!info) break;
        
        node->retain();
        node->removeFromParentAndCleanup(false);
        info->m_pParent->addChild(node, info->m_iIndex);
        node->setScaleX(info->m_fScaleX);
        node->setScaleY(info->m_fScaleY);
        node->setPosition(info->m_ptPos);
        node->release();
        
        restoreAllPriorities(info);
        m_pBakNodeList->removeObject(info);
    } while (false);
    if (notify->getTarget() && notify->getAction()) {
        (notify->getTarget()->*notify->getAction())(node);
    }
    return NULL;
}