bool ScrollMenu::onTouchBegan(Touch* touch, Event* event)
{
	if (_state != Menu::State::WAITING || !_visible || !_enabled)
	{
		return false;
	}

	for (Node *c = this->_parent; c != nullptr; c = c->getParent())
	{
		if (c->isVisible() == false)
		{
			return false;
		}
	}

	m_iStartPos = touch->getLocation();
	if (m_iEffectiveRange.containsPoint(m_iStartPos))
	{
		m_bTouchMoved = false;
		_selectedItem = this->getItemForTouch(touch);
		if (_selectedItem)
		{
			_state = Menu::State::TRACKING_TOUCH;
			_selectedItem->selected();

			return true;
		}
	}


	return false;
}