/*
================
DialogDeclEditor::LoadDecl
================
*/
void DialogDeclEditor::LoadDecl(idDecl *decl)
{
	int numLines = 0;
	int numCharsPerLine = 0;
	int maxCharsPerLine = 0;
	idStr declText;
	CRect rect;

	this->decl = decl;

	switch (decl->GetType()) {
		case DECL_ENTITYDEF:
			declEdit.SetStringColor(SRE_COLOR_BLUE, SRE_COLOR_DARK_CYAN);
			declEdit.LoadKeyWordsFromFile("editors/entity.def");
			break;
		case DECL_MATERIAL:
			declEdit.LoadKeyWordsFromFile("editors/material.def");
			break;
		case DECL_SKIN:
			declEdit.LoadKeyWordsFromFile("editors/skin.def");
			break;
		case DECL_SOUND:
			declEdit.LoadKeyWordsFromFile("editors/sound.def");
			break;
		case DECL_FX:
			declEdit.LoadKeyWordsFromFile("editors/fx.def");
			break;
		case DECL_PARTICLE:
			declEdit.LoadKeyWordsFromFile("editors/particle.def");
			break;
		case DECL_AF:
			declEdit.LoadKeyWordsFromFile("editors/af.def");
			break;
		case DECL_TABLE:
			declEdit.LoadKeyWordsFromFile("editors/table.def");
			break;
		case DECL_MODELDEF:
			declEdit.LoadKeyWordsFromFile("editors/model.def");
			break;
		default:
			declEdit.LoadKeyWordsFromFile(va("editors/%s.def", declManager->GetDeclNameFromType(decl->GetType())));
			break;
	}

	firstLine = decl->GetLineNum();

	char *localDeclText = (char *)_alloca((decl->GetTextLength() + 1) * sizeof(char));
	decl->GetText(localDeclText);
	declText = localDeclText;

	// clean up new-line crapola
	declText.Replace("\r", "");
	declText.Replace("\n", "\r");
	declText.Replace("\v", "\r");
	declText.StripLeading('\r');
	declText.Append("\r");

	declEdit.SetText(declText);

	for (const char *ptr = declText.c_str(); *ptr; ptr++) {
		if (*ptr == '\r') {
			if (numCharsPerLine > maxCharsPerLine) {
				maxCharsPerLine = numCharsPerLine;
			}

			numCharsPerLine = 0;
			numLines++;
		} else if (*ptr == '\t') {
			numCharsPerLine += TAB_SIZE;
		} else {
			numCharsPerLine++;
		}
	}

	SetWindowText(va("Declaration Editor (%s, line %d)", decl->GetFileName(), decl->GetLineNum()));

	rect.left = initialRect.left;
	rect.right = rect.left + maxCharsPerLine * FONT_WIDTH + 32;
	rect.top = initialRect.top;
	rect.bottom = rect.top + numLines * (FONT_HEIGHT+8) + 24 + 56;

	if (rect.right < initialRect.right) {
		rect.right = initialRect.right;
	} else if (rect.right - rect.left > 1024) {
		rect.right = rect.left + 1024;
	}

	if (rect.bottom < initialRect.bottom) {
		rect.bottom = initialRect.bottom;
	} else if (rect.bottom - rect.top > 768) {
		rect.bottom = rect.top + 768;
	}

	MoveWindow(rect);

	testButton.EnableWindow(FALSE);
	okButton.EnableWindow(FALSE);

	UpdateStatusBar();

	declEdit.SetFocus();
}