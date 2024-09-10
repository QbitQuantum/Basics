void
JXMenuBar::DeleteMenu
	(
	const JIndex index
	)
{
	JXMenu* theMenu = RemoveMenu(index);
	assert( theMenu->itsOwner == NULL );
	theMenu->itsMenuBar = NULL;
	delete theMenu;
}