ControlsPositionData BaseAlignHandler::AlignCenter(const List<UIControl*>& controlsList, bool isHorizontal)
{
	ControlsPositionData resultData;
	for (List<UIControl*>::const_iterator iter = controlsList.begin(); iter != controlsList.end(); iter ++)
	{
		UIControl* uiControl = *iter;
		if (!uiControl)
		{
			continue;
		}

		resultData.AddControl(uiControl);
	}

	// Perform the alignment on the first or last control, depending on the flag.
	UIControl* referenceControl = GetReferenceControl(controlsList);
	Vector2 referenceCenter = referenceControl->GetRect(true).GetCenter();

	// Second pass - update.
	for (List<UIControl*>::const_iterator iter = controlsList.begin(); iter != controlsList.end(); iter ++)
	{
		UIControl* uiControl = *iter;
		if (!uiControl)
		{
			continue;
		}

		Rect absoluteRect = uiControl->GetRect(true);
		Vector2 currentCenter = absoluteRect.GetCenter();
		if (isHorizontal)
		{
			absoluteRect.x -= (currentCenter.x - referenceCenter.x);
		}
		else
		{
			absoluteRect.y -= (currentCenter.y - referenceCenter.y);
		}

		uiControl->SetRect(absoluteRect, true);
	}

	return resultData;
}