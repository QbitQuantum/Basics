void api::refreshScreen()
{
	SetBitmapBits(back_buffer, 4 * numPixels, data);
	SelectObject(DC_back_buffer, back_buffer);
	BitBlt(hDC, 0, 0, width, height, DC_back_buffer, 0, 0, SRCCOPY);
}