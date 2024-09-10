void
CalcView::Draw(BRect updateRect)
{
	bool drawBackground = !_IsEmbedded();

	SetHighColor(fBaseColor);
	BRect expressionRect(_ExpressionRect());
	if (updateRect.Intersects(expressionRect)) {
		if (fOptions->keypad_mode == KEYPAD_MODE_COMPACT
			&& expressionRect.Height() >= fCalcIcon->Bounds().Height()) {
			// render calc icon
			expressionRect.left = fExpressionTextView->Frame().right + 2;
			if (drawBackground) {
				SetHighColor(fBaseColor);
				FillRect(updateRect & expressionRect);
			}

			if (fCalcIcon->ColorSpace() == B_RGBA32) {
				SetDrawingMode(B_OP_ALPHA);
				SetBlendingMode(B_PIXEL_ALPHA, B_ALPHA_OVERLAY);
			} else {
				SetDrawingMode(B_OP_OVER);
			}

			BPoint iconPos;
			iconPos.x = expressionRect.right - (expressionRect.Width()
				+ fCalcIcon->Bounds().Width()) / 2.0;
			iconPos.y = expressionRect.top + (expressionRect.Height()
				- fCalcIcon->Bounds().Height()) / 2.0;
			DrawBitmap(fCalcIcon, iconPos);

			SetDrawingMode(B_OP_COPY);
		}

		// render border around expression text view
		expressionRect = fExpressionTextView->Frame();
		expressionRect.InsetBy(-2, -2);
		if (fOptions->keypad_mode != KEYPAD_MODE_COMPACT && drawBackground) {
			expressionRect.InsetBy(-2, -2);
			StrokeRect(expressionRect);
			expressionRect.InsetBy(1, 1);
			StrokeRect(expressionRect);
			expressionRect.InsetBy(1, 1);
		}

		uint32 flags = 0;
		if (!drawBackground)
			flags |= BControlLook::B_BLEND_FRAME;
		be_control_look->DrawTextControlBorder(this, expressionRect,
			updateRect, fBaseColor, flags);
	}

	if (fOptions->keypad_mode == KEYPAD_MODE_COMPACT)
		return;

	// calculate grid sizes
	BRect keypadRect(_KeypadRect());

	if (be_control_look != NULL) {
		if (drawBackground)
			StrokeRect(keypadRect);
		keypadRect.InsetBy(1, 1);
	}

	float sizeDisp = keypadRect.top;
	float sizeCol = (keypadRect.Width() + 1) / (float)fColumns;
	float sizeRow = (keypadRect.Height() + 1) / (float)fRows;

	if (!updateRect.Intersects(keypadRect))
		return;

	SetFontSize(min_c(sizeRow * kFontScaleY, sizeCol * kFontScaleX));

	CalcKey* key = fKeypad;
	for (int row = 0; row < fRows; row++) {
		for (int col = 0; col < fColumns; col++) {
			BRect frame;
			frame.left = keypadRect.left + col * sizeCol;
			frame.right = keypadRect.left + (col + 1) * sizeCol - 1;
			frame.top = sizeDisp + row * sizeRow;
			frame.bottom = sizeDisp + (row + 1) * sizeRow - 1;

			if (drawBackground) {
				SetHighColor(fBaseColor);
				StrokeRect(frame);
			}
			frame.InsetBy(1, 1);

			uint32 flags = 0;
			if (!drawBackground)
				flags |= BControlLook::B_BLEND_FRAME;
			if (key->flags != 0)
				flags |= BControlLook::B_ACTIVATED;
			flags |= BControlLook::B_IGNORE_OUTLINE;

			be_control_look->DrawButtonFrame(this, frame, updateRect,
				fBaseColor, fBaseColor, flags);

			be_control_look->DrawButtonBackground(this, frame, updateRect,
				fBaseColor, flags);

			be_control_look->DrawLabel(this, key->label, frame, updateRect,
				fBaseColor, flags, BAlignment(B_ALIGN_HORIZONTAL_CENTER,
					B_ALIGN_VERTICAL_CENTER), &fButtonTextColor);

			key++;
		}
	}
}