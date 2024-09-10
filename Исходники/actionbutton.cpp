void ActionButton::onActionChanged()
{
	if (FAction)
	{
		setIcon(FAction->icon());
		setText(FAction->text());
		setMenu(FAction->menu());
	}
	else
	{
		setIcon(QIcon());
		setText(QString::null);
		setMenu(NULL);
	}
	emit buttonChanged();
}