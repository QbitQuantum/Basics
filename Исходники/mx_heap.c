MX_EXPORT int
mx_heap_check( unsigned long heap_flags )
{
	static const char fname[] = "mx_heap_check()";

	DWORD number_of_heaps;
	DWORD maximum_number_of_heaps;
	HANDLE heap_handle_array[100];
	HANDLE heap_handle;
	BOOL validate_status;
	int heap_ok;
	unsigned long i;

	/* This implementation does not call GetProcessHeaps() in a loop
	 * to resize heap_handle_array to the right size, since this will
	 * result in an infinite loop if mx_heap_check() is called from
	 * within any of the mx_win32_... allocation functions.  So we
	 * use a fixed array instead which is probably large enough.
	 */

	static const char getprocessheaps_error[] =
		"ERROR: A call to GetProcessHeaps() failed.\n";

	static const char toomanyheaps_error[] = 
		"ERROR: Too many heaps reported by GetProcessHeaps().  "
		"Increase the size of heap_handle_array and recompile MX "
		"to fix this.\n";

	maximum_number_of_heaps = sizeof( heap_handle_array )
					/ sizeof( heap_handle_array[0] );

	number_of_heaps = GetProcessHeaps( maximum_number_of_heaps,
						heap_handle_array );

	if ( number_of_heaps == 0 ) {
		write(2, getprocessheaps_error, sizeof(getprocessheaps_error));
	}

	if ( number_of_heaps > maximum_number_of_heaps ) {
		write(2, toomanyheaps_error, sizeof(toomanyheaps_error));
		return FALSE;
	}

	heap_ok = TRUE;

	for ( i = 0; i < number_of_heaps; i++ ) {

		heap_handle = heap_handle_array[i];

		validate_status = HeapValidate( heap_handle, 0, 0 );

		if ( validate_status == 0 ) {
			if ( heap_flags & MXF_HEAP_CHECK_CORRUPTED_VERBOSE ) {
#if defined(_WIN64)
			    mx_warning( "%s: Heap %lu (%#I64x) is CORRUPTED.",
					fname, i, (uint64_t) heap_handle );
#else
			    mx_warning( "%s: Heap %lu (%#lx) is CORRUPTED.",
					fname, i, (unsigned long) heap_handle );
#endif
			}

			heap_ok = FALSE;
		} else {
			if ( heap_flags & MXF_HEAP_CHECK_OK_VERBOSE ) {
#if defined(_WIN64)
			    mx_info( "%s: Heap %lu (%#I64x) is OK.",
					fname, i, (uint64_t) heap_handle );
#else
			    mx_info( "%s: Heap %lu (%#lx) is OK.",
					fname, i, (unsigned long) heap_handle );
#endif
			}
		}
	}

	if ( heap_ok ) {
		if ( heap_flags & MXF_HEAP_CHECK_OK ) {
			mx_info( "%s: Heap is OK", fname );
		}
	} else {
		if ( heap_flags & MXF_HEAP_CHECK_CORRUPTED ) {
			mx_warning("%s: Heap is corrupted.", fname);
		}
	}

	if ( heap_flags & MXF_HEAP_CHECK_STACK_TRACEBACK ) {
		mx_stack_traceback();
	}

	return heap_ok;
}