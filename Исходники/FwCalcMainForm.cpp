void __fastcall TFwCalcMainDlg::PaintBoxPaint(TObject *Sender)
{
TRect r = TRect(0,0,PaintBox->Width, PaintBox->Height);
TCanvas *cv = PaintBox->Canvas;
	// Paint background
	cv->FillRect(r);
	cv->TextFlags = 0;
	cv->Font->Style = TFontStyles() << fsBold;
	cv->Font->Name = "Courier New";

	SetBkMode(cv->Handle, TRANSPARENT);

int lh = cv->TextHeight("X");
int y_off = r.Height() - lh;
int index = 0;

	while(y_off + lh >= 0)
	{
	// Determine number to write
	AnsiString txt = m_engine->RegisterValue[index].UpperCase();

		if(txt != "")
		{
			if(txt == "ERR")
			{
			AnsiString err_text = AnsiString("ERROR - ") + m_engine->LastError;
				cv->Font->Size = m_font_size;
				cv->Font->Color = clRed;
				cv->TextOut(r.Right - 10 - cv->TextWidth(err_text), y_off, err_text);
			}
			else
			{
				if(m_engine->BaseMode == eBaseDec)
				{
				int tw = CalcWidthOfDecNumber(cv, txt);
					PaintDecNumber(cv, r.Right - 10 - tw, y_off, txt);
				}
				else
				{
					cv->Font->Size = m_font_size;

					cv->TextOut(r.Right-cv->TextWidth(txt)-10, y_off, txt);
				}
			}
		}

		y_off -= lh;
		index++;
	}
}