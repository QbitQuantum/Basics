bool AdInventoryBox::display() {
	AdGame *adGame = (AdGame *)_gameRef;

	if (!_visible) {
		return STATUS_OK;
	}

	int itemsX, itemsY;
	itemsX = (int)floor((float)((_itemsArea.right - _itemsArea.left + _spacing) / (_itemWidth + _spacing)));
	itemsY = (int)floor((float)((_itemsArea.bottom - _itemsArea.top + _spacing) / (_itemHeight + _spacing)));

	if (_window) {
		_window->enableWidget("prev", _scrollOffset > 0);
		_window->enableWidget("next", _scrollOffset + itemsX * itemsY < (int32)adGame->_inventoryOwner->getInventory()->_takenItems.size());
	}


	if (_closeButton) {
		_closeButton->_posX = _closeButton->_posY = 0;
		_closeButton->setWidth(_gameRef->_renderer->getWidth());
		_closeButton->setHeight(_gameRef->_renderer->getHeight());

		_closeButton->display();
	}


	// display window
	Rect32 rect = _itemsArea;
	if (_window) {
		rect.offsetRect(_window->_posX, _window->_posY);
		_window->display();
	}

	// display items
	if (_window && _window->_alphaColor != 0) {
		_gameRef->_renderer->_forceAlphaColor = _window->_alphaColor;
	}
	int yyy = rect.top;
	for (int j = 0; j < itemsY; j++) {
		int xxx = rect.left;
		for (int i = 0; i < itemsX; i++) {
			int itemIndex = _scrollOffset + j * itemsX + i;
			if (itemIndex >= 0 && itemIndex < (int32)adGame->_inventoryOwner->getInventory()->_takenItems.size()) {
				AdItem *item = adGame->_inventoryOwner->getInventory()->_takenItems[itemIndex];
				if (item != ((AdGame *)_gameRef)->_selectedItem || !_hideSelected) {
					item->update();
					item->display(xxx, yyy);
				}
			}

			xxx += (_itemWidth + _spacing);
		}
		yyy += (_itemHeight + _spacing);
	}
	if (_window && _window->_alphaColor != 0) {
		_gameRef->_renderer->_forceAlphaColor = 0;
	}

	return STATUS_OK;
}