void VDVideoWindow::UpdateSourcePARMenuItem() {
	VDStringW s;

	if (mSourcePAR <= 0)
		s = L"Unknown ratio";
	else
		s.sprintf(L"%.4g:1 pixel", mSourcePAR);

	VDStringW t(mSourcePARTextPattern);
	VDStringW::size_type pos = t.find('?');

	if (pos != VDStringW::npos)
		t.replace(pos, 1, s.data(), s.size());
	
	VDSetMenuItemTextByCommandW32(mhmenu, ID_DISPLAY_AR_PIXEL_SOURCE, t.c_str());
}