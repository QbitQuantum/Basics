void gdImage::CopyResampled(gdImage& dst,
		      int dstX, int dstY,
		      int /*srcX*/, int /*srcY*/,
		      int dstW, int dstH,
			  int srcW, int srcH,
			  int tolerance)
{
	gdImage& src=*this;
	int x, y;
	int srcTransparent=src.GetTransparent();
	int dstTransparent=dst.GetTransparent();
	for (y = dstY; (y < dstY + dstH); y++) {
		for (x = dstX; (x < dstX + dstW); x++) {
			int pd = dst.GetPixel (x, y);
			/* Added 7/24/95: support transparent copies */
			/* fixed by paf 20030116, another fix below */
			if (pd == dstTransparent)
				continue;
			
			double sy1, sy2, sx1, sx2;
			double sx, sy;
			double spixels = 0;
			double red = 0.0, green = 0.0, blue = 0.0;
			bool transparent=true;
			sy1 = ((double) y - (double) dstY) * (double) srcH /
				(double) dstH;
			sy2 = ((double) (y + 1) - (double) dstY) * (double) srcH /
				(double) dstH;
			sy = sy1;
			do
			{
				double yportion;
				if (floor (sy) == floor (sy1))
				{
					yportion = 1.0 - (sy - floor (sy));
					if (yportion > sy2 - sy1)
					{
						yportion = sy2 - sy1;
					}
					sy = floor (sy);
				}
				else if (sy == floor (sy2))
				{
					yportion = sy2 - floor (sy2);
				}
				else
				{
					yportion = 1.0;
				}
				sx1 = ((double) x - (double) dstX) * (double) srcW /
					dstW;
				sx2 = ((double) (x + 1) - (double) dstX) * (double) srcW /
					dstW;
				sx = sx1;
				do
				{
					double xportion;
					double pcontribution;
					int p;
					if (floor (sx) == floor (sx1))
					{
						xportion = 1.0 - (sx - floor (sx));
						if (xportion > sx2 - sx1)
						{
							xportion = sx2 - sx1;
						}
						sx = floor (sx);
					}
					else if (sx == floor (sx2))
					{
						xportion = sx2 - floor (sx2);
					}
					else
					{
						xportion = 1.0;
					}
					pcontribution = xportion * yportion;
					p = src.GetPixel (
						(int) sx,
						(int) sy);
					// fix added 20020116 by paf to support transparent src
					if (p!=srcTransparent) {
						transparent = false;
						red += Red (p) * pcontribution;
						green += Green (p) * pcontribution;
						blue += Blue (p) * pcontribution;
					}
					spixels += xportion * yportion;
					sx += 1.0;
				} while (sx < sx2);
				sy += 1.0;
			} while (sy < sy2);

			if(transparent)
				continue;

			if (spixels != 0.0) {
				red /= spixels;
				green /= spixels;
				blue /= spixels;
			}
			/* Clamping to allow for rounding errors above */
			if (red > 255.0)
				red = 255.0;
			if (green > 255.0)
				green = 255.0;
			if (blue > 255.0)
				blue = 255.0;
			
			red=round(red);
			green=round(green);
			blue=round(blue);
			/* First look for an exact match */
			int nc = dst.ColorExact((int)red, (int)green, (int)blue);
			if (nc == (-1)) {
				/* No, so go for the closest color with high tolerance */
				nc = dst.ColorClosest((int)red, (int)green, (int)blue,  tolerance);
				if (nc == (-1)) {
					/* Not found with even high tolerance, so try to allocate it */
					nc = dst.ColorAllocate((int)red, (int)green, (int)blue);

					/* If we're out of colors, go for the closest color */
					if (nc == (-1))
						nc = dst.ColorClosest((int)red, (int)green, (int)blue);
				}
			}
			dst.SetPixel(x, y, nc);
		}
    }
}