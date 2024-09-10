void RWsTextCursor::Draw(CFbsBitGc* aGc, const TRegion& aRegion)
	{
	iDrawRegion.Copy(iWin->VisibleRegion());
	if (iFlags&ETextCursorFlagClipped)
		{
		TRect rect(iClipRect);
		rect.Move(iWin->Origin());
		iDrawRegion.ClipRect(rect);
		}

	// Need to clip against a possible recent screen size change.
	iDrawRegion.ClipRect(iWin->Screen()->DrawDevice()->SizeInPixels());


	RWsRegion tmpRegion;
	tmpRegion.Intersection(iDrawRegion, aRegion);
	if (tmpRegion.CheckError())
		doDraw(aGc, iDrawRegion);
	else
		{
		if (!tmpRegion.IsEmpty())
			{
			doDraw(aGc, tmpRegion);
			}
		}
	tmpRegion.Close();
	}