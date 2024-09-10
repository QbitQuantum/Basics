void DynamicDisplayItem::DrawIcon(HDC theDC, bool theSelected, const RECT & theContainer, const Theme * theTheme)
{
	gDisplayItemCS.Enter();

	int aIconSite = theTheme->GetMetric(WIDTH_ICONSITE);
	int aLeftIndent = theTheme->GetMetric(WIDTH_INDENT_LEFT);

	RECT aRect;
	aRect.left   = theContainer.left + aLeftIndent;
	aRect.top    = theContainer.top  + (theContainer.bottom - theContainer.top - aIconSite) / 2;
	aRect.right  = aRect.left + aIconSite;
	aRect.bottom = aRect.top + aIconSite;


	DWORD aPrevLayout = GetLayout(theDC);
	DWORD aNewLayout = aPrevLayout | LAYOUT_BITMAPORIENTATIONPRESERVED;
	SetLayout(theDC, aNewLayout);

	int aDrawItemFlags = theSelected ? DIIF_NORMAL : DIIF_SELECTED;
	if (myIconData.IsIconDimmed)
		aDrawItemFlags |= DIIF_DIMMED;

	theTheme->DrawItemIcon(theDC, aDrawItemFlags, aRect, myIconData.ImageList, myIconData.IconIndex);

	if (myIconData.OverlayIndex != -1)
	{
		HIMAGELIST aSmall, aLarge;
		BOOL aRet = Shell_GetImageLists(&aLarge, &aSmall);

		if (aRet && aSmall != 0)
			ImageList_Draw(aSmall, myIconData.OverlayIndex, theDC, aRect.left, aRect.top, ILD_TRANSPARENT);
	}

	SetLayout(theDC, aPrevLayout);

	gDisplayItemCS.Leave();
}