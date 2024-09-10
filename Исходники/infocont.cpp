/////////////////////////////////////////////////////////////////////
// TInfoControl
// ------------
//
void TInfoControl::Paint (TDC& dc, BOOL erase, TRect& rect)
{
	TControl::Paint(dc, erase, rect);

	TRect cRect = GetClientRect();

	// Select font
	dc.SelectObject (*StaticFont);
	dc.SetBkMode (TRANSPARENT);

	// Draw each text line
	if ( TextLineTab != NULL )
	{
		for (int i = 0 ; i < NumLines ; i++)
		{
			if (TextLineTab[i] != NULL  && TextLineTab[i]->Text != NULL)
			{
				int x;

				dc.SetTextColor ( TMapDC::GetColor16(TextLineTab[i]->Color));
				dc.SetTextAlign( TextLineTab[i]->Align);

				switch (TextLineTab[i]->Align & (TA_CENTER |TA_LEFT |TA_RIGHT))
				{
				case TA_LEFT:
					x = 0;
					break;
				case TA_CENTER:
					x = cRect.Width() / 2;
					break;
				case TA_RIGHT:
					x = cRect.Width() - 1;
					break;
				}

				dc.TextOut( x, FontHeight * i, TextLineTab[i]->Text);
			}
		}
	}
	dc.RestoreFont();
}