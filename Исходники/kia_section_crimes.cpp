void KIASectionCrimes::draw(Graphics::Surface &surface) {
	const char *text = nullptr;
	if (_suspectPhotoShapeId != -1) {
		_suspectPhotoShape->draw(surface, 201 - _suspectPhotoShape->getWidth() / 2, 223 - _suspectPhotoShape->getHeight() / 2);
	}
	if (_suspectPhotoShapeId == 14 || _suspectPhotoShapeId == 13) {
		text = _vm->_textKIA->getText(49);
		_vm->_mainFont->drawColor(text, surface, 201 - _vm->_mainFont->getTextWidth(text) / 2, 218, 0x7FFF);
	}

	surface.fillRect(Common::Rect(120, 134, 250, 145), 0);
	surface.hLine(120, 133, 250, 0x18A5);
	surface.hLine(120, 146, 250, 0x2D4C);
	surface.vLine(119, 134, 145, 0x18A5);
	surface.vLine(251, 134, 145, 0x2D4C);
	surface.hLine(251, 146, 251, 0x2509);

	if (_crimeSelected == -1) {
		text = _vm->_textKIA->getText(49);
	} else {
		text = _vm->_textCrimes->getText(_crimeSelected);
	}

	_vm->_mainFont->drawColor(text, surface, 185 - _vm->_mainFont->getTextWidth(text) / 2, 136, 0x46BF);

	surface.fillRect(Common::Rect(136, 304, 266, 315), 0);
	surface.hLine(136, 303, 266, 0x18A5);
	surface.hLine(136, 316, 266, 0x2D4C);
	surface.vLine(135, 304, 315, 0x18A5);
	surface.vLine(267, 304, 315, 0x2D4C);
	surface.hLine(267, 316, 267, 0x2509);

	char generatedText[64];
	if (_suspectSelected == -1) {
		text = _vm->_textKIA->getText(22);
	} else {
		const char *suspectName = _vm->_suspectsDatabase->get(_suspectSelected)->getName();
		if (_suspectsWithIdentity[_suspectSelected]) {
			text = suspectName;
		} else if (_vm->_suspectsDatabase->get(_suspectSelected)->getSex()) {
			sprintf(generatedText, "%s %s", _vm->_textKIA->getText(20), KIASectionSuspects::scrambleSuspectsName(suspectName));
			text = generatedText;
		} else {
			sprintf(generatedText, "%s %s", _vm->_textKIA->getText(21), KIASectionSuspects::scrambleSuspectsName(suspectName));
			text = generatedText;
		}
	}
	_vm->_mainFont->drawColor(text, surface, 201 - _vm->_mainFont->getTextWidth(text) / 2, 306, 0x46BF);

	_uiContainer->draw(surface);
	_buttons->draw(surface);
	_buttons->drawTooltip(surface, _mouseX, _mouseY);
}