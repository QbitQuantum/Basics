void UITextInput::onKeyDown(PolyKEY key, wchar_t charCode) {
	
	if(!hasFocus)
		return;
	
	
//	Logger::log("UCHAR: %d\n", charCode);	
	
	CoreInput *input = CoreServices::getInstance()->getCore()->getInput();	

	if(key == KEY_a && (input->getKeyState(KEY_LSUPER) || input->getKeyState(KEY_RSUPER))) {
		selectAll();
		return;
	}

	if(key == KEY_c && (input->getKeyState(KEY_LSUPER) || input->getKeyState(KEY_RSUPER))) {
		CoreServices::getInstance()->getCore()->copyStringToClipboard(getSelectionText());
		return;
	}

	if(key == KEY_x && (input->getKeyState(KEY_LSUPER) || input->getKeyState(KEY_RSUPER))) {
		return;
	}

	if(key == KEY_v && (input->getKeyState(KEY_LSUPER) || input->getKeyState(KEY_RSUPER))) {
		insertText(CoreServices::getInstance()->getCore()->getClipboardString());
		return;
	}	
	
	
	if(key == KEY_LEFT) {
		if(input->getKeyState(KEY_LSUPER) || input->getKeyState(KEY_RSUPER)) {
			if(input->getKeyState(KEY_LSHIFT) || input->getKeyState(KEY_RSHIFT)) {
				if(hasSelection) {
					setSelection(this->lineOffset, selectionLine, this->caretPosition, 0);					
				} else {
					setSelection(this->lineOffset, this->lineOffset, this->caretPosition, 0);
				}
			} else {
				caretPosition = 0;
				clearSelection();				
				updateCaretPosition();
			}
		} else if (input->getKeyState(KEY_LALT) || input->getKeyState(KEY_RALT)) {
			if(input->getKeyState(KEY_LSHIFT) || input->getKeyState(KEY_RSHIFT)) {
				if(hasSelection) {
					setSelection(this->lineOffset, selectionLine, this->caretPosition, caretSkipWordBack(selectionLine, selectionCaretPosition));
				} else {
					setSelection(this->lineOffset, this->lineOffset, this->caretPosition, caretSkipWordBack(this->lineOffset, caretPosition));					
				}
			} else {				
				caretPosition = caretSkipWordBack(this->lineOffset,caretPosition);
				clearSelection();				
				updateCaretPosition();			
			}
		} else {
			if(caretPosition > 0) {
				if(input->getKeyState(KEY_LSHIFT) || input->getKeyState(KEY_RSHIFT)) {
					if(hasSelection) {
						if(selectionCaretPosition > 0)
							setSelection(this->lineOffset, selectionLine, this->caretPosition, selectionCaretPosition-1);
					} else {
						setSelection(this->lineOffset, this->lineOffset, this->caretPosition, caretPosition-1);					
					}					
				} else {									
					caretPosition--;
					clearSelection();					
					updateCaretPosition();
				}
			}
		}
		return;
	}
	
	if(key == KEY_RIGHT) {
		if(caretPosition < currentLine->getText().length()) {			
			if(input->getKeyState(KEY_LSUPER) || input->getKeyState(KEY_RSUPER)) {
				if(input->getKeyState(KEY_LSHIFT) || input->getKeyState(KEY_RSHIFT)) {
					if(hasSelection) {
						setSelection(this->lineOffset, selectionLine, this->caretPosition, lines[selectionLine]->getText().length());					
					} else {
						setSelection(this->lineOffset, this->lineOffset, this->caretPosition, currentLine->getText().length());
					}
				} else {
					caretPosition = currentLine->getText().length();
					clearSelection();
				}				
			} else if (input->getKeyState(KEY_LALT) || input->getKeyState(KEY_RALT)) {
				if(input->getKeyState(KEY_LSHIFT) || input->getKeyState(KEY_RSHIFT)) {
					if(hasSelection) {
						setSelection(this->lineOffset, selectionLine, this->caretPosition, caretSkipWordForward(selectionLine, selectionCaretPosition));
					} else {
						setSelection(this->lineOffset, this->lineOffset, this->caretPosition, caretSkipWordForward(this->lineOffset, caretPosition));					
					}
				} else {				
					caretPosition = caretSkipWordForward(this->lineOffset,caretPosition);
					clearSelection();					
				}				
			} else {
				if(input->getKeyState(KEY_LSHIFT) || input->getKeyState(KEY_RSHIFT)) {
					if(hasSelection) {
						setSelection(this->lineOffset, selectionLine, this->caretPosition, selectionCaretPosition+1);
					} else {
						setSelection(this->lineOffset, this->lineOffset, this->caretPosition, caretPosition+1);					
					}					
				} else {									
					caretPosition++;
					clearSelection();					
				}				
			}
			updateCaretPosition();			
		}
		return;
	}
	
	if(key == KEY_UP) {		
		if(multiLine) {
			if(input->getKeyState(KEY_LSHIFT) || input->getKeyState(KEY_RSHIFT)) {			
				if(hasSelection) {
					if(selectionLine > 0)
						setSelection(this->lineOffset, selectionLine-1, this->caretPosition, selectionCaretPosition);
				} else {
					if(this->lineOffset > 0)					
						setSelection(this->lineOffset, this->lineOffset-1, this->caretPosition, caretPosition);					
				}				
			} else {
				clearSelection();				
				if(lineOffset > 0) {
					lineOffset--;
					selectLineFromOffset();
					updateCaretPosition();							
				}
			}
		}
		blinkerRect->visible  = true;
		return;
	}
	
	if(key == KEY_DOWN) {
		if(multiLine) {
			if(input->getKeyState(KEY_LSHIFT) || input->getKeyState(KEY_RSHIFT)) {			
				if(hasSelection) {
					if(selectionLine < lines.size()-1)
						setSelection(this->lineOffset, selectionLine+1, this->caretPosition, selectionCaretPosition);
				} else {
					if(this->lineOffset < lines.size()-1)					
						setSelection(this->lineOffset, this->lineOffset+1, this->caretPosition, caretPosition);					
				}				
			} else {				
				clearSelection();
				if(lineOffset < lines.size()-1) {
					lineOffset++;
					selectLineFromOffset();
					updateCaretPosition();										
				}
			}
		}
		blinkerRect->visible  = true;		
		return;
	}
	
	
	if(key == KEY_RETURN) {
		if(hasSelection)
			deleteSelection();		
		if(multiLine) {
			insertLine(true);
			updateCaretPosition();
		}
		return;
	}	
	
	String ctext = currentLine->getText();
	
	
//	if(1) {
	if((charCode > 31 && charCode < 127) || charCode > 127) {	
		if(!isNumberOnly || (isNumberOnly && (charCode > 47 && charCode < 58))) {
			if(hasSelection)
				deleteSelection();
			ctext = currentLine->getText();		
			String text2 = ctext.substr(caretPosition, ctext.length()-caretPosition);
			ctext = ctext.substr(0,caretPosition);
			ctext += charCode + text2;
			caretPosition++;
		}
	}
	
	if(key == KEY_TAB && multiLine) {
		if(hasSelection)
			deleteSelection();		
		ctext = currentLine->getText();				
		String text2 = ctext.substr(caretPosition, ctext.length()-caretPosition);
		ctext = ctext.substr(0,caretPosition);
		ctext += (wchar_t)'\t' + text2;
		caretPosition++;		
	}
	
	if(key == KEY_BACKSPACE) {
		if(hasSelection) {
			deleteSelection();
			return;
		} else {
		ctext = currentLine->getText();					
		if(caretPosition > 0) {
			if(ctext.length() > 0) {
				String text2 = ctext.substr(caretPosition, ctext.length()-caretPosition);
				ctext = ctext.substr(0,caretPosition-1);
				ctext += text2;
				caretPosition--;
			}
		} else {
			if(lineOffset > 0) {
				ScreenLabel *lineToRemove = currentLine;
				lineOffset--;
				selectLineFromOffset();
				caretPosition = currentLine->getText().length();
				updateCaretPosition();
				currentLine->setText(currentLine->getText() + ctext);	
				removeLine(lineToRemove);				
				return;
			}
		}
		}
	}
	
	currentLine->setText(ctext);	
	dispatchEvent(new UIEvent(), UIEvent::CHANGE_EVENT);	
	updateCaretPosition();
}