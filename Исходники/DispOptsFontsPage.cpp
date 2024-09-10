int CDispOptsFontsPage::LogicalSizeToPoints(int nLogSize)
{
	CWindowDC dc(this);
	int nPoints = Round((Abs(nLogSize) / (float)::GetDeviceCaps(dc, LOGPIXELSY)) * 72);
	return nPoints;
}