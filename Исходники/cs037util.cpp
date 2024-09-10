void Window::setParent(Window* parent)
{
	if (!mHWND) {
		mParent = parent; // parent will be used in realize() later on
		mParent->mChildren.push_back(this);
		onParentChanged();
		return;
	}
	// Otherwise, reparent
	LONG currStyle = GetWindowLong(handle(), GWL_STYLE);
	if (parent) {
		SetParent(handle(), parent->handle());
		SETWINDOWLONGPTR(handle(), GWL_STYLE, currStyle | WS_CHILD);
	} else {
		SetParent(handle(), 0);
		SETWINDOWLONGPTR(handle(), GWL_STYLE, currStyle & ~WS_CHILD);
	}
	if (mParent)
		mParent->rebuildChildrenList();
	mParent = parent;
	if (mParent)
		mParent->rebuildChildrenList();
	onParentChanged();
}