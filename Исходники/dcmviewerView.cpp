CSize CdcmviewerView::get_lowinch_size()
{
	//0028,0030 DS pixel spacing, Physical distance in the patient between
	//the center of each pixel, specified by a
	//	numeric pair - adjacent row spacing
	//	(delimiter) adjacent column spacing in 	mm.
	dicom::Tag tag_pixel_spacing = dicom::makeTag(0x28,0x30);
	CDC dc;
	dc.m_hDC=::GetDC(GetDesktopWindow()->m_hWnd);
	int old_map_mode = dc.SetMapMode(MM_TEXT);
	int xpixel_per_inch = dc.GetDeviceCaps(LOGPIXELSX);
	int ypixel_per_inch = dc.GetDeviceCaps(LOGPIXELSY);
	CSize ret;
	ret.cx = m_cols/xpixel_per_inch;
	ret.cy = m_rows/ypixel_per_inch;
	dc.SetMapMode(old_map_mode);
	return ret;	
}