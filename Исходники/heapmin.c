int __cdecl _heapmin(void)
{
	if ( HeapCompact( _crtheap, 0 ) == 0 ) {

	    if ( GetLastError() == ERROR_CALL_NOT_IMPLEMENTED ) {
		_doserrno = ERROR_CALL_NOT_IMPLEMENTED;
		errno = ENOSYS;
	    }

	    return -1;
        }
	else {
	    return 0;
        }
}