 bool MyAboutLayer::init()
 {
	CCArray *array = CCDirector::sharedDirector()->getRunningScene()->getChildren();  
	CCObject *object = NULL;  
	int i=0;
	CCARRAY_FOREACH(array, object)  
	{  
		i++;
		CCLayer *layer = (CCLayer*) object;  
		layer->onExit();  
	}  