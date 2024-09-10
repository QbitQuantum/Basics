void DispLoading::onEraseBG( wxEraseEvent& event )
{
	wxDC *dc = event.GetDC();

	if (!m_imgHandle.getImg() || !m_imgHandle->IsOk())
	{
		dc->SetTextForeground(wxColor(0,0,0));
		dc->Clear();
		return;
	}

	int h = GetSize().GetHeight();
	int w = GetSize().GetWidth();
	int iw = m_imgHandle->GetSize().GetWidth();


	//size 7
	const int l_start = 0;
	const int l_width = 2;

	//size 6
	const int m_start = 2;
	const int m_width = 15;

	//size 7 with 1 pix gap
	const int r_start = 17;
	const int r_width = 2;


	wxBitmap   tmpBmp(w, h);
	wxMemoryDC tmpDC(tmpBmp);

	tmpDC.SetBrush(wxBrush(wxColor(255,0,255)));
	tmpDC.SetPen( wxPen(wxColor(255,0,255),1) );
	tmpDC.DrawRectangle(0,0,w,h);

	wxImage scaled = m_imgHandle->Scale(iw, h);

	if (scaled.IsOk())
	{
		wxBitmap left = wxBitmap(scaled.GetSubImage( wxRect(l_start,0,l_width,h)) );
		wxBitmap right = wxBitmap(scaled.GetSubImage( wxRect(r_start,0,r_width,h)) );
		wxBitmap center(w-(l_width+r_width),h);

		wxColor c(255,0,255);
		gcImage::tileImg(center, wxBitmap(scaled.GetSubImage( wxRect(m_start,0,m_width,h)) ), &c);

		tmpDC.DrawBitmap(left, l_start,0,true);
		tmpDC.DrawBitmap(center, m_start,0,true);
		tmpDC.DrawBitmap(right, w-r_width,0,true);
	}

	tmpDC.SelectObject(wxNullBitmap);
	dc->DrawBitmap(tmpBmp, 0,0, true);

	wxRegion region = wxRegion(tmpBmp, wxColor(255,0,255), 1);
	SetShape(region, this);
}