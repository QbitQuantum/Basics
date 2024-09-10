bool AgiEngine::predictiveDialog() {
	int key = 0, active = -1, lastactive = 0;
	bool rc = false;
	uint8 x;
	int y;
	int bx[17], by[17];
	Common::String prefix;
	char temp[MAXWORDLEN + 1], repeatcount[MAXWORDLEN];
	AgiBlock tmpwindow;
	bool navigationwithkeys = false;
	bool processkey;

	const char *buttonStr[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9", "0" };
	const char *buttons[] = {
		"(1)'-.&",  "(2)abc", "(3)def",
		"(4)ghi",  "(5)jkl", "(6)mno",
		"(7)pqrs", "(8)tuv", "(9)wxyz",
		"(#)next",    "add",
		"<",
		"Cancel",  "OK",
		"Pre", "(0) ", NULL
	};
	const int colors[] = {
		15, 0, 15, 0, 15, 0,
		15, 0, 15, 0, 15, 0,
		15, 0, 15, 0, 15, 0,
		15, 12, 15, 12,
		15, 0,
		15, 0, 15, 0,
		14, 0, 15, 0, 0, 0
	};
	const char *modes[] = { "(*)Pre", "(*)123", "(*)Abc" };

	// FIXME: Move this to a more appropriate place.
	if (!_predictiveDictText) {
		loadDict();
		if (!_predictiveDictText)
			return false;
	}
	_predictiveDictActLine = NULL;
	uint8 numMatchingWords = 0;

	_predictiveDialogRunning = true;
	_system->setFeatureState(OSystem::kFeatureDisableKeyFiltering, true);

	memset(repeatcount, 0, sizeof(repeatcount));

	// show the predictive dialog.
	// if another window is already in display, save its state into tmpwindow
	memset(&tmpwindow, 0, sizeof(tmpwindow));
	tmpwindow.active = false;
	if (_game.window.active)
		memcpy(&tmpwindow, &(_game.window), sizeof(AgiBlock));
	drawWindow(50, 40, 269, 159);
	_gfx->drawRectangle(62, 54, 249, 66, MSG_BOX_TEXT);
	_gfx->flushBlock(62, 54, 249, 66);

	bx[15] = 73; // Zero/space
	by[15] = 120;
	bx[9] = 110; // next
	by[9] = 120;
	bx[10] = 172; // add
	by[10] = 120;
	bx[14] = 200; // Mode
	by[14] = 120;
	bx[11] = 252; // Backspace
	by[11] = 57;
	bx[12] = 180; // Cancel
	by[12] = 140;
	bx[13] = 240; // OK
	by[13] = 140;

	x = 73;
	y = 75;
	for (int i = 0; i < 9; i++) {
		bx[i] = x;
		by[i] = y;
		x += 60;
		if (i % 3 == 2) {
			y += 15;
			x = 73;
		}
	}

	clearKeyQueue();

	prefix.clear();
	_currentCode.clear();
	_currentWord.clear();
	_wordNumber = 0;

	int mode = kModePre;

	bool needRefresh = true;

	for (;;) {
		if (needRefresh) {
			for (int i = 0; buttons[i]; i++) {
				int color1 = colors[i * 2];
				int color2 = colors[i * 2 + 1];

				if (i == 9 && !((mode != kModeAbc && _predictiveDictActLine && numMatchingWords > 1)
							|| (mode == kModeAbc && _currentWord.size() && _currentWord.lastChar() != ' '))) { // Next
					color2 = 7;
				}

				// needs fixing, or remove it!
				bool _addIsActive = false; // FIXME: word adding is not implemented
				if (i == 10 && !_addIsActive) { // Add
					color2 = 7;
				}
				if (i == 14) {
					_gfx->drawDefaultStyleButton(bx[i], by[i], modes[mode], i == active, 0, color1, color2);
				} else {
					_gfx->drawDefaultStyleButton(bx[i], by[i], buttons[i], i == active, 0, color1, color2);
				}
			}

			Common::strlcpy(temp, prefix.c_str(), sizeof(temp));
			Common::strlcat(temp, _currentWord.c_str(), sizeof(temp));

			for (int i = prefix.size() + _currentCode.size(); i < MAXWORDLEN; i++)
				temp[i] = ' ';
			temp[MAXWORDLEN] = 0;

			printText(temp, 0, 8, 7, MAXWORDLEN, 15, 0);
			_gfx->flushBlock(62, 54, 249, 66);

			if (active >= 0 && !navigationwithkeys) {
				// provide visual feedback only when not navigating with the arrows
				// so that the user can see the active button.
				active = -1;
				needRefresh = true;
			} else
				needRefresh = false;

			_gfx->doUpdate();
		}

		pollTimer();
		key = doPollKeyboard();
		processkey = false;
		switch (key) {
		case KEY_ENTER:
			if (navigationwithkeys) {
				// when the user has utilized arrow key navigation,
				// interpret enter as 'click' on the active button
				active = lastactive;
			} else {
				// else it is a shortcut for 'Ok'
				active = 13;
			}
			processkey = true;
			break;
		case KEY_ESCAPE:
			rc = false;
			goto getout;
		case BUTTON_LEFT:
			navigationwithkeys = false;
			for (int i = 0; buttons[i]; i++) {
				if (_gfx->testButton(bx[i], by[i], buttons[i])) {
					active = i;
					processkey = true;
					break;
				}
			}
			break;
		case KEY_BACKSPACE:
			active = 11;
			processkey = true;
			break;
		case '#':
			active = 9;
			processkey = true;
			break;
		case '*':
			active = 14;
			processkey = true;
			break;
		case 0x09:	// Tab
			navigationwithkeys = true;
			debugC(3, kDebugLevelText, "Focus change");
			lastactive = active = lastactive + 1;
			active %= ARRAYSIZE(buttons) - 1;
			needRefresh = true;
			break;
		case KEY_LEFT:
			navigationwithkeys = true;
			if (lastactive == 0 || lastactive == 3 || lastactive == 6)
				active = lastactive + 2;
			else if (lastactive == 9)
				active = 15;
			else if (lastactive == 11)
				active = 11;
			else if (lastactive == 12)
				active = 13;
			else if (lastactive == 14)
				active = 10;
			else
				active = lastactive - 1;
			lastactive = active;
			needRefresh = true;
			break;
		case KEY_RIGHT:
			navigationwithkeys = true;
			if (lastactive == 2 || lastactive == 5 || lastactive == 8)
				active = lastactive - 2;
			else if (lastactive == 10)
				active = 14;
			else if (lastactive == 11)
				active = 11;
			else if (lastactive == 13)
				active = 12;
			else if (lastactive == 15)
				active = 9;
			else
				active = lastactive + 1;
			lastactive = active;
			needRefresh = true;
			break;
		case KEY_UP:
			navigationwithkeys = true;
			if (lastactive <= 2)
				active = 11;
			else if (lastactive == 9 || lastactive == 10)
				active = lastactive - 2;
			else if (lastactive == 11)
				active = 13;
			else if (lastactive == 14)
				active = 8;
			else if (lastactive == 15)
				active = 6;
			else
				active = lastactive - 3;
			lastactive = active;
			needRefresh = true;
			break;
		case KEY_DOWN:
			navigationwithkeys = true;
			if (lastactive == 6)
				active = 15;
			else if (lastactive == 7 || lastactive == 8)
				active = lastactive + 2;
			else if (lastactive == 11)
				active = 0;
			else if (lastactive == 12 || lastactive == 13)
				active = 11;
			else if (lastactive == 14 || lastactive == 15)
				active = lastactive - 2;
			else
				active = lastactive + 3;
			lastactive = active;
			needRefresh = true;
			break;
		default:
			// handle numeric buttons
			if (key >= '1' && key <= '9') {
				active = key - '1';
				processkey = true;
			} else if (key == '0') {
				active = 15;
				processkey = true;
			}
			break;
		}

		if (processkey) {
			if (active >= 0) {
				needRefresh = true;
				lastactive = active;
				if (active == 15 && mode != kModeNum) { // Space
					// bring MRU word at the top of the list when changing words
					if (mode == kModePre && _predictiveDictActLine && numMatchingWords > 1 && _wordNumber != 0)
						bringWordtoTop(_predictiveDictActLine, _wordNumber);
					strncpy(temp, _currentWord.c_str(), _currentCode.size());
					temp[_currentCode.size()] = 0;
					prefix += temp;
					prefix += " ";
					_currentCode.clear();
					_currentWord.clear();
					numMatchingWords = 0;
					memset(repeatcount, 0, sizeof(repeatcount));
				} else if (active < 9 || active == 11 || active == 15) { // number or backspace
					if (active == 11) { // backspace
						if (_currentCode.size()) {
							repeatcount[_currentCode.size() - 1] = 0;
							_currentCode.deleteLastChar();
						} else {
							if (prefix.size())
								prefix.deleteLastChar();
						}
					} else if (prefix.size() + _currentCode.size() < MAXWORDLEN - 1) { // don't overflow the dialog line
						if (active == 15) { // zero
							_currentCode += buttonStr[9];
						} else {
							_currentCode += buttonStr[active];
						}
					}

					switch (mode) {
					case kModeNum:
						_currentWord = _currentCode;
						break;
					case kModePre:
						if (!matchWord() && _currentCode.size()) {
							_currentCode.deleteLastChar();
							matchWord();
						}
						numMatchingWords = countWordsInString(_predictiveDictActLine);
						break;
					case kModeAbc:
						for (x = 0; x < _currentCode.size(); x++)
							if (_currentCode[x] >= '1')
								temp[x] = buttons[_currentCode[x] - '1'][3 + repeatcount[x]];
						temp[_currentCode.size()] = 0;
						_currentWord = temp;
					}
				} else if (active == 9) { // next
					if (mode == kModePre) {
						if (_predictiveDictActLine && numMatchingWords > 1) {
							_wordNumber = (_wordNumber + 1) % numMatchingWords;
							char tmp[MAXLINELEN];
							strncpy(tmp, _predictiveDictActLine, MAXLINELEN);
							tmp[MAXLINELEN - 1] = 0;
							char *tok = strtok(tmp, " ");
							for (uint8 i = 0; i <= _wordNumber; i++)
								tok = strtok(NULL, " ");
							_currentWord = Common::String(tok, _currentCode.size());
						}
					} else if (mode == kModeAbc){
						x = _currentCode.size();
						if (x) {
							if (_currentCode.lastChar() == '1' || _currentCode.lastChar() == '7' || _currentCode.lastChar() == '9')
								repeatcount[x - 1] = (repeatcount[x - 1] + 1) % 4;
							else
								repeatcount[x - 1] = (repeatcount[x - 1] + 1) % 3;
							if (_currentCode.lastChar() >= '1')
								_currentWord.setChar(buttons[_currentCode[x - 1] - '1'][3 + repeatcount[x - 1]], x-1);
						}
					}
				} else if (active == 10) { // add
					debug(0, "add");
				} else if (active == 13) { // Ok
					// bring MRU word at the top of the list when ok'ed out of the dialog
					if (mode == kModePre && _predictiveDictActLine && numMatchingWords > 1 && _wordNumber != 0)
						bringWordtoTop(_predictiveDictActLine, _wordNumber);
					rc = true;
					goto press;
				} else if (active == 14) { // Mode
					mode++;
					if (mode > kModeAbc)
						mode = kModePre;

					// truncate current input at mode change
					strncpy(temp, _currentWord.c_str(), _currentCode.size());
					temp[_currentCode.size()] = 0;
					prefix += temp;
					_currentCode.clear();
					_currentWord.clear();
					memset(repeatcount, 0, sizeof(repeatcount));
				} else {
					goto press;
				}
			}
		}
	}

 press:
	Common::strlcpy(_predictiveResult, prefix.c_str(), sizeof(_predictiveResult));
	Common::strlcat(_predictiveResult, _currentWord.c_str(), sizeof(_predictiveResult));

 getout:
	// if another window was shown, bring it up again
	if (!tmpwindow.active)
		closeWindow();
	else {
		_gfx->restoreBlock(_game.window.x1, _game.window.y1,
				_game.window.x2, _game.window.y2, _game.window.buffer);

		free(_game.window.buffer);
		memcpy(&(_game.window), &tmpwindow, sizeof(AgiBlock));
		_gfx->doUpdate();
	}

	_system->setFeatureState(OSystem::kFeatureDisableKeyFiltering, false);
	_predictiveDialogRunning = false;

	return rc;
}