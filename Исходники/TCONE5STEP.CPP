/**
  Auxilliary Function performing the layout for a control.\n
  Checks if the used up width and height are less that than the available width and height respectively.\n
  If yes, initializes the top left and bottom right coordinates of the control 
  and assigns the same to the control's extent.\n
  
  @return KErrNone if successful else KErrTooBig
*/
TInt CLayoutTest::LayoutControl(TUint aCurCtrlIndex, TSize aCtrlSize)
	{
	TInt layoutSuccess = KErrNone;
	// check that we haven't used all the space left on the screen
	if (((iSizeUsed.iWidth + aCtrlSize.iWidth + KHorizontalBorder) <= iLayoutRect.Width()) &&
		((iSizeUsed.iHeight + aCtrlSize.iHeight + KVerticalBorder) <= iLayoutRect.Height()))
		{
		TPoint topLeft(iSizeUsed.iWidth + KHorizontalBorder, iSizeUsed.iHeight + KVerticalBorder);
		TPoint bottomRight(iSizeUsed.iWidth + aCtrlSize.iWidth + KHorizontalBorder, 
						   iSizeUsed.iHeight + aCtrlSize.iHeight + KVerticalBorder);
		TRect ctrlRect(topLeft, bottomRight);
		CCoeControl* ctrl = iCtrlArray[aCurCtrlIndex];
		ctrl->SetRect(ctrlRect);
		iControlsCompleted++;
		}
	else
		{
		layoutSuccess = KErrTooBig;
		}
	return layoutSuccess;
	}