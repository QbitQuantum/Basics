void DetectEdge(BinaryBitmap* pBitmap)
{
	BinaryBitmap* pBitmapCopy = new BinaryBitmap(pBitmap->GetWidth(), pBitmap->GetHeight());
	
	for(long x = 0; x < pBitmap->GetWidth(); x++)
	{
		for(long y = 0; y < pBitmap->GetHeight(); y++)
		{
			if(!pBitmap->GetPixel(x, y))
				continue;

			bool detected = false;

			for(long dx = x - 1; dx <= x+1 && !detected; dx++)
			{
				if(dx < 0 || dx >= pBitmap->GetWidth())
					continue;
								
				for(long dy = y - 1; dy <= y+1 && !detected; dy++)
				{
					if(dy < 0 || dy >= pBitmap->GetHeight())
						continue;

					if(dx == x && dy == y)
						continue;

					if(!pBitmap->GetPixel(dx, dy))
						detected = true;
				}
			}

			pBitmapCopy->SetPixel(x, y, detected);
		}
	}

	*pBitmap = *pBitmapCopy;//!!!do we need copying???
	delete pBitmapCopy;
}