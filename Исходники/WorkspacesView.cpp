BRect
WorkspacesView::_WindowFrame(const BRect& workspaceFrame,
	const BRect& screenFrame, const BRect& windowFrame,
	BPoint windowPosition)
{
	BRect frame = windowFrame;
	frame.OffsetTo(windowPosition);

	// scale down the rect
	float factor = workspaceFrame.Width() / screenFrame.Width();
	frame.left = frame.left * factor;
	frame.right = frame.right * factor;

	factor = workspaceFrame.Height() / screenFrame.Height();
	frame.top = frame.top * factor;
	frame.bottom = frame.bottom * factor;

	// offset by the workspace fame position
	// and snap to integer coordinates without distorting the size too much
	frame.OffsetTo(rintf(frame.left + workspaceFrame.left),
		rintf(frame.top + workspaceFrame.top));
	frame.right = rintf(frame.right);
	frame.bottom = rintf(frame.bottom);

	return frame;
}