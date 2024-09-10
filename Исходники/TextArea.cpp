/** Key Press Event */
void TextArea::OnKeyPress(unsigned char Key, unsigned short /*Mod*/)
{
	if (Flags & IE_GUI_TEXTAREA_EDITABLE) {
		if (Key >= 0x20) {
			Owner->Invalidate();
			Changed = true;
			int len = GetRowLength(CurLine);
			//printf("len: %d Before: %s\n",len, lines[CurLine]);
			lines[CurLine] = (char *) realloc( lines[CurLine], len + 2 );
			for (int i = len; i > CurPos; i--) {
				lines[CurLine][i] = lines[CurLine][i - 1];
			}
			lines[CurLine][CurPos] = Key;
			lines[CurLine][len + 1] = 0;
			CurPos++;
			//printf("pos: %d After: %s\n",CurPos, lines[CurLine]);
			CalcRowCount();
			RunEventHandler( TextAreaOnChange );
		}
		return;
	}

	//Selectable=false for dialogs, rather unintuitive, but fact
	if ((Flags & IE_GUI_TEXTAREA_SELECTABLE) || ( Key < '1' ) || ( Key > '9' ))
		return;
	GameControl *gc = core->GetGameControl();
	if (gc && (gc->GetDialogueFlags()&DF_IN_DIALOG) ) {
		Changed = true;
		seltext=minrow-1;
		if ((unsigned int) seltext>=lines.size()) {
			return;
		}
		for(int i=0;i<Key-'0';i++) {
			do {
				seltext++;
				if ((unsigned int) seltext>=lines.size()) {
					return;
				}
			}
			while (strnicmp( lines[seltext], "[s=", 3 ) != 0 );
		}
		int idx=-1;
		sscanf( lines[seltext], "[s=%d,", &idx);
		if (idx==-1) {
			//this kills this object, don't use any more data!
			gc->EndDialog();
			return;
		}
		gc->DialogChoose( idx );
	}
}