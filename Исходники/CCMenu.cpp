bool Menu::onTouchBegan(Touch* touch, Event* event)
{
    auto camera = Camera::getVisitingCamera();
    if (_state != Menu::State::WAITING || ! _visible || !_enabled || !camera)
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
    _selectedItem = this->getItemForTouch(touch, camera);

    if (_selectedItem)
    {
        _state = Menu::State::TRACKING_TOUCH;
        _selectedWithCamera = camera;
        _selectedItem->selected();
        
        return true;
    }
    
    return false;
}