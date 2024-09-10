inline static void _win32_freeMem( void *ptr )
{
    if ( ptr )
    {
        MEM_INTERRUPT( HeapValidate( g_privateHeap, 0, ptr ) );
        HeapFree( g_privateHeap, 0, ptr );
    }
}