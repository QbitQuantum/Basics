void CTabsControl::DrawItem(CTabControl *item, Gdiplus::Graphics &g)
{
	CRect rect = ItemRect(item);

	g.ResetTransform();
	g.TranslateTransform((REAL)rect.left, (REAL)rect.top);

	RectF rf(0.0f, 0.0f, (REAL)rect.Width(), (REAL)rect.Height());
	RectF rx;

	if(item->selected)
	{
		#define shadowb 10

		CDIB tmp;
		tmp.Resize(rect.Width() + shadowb * 2, rect.Height() + shadowb * 2);
		if(tmp.Ready())
		{
			Graphics gt(tmp.bmp);
			RectF rx(0, 0, (REAL)tmp.Width(), (REAL)tmp.Height());
			
			GraphicsPath *path = new GraphicsPath();
			path->AddLine(rx.X + shadowb, rx.Y + rx.Height - shadowb, rx.X + rx.Width - 2 - shadowb, rx.Y + rx.Height - shadowb);
			path->AddLine(rx.X + rx.Width - 2 - shadowb, rx.Y + rx.Height - shadowb, rx.X + rx.Width - 2, rx.Y);
			path->AddLine(rx.X + rx.Width - 2, rx.Y, rx.X + rx.Width, rx.Y + rx.Height);
			path->AddLine(rx.X + rx.Width, rx.Y + rx.Height, rx.X, rx.Y + rx.Height);
			path->AddLine(rx.X, rx.Y, rx.X + shadowb, rx.Y + rx.Height - shadowb);
			path->CloseFigure();

			SolidBrush brush(0xff000000);
			gt.FillPath(&brush, path);

			tmp.Blur(tmp.Rect(), CRect(0, 0, 0, 0), shadowb);

			g.DrawImage(tmp.bmp, rf, shadowb, shadowb, rf.Width, rf.Height, UnitPixel);

			delete path;
		}
	}

	Font font(L"Arial", item->selected ? 8.0f : 8.0f);
	StringFormat *stringFormat = new StringFormat();
	stringFormat->SetAlignment(StringAlignmentCenter);
	stringFormat->SetLineAlignment(StringAlignmentCenter);
	stringFormat->SetTrimming(StringTrimmingEllipsisCharacter);
	stringFormat->SetFormatFlags(StringFormatFlagsLineLimit);

	if(item->icon->Ready())
	{
		g.SetInterpolationMode(InterpolationModeBicubic);
		rx = rf;
		rx.Y += 6;
		rx.Height -= (20 + rx.Y);
		rx.Width = rx.Height;
		rx.X += (rf.Width - rx.Width) / 2;

		if(item->selected)
		{
			rx.Y++;

			#define shadow 5
			CDIB tmp;
			tmp.Resize(item->icon->Width(), item->icon->Height());
			if(tmp.Ready())
			{
				tmp.Draw(CRect(shadow, shadow, 
					item->icon->Width() - shadow, 
					item->icon->Height() - shadow), 
					item->icon->Rect(), item->icon);
				DIB_ARGB *p = tmp.scan0;
				int size = tmp.Width() * tmp.Height();
				for(int i = 0; i < size; i++, p++)
				{
					p->r = 0;
					p->g = 0;
					p->b = 0;
				}
				tmp.Blur(tmp.Rect(), CRect(0, 0, 0, 0), shadow);
				g.DrawImage(tmp.bmp, RectF(rx.X, rx.Y + shadow, rx.Width, rx.Height));
			}
			tmp.Assign(item->icon);
			/*if(tmp.Ready())
			{
				DIB_ARGB *p = tmp.scan0;
				int size = tmp.Width() * tmp.Height();
				for(int i = 0; i < size; i++, p++)
				{
					p->r = 0x6f;
					p->g = 0xa6;
					p->b = 0xde;
				} 
			}*/
			g.DrawImage(tmp.bmp, rx);
		}
		else
		{
			g.DrawImage(item->icon->bmp, rx);
		}
	}

	SolidBrush brush(0xff000000);
	rx = rf;
	rx.Height = 20;
	rx.Y = rf.Height - rx.Height;

	rx.Y++;
	g.DrawString(item->text.GetBuffer(), item->text.GetLength(), &font, rx, stringFormat, &brush);

	brush.SetColor(item->selected && false ? 0xff6fa6de : 0xfff0f0f0);
	rx.Y--;
	g.DrawString(item->text.GetBuffer(), item->text.GetLength(), &font, rx, stringFormat, &brush);

	delete stringFormat;

	//POSITION p = items.Find(item);
	//items.GetNext(p);
	//if(p)
	{
		RectF rx = rf;
		rx.X += rx.Width - 1;
		rx.Width = 1;
		LinearGradientBrush brush(rx, Color(140, 0x69, 0x69, 0x69), Color(0x69, 0x69, 0x69), LinearGradientModeVertical);
		g.FillRectangle(&brush, rx);
	}
}