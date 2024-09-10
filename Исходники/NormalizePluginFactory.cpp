/**
 * @brief Function called to describe the plugin controls and features.
 * @param[in, out]   desc       Effect descriptor
 * @param[in]        context    Application context
 */
void NormalizePluginFactory::describeInContext( OFX::ImageEffectDescriptor& desc,
                                                  OFX::EContext context )
{
	OFX::ClipDescriptor* srcClip = desc.defineClip( kOfxImageEffectSimpleSourceClipName );
	srcClip->addSupportedComponent( OFX::ePixelComponentRGBA );
	srcClip->addSupportedComponent( OFX::ePixelComponentRGB );
	srcClip->addSupportedComponent( OFX::ePixelComponentAlpha );
	srcClip->setSupportsTiles( kSupportTiles );

	// Create the mandated output clip
	OFX::ClipDescriptor* dstClip = desc.defineClip( kOfxImageEffectOutputClipName );
	dstClip->addSupportedComponent( OFX::ePixelComponentRGBA );
	dstClip->addSupportedComponent( OFX::ePixelComponentRGB );
	dstClip->addSupportedComponent( OFX::ePixelComponentAlpha );
	dstClip->setSupportsTiles( kSupportTiles );

	OFX::ChoiceParamDescriptor* mode = desc.defineChoiceParam( kParamMode );
	mode->setLabel( "Input" );
	mode->appendOption( kParamModeAnalyse );
	mode->appendOption( kParamModeCustom );

	OFX::ChoiceParamDescriptor* analyse = desc.defineChoiceParam( kParamAnalyseMode );
	analyse->setLabel( "Analyse" );
	analyse->appendOption( kParamAnalysePerChannel );
	analyse->appendOption( kParamAnalyseLuminosity );
	analyse->appendOption( kParamAnalyseR );
	analyse->appendOption( kParamAnalyseG );
	analyse->appendOption( kParamAnalyseB );
	analyse->appendOption( kParamAnalyseA );

	OFX::PushButtonParamDescriptor* analyseNow = desc.definePushButtonParam( kParamAnalyseNow );
	analyseNow->setLabel( "Analyse" );

	OFX::GroupParamDescriptor* srcGroup = desc.defineGroupParam( kParamSrcGroup );
	srcGroup->setLabel( "Source" );

	OFX::RGBAParamDescriptor* srcMinColor = desc.defineRGBAParam( kParamSrcCustomColorMin );
	srcMinColor->setLabel( "Min" );
	srcMinColor->setDefault( 0.0, 0.0, 0.0, 0.0 );
	srcMinColor->setParent( srcGroup );

	OFX::RGBAParamDescriptor* srcMaxColor = desc.defineRGBAParam( kParamSrcCustomColorMax );
	srcMaxColor->setLabel( "Max" );
	srcMaxColor->setDefault( 1.0, 1.0, 1.0, 1.0 );
	srcMaxColor->setParent( srcGroup );

	OFX::GroupParamDescriptor* dstGroup = desc.defineGroupParam( kParamDstGroup );
	dstGroup->setLabel( "Destination" );

	OFX::RGBAParamDescriptor* dstMinColor = desc.defineRGBAParam( kParamDstCustomColorMin );
	dstMinColor->setLabel( "Min" );
	dstMinColor->setDefault( 0.0, 0.0, 0.0, 0.0 );
	dstMinColor->setParent( dstGroup );

	OFX::RGBAParamDescriptor* dstMaxColor = desc.defineRGBAParam( kParamDstCustomColorMax );
	dstMaxColor->setLabel( "Max" );
	dstMaxColor->setDefault( 1.0, 1.0, 1.0, 1.0 );
	dstMaxColor->setParent( dstGroup );

	OFX::GroupParamDescriptor* processGroup = desc.defineGroupParam( kParamProcessGroup );
	processGroup->setLabel( "Process" );

	OFX::BooleanParamDescriptor* processR = desc.defineBooleanParam( kParamProcessR );
	processR->setLabel( "R" );
	processR->setDefault( true );
	processR->setParent( processGroup );

	OFX::BooleanParamDescriptor* processG = desc.defineBooleanParam( kParamProcessG );
	processG->setLabel( "G" );
	processG->setDefault( true );
	processG->setParent( processGroup );

	OFX::BooleanParamDescriptor* processB = desc.defineBooleanParam( kParamProcessB );
	processB->setLabel( "B" );
	processB->setDefault( true );
	processB->setParent( processGroup );

	OFX::BooleanParamDescriptor* processA = desc.defineBooleanParam( kParamProcessA );
	processA->setLabel( "A" );
	processA->setDefault( true );
	processA->setParent( processGroup );
}