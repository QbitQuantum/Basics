	void Factory::Init( FactoryType factoryType, DebugLevel debugLevel )
	{
		ID2D1Factory *factory = NULL;

		D2D1_FACTORY_OPTIONS options;
		options.debugLevel = static_cast<D2D1_DEBUG_LEVEL>( debugLevel );

		if( RECORD_D2D( D2D1CreateFactory( static_cast<D2D1_FACTORY_TYPE>( factoryType ), IID_ID2D1Factory, &options, (void**) &factory ) ).IsFailure )
			throw gcnew Direct2DException( Result::Last );

		Construct( factory );
	}