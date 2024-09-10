void LBMessage_DrawItem(TWinControl *Control, int Index, TRect &Rect, TOwnerDrawState State)
{
	TListBox* lbox = dynamic_cast<TListBox*>(Control);
	if (!lbox) return;

	TCanvas* canvas = lbox->Canvas;

	// Set defaults:
	canvas->Brush->Color = lbox->Color;
	canvas->Font->Style = lbox->Font->Style;

	TLBMessageStyle style = (TLBMessageStyle)lbox->Items->Objects[Index];

	switch (style)
	{
		default:
		case smtDefaultB:
		case smtDefB:
			canvas->Font->Style = canvas->Font->Style << fsBold;
		case smtDefault:
		case smtDef:
			canvas->Font->Color = clWindowText;
			break;

		case smtNotificationB:
		case smtNotifB:
			canvas->Font->Color = clNavy;
			canvas->Font->Style = canvas->Font->Style << fsBold;
			canvas->Brush->Color = (TColor)0xFFF0F0;
			break;
		case smtNotification:
		case smtNotif:
			canvas->Font->Color = clBlue;
			break;

		case smtWarning:
			//canvas->Font->Color = clFuchsia;
			canvas->Font->Color = (TColor)0x9900cc;
			break;

		case smtError:
			canvas->Font->Color = clRed;
			canvas->Brush->Color = clCream;
			break;

		case smtAppError:
			canvas->Font->Color = clYellow;
			canvas->Brush->Color = clRed;
			break;
	}

	// Clear the rectangle: (NECESSARY!)
	canvas->FillRect(Rect);

	// Display text:
	canvas->TextOut(Rect.Left + 2, Rect.Top, lbox->Items->Strings[Index]);
}