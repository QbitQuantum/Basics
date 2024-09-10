ImageTargetFileWic::ImageTargetFileWic( DataTargetRef dataTarget, ImageSourceRef imageSource, ImageTarget::Options options, const string &extensionData )
	: ImageTarget(), mDataTarget( dataTarget )
{
	mCodecGUID = getExtensionMap()[extensionData];

	setSize( imageSource->getWidth(), imageSource->getHeight() );

	// determine the pixel format we'll request
	WICPixelFormatGUID formatGUID;
	if( imageSource->hasAlpha() ) {
		bool premultAlpha = imageSource->isPremultiplied();
		// WIC doesn't support gray+alpha, so we need to do RGBA regardless
		if( imageSource->getDataType() == ImageIo::UINT8 )
			formatGUID = premultAlpha ? GUID_WICPixelFormat32bppPBGRA : GUID_WICPixelFormat32bppBGRA;
		else if( imageSource->getDataType() == ImageIo::UINT16 )
			formatGUID = premultAlpha ? GUID_WICPixelFormat64bppPRGBA : GUID_WICPixelFormat64bppRGBA;
		else
			formatGUID = premultAlpha ? GUID_WICPixelFormat128bppPRGBAFloat : GUID_WICPixelFormat128bppRGBAFloat;
	}
	else {
		ImageIo::ColorModel cm = options.isColorModelDefault() ? imageSource->getColorModel() : options.getColorModel();
		if( cm == ImageIo::CM_GRAY ) {
			if( imageSource->getDataType() == ImageIo::UINT8 )
				formatGUID = GUID_WICPixelFormat8bppGray;
			else if( imageSource->getDataType() == ImageIo::UINT16 )
				formatGUID = GUID_WICPixelFormat16bppGray;
			else
				formatGUID = GUID_WICPixelFormat32bppGrayFloat;
		}
		else { // RGB
			if( imageSource->getDataType() == ImageIo::UINT8 )
				formatGUID = GUID_WICPixelFormat24bppBGR;
			else if( imageSource->getDataType() == ImageIo::UINT16 )
				formatGUID = GUID_WICPixelFormat48bppRGB;
			else
				formatGUID = GUID_WICPixelFormat128bppRGBFloat;
		}
	}
	
	::HRESULT hr = S_OK;

	msw::initializeCom();

 // Create WIC factory
    IWICImagingFactory *IWICFactoryP = NULL;
    hr = ::CoCreateInstance( CLSID_WICImagingFactory, NULL, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&IWICFactoryP) );
	if( ! SUCCEEDED( hr ) )
		throw ImageIoExceptionFailedWrite( "Could not create WIC Factory." );
	shared_ptr<IWICImagingFactory> IWICFactory = msw::makeComShared( IWICFactoryP );

	IWICBitmapEncoder *encoderP = NULL;
	hr = IWICFactory->CreateEncoder( *mCodecGUID, 0, &encoderP );
	if( ! SUCCEEDED( hr ) )
		throw ImageIoExceptionFailedWrite( "Could not create WIC Encoder." );
	mEncoder = msw::makeComShared( encoderP );
	
	// create the stream		
	IWICStream *pIWICStream = NULL;
	hr = IWICFactory->CreateStream( &pIWICStream );
	if( ! SUCCEEDED(hr) )
		throw ImageIoExceptionFailedWrite( "Could not create WIC stream." );
	shared_ptr<IWICStream> stream = msw::makeComShared( pIWICStream );
	
	// initialize the stream based on properties of the cinder::DataSouce
	if( mDataTarget->providesFilePath() ) {
#if defined( CINDER_WINRT)
		std::string s = mDataTarget->getFilePath().string();
		std::wstring filePath =	std::wstring(s.begin(), s.end());                 
#else
		std::wstring filePath =	mDataTarget->getFilePath().wstring().c_str();
#endif
		hr = stream->InitializeFromFilename( filePath.c_str(), GENERIC_WRITE );
		if( ! SUCCEEDED(hr) )
			throw ImageIoExceptionFailedWrite( "Could not initialize WIC Stream from filename." );
	}
	else {
		shared_ptr<msw::ComOStream> comOStream = msw::makeComShared( new msw::ComOStream( mDataTarget->getStream() ) );
		hr = stream->InitializeFromIStream( comOStream.get() );
		if( ! SUCCEEDED(hr) )
			throw ImageIoExceptionFailedWrite( "Could not initialize WIC Stream from IStream." );
	}
	
	hr = mEncoder->Initialize( stream.get(), WICBitmapEncoderNoCache );
	if( ! SUCCEEDED( hr ) )
		throw ImageIoExceptionFailedWrite( "Could not initialize WIC Encoder." );

	// create the frame encoder
	IPropertyBag2 *pPropertybag = NULL;
	IWICBitmapFrameEncode *pBitmapFrame = NULL;
	hr = mEncoder->CreateNewFrame( &pBitmapFrame, &pPropertybag );
	if( ! SUCCEEDED( hr ) )
		throw ImageIoExceptionFailedWrite( "Could not ceate WIC Frame." );
	mBitmapFrame = msw::makeComShared( pBitmapFrame );

	// setup the propertyBag to express quality
	PROPBAG2 option = { 0 };
    option.pstrName = L"ImageQuality";
    VARIANT varValue;    
    VariantInit(&varValue);
    varValue.vt = VT_R4;
    varValue.fltVal = options.getQuality();      
    hr = pPropertybag->Write( 1, &option, &varValue );

	hr = mBitmapFrame->Initialize( pPropertybag );
	if( ! SUCCEEDED( hr ) )
		throw ImageIoExceptionFailedWrite( "Could not initialize WIC PROPBAG2." );
	
	hr = mBitmapFrame->SetSize( mWidth, mHeight );
	if( ! SUCCEEDED( hr ) )
		throw ImageIoExceptionFailedWrite( "Could not set WIC Frame size." );
	
	// ask for our ideal pixel format and then process the one we actually get
	hr = mBitmapFrame->SetPixelFormat( &formatGUID );
	if( ! SUCCEEDED( hr ) )
		throw ImageIoExceptionFailedWrite( "Could not set WIC Frame pixel format." );
	
	setupPixelFormat( formatGUID );
	
	mData = shared_ptr<uint8_t>( new uint8_t[mHeight * mRowBytes], std::default_delete<uint8_t[]>() );
}