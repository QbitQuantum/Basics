static void DrawIconL(CWindowGc& aGc, CGulIcon& aIcon, const TJuikLayoutItem& aL, TBool aDoCenter=ETrue) 
{
	CALLSTACKITEMSTATIC_N(_CL(""), _CL("DrawIconL"));
	CFbsBitmap* bmp = aIcon.Bitmap();
	CFbsBitmap* mask = aIcon.Mask();
	
	aGc.SetBrushStyle(CGraphicsContext::ENullBrush);
	// center 
	TInt bmpW = bmp->SizeInPixels().iWidth;
	TInt areaW = aL.Size().iWidth;
	
	TInt dx = 0;
	TInt dy = 0;
	if ( aDoCenter && bmpW < areaW )
		{
			dx = (areaW - bmpW) / 2;
		}


	TPoint tl = aL.TopLeft();
	tl += TPoint(dx,dy);
	TRect r(TPoint(0,0), bmp->SizeInPixels());
 	if ( mask )
 		{
 			aGc.BitBltMasked( tl, bmp, r, mask, ETrue);
 		}
 	else
 		{
			aGc.BitBlt( tl, bmp, r);
  		}
}