//-----------------------------------------------------------------------------
bool CFrame::advanceNextFocusView (CView* oldFocus, bool reverse)
{
	if (pModalView)
	{
		CViewContainer* container = dynamic_cast<CViewContainer*> (pModalView);
		if (container)
		{
			if (oldFocus == 0 || container->isChild (oldFocus, true) == false)
				return container->advanceNextFocusView (0, reverse);
			else
			{
				CViewContainer* parentView = static_cast<CViewContainer*> (oldFocus->getParentView ());
				if (parentView)
				{
					CView* tempOldFocus = oldFocus;
					while (parentView != container)
					{
						if (parentView->advanceNextFocusView (tempOldFocus, reverse))
							return true;
						else
						{
							tempOldFocus = parentView;
							parentView = static_cast<CViewContainer*> (parentView->getParentView ());
						}
					}
					if (container->advanceNextFocusView (tempOldFocus, reverse))
						return true;
					return container->advanceNextFocusView (0, reverse);
				}
			}
		}
		else if (oldFocus != pModalView)
		{
			setFocusView (pModalView);
			return true;
		}
		return false; // currently not supported, but should be done sometime
	}
	if (oldFocus == 0)
	{
		if (pFocusView == 0)
			return CViewContainer::advanceNextFocusView (0, reverse);
		oldFocus = pFocusView;
	}
	if (isChild (oldFocus))
	{
		if (CViewContainer::advanceNextFocusView (oldFocus, reverse))
			return true;
		else
		{
			setFocusView (0);
			return false;
		}
	}
	CViewContainer* parentView = static_cast<CViewContainer*> (oldFocus->getParentView ());
	if (parentView)
	{
		CView* tempOldFocus = oldFocus;
		while (parentView)
		{
			if (parentView->advanceNextFocusView (tempOldFocus, reverse))
				return true;
			else
			{
				tempOldFocus = parentView;
				parentView = static_cast<CViewContainer*> (parentView->getParentView ());
			}
		}
	}
	return CViewContainer::advanceNextFocusView (oldFocus, reverse);
}