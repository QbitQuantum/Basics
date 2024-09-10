	void UIScrollLayer::ccTouchMoved(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
	{
		// ÒÆ¶¯
		CCPoint touchPoint = CCDirector::sharedDirector()->convertToGL(pTouch->getLocationInView());

		if(!touchIsInContent(touchPoint) || !m_bVisible)
		{
			return;
		}		

		for (CCNode *c = this->m_pParent; c != NULL; c = c->getParent())
		{
			if (c->isVisible() == false)
			{
				return;
			}
		}

		CCPoint ptbaselayer = m_baseLayer->getPosition();

		if (m_ScrollDir == ESD_Horizontal)
		{
			CCPoint posPoint = CCPointMake(m_baseLayer->getPosition().x + touchPoint.x - m_TouchCurPoint.x, ptbaselayer.y);

			if(abs(touchPoint.x - m_TouchCurPoint.x) > TOUCH_DELTA)
			{
				m_bShouldStolenTouch = true;
			}
			if(abs(touchPoint.x - m_TouchDownPoint.x) > MIN_MOVE_DELTA)
			{
				m_baseLayer->setPosition(posPoint);
			}
		}
		else
		{
			CCPoint posPoint = CCPointMake(ptbaselayer.x, m_baseLayer->getPosition().y + touchPoint.y - m_TouchCurPoint.y);

			if(abs(touchPoint.y - m_TouchCurPoint.y) > TOUCH_DELTA)
			{
				m_bShouldStolenTouch = true;
			}
			if(abs(touchPoint.y - m_TouchDownPoint.y) > MIN_MOVE_DELTA)
			{
				m_baseLayer->setPosition(posPoint);
			}
		}
    
		m_TouchCurPoint = touchPoint;
		m_ScrollStatus = ESS_DRAGGING;
	}