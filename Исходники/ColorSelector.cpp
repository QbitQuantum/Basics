	virtual	void DrawContent()
	{
		BRect		b = Frame();
		BMenu		*parent = Menu();
		BPoint		loc = parent->PenLocation();

		enum {
			W_CHAR = 0,
			A_CHAR = 1,
			OPEN_CHAR = 2,
			CLOSE_CHAR = 3,
			SPACE_CHAR = 4,
			NUM_CHARS = 5
		};
		float escapements[NUM_CHARS];
		BFont font;
		parent->GetFont(&font);
		font.GetEscapements("WA() ", NUM_CHARS, escapements);
		for (int32 i=0; i<NUM_CHARS; i++) {
			escapements[i] *= font.Size();
		}

		const float blockWidth = escapements[W_CHAR]+escapements[A_CHAR];

		const rgb_color old_col = parent->HighColor();
		font_height fh;

		const bool showInitial = !CompareColors(fInitialColor, fColor);

		b.InsetBy(1, 1);
		b.bottom -= 1;
		b.left = loc.x;

		if (showInitial) {
			parent->GetFontHeight(&fh);
			parent->DrawString("(", BPoint(b.left, loc.y+fh.ascent));
		}
		b.left += escapements[OPEN_CHAR];
		b.InsetBy(2, 2);
		b.right = b.left + escapements[W_CHAR];
		if (showInitial) {
			parent->SetHighColor(fInitialColor);
			parent->FillRect(b);
		}
		b.InsetBy(-1, -1);
		if (showInitial) {
			parent->SetHighColor(old_col);
			parent->StrokeRect(b);
		}
		b.InsetBy(-1, -1);
		if (showInitial) {
			parent->DrawString(")", BPoint(b.right+1, loc.y+fh.ascent));
		}
		b.right += escapements[CLOSE_CHAR] + 1;

		b.left = b.right + escapements[SPACE_CHAR];
		b.right = b.left + blockWidth;

		parent->SetHighColor(fColor);
		parent->FillRect(b);
		parent->SetHighColor(old_col);
		b.InsetBy(-1, -1);
		parent->StrokeRect(b);

		parent->MovePenTo(b.right + escapements[SPACE_CHAR]*2 + 2, loc.y);

		BMenuItem::DrawContent();
	}