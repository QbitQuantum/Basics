void COXNetBrowseTree::PostNcDestroy() 
{
	// Unitialize the control
	Uninitialize();

	CTreeCtrl::PostNcDestroy();
}