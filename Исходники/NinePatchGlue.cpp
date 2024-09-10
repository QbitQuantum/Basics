void
NinePatchGlue::NinePatch_Draw(SkCanvas* canvas, const SkRect& bounds,
			      const BitmapGlue& bitmap, const Res_png_9patch& chunk,
			      const PaintGlue* paint, RegionGlue* *outRegion)
{
	if (canvas && canvas->quickReject(bounds, SkCanvas::kBW_EdgeType))
		return;

	PaintGlue defaultPaint;
	if (NULL == paint) {
		// matches default dither in NinePatchDrawable.java.
		defaultPaint.setDither(true);
		paint = &defaultPaint;
	}
    
	// if our SkCanvas were back by GL we should enable this and draw this as
	// a mesh, which will be faster in most cases.
	if (false) {
		SkNinePatch::DrawMesh(canvas, bounds, bitmap,
				      chunk.xDivs, chunk.numXDivs,
				      chunk.yDivs, chunk.numYDivs,
				      paint);
		return;
	}

	SkASSERT(canvas || outRegion);

	if (bounds.isEmpty() ||
	    bitmap.width() == 0 || bitmap.height() == 0 ||
	    (paint && paint->getXfermode() == NULL && paint->getAlpha() == 0)) {
		return;
	}
    
	// should try a quick-reject test before calling lockPixels 

	SkAutoLockPixels alp(bitmap);
	// after the lock, it is valid to check getPixels()
	if (bitmap.getPixels() == NULL)
		return;

	const bool hasXfer = paint->getXfermode() != NULL;
	SkRect      dst;
	SkIRect     src;

	const int32_t x0 = chunk.xDivs[0];
	const int32_t y0 = chunk.yDivs[0];
	const SkColor initColor = ((SkPaint*)paint)->getColor();
	const uint8_t numXDivs = chunk.numXDivs;
	const uint8_t numYDivs = chunk.numYDivs;
	int i;
	int j;
	int colorIndex = 0;
	uint32_t color;
	bool xIsStretchable;
	const bool initialXIsStretchable =  (x0 == 0);
	bool yIsStretchable = (y0 == 0);
	const int bitmapWidth = bitmap.width();
	const int bitmapHeight = bitmap.height();

	SkScalar* dstRights = (SkScalar*) alloca((numXDivs + 1) * sizeof(SkScalar));
	bool dstRightsHaveBeenCached = false;

	int numStretchyXPixelsRemaining = 0;
	for (i = 0; i < numXDivs; i += 2) {
		numStretchyXPixelsRemaining += chunk.xDivs[i + 1] - chunk.xDivs[i];
	}
	int numFixedXPixelsRemaining = bitmapWidth - numStretchyXPixelsRemaining;
	int numStretchyYPixelsRemaining = 0;
	for (i = 0; i < numYDivs; i += 2) {
		numStretchyYPixelsRemaining += chunk.yDivs[i + 1] - chunk.yDivs[i];
	}
	int numFixedYPixelsRemaining = bitmapHeight - numStretchyYPixelsRemaining;

	src.fTop = 0;
	dst.fTop = bounds.fTop;
	// The first row always starts with the top being at y=0 and the bottom
	// being either yDivs[1] (if yDivs[0]=0) of yDivs[0].  In the former case
	// the first row is stretchable along the Y axis, otherwise it is fixed.
	// The last row always ends with the bottom being bitmap.height and the top
	// being either yDivs[numYDivs-2] (if yDivs[numYDivs-1]=bitmap.height) or
	// yDivs[numYDivs-1]. In the former case the last row is stretchable along
	// the Y axis, otherwise it is fixed.
	//
	// The first and last columns are similarly treated with respect to the X
	// axis.
	//
	// The above is to help explain some of the special casing that goes on the
	// code below.

	// The initial yDiv and whether the first row is considered stretchable or
	// not depends on whether yDiv[0] was zero or not.
	for (j = yIsStretchable ? 1 : 0;
	     j <= numYDivs && src.fTop < bitmapHeight;
	     j++, yIsStretchable = !yIsStretchable) {
		src.fLeft = 0;
		dst.fLeft = bounds.fLeft;
		if (j == numYDivs) {
			src.fBottom = bitmapHeight;
			dst.fBottom = bounds.fBottom;
		} else {
			src.fBottom = chunk.yDivs[j];
			const int srcYSize = src.fBottom - src.fTop;
			if (yIsStretchable) {
				dst.fBottom = dst.fTop + calculateStretch(bounds.fBottom, dst.fTop,
									  srcYSize,
									  numStretchyYPixelsRemaining,
									  numFixedYPixelsRemaining);
				numStretchyYPixelsRemaining -= srcYSize;
			} else {
				dst.fBottom = dst.fTop + SkIntToScalar(srcYSize);
				numFixedYPixelsRemaining -= srcYSize;
			}
		}

		xIsStretchable = initialXIsStretchable;
		// The initial xDiv and whether the first column is considered
		// stretchable or not depends on whether xDiv[0] was zero or not.
		for (i = xIsStretchable ? 1 : 0;
		     i <= numXDivs && src.fLeft < bitmapWidth;
		     i++, xIsStretchable = !xIsStretchable) {
			color = chunk.colors[colorIndex++];
			if (i == numXDivs) {
				src.fRight = bitmapWidth;
				dst.fRight = bounds.fRight;
			} else {
				src.fRight = chunk.xDivs[i];
				if (dstRightsHaveBeenCached) {
					dst.fRight = dstRights[i];
				} else {
					const int srcXSize = src.fRight - src.fLeft;
					if (xIsStretchable) {
						dst.fRight = dst.fLeft + calculateStretch(bounds.fRight, dst.fLeft,
											  srcXSize,
											  numStretchyXPixelsRemaining,
											  numFixedXPixelsRemaining);
						numStretchyXPixelsRemaining -= srcXSize;
					} else {
						dst.fRight = dst.fLeft + SkIntToScalar(srcXSize);
						numFixedXPixelsRemaining -= srcXSize;
					}
					dstRights[i] = dst.fRight;
				}
			}
			// If this horizontal patch is too small to be displayed, leave
			// the destination left edge where it is and go on to the next patch
			// in the source.
			if (src.fLeft >= src.fRight) {
				src.fLeft = src.fRight;
				continue;
			}
			// Make sure that we actually have room to draw any bits
			if (dst.fRight <= dst.fLeft || dst.fBottom <= dst.fTop) {
				goto nextDiv;
			}
			// If this patch is transparent, skip and don't draw.
			if (color == Res_png_9patch::TRANSPARENT_COLOR && !hasXfer) {
				if (outRegion) {
					if (*outRegion == NULL) {
						*outRegion = new RegionGlue();
					}
					SkIRect idst;
					dst.round(&idst);
					//LOGI("Adding trans rect: (%d,%d)-(%d,%d)\n",
					//     idst.fLeft, idst.fTop, idst.fRight, idst.fBottom);
					(*outRegion)->op(idst, SkRegion::kUnion_Op);
				}
				goto nextDiv;
			}
			if (canvas) {
				drawStretchyPatch(*canvas, src, dst, bitmap, *paint, initColor,
						  color, hasXfer);
			}

		nextDiv:
			src.fLeft = src.fRight;
			dst.fLeft = dst.fRight;
		}
		src.fTop = src.fBottom;
		dst.fTop = dst.fBottom;
		dstRightsHaveBeenCached = true;
	}
}