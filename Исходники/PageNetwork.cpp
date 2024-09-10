//
// Process mouse click in the target list.  For a worker, assign the selected
// target.  For a manager, distribute the assigned targets among its net servers.
//
void CPageNetwork::OnClickTTargets(NMHDR* pNMHDR, LRESULT* pResult) 
{
	CPoint point;
	TV_HITTESTINFO test_info;
	TargetSelType state;

	// Get the cursor position.
	GetCursorPos( &point );
	test_info.pt = point;
	m_TTargets.ScreenToClient( &(test_info.pt) );

	// Check to see whether the cursor is on an item.
	m_TTargets.HitTest( &test_info );

	// Check that we have an interface item.
	if ( !test_info.hItem || !m_TTargets.GetParentItem( test_info.hItem ) )
		return;

	// A new target assignment is being made.  Clear the results since they are
	// for a configuration we no longer have.
	theApp.pView->ResetDisplayforNewTest();

	// Toggle the selection if the control key is pressed.
	if ( GetKeyState( VK_CONTROL ) & 0x8000 && 
		GetSelectionCheck( test_info.hItem ) == TargetChecked )
	{
		state = TargetUnChecked;
	}
	else
	{
		state = TargetChecked;
	}

	switch ( theApp.pView->m_pWorkerView->GetSelectedType() )
	{
	case WORKER:
		// All clicks work the same for the worker.
		SelectRange( test_info.hItem, test_info.hItem, TRUE, state );
		break;
	case MANAGER:
		// A shift click extends the selection from the last selected item
		// to the currently focused item.  When the control key is also
		// pressed, any previous selection is not cleared.
		if ( (GetKeyState( VK_SHIFT ) & 0x8000 ) && selected )
		{
			// We have a previous item (not the first click) and the shift
			// key is down.
			SelectRange( selected, test_info.hItem, 
				!(GetKeyState( VK_CONTROL ) & 0x8000) );
		}
		else if ( GetKeyState( VK_CONTROL ) & 0x8000 )
		{
			// The control key is down.
			SelectRange( test_info.hItem, test_info.hItem, FALSE, state );
		}
		else 
		{
			SelectRange( test_info.hItem, test_info.hItem, TRUE, state );
		}
		break;
	default:
		ErrorMessage( "Unexpected selection type in CPageNetwork::"
			"OnClickTTargets()." );
		return;
	}

	// immediately refresh the display (create/delete NetClients as needed)
	StoreTargetSelection();
	ShowSettings();
	EnableWindow();

	*pResult = 0;
}