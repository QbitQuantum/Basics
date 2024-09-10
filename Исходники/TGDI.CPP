void CGdiBlitMasked::BaseTest(const TRect &aRect, TInt)
	{
// needs re-writing to emulate tiling of the source rect
	if (!aRect.Intersects(TRect(BaseWin->Size())))
		return;
	TSize size(aRect.Size());
	TSize bitSize=iBitmap->SizeInPixels();
	if (size.iWidth>bitSize.iWidth)
		size.iWidth=bitSize.iWidth;
	if (size.iHeight>bitSize.iHeight)
		size.iHeight=bitSize.iHeight;
//
// Set up the scratch mask as a black and white bitmap containing the mask to blit
// The mask pattern is replicated all over the scratchmask bitmap
//
	iScratchMaskGc->SetBrushStyle(CGraphicsContext::ESolidBrush);
	iScratchMaskGc->SetPenStyle(CGraphicsContext::ENullPen);
	iScratchMaskGc->SetBrushColor(TRgb(0,0,0));
	iScratchMaskGc->DrawRect(TRect(iScratchMask->SizeInPixels()));
	iScratchMaskGc->SetPenColor(TRgb(255,255,255));
	iScratchMaskGc->SetPenStyle(CGraphicsContext::ESolidPen);
	TSize maskSize(iCurrMask->SizeInPixels());
	TPoint pos;
	TRgb *rgbBuf=(TRgb *)User::AllocL(maskSize.iWidth*sizeof(TRgb));		//Doesn't do any harm if it leaves
	for(pos.iY=0;pos.iY<maskSize.iHeight;pos.iY++)
		{
		TPtr8 ptr((TUint8 *)rgbBuf,maskSize.iWidth*sizeof(TRgb));
		iCurrMask->GetScanLine(ptr, pos, maskSize.iWidth, ERgb);
		for(TInt index=0;index<maskSize.iWidth;index++)
			{
			iScratchMaskGc->SetPenColor(rgbBuf[index]);
//			if ((isLow && !iLowCutOff) || (!isLow && iLowCutOff))
				iScratchMaskGc->Plot(TPoint(index,pos.iY));
			}
		}
	User::Free(rgbBuf);

	for(pos.iY=0;pos.iY<size.iHeight;pos.iY+=maskSize.iHeight)
		for(pos.iX=0;pos.iX<size.iWidth;pos.iX+=maskSize.iWidth)
			iScratchMaskGc->CopyRect(pos, TRect(maskSize));
//
// Blit this to the screen in ANDNOT mode to clear all the pixels we want the mask blit to draw to
//
	iGdi->SetDrawMode(CGraphicsContext::EDrawModeANDNOT);
	iGdi->BitBlt(aRect.iTl, iScratchMask, TRect(size));
//
// Copy the test bitmap to the scratch bitmap then use the scratch mask to clear all the bits
// that should masked out of the draw to the screen
//
	iScratchGc->SetDrawMode(CGraphicsContext::EDrawModePEN);
	iScratchGc->BitBlt(TPoint(0,0), iBitmap);
	iScratchGc->SetDrawMode(CGraphicsContext::EDrawModeAND);
	iScratchGc->BitBlt(TPoint(0,0), iScratchMask);
//
// Now copy the scratch bitmap to the screen in OR mode to get the final result
//
	iGdi->SetDrawMode(CGraphicsContext::EDrawModeOR);
	iGdi->BitBlt(aRect.iTl, iScratch, TRect(size));
	}