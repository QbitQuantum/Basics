void CBitmapAnimator::RenderMask(CBitmapContext& aBitmapContext, TInt aFrame) const
	{
	aBitmapContext.Reset();
	
	const CAnimationFrame& nextFrame = *iFrameArray[aFrame];

	if (aFrame == 0)
		{
		aBitmapContext.SetBrushColor(KRgbBlack);
		aBitmapContext.Clear(iMaxSize);		
		}
	else
		{
		const CAnimationFrame& currentFrame = *iFrameArray[aFrame - 1];
		if (currentFrame.FrameInfo().iFlags & TFrameInfo::ERestoreToBackground)
			{
			aBitmapContext.SetBrushColor(KRgbBlack);
			aBitmapContext.Clear(currentFrame.FrameInfo().iFrameCoordsInPixels);
			}
		}
	const TBool useMask = nextFrame.FrameInfo().iFlags&TFrameInfo::ETransparencyPossible || nextFrame.FrameInfo().iFlags&TFrameInfo::EAlphaChannel;
	if (useMask)
		{
		aBitmapContext.SetDrawMode(CGraphicsContext::EDrawModeOR);
		aBitmapContext.BitBlt(nextFrame.FrameInfo().iFrameCoordsInPixels.iTl, nextFrame.Mask(), nextFrame.FrameInfo().iOverallSizeInPixels);
		}
	else
		{
		aBitmapContext.SetBrushColor(KRgbWhite);
		if (nextFrame.FrameInfo().iOverallSizeInPixels != nextFrame.FrameInfo().iFrameSizeInPixels)
			{
			// If the frame size smaller than the overall size, the mask shall not take effect later in CBasicAnimation::Draw().
			aBitmapContext.Clear(nextFrame.FrameInfo().iOverallSizeInPixels);
			}
		else
			{
			aBitmapContext.Clear(nextFrame.FrameInfo().iFrameCoordsInPixels);
			}
		}
	}