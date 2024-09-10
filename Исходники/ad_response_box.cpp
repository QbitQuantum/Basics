bool AdResponseBox::display() {
    Rect32 rect = _responseArea;
    if (_window) {
        rect.offsetRect(_window->_posX, _window->_posY);
        //_window->display();
    }

    int xxx, yyy;
    uint32 i;

    xxx = rect.left;
    yyy = rect.top;

    // shift down if needed
    if (!_horizontal) {
        int totalHeight = 0;
        for (i = 0; i < _respButtons.size(); i++) {
            totalHeight += (_respButtons[i]->_height + _spacing);
        }
        totalHeight -= _spacing;

        switch (_verticalAlign) {
        case VAL_BOTTOM:
            if (yyy + totalHeight < rect.bottom) {
                yyy = rect.bottom - totalHeight;
            }
            break;

        case VAL_CENTER:
            if (yyy + totalHeight < rect.bottom) {
                yyy += ((rect.bottom - rect.top) - totalHeight) / 2;
            }
            break;

        case VAL_TOP:
            // do nothing
            break;
        }
    }

    // prepare response buttons
    bool scrollNeeded = false;
    for (i = _scrollOffset; i < _respButtons.size(); i++) {
        if ((_horizontal && xxx + _respButtons[i]->_width > rect.right)
                || (!_horizontal && yyy + _respButtons[i]->_height > rect.bottom)) {

            scrollNeeded = true;
            _respButtons[i]->_visible = false;
            break;
        }

        _respButtons[i]->_visible = true;
        _respButtons[i]->_posX = xxx;
        _respButtons[i]->_posY = yyy;

        if (_horizontal) {
            xxx += (_respButtons[i]->_width + _spacing);
        } else {
            yyy += (_respButtons[i]->_height + _spacing);
        }
    }

    // show appropriate scroll buttons
    if (_window) {
        _window->showWidget("prev", _scrollOffset > 0);
        _window->showWidget("next", scrollNeeded);
    }

    // go exclusive
    if (_shieldWindow) {
        _shieldWindow->_posX = _shieldWindow->_posY = 0;
        _shieldWindow->_width = _gameRef->_renderer->getWidth();
        _shieldWindow->_height = _gameRef->_renderer->getHeight();

        _shieldWindow->display();
    }

    // display window
    if (_window) {
        _window->display();
    }


    // display response buttons
    for (i = _scrollOffset; i < _respButtons.size(); i++) {
        _respButtons[i]->display();
    }

    return STATUS_OK;
}