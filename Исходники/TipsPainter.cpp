void TipsPainter::eraseRect(const int x, const int y, const int w, const int h)
{	
	setCompositionMode(QPainter::CompositionMode_Source);
	fillRect(x,y,w,h, Qt::transparent);
}