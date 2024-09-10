ToolbarView::ToolbarView()
	: BGroupView(B_HORIZONTAL, 5)
{
	SetFlags(Flags() | B_WILL_DRAW);
	SetViewColor(ui_color(B_MENU_BACKGROUND_COLOR));
}