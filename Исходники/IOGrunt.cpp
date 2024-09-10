//
// Setting the targets that this grunt will access.
//
BOOL Grunt::Set_Targets( int count, Target_Spec *target_specs )
{
	// Remove previous completion queue if it was created by the Grunt.
	if ( !IsType( type, GenericVIType ) && io_cq )
	{
		delete io_cq;
	}
	io_cq = NULL;

	// If no targets are being set, simply clear the target list.
	if ( !count )
	{
		cout << "   clearing target list." << endl;
		return Size_Target_Array( 0 );
	}

	// Allocate enough targets
	if ( !Size_Target_Array( count, target_specs ) )
		return FALSE;

	worker_performance.target_results.count = count;

	// Create appropriate completion queue object based on targets.
	// If the Grunt will manage VI targets, the targets will provide a
	// pointer to the completion queue to use.
#if defined(IOMTR_SETTING_VI_SUPPORT)
	if ( IsType( type, GenericVIType ) )
	{
		// VI targets must know where the data buffer is and its size before
		// being initialized.
		((TargetVI*)targets[0])->data_buffer = (char*) read_data;
		((TargetVI*)targets[0])->data_buffer_size = access_spec.max_transfer;
		io_cq = &((TargetVI*)targets[0])->vi.vi_cq;
	}
	else
#endif // IOMTR_SETTING_VI_SUPPORT
	{
		// Create completion queue and verify its creation.
		if ( !(io_cq = new CQAIO) )
		{
			cout << "*** Unable to create completion queue while setting "
				<< "targets." << endl;
			return FALSE;
		}
	}

	// Initialize the specific targets.
	for ( int i = 0; i < count; i++ )
	{
		if ( !targets[i]->Initialize( &target_specs[i], io_cq ) )
			return FALSE;
	}

	// Seed the random number generator.  Grunts transferring data over a
	// network will use the same seed to produce the same sequence of random
	// numbers.  This will keep them in synch.
	Srand( target_specs[0].random );

	return Resize_Transaction_Arrays();
}