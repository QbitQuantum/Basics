// ---------------------------------------------------------
// CNSmlCmdsBase::TrimRightSpaceAndNull
// Trims right spaces and zero terminator (NULL) 
// ---------------------------------------------------------
EXPORT_C void CNSmlCmdsBase::TrimRightSpaceAndNull( TDes8& aDes ) const
	{
	aDes.TrimRight();
	if ( aDes.Length() > 0 )
		{
		if ( aDes[aDes.Length() - 1] == NULL )
			{
			aDes.SetLength( aDes.Length() - 1 );
			}	
		}
	}