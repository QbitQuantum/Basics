wxPoint wxJigsawEditorCanvas::GetScrollPosition()
{
	return wxPoint(GetScrollPos(wxHORIZONTAL),GetScrollPos(wxVERTICAL));
}