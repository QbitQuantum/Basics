//
// Setting access specifications for next test.
// Note that Iometer will call Set_Access before testing starts to ensure that
// Dynamo can run the spec with the largest transfer request.
//
BOOL Manager::Set_Access( int target, const Test_Spec *spec )
{
	int		g;			// loop control variable

	// Recursively assign all workers the same access specification.
	if ( target == ALL_WORKERS )
	{
		cout << "All workers running Access Spec: " << spec->name << endl;
		for ( g = 0; g < grunt_count; g++ )
		{
			if ( !Set_Access( g, spec ) )
				return FALSE;
		}
		return TRUE;
	}

	cout << "Worker " << target << " running Access Spec: " << spec->name << endl;

	// If the grunt could not set the access spec properly, return.
	// The grunt may not have been able to grow its data buffer.
	if ( !grunts[target]->Set_Access( spec ) )
		return FALSE;

	// If the grunt is not using the manager's data buffer or the manager's
	// buffer is already large enough, just return.
	if ( grunts[target]->data_size ||
		data_size >= grunts[target]->access_spec.max_transfer )
	{
		return TRUE;
	}

	// Grow the manager's data buffer and update all grunts using it.
	#if _DEBUG
		cout << "Growing manager data buffer from " << data_size << " to " 
			 << grunts[target]->access_spec.max_transfer << endl << flush;
	#endif

	// Align all data transfers on a page boundary.  This will work for all disks
	// with sector sizes that divide evenly into the page size - which is always
	// the case.
#if defined (_WIN32) || defined (_WIN64)
	VirtualFree( data, 0, MEM_RELEASE );
	if ( !(data = VirtualAlloc( NULL, grunts[target]->access_spec.max_transfer, 
		MEM_COMMIT, PAGE_READWRITE )) )
#else // UNIX
	free(data);
	errno = 0;
	if ( !(data = valloc(grunts[target]->access_spec.max_transfer) ))
#endif
	{
		// Could not allocate a larger buffer.  Signal failure.
		cout << "*** Manager could not allocate data buffer for I/O transfers." 
			<< endl << flush;
		data_size = 0;
		return FALSE;
	}
	data_size = grunts[target]->access_spec.max_transfer;

	// Update all grunts using the manager's data buffer.
	for ( g = 0; g < grunt_count; g++ )
	{
		if ( !grunts[g]->data_size )
			grunts[g]->data = data;
	}
	return TRUE;
}