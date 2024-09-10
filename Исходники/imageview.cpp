ImageView::ImageView( const std::string &name )
	:	View( name, new GafferImage::ImagePlug() ),
		m_imageGadget( new ImageGadget() ),
		m_framed( false )
{

	// build the preprocessor we use for applying colour
	// transforms, and the stats node we use for displaying stats.

	NodePtr preprocessor = new Node;
	ImagePlugPtr preprocessorInput = new ImagePlug( "in" );
	preprocessor->addChild( preprocessorInput );

	ClampPtr clampNode = new Clamp();
	preprocessor->setChild(  "__clamp", clampNode );
	clampNode->inPlug()->setInput( preprocessorInput );
	clampNode->enabledPlug()->setValue( false );
	clampNode->minClampToEnabledPlug()->setValue( true );
	clampNode->maxClampToEnabledPlug()->setValue( true );
	clampNode->minClampToPlug()->setValue( Color4f( 1.0f, 1.0f, 1.0f, 0.0f ) );
	clampNode->maxClampToPlug()->setValue( Color4f( 0.0f, 0.0f, 0.0f, 1.0f ) );

	BoolPlugPtr clippingPlug = new BoolPlug( "clipping" );
	clippingPlug->setFlags( Plug::AcceptsInputs, false );
	addChild( clippingPlug );

	GradePtr gradeNode = new Grade;
	preprocessor->setChild( "__grade", gradeNode );
	gradeNode->inPlug()->setInput( clampNode->outPlug() );

	FloatPlugPtr exposurePlug = new FloatPlug( "exposure" );
	exposurePlug->setFlags( Plug::AcceptsInputs, false );
	addChild( exposurePlug ); // dealt with in plugSet()

	PlugPtr gammaPlug = gradeNode->gammaPlug()->getChild( 0 )->createCounterpart( "gamma", Plug::In );
	gammaPlug->setFlags( Plug::AcceptsInputs, false );
	addChild( gammaPlug );

	addChild( new StringPlug( "displayTransform", Plug::In, "Default", Plug::Default & ~Plug::AcceptsInputs ) );

	ImagePlugPtr preprocessorOutput = new ImagePlug( "out", Plug::Out );
	preprocessor->addChild( preprocessorOutput );
	preprocessorOutput->setInput( gradeNode->outPlug() );

	// tell the base class about all the preprocessing we want to do

	setPreprocessor( preprocessor );

	// connect up to some signals

	plugSetSignal().connect( boost::bind( &ImageView::plugSet, this, ::_1 ) );
	viewportGadget()->keyPressSignal().connect( boost::bind( &ImageView::keyPress, this, ::_2 ) );
	viewportGadget()->preRenderSignal().connect( boost::bind( &ImageView::preRender, this ) );

	// get our display transform right

	insertDisplayTransform();

	// Now we can connect up our ImageGadget, which will do the
	// hard work of actually displaying the image.

	m_imageGadget->setImage( preprocessedInPlug<ImagePlug>() );
	m_imageGadget->setContext( getContext() );
	viewportGadget()->setPrimaryChild( m_imageGadget );

	m_colorInspector = shared_ptr<ColorInspector>( new ColorInspector( this ) );
}