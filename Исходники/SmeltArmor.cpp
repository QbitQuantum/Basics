void CSmeltArmor::initFire()
{
	//获取参考位置
	CCNode* pNode = (CCNode*)m_ui->findWidgetById("fire_circle");
	CCPoint pPos = ccp(pNode->getPositionX()+15, pNode->getPositionY()+75);

	if(m_pFire1 == nullptr)
	{
		CCAnimation* pAnimation = AnimationManager::sharedAction()->getAnimation("9010");
		pAnimation->setDelayPerUnit(0.15f);
		m_pFire1 = CCSprite::create("skill/9010.png");
		m_pFire1->setPosition(pPos);
		m_pFire1->runAction(CCRepeatForever::create(CCAnimate::create(pAnimation)));
		m_pFire1->setVisible(false);
		m_pFire1->setScale(1.6f);
		pNode->getParent()->addChild(m_pFire1, pNode->getZOrder());
	}
	if(m_pFire2 == nullptr)
	{
		CCAnimation* pAnimation = AnimationManager::sharedAction()->getAnimation("9011");
		pAnimation->setDelayPerUnit(0.15f);
		m_pFire2 = CCSprite::create("skill/9011.png");
		m_pFire2->setPosition(pPos);
		m_pFire2->runAction(CCRepeatForever::create(CCAnimate::create(pAnimation)));
		m_pFire2->setVisible(false);
		m_pFire2->setScale(1.5f);
		pNode->getParent()->addChild(m_pFire2, pNode->getZOrder());
	}
}