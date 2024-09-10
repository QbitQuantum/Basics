DesktopDock::~DesktopDock()
{
	kdebugf();

	destroyMenu();

	delete MoveMenuAction;
	MoveMenuAction = 0;

	delete DockWindow;
	DockWindow = 0;

	kdebugf2();
}