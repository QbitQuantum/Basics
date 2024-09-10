bool RAUX::MTLFile :: ProcessTransmissionFilter ( const std :: string & Line, uint32_t Index )
{
	
	if ( Materials.size () == 0 )
		return false;
	
	Vec3 Coefficients ( MTLFILE_VEC3_NOINIT );
	bool IsCIEXYZ = false;
	
	uint32_t StringIndex;
	
	Index ++;
	
	while ( ( Index < Line.size () ) && ( Line.at ( Index ) == ' ' ) )
		Index ++;
	
	if ( Index >= Line.size () )
		return false;
	
	StringIndex = Index;
	
	while ( ( Index < Line.size () ) && ( Line.at ( Index ) != ' ' ) )
		Index ++;
	
	if ( Index >= Line.size () )
		return false;
	
	std :: string FloatString = Line.substr ( StringIndex, Index - StringIndex );
	
	if ( FloatString == "xyz" )
	{
		
		IsCIEXYZ = true;
		
		Index ++;
		
		while ( ( Index < Line.size () ) && ( Line.at ( Index ) == ' ' ) )
			Index ++;
		
		if ( Index >= Line.size () )
			return false;
		
		StringIndex = Index;
		
		while ( ( Index < Line.size () ) && ( Line.at ( Index ) != ' ' ) )
			Index ++;
		
		if ( Index >= Line.size () )
			return false;
		
		FloatString = Line.substr ( StringIndex, Index - StringIndex );
		
	}
	
	Coefficients.X = strtof ( FloatString.c_str (), NULL );
	
	while ( ( Index < Line.size () ) && ( Line.at ( Index ) == ' ' ) )
		Index ++;
	
	if ( Index >= Line.size () )
		return false;
	
	StringIndex = Index;
	
	while ( ( Index < Line.size () ) && ( Line.at ( Index ) != ' ' ) )
		Index ++;
	
	if ( Index >= Line.size () )
		return false;
	
	FloatString = Line.substr ( StringIndex, Index - StringIndex );
	Coefficients.Y = strtof ( FloatString.c_str (), NULL );
	
	while ( ( Index < Line.size () ) && ( Line.at ( Index ) == ' ' ) )
		Index ++;
	
	if ( Index >= Line.size () )
		return false;
	
	StringIndex = Index;
	
	while ( ( Index < Line.size () ) && ( Line.at ( Index ) != ' ' ) )
		Index ++;
	
	FloatString = Line.substr ( StringIndex, Index - StringIndex );
	Coefficients.Z = strtof ( FloatString.c_str (), NULL );
	
	Materials [ Materials.size () - 1 ].TransmissionFilter = Coefficients;
	Materials [ Materials.size () - 1 ].TransmissionIsCIEXYZ = IsCIEXYZ;
	
	return true;
	
}