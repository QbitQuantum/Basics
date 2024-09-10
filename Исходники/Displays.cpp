Gaffer::CompoundPlug *Displays::addDisplay( const std::string &label, const IECore::Display *display )
{
	CompoundPlugPtr displayPlug = new CompoundPlug( "display1" );
	displayPlug->setFlags( Plug::Dynamic, true );
	
	StringPlugPtr labelPlug = new StringPlug( "label" );
	labelPlug->setValue( label );
	labelPlug->setFlags( Plug::Dynamic, true );
	displayPlug->addChild( labelPlug );
	
	BoolPlugPtr activePlug = new BoolPlug( "active", Plug::In, true );
	activePlug->setFlags( Plug::Dynamic, true );
	displayPlug->addChild( activePlug );
	
	StringPlugPtr namePlug = new StringPlug( "name" );
	namePlug->setValue( display->getName() );
	namePlug->setFlags( Plug::Dynamic, true );
	displayPlug->addChild( namePlug );

	StringPlugPtr typePlug = new StringPlug( "type" );
	typePlug->setValue( display->getType() );
	typePlug->setFlags( Plug::Dynamic, true );
	displayPlug->addChild( typePlug );
	
	StringPlugPtr dataPlug = new StringPlug( "data" );
	dataPlug->setValue( display->getData() );
	dataPlug->setFlags( Plug::Dynamic, true );
	displayPlug->addChild( dataPlug );
	
	CompoundDataPlugPtr parametersPlug = new CompoundDataPlug( "parameters" );
	parametersPlug->setFlags( Plug::Dynamic, true );
	parametersPlug->addMembers( const_cast<Display *>( display )->parametersData() );
	displayPlug->addChild( parametersPlug );
	
	displaysPlug()->addChild( displayPlug );
	
	return displayPlug;
}