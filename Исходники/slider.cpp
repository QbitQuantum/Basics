void Slider::Draw (BRect rect)
{
	BRect label = BRect (0, 0, sep, height);
	if (rect.Intersects (label))	// Label needs to be redrawn
	{
		SetLowColor (LightGrey);
		SetHighColor (Black);
		FillRect (label, B_SOLID_LOW);
		DrawString (name, BPoint (0, label.bottom - 5));
	}
	offslid->Lock ();
	offview->SetHighColor (Grey21);
	offview->FillRect (bounds);
	offview->SetHighColor (Grey30);
	offview->StrokeLine (bounds.RightTop (), bounds.RightBottom ());
	offview->StrokeLine (bounds.LeftBottom ());
	offview->SetHighColor (Grey14);
	offview->StrokeLine (bounds.LeftTop ());
	offview->StrokeLine (bounds.RightTop ());
	knobpos = BPoint (float (value - min)/(max - min)*(width - knobsize), 1);
	knob = BRect (knobpos.x + 1, knobpos.y + 1, knobpos.x + knobsize - 2, knobpos.y + height - 2);
	offview->SetHighColor (Grey27);
	offview->FillRect (knob);
	offview->SetHighColor (Black);
	offview->SetLowColor (Grey27);
	offview->SetFont (be_plain_font);
	char val[KNOBVAL];
	sprintf (val, fmt, value);
	offview->DrawString (val, BPoint (knobpos.x + (knobsize - StringWidth (val))/2 + 1, knobpos.y + 12));
	offview->SetHighColor (Grey30);
	offview->StrokeLine (BPoint (knobpos.x + knobsize - 1, knobpos.y), BPoint (knobpos.x + 1, knobpos.y));
	offview->StrokeLine (BPoint (knobpos.x + 1, knobpos.y + height - 2));
	offview->SetHighColor (Grey13);
	offview->StrokeLine (BPoint (knobpos.x + knobsize - 1, knobpos.y + height - 2));
	offview->StrokeLine (BPoint (knobpos.x + knobsize - 1, knobpos.y));
	if (IsFocus())
	{
		// printf ("%s focused!\n", Name());
		BRect k (knobpos.x, knobpos.y - 1, knobpos.x + knobsize - 1, knobpos.y + height - 2);
		k.InsetBy (1, 1);
		offview->SetHighColor (ui_color (B_KEYBOARD_NAVIGATION_COLOR));
		offview->StrokeRect (k);
	}
	offview->Sync ();
	offslid->Unlock ();
	DrawBitmapAsync (offslid, BPoint (sep, 0));
}