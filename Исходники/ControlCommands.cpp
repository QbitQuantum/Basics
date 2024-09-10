void ControlsAdjustSizeCommand::UndoAdjustedSize(const ControlsPositionData& sizeData)
{
	for (Map<UIControl*, Rect>::const_iterator iter = sizeData.GetControlPositions().begin();
		 iter != sizeData.GetControlPositions().end(); iter ++)
	{
		UIControl* control = iter->first;
		Rect rect = iter->second;

		if (control)
		{
			control->SetRect(rect);
		}
	}
}