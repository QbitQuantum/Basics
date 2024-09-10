void CSpriteSet::RenderSprite(TInt aSpriteType, TInternalSpriteResizeMode aInternalSpriteResizeMode, const TSize& aSourceSize, const TSize& aSpriteSize)
	{
	const TInt sourceWidth = aSourceSize.iWidth;
	const TInt sourceHeight = aSourceSize.iHeight;
	const TInt spriteWidth = aSpriteSize.iWidth;
	const TInt spriteHeight = aSpriteSize.iHeight;
	const TInt numOfHorizAddedLines = spriteHeight-sourceHeight;
	const TInt numOfVertAddedLines = spriteWidth-sourceWidth;
	const TPoint posZeroZero(0,0);	// cached for repeated use
	CGulIcon* spriteSetMember = iSourceMembers[aSpriteType];
	CFbsBitmap* bitmapToUse = spriteSetMember->Bitmap();
	CFbsBitmap* maskToUse = spriteSetMember->Mask();
	TRect fromRect;
	TPoint toPoint;

	switch(aInternalSpriteResizeMode)
		{
	case EHSameVSame:
		{
		fromRect.SetRect(0,0,sourceWidth,sourceHeight);
		iMainFbsBitGc->BitBlt(posZeroZero,bitmapToUse,fromRect);
		iMaskFbsBitGc->BitBlt(posZeroZero,maskToUse,fromRect);
		break;
		}
	case EHSameVShrink:
		{
		const TInt halfSpriteHeight = spriteHeight/2;
		fromRect.SetRect(0,0,spriteWidth,halfSpriteHeight);
		iMainFbsBitGc->BitBlt(posZeroZero,bitmapToUse,fromRect);
		iMaskFbsBitGc->BitBlt(posZeroZero,maskToUse,fromRect);
		fromRect.SetRect(0,sourceHeight - (halfSpriteHeight) - (spriteHeight%2),sourceWidth,sourceHeight);
		toPoint.SetXY(0,halfSpriteHeight);
		iMainFbsBitGc->BitBlt(toPoint,bitmapToUse,fromRect);
		iMaskFbsBitGc->BitBlt(toPoint,maskToUse,fromRect);
		break;
		}
	case EHSameVStretch:
		{
		const TInt halfSourceHeight = sourceHeight/2;
		fromRect.SetRect(0,0,sourceWidth,halfSourceHeight);
		iMainFbsBitGc->BitBlt(posZeroZero,bitmapToUse,fromRect);
		iMaskFbsBitGc->BitBlt(posZeroZero,maskToUse,fromRect);
		fromRect.SetRect(0,halfSourceHeight,sourceWidth,sourceHeight);
		toPoint.SetXY(0,spriteHeight-(halfSourceHeight)-(sourceHeight%2));
		iMainFbsBitGc->BitBlt(toPoint,bitmapToUse,fromRect);
		iMaskFbsBitGc->BitBlt(toPoint,maskToUse,fromRect);
		for(TInt i = 0; i < numOfHorizAddedLines;i++)
			{
			fromRect.SetRect(0,halfSourceHeight,sourceWidth,(halfSourceHeight)+1);
			toPoint.SetXY(0,(halfSourceHeight)+i);
			iMainFbsBitGc->BitBlt(toPoint,bitmapToUse,fromRect);
			iMaskFbsBitGc->BitBlt(toPoint,maskToUse,fromRect);
			}
		break;
		}
	case EHShrinkVSame:
		{
		const TInt halfSpriteWidth = spriteWidth/2;
		fromRect.SetRect(0,0,halfSpriteWidth,spriteHeight);
		iMainFbsBitGc->BitBlt(posZeroZero,bitmapToUse,fromRect);
		iMaskFbsBitGc->BitBlt(posZeroZero,maskToUse,fromRect);
		fromRect.SetRect(sourceWidth - (halfSpriteWidth) - (spriteWidth%2),0,sourceWidth,sourceHeight);
		toPoint.SetXY(halfSpriteWidth,0);
		iMainFbsBitGc->BitBlt(toPoint,bitmapToUse,fromRect);
		iMaskFbsBitGc->BitBlt(toPoint,maskToUse,fromRect);
		break;
		}
	case EHShrinkVShrink:
		{
		const TInt halfSpriteWidth = spriteWidth/2;
		const TInt halfSpriteHeight = spriteHeight/2;
		const TInt spriteHeightModTwo = spriteHeight%2;
		const TInt spriteWidthModTwo = spriteWidth%2;
		fromRect.SetRect(0,0,halfSpriteWidth,halfSpriteHeight);
		iMainFbsBitGc->BitBlt(posZeroZero,bitmapToUse,fromRect);
		iMaskFbsBitGc->BitBlt(posZeroZero,maskToUse,fromRect);
		fromRect.SetRect(sourceWidth - (halfSpriteWidth) - (spriteWidthModTwo),0,sourceWidth,halfSpriteHeight);
		toPoint.SetXY(halfSpriteWidth,0);
		iMainFbsBitGc->BitBlt(toPoint,bitmapToUse,fromRect);
		iMaskFbsBitGc->BitBlt(toPoint,maskToUse,fromRect);
		fromRect.SetRect(0,sourceHeight - (halfSpriteHeight) - (spriteHeightModTwo),halfSpriteWidth,sourceHeight);
		toPoint.SetXY(0,halfSpriteHeight);
		iMainFbsBitGc->BitBlt(toPoint,bitmapToUse,fromRect);
		iMaskFbsBitGc->BitBlt(toPoint,maskToUse,fromRect);
		fromRect.SetRect(sourceWidth - (halfSpriteWidth) - (spriteWidthModTwo),sourceHeight - (halfSpriteHeight) - (spriteHeightModTwo),sourceWidth,sourceHeight);
		toPoint.SetXY(halfSpriteWidth,halfSpriteHeight);
		iMainFbsBitGc->BitBlt(toPoint,bitmapToUse,fromRect);
		iMaskFbsBitGc->BitBlt(toPoint,maskToUse,fromRect);
		break;
		}
	case EHShrinkVStretch:
		{
		const TInt halfSourceHeight = sourceHeight/2;
		const TInt halfSpriteWidth = spriteWidth/2;
		const TInt sourceHeightModTwo = sourceHeight%2;
		const TInt spriteWidthModTwo = spriteWidth%2;
		fromRect.SetRect(0,0,halfSpriteWidth,halfSourceHeight);	
		iMainFbsBitGc->BitBlt(posZeroZero,bitmapToUse,fromRect);
		iMaskFbsBitGc->BitBlt(posZeroZero,maskToUse,fromRect);
		fromRect.SetRect(sourceWidth - (halfSpriteWidth) - (spriteWidthModTwo),0,sourceWidth,halfSourceHeight);
		toPoint.SetXY(halfSpriteWidth,0);
		iMainFbsBitGc->BitBlt(toPoint,bitmapToUse,fromRect);
		iMaskFbsBitGc->BitBlt(toPoint,maskToUse,fromRect);
		fromRect.SetRect(0,sourceHeight - (halfSourceHeight) - (sourceHeightModTwo),halfSpriteWidth,sourceHeight);
		toPoint.SetXY(0,spriteHeight - (halfSourceHeight) - (sourceHeightModTwo));
		iMainFbsBitGc->BitBlt(toPoint,bitmapToUse,fromRect);
		iMaskFbsBitGc->BitBlt(toPoint,maskToUse,fromRect);
		fromRect.SetRect(sourceWidth - (halfSpriteWidth) - (spriteWidthModTwo),sourceHeight - (halfSourceHeight) - (sourceHeightModTwo),sourceWidth,sourceHeight);
		toPoint.SetXY(halfSpriteWidth,spriteHeight - (halfSourceHeight) - (sourceHeightModTwo));
		iMainFbsBitGc->BitBlt(toPoint,bitmapToUse,fromRect);
		iMaskFbsBitGc->BitBlt(toPoint,maskToUse,fromRect);
		for(TInt j = 0; j < numOfHorizAddedLines;j++)
			{
			fromRect.SetRect(0,spriteHeight - (halfSourceHeight) - (sourceHeightModTwo),spriteWidth,spriteHeight - (halfSourceHeight) - (sourceHeightModTwo)+1);
			toPoint.SetXY(0,(halfSourceHeight)+j);
			iMainFbsBitGc->BitBlt(toPoint,iTargetBitmap,fromRect);
			iMaskFbsBitGc->BitBlt(toPoint,iTargetMaskBitmap,fromRect);
			}
		break;
		}
	case EHStretchVSame:
		{
		const TInt halfSourceWidth = sourceWidth/2;
		fromRect.SetRect(0,0,halfSourceWidth,sourceHeight);
		iMainFbsBitGc->BitBlt(posZeroZero,bitmapToUse,fromRect);
		iMaskFbsBitGc->BitBlt(posZeroZero,maskToUse,fromRect);
		fromRect.SetRect(halfSourceWidth,0,sourceWidth,sourceHeight);
		toPoint.SetXY(spriteWidth-(halfSourceWidth)-(sourceWidth%2),0);
		iMainFbsBitGc->BitBlt(toPoint,bitmapToUse,fromRect);
		iMaskFbsBitGc->BitBlt(toPoint,maskToUse,fromRect);
		for(TInt i = 0; i < numOfVertAddedLines;i++)
			{
			fromRect.SetRect(halfSourceWidth,0,(halfSourceWidth)+1,sourceHeight);
			toPoint.SetXY((halfSourceWidth)+i,0);
			iMaskFbsBitGc->BitBlt(toPoint,maskToUse,fromRect);
			iMainFbsBitGc->BitBlt(toPoint,bitmapToUse,fromRect);
			}
		break;
		}
	case EHStretchVShrink:
		{
		const TInt halfSourceWidth = sourceWidth/2;
		const TInt halfSpriteHeight = spriteHeight/2;
		const TInt sourceWidthModTwo = sourceWidth%2;
		const TInt spriteHeightModTwo = spriteHeight%2;
		fromRect.SetRect(0,0,halfSourceWidth,halfSpriteHeight);
		iMainFbsBitGc->BitBlt(posZeroZero,bitmapToUse,fromRect);
		iMaskFbsBitGc->BitBlt(posZeroZero,maskToUse,fromRect);
		fromRect.SetRect(sourceWidth - (halfSourceWidth) - (sourceWidthModTwo),0,sourceWidth,halfSpriteHeight);
		toPoint.SetXY(spriteWidth - (halfSourceWidth) - (sourceWidthModTwo),0);
		iMainFbsBitGc->BitBlt(toPoint,bitmapToUse,fromRect);
		iMaskFbsBitGc->BitBlt(toPoint,maskToUse,fromRect);
		fromRect.SetRect(0,sourceHeight - (halfSpriteHeight) - (spriteHeightModTwo),halfSourceWidth,sourceHeight);
		toPoint.SetXY(0,halfSpriteHeight);
		iMainFbsBitGc->BitBlt(toPoint,bitmapToUse,fromRect);
		iMaskFbsBitGc->BitBlt(toPoint,maskToUse,fromRect);
		fromRect.SetRect(sourceWidth - (halfSourceWidth) - (sourceWidthModTwo),sourceHeight - (halfSpriteHeight) - (spriteHeightModTwo),sourceWidth,sourceHeight);
		toPoint.SetXY(spriteWidth - (halfSourceWidth) - (sourceWidthModTwo),halfSpriteHeight);
		iMainFbsBitGc->BitBlt(toPoint,bitmapToUse,fromRect);
		iMaskFbsBitGc->BitBlt(toPoint,maskToUse,fromRect);
		for(TInt j = 0; j < numOfVertAddedLines;j++)
			{
			fromRect.SetRect(spriteWidth - (halfSourceWidth) - (sourceWidthModTwo),0,spriteWidth - (halfSourceWidth) - (sourceWidthModTwo)+1,spriteHeight);
			toPoint.SetXY((halfSourceWidth)+j,0);
			iMainFbsBitGc->BitBlt(toPoint,iTargetBitmap,fromRect);
			iMaskFbsBitGc->BitBlt(toPoint,iTargetMaskBitmap,fromRect);
			}
		break;
		}
	case EHStretchVStretch:
		{
		const TInt halfSourceWidth = sourceWidth/2;
		const TInt halfSourceHeight = sourceHeight/2;
		const TInt sourceWidthModTwo = sourceWidth%2;
		const TInt sourceHeightModTwo = sourceHeight%2;
		fromRect.SetRect(0,0,halfSourceWidth,halfSourceHeight);
		iMaskFbsBitGc->BitBlt(posZeroZero,maskToUse,fromRect);
		iMainFbsBitGc->BitBlt(posZeroZero,maskToUse,fromRect);
		fromRect.SetRect(0,halfSourceHeight,halfSourceWidth,sourceHeight);
		toPoint.SetXY(0,spriteHeight-(halfSourceHeight)-(sourceHeightModTwo));
		iMaskFbsBitGc->BitBlt(toPoint,maskToUse,fromRect);
		iMainFbsBitGc->BitBlt(toPoint,maskToUse,fromRect);
		fromRect.SetRect(halfSourceWidth,0,sourceWidth,halfSourceHeight);
		toPoint.SetXY(spriteWidth-(halfSourceWidth)-(sourceWidthModTwo),0);
		iMaskFbsBitGc->BitBlt(toPoint,maskToUse,fromRect);
		iMainFbsBitGc->BitBlt(toPoint,maskToUse,fromRect);
		fromRect.SetRect(halfSourceWidth,halfSourceHeight,sourceWidth,sourceHeight);
		toPoint.SetXY(spriteWidth-(halfSourceWidth)-(sourceWidthModTwo),spriteHeight-(halfSourceHeight)-(sourceHeightModTwo));
		iMaskFbsBitGc->BitBlt(toPoint,maskToUse,fromRect);
		iMainFbsBitGc->BitBlt(toPoint,maskToUse,fromRect);
		for(TInt h = 0; h < numOfVertAddedLines;h++)
			{
			fromRect.SetRect(spriteWidth-(halfSourceWidth)-(sourceWidthModTwo),0,spriteWidth-(halfSourceWidth)-(sourceWidthModTwo)+1,spriteHeight);
			toPoint.SetXY((halfSourceWidth)+h,0);
			iMainFbsBitGc->BitBlt(toPoint,iTargetBitmap,fromRect);
			iMaskFbsBitGc->BitBlt(toPoint,iTargetBitmap,fromRect);
			}
		for(TInt m = 0; m < numOfHorizAddedLines;m++)
			{
			fromRect.SetRect(0,spriteHeight-(halfSourceHeight)-(sourceHeightModTwo),spriteWidth,spriteHeight-(halfSourceHeight)-(sourceHeightModTwo)+1);
			toPoint.SetXY(0,(halfSourceHeight)+m);
			iMaskFbsBitGc->BitBlt(toPoint,iTargetBitmap,fromRect);
			}
		fromRect.SetRect(0,0,halfSourceWidth,halfSourceHeight);
		iMainFbsBitGc->BitBlt(posZeroZero,bitmapToUse,fromRect);
		fromRect.SetRect(0,halfSourceHeight,halfSourceWidth,sourceHeight);
		toPoint.SetXY(0,spriteHeight-(halfSourceHeight)-(sourceHeightModTwo));
		iMainFbsBitGc->BitBlt(toPoint,bitmapToUse,fromRect);
		fromRect.SetRect(halfSourceWidth,0,sourceWidth,halfSourceHeight);
		toPoint.SetXY(spriteWidth-(halfSourceWidth)-(sourceWidthModTwo),0);
		iMainFbsBitGc->BitBlt(toPoint,bitmapToUse,fromRect);
		fromRect.SetRect(halfSourceWidth,halfSourceHeight,sourceWidth,sourceHeight);
		toPoint.SetXY(spriteWidth-(halfSourceWidth)-(sourceWidthModTwo),spriteHeight-(halfSourceHeight)-(sourceHeightModTwo));
		iMainFbsBitGc->BitBlt(toPoint,bitmapToUse,fromRect);
		for(TInt j = 0; j < numOfVertAddedLines;j++)
			{
			fromRect.SetRect(spriteWidth-(halfSourceWidth)-(sourceWidthModTwo),0,spriteWidth-(halfSourceWidth)-(sourceWidthModTwo)+1,spriteHeight);
			toPoint.SetXY((halfSourceWidth)+j,0);
			iMainFbsBitGc->BitBlt(toPoint,iTargetBitmap,fromRect);
			}
		for(TInt i = 0; i < numOfHorizAddedLines;i++)
			{
			fromRect.SetRect(0,spriteHeight-(halfSourceHeight)-(sourceHeightModTwo),spriteWidth,spriteHeight-(halfSourceHeight)-(sourceHeightModTwo)+1);
			toPoint.SetXY(0,(halfSourceHeight)+i);
			iMainFbsBitGc->BitBlt(toPoint,iTargetBitmap,fromRect);
			}
		break;
		}
	default:
		Panic(EEgulPanicInvalidInternalSpriteResizeMode);
		break;
		}
	}