void MoveLeft::update(float delta){
    CCNode* parent = (CCNode*)getOwner();
    if (parent == NULL) return;
    
    if ( ((HelloWorld*)parent->getParent())->GameOver )
    {
        parent->stopAllActions();
    }
}