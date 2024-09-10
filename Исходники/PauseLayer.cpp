bool PauseLayer::init()
{
    bool ret = false;
    
    do {
        CC_BREAK_IF(!CCLayerColor::initWithColor(ccc4f(255, 0, 0, 50)));
        
        CCArray *array = CCDirector::sharedDirector()->getRunningScene()->getChildren();
        CCObject *object = NULL;
        CCARRAY_FOREACH(array, object)
        {
            CCLayer *layer = (CCLayer*) object;
            layer->onExit();
        }
        
        ret = true;
    } while (0);