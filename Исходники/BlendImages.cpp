/******************* TO DO *********************
* AccumulateBlend:
*	INPUT:
*		img: a new image to be added to acc
*		acc: portion of the accumulated image where img is to be added
*       M: the transformation mapping the input image 'img' into the output panorama 'acc'
*		blendWidth: width of the blending function (horizontal hat function;
*	    try other blending functions for extra credit)
*	OUTPUT:
*		add a weighted copy of img to the subimage specified in acc
*		the first 3 band of acc records the weighted sum of pixel colors
*		the fourth band of acc records the sum of weight
*/
static void AccumulateBlend(CByteImage& img, CFloatImage& acc, CTransform3x3 M, float blendWidth)
{
    // BEGIN TODO
    // Fill in this routine
	// get shape of acc and img
	CShape sh = img.Shape();
    int width = sh.width;
    int height = sh.height;
	CShape shacc = acc.Shape();
    int widthacc = shacc.width;
    int heightacc = shacc.height;
	
	// get the bounding box of img in acc
	int min_x, min_y, max_x, max_y;
	ImageBoundingBox(img, M, min_x, min_y, max_x, max_y);

	CVector3 p;
	double newx, newy;

	// Exposure Compensation
	double lumaScale = 1.0;
	double lumaAcc = 0.0;
	double lumaImg = 0.0;
	int cnt = 0;

	for (int ii = min_x; ii < max_x; ii++)
		for (int jj = min_y; jj < max_y; jj++)
		{
			// flag: current pixel black or not
			bool flag = false;
			p[0] = ii; p[1] = jj; p[2] = 1;
			p = M.Inverse() * p;
			newx = p[0] / p[2];
			newy = p[1] / p[2];
			// If in the overlapping region
			if (newx >=0 && newx < width && newy >=0 && newy < height)
			{
				if (acc.Pixel(ii,jj,0) == 0 &&
					acc.Pixel(ii,jj,1) == 0 &&
					acc.Pixel(ii,jj,2) == 0)
					flag = true;
				if (img.PixelLerp(newx,newy,0) == 0 &&
					img.PixelLerp(newx,newy,1) == 0 &&
					img.PixelLerp(newx,newy,2) == 0)
					flag = true;
				if (!flag)
				{
					// Compute Y using RGB (RGB -> YUV)
					lumaAcc = 0.299 * acc.Pixel(ii,jj,0) +
							   0.587 * acc.Pixel(ii,jj,1) +
							   0.114 * acc.Pixel(ii,jj,2);
					lumaImg = 0.299 * img.PixelLerp(newx,newy,0) +
							   0.587 * img.PixelLerp(newx,newy,1) +
							   0.114 * img.PixelLerp(newx,newy,2);
					
					if (lumaImg != 0)
					{
						double scale = lumaAcc / lumaImg;
						if (scale > 0.5 && scale < 2)
						{
							lumaScale += lumaAcc / lumaImg;
							cnt++;
						}
					}
				}
			}
		}

	if (cnt != 0)
		lumaScale = lumaScale / (double)cnt;
	else lumaScale = 1.0;

	// add every pixel in img to acc, feather the region withing blendwidth to the bounding box,
	// pure black pixels (caused by warping) are not added
	double weight;
	
	for (int ii = min_x; ii < max_x; ii++)
		for (int jj = min_y; jj < max_y; jj++)
		{
			p[0] = ii; p[1] = jj; p[2] = 1;
			p = M.Inverse() * p;
			newx = p[0] / p[2];
			newy = p[1] / p[2];
			if ((newx >= 0) && (newx < width-1) && (newy >= 0) && (newy < height-1))
			{
				weight = 1.0;
				if ( (ii >= min_x) && (ii < (min_x+blendWidth)) )
					weight = (ii-min_x) / blendWidth;
				if ( (ii <= max_x) && (ii > (max_x-blendWidth)) )
					weight = (max_x-ii) / blendWidth;
				if (img.Pixel(iround(newx),iround(newy),0) == 0 &&
					img.Pixel(iround(newx),iround(newy),1) == 0 &&
					img.Pixel(iround(newx),iround(newy),2) == 0)
					weight = 0.0;

				double LerpR = img.PixelLerp(newx, newy, 0);
				double LerpG = img.PixelLerp(newx, newy, 1);
				double LerpB = img.PixelLerp(newx, newy, 2);
				
				double r = LerpR*lumaScale > 255.0 ? 255.0 : LerpR*lumaScale;
				double g = LerpG*lumaScale > 255.0 ? 255.0 : LerpG*lumaScale;
				double b = LerpB*lumaScale > 255.0 ? 255.0 : LerpB*lumaScale;
				acc.Pixel(ii,jj,0) += r * weight;
				acc.Pixel(ii,jj,1) += g * weight;
				acc.Pixel(ii,jj,2) += b * weight;
				acc.Pixel(ii,jj,3) += weight;
			}
		}
	
	printf("AccumulateBlend\n"); 

    // END TODO
}