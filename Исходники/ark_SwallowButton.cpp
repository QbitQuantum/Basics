bool ark_SwallowButton::onTouchBegan(Touch *touch, Event *event) {
	if (!ark_engine::instance()->checkIsVisible(this))
	{
		return false;
	}
	dragging = false;
	if (m_isDirty == true)
	{
		for (Node *i = this->getParent();i != NULL;i=i->getParent())
		{
			ScrollView *t = dynamic_cast<ScrollView*>(i);
			if (t)
			{
				this->m_scrollView = t;
				break;
			}
		}
		m_isDirty = false;
	}
	if (this->m_scrollView &&m_scrollView->isTouchEnabled())
	{
		Rect rect = ark_engine::instance()->getViewRect(m_scrollView);
		if (rect.containsPoint(touch->getLocation()))
		{
			return ControlButton::onTouchBegan(touch, event);
		}else
		{
			return false;
		}
	}
	return ControlButton::onTouchBegan(touch, event);
}