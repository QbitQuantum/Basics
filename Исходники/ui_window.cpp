bool UIWindow::display(int offsetX, int offsetY) {
	// go exclusive
	if (_mode == WINDOW_EXCLUSIVE || _mode == WINDOW_SYSTEM_EXCLUSIVE) {
		if (!_shieldWindow) {
			_shieldWindow = new UIWindow(_gameRef);
		}
		if (_shieldWindow) {
			_shieldWindow->_posX = _shieldWindow->_posY = 0;
			_shieldWindow->_width = _gameRef->_renderer->getWidth();
			_shieldWindow->_height = _gameRef->_renderer->getHeight();

			_shieldWindow->display();
		}
	} else if (_isMenu) {
		if (!_shieldButton) {
			_shieldButton = new UIButton(_gameRef);
			_shieldButton->setName("close");
			_shieldButton->setListener(this, _shieldButton, 0);
			_shieldButton->_parent = this;
		}
		if (_shieldButton) {
			_shieldButton->_posX = _shieldButton->_posY = 0;
			_shieldButton->setWidth(_gameRef->_renderer->getWidth());
			_shieldButton->setHeight(_gameRef->_renderer->getHeight());

			_shieldButton->display();
		}
	}

	if (!_visible) {
		return STATUS_OK;
	}

	if (_fadeBackground) {
		Graphics::PixelFormat format = _gameRef->_renderer->getPixelFormat();
		byte fadeR, fadeG, fadeB, fadeA;
		// First convert from the internal format to the screen-format
		uint32 fadeColor = format.ARGBToColor(RGBCOLGetA(_fadeColor), RGBCOLGetR(_fadeColor), RGBCOLGetG(_fadeColor), RGBCOLGetB(_fadeColor));
		// Then get components
		format.colorToARGB(fadeColor, fadeA, fadeR, fadeG, fadeB);
		_gameRef->_renderer->fadeToColor(fadeR, fadeG, fadeB, fadeA);
	}

	if (_dragging) {
		_posX += (_gameRef->_mousePos.x - _dragFrom.x);
		_posY += (_gameRef->_mousePos.y - _dragFrom.y);

		_dragFrom.x = _gameRef->_mousePos.x;
		_dragFrom.y = _gameRef->_mousePos.y;
	}

	if (!_focusedWidget || (!_focusedWidget->canFocus() || _focusedWidget->isDisabled() || !_focusedWidget->isVisible())) {
		moveFocus();
	}

	bool popViewport = false;
	if (_clipContents) {
		if (!_viewport) {
			_viewport = new BaseViewport(_gameRef);
		}
		if (_viewport) {
			_viewport->setRect(_posX + offsetX, _posY + offsetY, _posX + _width + offsetX, _posY + _height + offsetY);
			_gameRef->pushViewport(_viewport);
			popViewport = true;
		}
	}


	UITiledImage *back = _back;
	BaseSprite *image = _image;
	BaseFont *font = _font;

	if (!isFocused()) {
		if (_backInactive) {
			back = _backInactive;
		}
		if (_imageInactive) {
			image = _imageInactive;
		}
		if (_fontInactive) {
			font = _fontInactive;
		}
	}

	if (_alphaColor != 0) {
		_gameRef->_renderer->_forceAlphaColor = _alphaColor;
	}
	if (back) {
		back->display(_posX + offsetX, _posY + offsetY, _width, _height);
	}
	if (image) {
		image->draw(_posX + offsetX, _posY + offsetY, _transparent ? nullptr : this);
	}

	if (!BasePlatform::isRectEmpty(&_titleRect) && font && _text) {
		font->drawText((byte *)_text, _posX + offsetX + _titleRect.left, _posY + offsetY + _titleRect.top, _titleRect.right - _titleRect.left, _titleAlign, _titleRect.bottom - _titleRect.top);
	}

	if (!_transparent && !image) {
		_gameRef->_renderer->addRectToList(new BaseActiveRect(_gameRef,  this, nullptr, _posX + offsetX, _posY + offsetY, _width, _height, 100, 100, false));
	}

	for (uint32 i = 0; i < _widgets.size(); i++) {
		_widgets[i]->display(_posX + offsetX, _posY + offsetY);
	}

	if (_alphaColor != 0) {
		_gameRef->_renderer->_forceAlphaColor = 0;
	}

	if (popViewport) {
		_gameRef->popViewport();
	}

	return STATUS_OK;
}