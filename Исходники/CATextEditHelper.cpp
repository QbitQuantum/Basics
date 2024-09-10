bool CATextArrowView::ccTouchBegan(CATouch *pTouch, CAEvent *pEvent)
{
	CCPoint point = this->convertTouchToNodeSpace(pTouch);

	CCRect newRectR = m_pArrowView->getFrame();
	newRectR.InflateRect(5);

	if (!newRectR.containsPoint(point))
	{
        hideTextArrView();
        return false;
	}
	
    m_isBtnPress = true;
	return true;
}