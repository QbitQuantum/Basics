void media_track_info::fix_sample_table( trak & track )
{
	if( _heapchk() != _HEAPOK )
	{
		cout << "heap corrupted." << endl;
		assert( false );
	}

	// fix stts, decoding time to sample
	fix_stts(track);

	// fix ctts, composition time to sample box
	fix_ctts(track);

	// fix stsc, sample to chunk
	fix_stsc(track);

	// fix stss, sync sample box
	fix_stss(track);

	fix_stsz(track);

	//// FIX STSC, STCO
	//throw std::exception( "to fix stsz, stco" );


	if( _heapchk() != _HEAPOK )
	{
		cout << "heap corrupted." << endl;
		assert( false );
	}
}