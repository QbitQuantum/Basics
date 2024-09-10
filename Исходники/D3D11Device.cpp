    KT_API D3D11Device::D3D11Device(
		kT::GraphicsDevice<kTD3D11DeviceTemplateListLineTypes>::ProcessingMethod processingMethod,
		bool debugFlag ):
     myDevice( 0 ),
     myProcessingMethod( processingMethod ),
     myImmediateContext( 0 )
    {
        D3D_DRIVER_TYPE driverTypes[] = {
            D3D_DRIVER_TYPE_HARDWARE,
            D3D_DRIVER_TYPE_WARP,
            D3D_DRIVER_TYPE_REFERENCE
        };

		UINT flags = debugFlag ? D3D11_CREATE_DEVICE_DEBUG : 0;
		ID3D11DeviceContext* imDev = 0;

		HRESULT hr = 0;
		for( size_t i = 0; i < 3; i++ )
		{
			D3D_FEATURE_LEVEL lvl;

			hr = D3D11CreateDevice( NULL, driverTypes[i], NULL, flags, NULL, 0, D3D11_SDK_VERSION, &myDevice, &lvl, &imDev );
			if( !FAILED(hr) )
				break;

			myFeatureLevel = lvl;
		}

        if( FAILED(hr) )
            kTLaunchException( kT::Exception, "Error while trying to create the D3D11 device" );

		myImmediateContext = new D3D11ImmediateContext( imDev );
    }