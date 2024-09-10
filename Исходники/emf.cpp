// map a rectangle in logical coordinate to 0.01 mm units
void Map10um(HDC hDC, RECT & rect)
{
	int widthmm    = GetDeviceCaps(hDC, HORZSIZE);
	int heightmm   = GetDeviceCaps(hDC, VERTSIZE);
	int widthpixel = GetDeviceCaps(hDC, HORZRES);
	int heightpixel= GetDeviceCaps(hDC, VERTRES);

	LPtoDP(hDC, (POINT *) & rect, 2);

	rect.left   = ( rect.left   * widthmm  * 100 + widthpixel/2)  /  widthpixel;
	rect.right  = ( rect.right  * widthmm  * 100 + widthpixel/2)  /  widthpixel;
	rect.top    = ( rect.top    * heightmm * 100 + heightpixel/2) / heightpixel;
	rect.bottom = ( rect.bottom * heightmm * 100 + heightpixel/2) / heightpixel;
}