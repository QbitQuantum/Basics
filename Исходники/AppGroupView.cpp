AppGroupView::AppGroupView(NotificationWindow* win, const char* label)
	:
	BGroupView("appGroup", B_VERTICAL, 0),
	fLabel(label),
	fParent(win),
	fCollapsed(false)
{
	SetFlags(Flags() | B_WILL_DRAW);

	static_cast<BGroupLayout*>(GetLayout())->SetInsets(0, kHeaderSize, 0, 0);
}