void StatusButton::setUserMenu(QMenu *menu)
{
	setMenu(menu);

	connect(menu, SIGNAL(aboutToShow()), this, SLOT(onMenuAboutToShow()));
	connect(menu, SIGNAL(aboutToHide()), this, SLOT(onMenuAboutToHide()));
}