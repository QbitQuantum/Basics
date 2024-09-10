void MenuImage::Draw()
{
	BITMAP bitmap;
	BITMAP indicatorBitmap;

	//If menuitem needs to be centered
	if(!fixedPosition)
	{
			//Draw menu item
			GetObject(sprite, sizeof(BITMAP), &bitmap);
			HANDLE old = SelectObject(imageHDC, sprite);
		
			int xPos = (1280 / 2)-(bitmap.bmWidth / 2);
			TransparentBlt(drawDC, xPos, location.y, bitmap.bmWidth, bitmap.bmHeight, imageHDC, 0, 0, bitmap.bmWidth, bitmap.bmHeight, GetPixel(imageHDC, 1,1));
			SelectObject(imageHDC, old);
			//BitBlt(drawDC, 0, 0, bitmap.bmWidth, bitmap.bmHeight, imageHDC, 0, 0, SRCCOPY);
			if(selected)
			{
				//Draw indicator
				GetObject(indicatorSprite, sizeof(indicatorBitmap), &indicatorBitmap);
				HANDLE old = SelectObject(imageHDC, indicatorSprite);
				TransparentBlt(drawDC, xPos-(indicatorBitmap.bmWidth) - 10, location.y, indicatorBitmap.bmWidth, indicatorBitmap.bmHeight, imageHDC, 0, 0, indicatorBitmap.bmWidth, indicatorBitmap.bmHeight, GetPixel(imageHDC, 1,1));		
				SelectObject(imageHDC, old);
			}
	}else
	{
		//If menuitem has fixed position
		if(selected)
		{
			//Draw indicator
			GetObject(indicatorSprite, sizeof(BITMAP), &bitmap);
			HANDLE old = SelectObject(imageHDC, indicatorSprite);
			TransparentBlt(drawDC, (location.x-bitmap.bmWidth)-10, location.y, bitmap.bmWidth, bitmap.bmHeight, imageHDC, 0, 0, bitmap.bmWidth, bitmap.bmHeight, GetPixel(imageHDC, 1,1));		
			SelectObject(imageHDC, old);
		}
			//Draw menu item
			GetObject(sprite, sizeof(BITMAP), &bitmap);
			HANDLE old = SelectObject(imageHDC, sprite);
		
			TransparentBlt(drawDC, location.x/* - (bitmap.bmWidth / 2)*/, location.y, bitmap.bmWidth, bitmap.bmHeight, imageHDC, 0, 0, bitmap.bmWidth, bitmap.bmHeight, GetPixel(imageHDC, 1,1));
			SelectObject(imageHDC, old);
	}
}