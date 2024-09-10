DIBitmap::DIBitmap(const char *fileName,GLubyte r,GLubyte g,GLubyte b)
{
	_bitmap = 0;
	_bitMapInfo = 0;
	setLimpidColor(r,g,b);
	loadBitmapA(fileName);
}