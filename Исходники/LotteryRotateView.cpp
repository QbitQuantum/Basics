CCRect LotteryRotateView::getViewRect()
{
    CCSize size = getPanelChild()->getContentSize();
    CCPoint screenPos = this->convertToWorldSpace(CCPointZero);
    
    float scaleX = this->getScaleX();
    float scaleY = this->getScaleY();
    
    for (CCNode *p = _parent; p != NULL; p = p->getParent()) {
        scaleX *= p->getScaleX();
        scaleY *= p->getScaleY();
    }
    
    if(scaleX<0.f) {
        screenPos.x += size.width*scaleX;
        scaleX = -scaleX;
    }
    
    if(scaleY<0.f) {
        screenPos.y += size.height*scaleY;
        scaleY = -scaleY;
    }

    return CCRectMake(getPanelChild()->getPositionX() - size.width/2, getPanelChild()->getPositionY() - size.height/2, size.width, size.height);
}