SkPath TextArt::EnvelopeWarp::warp(const std::string& text, SkTypeface* typeface)
{
	SkPath				warpedPath;

	if (text.empty())
		return warpedPath;

	//prepare paint
	SkPaint paint;
	paint.setTextSize(SkIntToScalar(64));
	paint.setTypeface(typeface);
	paint.setTextAlign(SkPaint::kCenter_Align);

	//measure Bottom path to center text on it
	SkPathMeasure   bMeasure(bSkeleton_, false);
	SkScalar        hBOffset = 0;

    if (paint.getTextAlign() != SkPaint::kLeft_Align)
	{
        SkScalar pathLen = bMeasure.getLength();
        if (paint.getTextAlign() == SkPaint::kCenter_Align)
		{
            pathLen = SkScalarHalf(pathLen);
        }
        hBOffset += pathLen;
    }

	//get text boundaries on normal(non-warped) state
	{
		SkMatrix scaleMartix;
		scaleMartix.setIdentity();

		SkTextToPathIter	iter(text.c_str(), text.size(), paint, true);
		const SkPath*   glypthPath;
		SkScalar        xpos;

		SkScalar        scale = iter.getPathScale();
		scaleMartix.setScale(scale, scale);

		while (iter.next(&glypthPath, &xpos))
		{
			if (glypthPath)
			{
				//prepare resulting transformatiom Matrix
				SkMatrix	compositeMatrix(scaleMartix);
				compositeMatrix.postTranslate(xpos + hBOffset, 0);
				
				SkPath p;
				(*glypthPath).transform(compositeMatrix, &p);
				//get normal(without any warps) text boundaries
				boundsRect_.join( p.getBounds() );
			}
		}
	}

	//center text on Top skeleton
	SkPathMeasure   tMeasure(tSkeleton_, false);
	SkScalar        hTOffset = 0;	
	{
		if (paint.getTextAlign() != SkPaint::kLeft_Align)
		{
			SkScalar pathLen = tMeasure.getLength();
			if (paint.getTextAlign() == SkPaint::kCenter_Align)
			{
				pathLen = SkScalarHalf(pathLen);
			}
			hTOffset += pathLen;
		}
	}		
	
	//warp text on Bottom and Top skeletons
	{
		SkTextToPathIter	iter(text.c_str(), text.size(), paint, true);
		SkScalar        xpos;

		SkMatrix        scaleMartix;
		SkScalar        scale = iter.getPathScale();
		scaleMartix.setScale(scale, scale);

		SkPath line;
		line.lineTo(SkIntToScalar(100), SkIntToScalar(0));
		SkPathMeasure   lineMeasure(line, false);

		SkPathCrossing bCrossing(bSkeleton_);
		SkPathCrossing tCrossing(tSkeleton_);

		const SkPath*   glypthPathOrig;
		while (iter.next(&glypthPathOrig, &xpos))
		{
			if (glypthPathOrig)
			{
				SkPath glypthPath;
				SkRect glypthBound;
				glypthBound = (*glypthPathOrig).getBounds();
				glypthPathOrig->offset(-glypthBound.fLeft, 0, &glypthPath);

				morph(bSkeleton_, bMeasure, bCrossing,
						tSkeleton_, tMeasure, tCrossing,
						glypthPath, lineMeasure, scaleMartix,
						xpos, hBOffset, hTOffset, warpedPath);

			}
		}
	}
	
	return warpedPath;
}