void
imb_XYZ2Lab_tables( void )
{
	static int built_tables = 0;

	int was_built;
	int i;

	g_mutex_lock( im__global_lock );
	was_built = built_tables;
	built_tables = 1;
	g_mutex_unlock( im__global_lock );
	if( was_built )
		return;

	for( i = 0; i < QUANT_ELEMENTS; i++ ) {
		float Y = (double) i / QUANT_ELEMENTS;

		if( Y < 0.008856 ) 
			cbrt_table[i] = 7.787 * Y + (16.0 / 116.0);
		else 
			cbrt_table[i] = cbrt( Y );
	}
}