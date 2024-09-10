//
// Removes the item at item_index from the assigned list.
//
void CPageAccess::Remove()
{
	Manager *manager;
	Worker *worker;
	int new_selection;
	int selected_type;
	int item_index, old_item_index;

	// Check to make sure something was selected.
	if ( m_LAssignedAccess.GetSelectedCount() == 0 )
		return;

	// Store the first selected index as the index to be selected after removal.
	new_selection = m_LAssignedAccess.GetNextItem( FIND_FIRST, LVNI_SELECTED );

	// Store the manager/worker selection type since it is used inside the while loop.
	selected_type = theApp.pView->m_pWorkerView->GetSelectedType();

	// Find out who is selected: All managers, a manager, or a worker.
	manager = theApp.pView->m_pWorkerView->GetSelectedManager();
	worker = theApp.pView->m_pWorkerView->GetSelectedWorker();

	LockWindowUpdate();

	// Items must be removed in reverse order (bottom --> up).
	// This isn't the case for the global access spec list.
	// See the comment within the removal loop below.

	// See if the last item in the list is selected.
	if ( m_LAssignedAccess.GetItemState(
						m_LAssignedAccess.GetItemCount() - 1, LVNI_SELECTED) )
	{
		// It is.
		item_index = m_LAssignedAccess.GetItemCount() - 1;
	}
	else
	{
		// It isn't.  Find the next highest selected item.
		item_index = m_LAssignedAccess.GetNextItem(
						m_LAssignedAccess.GetItemCount() - 1,
						LVNI_ABOVE | LVNI_SELECTED );
	}

	// Loop through all the selected list items and remove them.
	while ( item_index != NOTHING )
	{
		// Remove the entry from the selected assigned (all managers,
		// manager, or worker).  There is no point in updating the
		// GUI since we will just refresh the contents when we are done
		// deleting.
		switch ( selected_type )
		{
		// Nothing is actually removed from the GUI until the call to
		// ShowAssignedAccess(), below.  This is why we have to remove
		// the list items from the bottom up.
		case ALL_MANAGERS:
			theApp.manager_list.RemoveAccessSpecAt( item_index );
			break;
		case MANAGER:
			manager->RemoveAccessSpecAt( item_index );
			break;
		case WORKER:
			worker->RemoveAccessSpecAt( item_index );
			break;
		}

		// Keep track of the last item we removed.
		old_item_index = item_index;
		// Find the next selected item above it.
		item_index = m_LAssignedAccess.GetNextItem( old_item_index, LVNI_ABOVE | LVNI_SELECTED );
		// If the values are the same, we're at the top of the list.
		// (The CListCtrl should return -1, but doesn't.)
		if (item_index == old_item_index)
			break;
	}

	ShowAssignedAccess();

	// See if the selected item is beyond the end of the list now.
	if ( new_selection >= m_LAssignedAccess.GetItemCount() )
		new_selection = m_LAssignedAccess.GetItemCount() - 1;

	m_LAssignedAccess.SetItemState( new_selection, LVNI_SELECTED, LVNI_SELECTED );

	UnlockWindowUpdate();
}