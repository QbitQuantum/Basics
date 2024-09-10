void VGraphicPath::_ComputeBounds()
{
	if (fComputeBoundsAccurate)
	{
		if (fPathMin == GP_BOUNDS_MIN_DEFAULT
			||
			fPathMax == GP_BOUNDS_MAX_DEFAULT)
			fBounds = VRect(0,0,0,0);
		else
			fBounds.SetCoords(	(GReal)fPathMin.x, 
								(GReal)fPathMin.y, 
								(GReal)(fPathMax.x-fPathMin.x), 
								(GReal)(fPathMax.y-fPathMin.y));
	}
	else
	{
#if ENABLE_D2D
		if (fPathD2D != NULL)
		{
			if (fGeomSink == NULL)
			{
				D2D1_RECT_F bounds;
				fPathD2D->GetBounds( NULL, &bounds);
				fBounds.SetCoords( bounds.left, bounds.top, bounds.right-bounds.left, bounds.bottom-bounds.top);
				return;
			}
		}
#endif

#if !GRAPHIC_MIXED_GDIPLUS_D2D
		if (!VWinD2DGraphicContext::IsAvailable())
		{
#endif
			Gdiplus::RectF bounds;
			fPath->GetBounds( &bounds);
			fBounds = VRect ( bounds.GetLeft(), bounds.GetTop(), bounds.GetRight()-bounds.GetLeft(), bounds.GetBottom()-bounds.GetTop());
#if !GRAPHIC_MIXED_GDIPLUS_D2D
		}
#endif
	}
}