//获取grid的str的作画rect
QRectF CDigitalStatusPrinter::CenterInGrid(int left,int right,int y,QString str)
{
	QFontMetrics metics(m_font);

	int nDescWidth = metics.width(str);
	int nHeight = metics.height();
	int nStart = (left+right)/2;
	nStart = nStart - nDescWidth/2;
	int nWidth = right-nStart;
	QRectF rectF(nStart,y,nWidth,nHeight);
	return rectF;
}