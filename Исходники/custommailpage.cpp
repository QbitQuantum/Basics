void CustomMailPage::assignTabPage()
{
	if (FMessageWidgets && isWindow() && !isVisible())
		FMessageWidgets->assignTabWindowPage(this);
	else
		emit tabPageAssign();
}