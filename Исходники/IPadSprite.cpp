void IPadSprite::ccTouchEnded(CCTouch* touch, CCEvent* event)
{
	CCNode* pNode = this->getParent();
	CCNode* pNode1 = this;
	while(pNode->getParent() != NULL)
	{
		pNode1 = pNode;
		pNode = pNode->getParent();
	}
	MainScene* pScene = dynamic_cast<MainScene*>(pNode1);
	if(pScene)
	{
		pScene->hideMenu();
	}
	
	MS5Layer* pLayer = dynamic_cast<MS5Layer*>(this->getParent());
	if(pLayer)
		pLayer->hidePopupPanel();
		
	this->setIsVisible(false);
	pNode = this->getParent();
	pNode = pNode->getParent();
	
	if(pNode->getChildByTag(TAG_IPAD_BIG) == NULL)
	{
		ScaleSprite* pSprite = ScaleSprite::scaleSpriteWithFile("ipad_big.png");
		pSprite->setTag(TAG_IPAD_BIG);
		pSprite->setScale(0.24f);
		pSprite->setPosition( ccp(855, 420) );
		pNode->addChild(pSprite, 2);
		pSprite->startScale();
	}
} 