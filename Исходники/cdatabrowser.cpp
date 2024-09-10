//-----------------------------------------------------------------------------
CMouseEventResult CDataBrowser::onMouseDown (CPoint& where, const CButtonState& buttons)
{
	CMouseEventResult result = CViewContainer::onMouseDown (where, buttons);
	CView* focusView = getFrame ()->getFocusView ();
	if (focusView != dbView && !isChild (focusView, true))
		getFrame ()->setFocusView (dbView);
	return result;
}