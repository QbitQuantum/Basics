void HistogramImg::DrawItem(LPDRAWITEMSTRUCT draw_item_struct)
{
	if (draw_item_struct->itemAction != ODA_DRAWENTIRE)
		return;

	CDC* dc= CDC::FromHandle(draw_item_struct->hDC);

	dc->SetBkMode(OPAQUE);
	COLORREF rgb_back= RGB(255,255,255);

	if (bmp_)
	{
		CRect rect;
		GetClientRect(rect);
		int width= bmp_->GetWidth();
		int height= bmp_->GetHeight();

		if (width > rect.Width())
			width = rect.Width();
		if (height > rect.Height())
			height = rect.Height();
		if (width != bmp_->GetWidth() || height != bmp_->GetHeight())
		{
			double ratio_org= double(bmp_->GetWidth()) / double(bmp_->GetHeight());
			if (double(width) / double(height) > ratio_org)
				width = static_cast<int>(height * ratio_org);
			else
				height = static_cast<int>(width / ratio_org);
		}

		CRect dest_rect= rect;

		if (width < dest_rect.Width())
			dest_rect.left = (dest_rect.Width() - width) / 2;
		else
			dest_rect.left = 0;

		if (height < rect.Height())
			dest_rect.top = (dest_rect.Height() - height) / 2;
		else
			dest_rect.top = 0;

		dest_rect.right = dest_rect.left + width;
		dest_rect.bottom = dest_rect.top + height;

		CRect fill_rect= rect;
		fill_rect.right = dest_rect.left;
		if (fill_rect.Width() > 0)
			dc->FillSolidRect(fill_rect, rgb_back);
		fill_rect.left = dest_rect.right;
		fill_rect.right = rect.right;
		if (fill_rect.Width() > 0)
			dc->FillSolidRect(fill_rect, rgb_back);

		fill_rect = rect;
		fill_rect.bottom = dest_rect.top;
		if (fill_rect.Height() > 0)
			dc->FillSolidRect(fill_rect, rgb_back);
		fill_rect.top = dest_rect.bottom;
		fill_rect.bottom = rect.bottom;
		if (fill_rect.Height() > 0)
			dc->FillSolidRect(fill_rect, rgb_back);

		bmp_->Draw(dc, dest_rect);
		image_rect_ = dest_rect;
	}

	if (!selection_rect_.IsRectEmpty())
	{
		CRect rect= selection_rect_;
		rect.NormalizeRect();
		CBitmap bmp;
		bmp.LoadBitmap(IDB_PATTERN);
		CBrush br;
		br.CreatePatternBrush(&bmp);
		dc->SetBkColor(RGB(255,255,255));
		dc->SetTextColor(RGB(255,0,0));
		dc->FrameRect(rect, &br);
	}
}