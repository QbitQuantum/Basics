//-------------------------------------------------------------------//
// BeginDrag()
//-------------------------------------------------------------------//
// This function attempts a drag when the left button has been
// pressed on an item.  It returns true if a drag was made.
//-------------------------------------------------------------------//
BOOL OleListCtrl::BeginDrag(
	int	nUnderCursor,
	UINT	nKeyFlags
) {
	// Attempt a drag.

	/////////////////////////////////////////////////////
	// Next, we provide a ClipFormat holding the item reference.

	// Make sure ClipFormat is ready to go.
	ASSERT( ClipFormat != NULL );

	// Dump the current selection into drag data array.
	ExtractItemsToDragData( 
		true,
		nUnderCursor
	);

	// To drag, we need a COleDataSource that is loaded with our data.
	// Get a new one.
	COleDataSource DataSource;

	// Put the drag data into the DS.
	ArchiveAndRenderClipFormats( &DataSource );
	
	// Now we can clear the previous drag contents.
	Items.RemoveAll();

	//	
	/////////////////////////////////////////////////////

	// Get the rectangle of the list item.
	// This will help us avoid a drag unless the user really means it.
	CRect ItemRect;
	GetItemRect( nUnderCursor, &ItemRect, LVIR_BOUNDS );
	ClientToScreen( &ItemRect );
		
	// Set flags to indicate that we are dragging.
	nListItemBeingDragged = nUnderCursor;
	bDraggingFromThisList = true;

	// Now drag it.
	DROPEFFECT deResult = DataSource.DoDragDrop(
		DROPEFFECT_COPY | DROPEFFECT_MOVE,	// | DROPEFFECT_LINK,
		ItemRect
	);

	InsertStart();

	// Indicate that we are no longer dragging.
	bDraggingFromThisList = false;
	nListItemBeingDragged = -1;

	// If it was a move, remove the item(s).
	if ( deResult == DROPEFFECT_MOVE )
	{
		// Delete the current selection, then
		// highlight the dragged items.
		DeleteOldAndHighlightNew();
	}

	// Successful drag and drop operation.
	if ( deResult != DROPEFFECT_NONE )
	{
		// Allow derived classes to do any additional clean up steps.
		FinishDragAndDrop();
	}

	InsertEnd();

	return ( deResult != DROPEFFECT_NONE );

}