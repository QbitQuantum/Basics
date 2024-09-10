void LLDragDropWin32::reset()
{
	if ( mDropTarget )
	{
		RevokeDragDrop( mDropWindowHandle );
		CoLockObjectExternal( mDropTarget, FALSE, TRUE );
		mDropTarget->Release();  
	};
	
	OleUninitialize();
}