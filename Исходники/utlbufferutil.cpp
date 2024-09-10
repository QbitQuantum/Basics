bool Unserialize( CUtlBuffer &buf, VMatrix &dest )
{
	if ( !buf.IsValid() )
		return false;

	if ( buf.IsText() )
	{
		int nRetVal = buf.Scanf( "%f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f",
			&dest[ 0 ][ 0 ], &dest[ 0 ][ 1 ], &dest[ 0 ][ 2 ], &dest[ 0 ][ 3 ],
			&dest[ 1 ][ 0 ], &dest[ 1 ][ 1 ], &dest[ 1 ][ 2 ], &dest[ 1 ][ 3 ],
			&dest[ 2 ][ 0 ], &dest[ 2 ][ 1 ], &dest[ 2 ][ 2 ], &dest[ 2 ][ 3 ],
			&dest[ 3 ][ 0 ], &dest[ 3 ][ 1 ], &dest[ 3 ][ 2 ], &dest[ 3 ][ 3 ] );
		return (nRetVal == 16);
	}

	buf.Get( &dest, sizeof(VMatrix) );
	return true;
}