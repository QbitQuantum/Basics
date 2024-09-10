void wxVideoTerminal::OnEraseBackground(wxEraseEvent &evt)
{
	wxDC *p_dc = evt.GetDC();
	
	wxSize sz = p_dc->GetSize();
	p_dc->SetBrush( brushes[0] );

	if (mp_bitmap)
	{
		wxSize sz_bmp = mp_bitmap->GetSize();
		if (sz_bmp.x < sz.x)
			p_dc->DrawRectangle(wxPoint(sz_bmp.x,0), wxSize(sz.x-sz_bmp.x,sz.y));

		if (sz_bmp.y < sz.y)
			p_dc->DrawRectangle(wxPoint(0,sz_bmp.y), wxSize(sz.x, sz.y-sz_bmp.y));
	} else {
		p_dc->DrawRectangle(wxPoint(0,0), sz);
	}
}