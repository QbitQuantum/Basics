bool TextInputWidget::handleKey(int key) {
	bool handled(true);
	
	if (!_hasFocus) return false;
	std::wstring old_input(_input);
	
	int size = static_cast<int>(_input.size());
	
	switch (key) {
	
		case osgGA::GUIEventAdapter::KEY_Left: 
			setCursorPos(_cursorPos - 1);
			break;
		case osgGA::GUIEventAdapter::KEY_Right:
			setCursorPos(_cursorPos + 1);
			break;
		
		case osgGA::GUIEventAdapter::KEY_BackSpace:
			if ((_cursorPos >= size) && (size >=1)) 
			{
				// letztes Zeichen löschen
				_input = _input.substr(0, size - 2);
				setCursorPos(getCursorPosition()-1);
			}
			else if ((_cursorPos >= 0) &&  (_cursorPos < size)) 
			{
				//Zeichen links vom Cursor löschen
				_input = _input.substr(0,_cursorPos)+_input.substr(_cursorPos+1, size);
				setCursorPos(getCursorPosition()-1);
			}
			break;
		case osgGA::GUIEventAdapter::KEY_Delete:
		case osgGA::GUIEventAdapter::KEY_KP_Delete:
			if ((_cursorPos > 0) &&  (_cursorPos < size-1))
				_input = _input.substr(0,_cursorPos+1)+_input.substr(_cursorPos+2, size);
			break;
			
		default:
			if (key >= 0xff00) {
				handled = false;
			} else {
				// std::cout <<"key " << key << std::endl;
				// TODO hande utf?
				if (_cursorPos < size)
					_input.insert(_cursorPos+1, 1, static_cast<char>(key)); 
				else 
					_input += static_cast<char>(key);
				
				_cursorPos++;
			}
	}
	
	if (_input != old_input)
		informAttachedResponder(Actions::valueChanged());
	if (handled)
		update();
	return handled;
}