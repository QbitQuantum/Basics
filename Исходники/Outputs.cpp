Gaffer::CompoundPlug *Outputs::addOutput( const std::string &name, const IECore::Display *output )
{
	CompoundPlugPtr outputPlug = new CompoundPlug( "output1" );
	outputPlug->setFlags( Plug::Dynamic, true );

	StringPlugPtr namePlug = new StringPlug( "name" );
	namePlug->setValue( name );
	namePlug->setFlags( Plug::Dynamic, true );
	outputPlug->addChild( namePlug );

	BoolPlugPtr activePlug = new BoolPlug( "active", Plug::In, true );
	activePlug->setFlags( Plug::Dynamic, true );
	outputPlug->addChild( activePlug );

	StringPlugPtr fileNamePlug = new StringPlug( "fileName" );
	fileNamePlug->setValue( output->getName() );
	fileNamePlug->setFlags( Plug::Dynamic, true );
	outputPlug->addChild( fileNamePlug );

	StringPlugPtr typePlug = new StringPlug( "type" );
	typePlug->setValue( output->getType() );
	typePlug->setFlags( Plug::Dynamic, true );
	outputPlug->addChild( typePlug );

	StringPlugPtr dataPlug = new StringPlug( "data" );
	dataPlug->setValue( output->getData() );
	dataPlug->setFlags( Plug::Dynamic, true );
	outputPlug->addChild( dataPlug );

	CompoundDataPlugPtr parametersPlug = new CompoundDataPlug( "parameters" );
	parametersPlug->setFlags( Plug::Dynamic, true );
	parametersPlug->addMembers( const_cast<Display *>( output )->parametersData(), /* useNameAsPlugName = */ true );
	outputPlug->addChild( parametersPlug );

	outputsPlug()->addChild( outputPlug );

	return outputPlug.get();
}