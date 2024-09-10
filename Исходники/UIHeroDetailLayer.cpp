void UIHeroDetailLayer::onTouchMoved( cocos2d::Touch* touch, cocos2d::Event* event ) {
    if( _is_touch_down ) {
        Point pos = this->convertTouchToNodeSpace( touch );
        if( !_is_dragging ) {
            Sprite* new_equip_icon = nullptr;
            if( _selected_equiped_cell != nullptr &&_selected_equiped_cell->getEquipData() != nullptr ) {
                if( pos.distance( _touch_down_pos ) > MIN_DRAG_BIAS ) {
                    _is_dragging = true;
                    new_equip_icon = _selected_equiped_cell->getEquipSprite();
                }
            }
            else if( _selected_repo_cell != nullptr && _selected_repo_cell->getEquipData() != nullptr ) {
                if( pos.distance( _touch_down_pos ) > MIN_DRAG_BIAS ) {
                    _is_dragging = true;
                    new_equip_icon = _selected_repo_cell->getEquipSprite();
                }
            }
            if( new_equip_icon != nullptr ) {
                if( _drag_equip == nullptr ) {
                    _drag_equip = Sprite::createWithSpriteFrame( new_equip_icon->getSpriteFrame() );
                    this->addChild( _drag_equip, 10 );
                }
                _drag_equip->setVisible( true );
                _drag_equip->setSpriteFrame( new_equip_icon->getSpriteFrame() );
                _drag_equip->setPosition( pos );
            }
        }
        else {
            _drag_equip->setPosition( pos );
            this->checkTargetCell();
        }
    }
}