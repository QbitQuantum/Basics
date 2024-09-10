bool ButtonControlLayer::onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event)
{
    auto camera = cocos2d::Camera::getVisitingCamera();
    if (_selectedItem != nullptr || !_visible || !camera)
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
        _selectedWithCamera = camera;
        _selectedItem->selected();
        onButtonPressed(_selectedItem->getTag());
        return true;
    }
    
    return false;
}