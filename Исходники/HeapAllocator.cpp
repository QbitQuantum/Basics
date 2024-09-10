void _createHeap_wxObject()
{
	if( win32_object_heap == INVALID_HANDLE_VALUE )
	{
		//wxASSERT( win32_object_heap_refcount == 0 );
		win32_object_heap = HeapCreate( 0, 0x200000, 0 );
	}
}