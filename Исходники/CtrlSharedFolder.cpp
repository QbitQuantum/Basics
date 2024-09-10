void CLibraryFolderCtrl::NotifySelectionChanged()
{
	GetParent()->PostMessage( WM_TIMER, 2 );
}