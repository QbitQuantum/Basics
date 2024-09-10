void CGameMessage::showHp()
{
	int iHp = CGameManager::getPlayer()->getHp();
	int iHpMax = CGameManager::getPlayer()->getHpMax();
	CCRect rect;
	rect.setRect(m_fMinX, m_fMinY, m_iWidth*(float)iHp/iHpMax, m_iHeight);
	m_pHp->setTextureRect(rect);
}