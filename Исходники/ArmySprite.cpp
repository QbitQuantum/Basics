void CArmySprite::enemyUpdate(float fEscapeTime)
{
	switch(m_eCurState)
	{
	case AS_DEFAULT:
		break;
	case AS_MOVE:
		//if (getPosition().y < -getContentSize().height || getPosition().y > mScreenSize.height - BANNER_HEIGHT + getContentSize().height)
		//{
		//	m_eCurState = BS_HIDE;
		//}
		m_fFireCoolTime += fEscapeTime;
		if (m_fFireCoolTime > 2.0f)
		{
			fireBullet(fEscapeTime);
		}
		break;
	case AS_EXPLODE:
		break;
	case AS_HIDE:
		if(getPosition().y < -getContentSize().height * 0.5f)
		{
			getParent()->removeChild(this, true);
		}
		break;
	}

	if (m_eCurState < AS_EXPLODE && m_sCurData.mKind < AK_BUNKER01)
	{
		CCNode *m_pTarget = (CCNode*)(getParent()->getChildByTag(PALYER_TYPE));

		float o = m_pTarget->getPosition().x - getPosition().x;
		float a = m_pTarget->getPosition().y - getPosition().y;
		float at = (float) CC_RADIANS_TO_DEGREES( atanf( o/a) );

		if( a < 0 ) 
		{
			if(  o < 0 )
				at = 180 + fabs(at);
			else
				at = 180 - fabs(at);    
		}
		m_pTurretSprite->setRotation(180 + at);
	}

	if (getPosition().y > -getContentSize().height * 0.5f)
	{
		setPosition(ccpAdd(getPosition(),ccpMult(ccp(0.0f, -1.0f), m_sCurData.mMoveSpeed * fEscapeTime)));
	}
	else
	{
		m_eCurState = AS_HIDE;
	}

	if (!m_bIsNormal)
	{
		m_fFlashTime += fEscapeTime;
		if (m_fFlashTime > 0.1f)
		{
			m_fFlashTime = 0.0f;
			CCRGBAProtocol *pRGBAProtocol = dynamic_cast<CCRGBAProtocol*>(m_pTurretSprite);
			pRGBAProtocol->setColor(color);
			m_bIsNormal = true;
		}
	}
}