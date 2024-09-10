bool PerfectMenu::onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event)
{
    if (isTouched||_state != Menu::State::WAITING || ! _visible || !_enabled)
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
    
    _selectedItem = this->getItemForTouch(touch);
    if (_selectedItem)
    {
        _state = Menu::State::TRACKING_TOUCH;
        _selectedItem->selected();
        isTouched = true;
        return true;
    }
    
    return false;
}