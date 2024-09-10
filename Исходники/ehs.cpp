EHS::EHS ( EHS * ipoParent, ///< parent EHS object for routing purposes
		   std::string isRegisteredAs ///< path string for routing purposes
	) :
	poParent ( NULL ),
	poEHSServer ( NULL ),
	m_poSourceEHS ( NULL )
{

	if ( ipoParent != NULL ) {
		SetParent ( ipoParent, isRegisteredAs );
	}

#ifdef EHS_MEMORY
	fprintf ( stderr, "[EHS_MEMORY] Allocated: EHS\n" );
#endif		

}