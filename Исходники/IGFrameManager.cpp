void IGFrameManager::getIntersectFrameList (IGSmartPtr <IGFrame> const &spFrame, std::list <IGSmartPtr <IGFrame>> &spIntersectFrameList, bool bTry)
{
	// get frame layout
	float fLayoutWidth = 0;
	float fLayoutHeight = 0;
	float fLayoutTop = 0;
	float fLayoutLeft = 0;
	spFrame->GetLayout (fLayoutLeft, fLayoutTop, fLayoutWidth, fLayoutHeight, bTry);
	float fLayoutRight = fLayoutLeft + fLayoutWidth;
	float fLayoutBottom = fLayoutTop + fLayoutHeight;
	// current frame layout
	float fCurrentLayoutWidth = 0;
	float fCurrentLayoutHeight = 0;
	float fCurrentLayoutTop = 0;
	float fCurrentLayoutLeft = 0;
	for (std::list<IGSmartPtr <IGFrame>>::const_iterator iterFrames = m_lspFrames.begin(); 
		iterFrames != m_lspFrames.end();
		++iterFrames)
	{
		if (*iterFrames == spFrame)
			continue;	// do not process intersection with itself
		if (isMinimized (*iterFrames))
			continue;
		// if current frame is already in intersect list, just skip it
		bool bAlreadyInList = false;
		for (std::list<IGSmartPtr <IGFrame>>::const_iterator iterIsectFrames = spIntersectFrameList.begin(); 
			iterIsectFrames != spIntersectFrameList.end();
			++iterIsectFrames)
		{
			if (*iterIsectFrames == *iterFrames)
			{
				bAlreadyInList = true;
				break;
			}
		}
		if (bAlreadyInList)
			continue;		
		// get current frame layout
		(*iterFrames)->GetLayout (fCurrentLayoutLeft, fCurrentLayoutTop, fCurrentLayoutWidth, fCurrentLayoutHeight, bTry);
		// compute intersection
		if (fLayoutRight <= fCurrentLayoutLeft)
			continue;
		if (fLayoutBottom <= fCurrentLayoutTop)
			continue;
		if (fLayoutLeft >= (float)(fCurrentLayoutLeft + fCurrentLayoutWidth))
			continue;
		if (fLayoutTop >= (float)(fCurrentLayoutTop + fCurrentLayoutHeight))
			continue;
		// an intersection has been found, add it to the list
		spIntersectFrameList.push_back (*iterFrames);
	}
}