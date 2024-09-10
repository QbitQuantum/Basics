void SpriteDecorationBatchNode::RemoveShadow(CCNode* pNode)
{
	if (pNode)
	{
		std::map<CCNode*,CCSprite*>::iterator iter = m_playerShadows.find(pNode);
		if (iter != m_playerShadows.end())
		{
			CCSprite* pShadowSprite = (*iter).second;
			if (pShadowSprite)
			{
				CCNode* pParentNode = pShadowSprite->getParent();
				if (pParentNode)
				{
					pParentNode->removeChild(pShadowSprite);
				}
			}
			m_playerShadows.erase(iter);
		}
	}
}