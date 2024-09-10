void StretchBitmap(BUFFER &pBuffer, int pic, int screenx, int screeny, int width, int height, int imagex, int imagey, int imagew, int imageh)
{
	//select bitmap handle
	SelectObject(pBuffer.hdcBitmap, tiles[pic]);

	//blit bitmap into backbuffer
	StretchBlt(pBuffer.hdcBack, screenx, screeny, width, height, 
				   pBuffer.hdcBitmap, imagex, imagey, imagew, imageh, SRCCOPY);

	//select old handle to clean up
	SelectObject(pBuffer.hdcBitmap, pBuffer.hOldBitmap);
}