ulong MEMGetSizeHnd( scMemHandle obj )
{
	if ( obj == 0 )
		return 0;
	
	return _msize( (void*)obj ) - sizeof( MacHandle );
}